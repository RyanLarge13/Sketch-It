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

#include <gtkmm.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "../lib/config.h"
#include "../widgets/ErrorModal.h"

class MyWindow : public Gtk::Window {
 public:
  MyWindow() {
    set_title("Sketch it");
    signal_realize().connect(
        sigc::mem_fun(*this, &MyWindow::setDefaultScreenSize));
    applyGlobalCSS();
    Config configManager("/sketch-it/config.json");
    if (configManager.errorState) {
      Config::EventLog error = configManager.getLogAt(0);
      ErrorModal newError("Configuration Error", error.message);
      newError.addBtns(std::vector<ErrorModal::ErrorModalButtons>{
          ErrorModal::ErrorModalButtons(
              "Okay", 0, [ this ]() { this->close(); }),
          ErrorModal::ErrorModalButtons(
              "Reload App", 1, [ this ]() { this->reloadApp(); })});
      newError.errorModal->set_transient_for(*this);
      configManager.clearAllErrors();
      return;
    }
    Config::EventLog log = configManager.getLogAt(0);
    if (log.status == Config::StatusCodes::NEW_USER) {
      setUpNewUser();
    }
    setUpSession();
  }

 private:
  Glib::RefPtr<Gtk::CssProvider> css_provider;
  std::pair<int, int> dems = std::make_pair(1250, 900);
  std::string sessionName = "Untitled Session";

  void setDefaultScreenSize() {
    auto display = Gdk::Display::get_default();
    if (!display) {
      set_default_size(dems.first, dems.second);
      return;
    }
    auto monitor = display->get_monitor_at_surface(get_surface());
    if (!monitor) {
      set_default_size(dems.first, dems.second);
      return;
    }
    Gdk::Rectangle monitor_geometry;
    monitor->get_geometry(monitor_geometry);
    const size_t width = monitor_geometry.get_width();
    const size_t height = monitor_geometry.get_height();
    set_default_size(width, height);
    dems.first = width;
    dems.second = height;
  }

  void applyGlobalCSS() {
    css_provider = Gtk::CssProvider::create();
    try {
      css_provider->load_from_path("../styles/global.css");
    } catch (const Glib::Error& err) {
      std::cerr << "Error loading css files: " << err.what() << "\n";
    }
    auto display = Gdk::Display::get_default();
    Gtk::StyleContext::add_provider_for_display(
        display, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
  }

  void setUpNewUser() {}

  void setUpSession() {}

  void reloadApp() {
    this->close();
    Glib::signal_timeout().connect_once(
        []() {
          auto app = Gtk::Application::create("org.gtkmm.example");
          MyWindow newWindow;
          app->make_window_and_run<MyWindow>(0, nullptr);
        },
        100);
  }
};

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("org.gtkmm.example");
  return app->make_window_and_run<MyWindow>(argc, argv);
}
