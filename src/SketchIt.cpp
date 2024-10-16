/*
Sketch It - A learn to draw program
Copyright (C) 2024 Ryan Large

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "SketchIt.h"

#include <gtkmm.h>

#include <iostream>

#include "./layouts/Layouts.h"
#include "./layouts/newUser/newUser.h"
#include "./lib/config.h"
#include "./widgets/modals/ErrorModal.h"

namespace UI {
class Layout;
namespace NewUserSession {
class NewUser;
}  // namespace NewUserSession
};  // namespace UI

SketchIt::SketchIt() : Gtk::Window() {
  // Initialize main window with default values
  set_title("Sketch it");
  signal_realize().connect(
      sigc::mem_fun(*this, &SketchIt::setDefaultScreenSize));
  applyGlobalCSS();

  // Load up user config, check for existing sessions, user data, etc...
  // SketchIt -> config file -> app setup
  loadConfig();
}

void SketchIt::applyGlobalCSS() {
  // Load global css file into the appl
  css_provider = Gtk::CssProvider::create();
  try {
    css_provider->load_from_path("../src/styles/global.css");
  } catch (const Glib::Error& err) {
    std::cerr << "Error loading css files: " << err.what() << "\n";
  }
  auto display = Gdk::Display::get_default();
  Gtk::StyleContext::add_provider_for_display(
      display, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void SketchIt::loadConfig() {
  Config configManager("/sketch-it/config.json");

  // Check for errors in configuration file operations
  // parsing, reading, creating etc..
  if (configManager.errorState) {
    Config::EventLog error = configManager.getLogAt(0);

    // Create custom modal buttons
    std::vector<Gtk::Button*> modalBtns = {
        Gtk::make_managed<ModalBtn>(ModalBtn::ModalBtnProps("Okay",
            "icons/modal-check", "error-modal-btn", true, true,
            Gtk::Align::FILL, Gtk::Align::FILL, [ this ]() { this->close(); })),
        Gtk::make_managed<ModalBtn>(
            ModalBtn::ModalBtnProps("Reload App", "icons/modal-reload",
                "error-modal-btn", true, true, Gtk::Align::FILL,
                Gtk::Align::FILL, [ this ]() { this->close(); }))};

    ErrorModal newError("Configuration Error", error.message, modalBtns);

    newError.errorModal->signal_close_request().connect(
        [ this ]() { this->close(); });
    newError.errorModal->set_transient_for(*this);

    configManager.clearAllErrors();
    return;
  }
  Config::EventLog log = configManager.getLogAt(0);

  // On success read for config file, set up new user
  if (log.status == Config::StatusCodes::NEW_USER) {
    setUpNewUser();
  }

  // User config already contains user data: load
  // data and initialize new session
  setUpSession();
}

void SketchIt::setDefaultScreenSize() {
  auto display = Gdk::Display::get_default();

  // Window fallback size if queries to the
  // monitor or display fail
  if (!display) {
    set_default_size(1250, 900);
    return;
  }
  auto monitor = display->get_monitor_at_surface(get_surface());
  if (!monitor) {
    set_default_size(1250, 900);
    return;
  }

  // Set window width and height
  // properties to full size of monitor
  Gdk::Rectangle monitor_geometry;
  monitor->get_geometry(monitor_geometry);
  const size_t width = monitor_geometry.get_width();
  const size_t height = monitor_geometry.get_height();
  set_default_size(width, height);
}

void SketchIt::setUpNewUser() { UI::Layouts::NewUser(); }

void SketchIt::setUpSession() {}

void SketchIt::reloadApp() {
  this->close();
  Glib::signal_timeout().connect_once(
      []() { std::cout << "restart" << "\n"; }, 100);
}