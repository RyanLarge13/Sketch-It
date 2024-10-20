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

#include <iostream>

#include "gtkmm.h"

namespace SketchItApplication {
Glib::RefPtr<SketchIt> SketchIt::create() {
  return Glib::make_refptr_for_instance<SketchIt>(new SketchIt());
}

SketchIt::SketchIt() : config("sketchit.config.json"), styleSheets("") {
  // Initialize core application logic and state
}

void SketchIt::on_startup() {
  Gtk::Application::on_startup();
  Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
  try {
    css_provider->load_from_path("../src/Styles/styleSheets/global.css");
  } catch (const Glib::Error& err) {
    std::cerr << "Error loading css files: " << err.what() << "\n";
  }
  Glib::RefPtr<Gdk::Display> display = Gdk::Display::get_default();
  Gtk::StyleContext::add_provider_for_display(
      display, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
  // Set up logic for before window is shown
  // Customize on start up logic and build the core application
  // initial state, load config, set ui, set window size and load css add
  // signals etc...
}

void SketchIt::on_activate() {
  Gtk::Application::on_activate();
  // Call add_window() and present the window.
  // Set up logic for when window is shown
}

}  // namespace SketchItApplication