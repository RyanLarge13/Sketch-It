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

#include "../Styles/Styles.h"
#include "../lib/Tools.h"
#include "SketchItWindow.h"

namespace SketchItApplication {
// Initialize global config singleton instance
Files::ConfigManager SketchIt::config("sketchit.config.json");

Glib::RefPtr<SketchIt> SketchIt::create() {
  return Glib::make_refptr_for_instance<SketchIt>(new SketchIt());
}

SketchIt::SketchIt() {
  // Initialize core application logic and state

  // Create default tools and initialize their categorization
  // "../lib/Tools.h"
  Tools();
}

void SketchIt::on_startup() {
  // Load up stuff before the window is ready to show
  Gtk::Application::on_startup();

  initializeStyles();
}

void SketchIt::on_activate() {
  Gtk::Application::on_activate();
  // Call add_window() and present the window.
  // Set up logic for when window is shown
}

void SketchIt::initializeStyles() {
  auto settings = Gtk::Settings::get_default();
  bool darkMode = false;

  // Style sheet path references
  // darkModePath = "src/Styles/styleSheets/globalDark.css";
  // lightModePath = "src/Styles/styleSheets/globalLight.css";

  if (!settings) {
    UI::Styles("src/Styles/styleSheets/globalDark.css");
    std::cout << "No settings detected when trying to initialize stylesheet" << "\n";
    // Set the style to automatic dark mode the user can change this later
    return;
  }

  settings->get_property("gtk-application-prefer-dark-theme", darkMode);

  if (!darkMode) {
    UI::Styles("src/Styles/styleSheets/globalDark.css");
  } else {
    UI::Styles("src/Styles/styleSheets/globalLight.css");
  }
}

}  // namespace SketchItApplication