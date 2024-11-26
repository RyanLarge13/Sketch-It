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

#include "../lib/Tools.h"
#include "SketchItWindow.h"

namespace SketchItApplication {
// Initialize global config singleton instance
Files::ConfigManager SketchIt::config("sketchit.config.json");

Glib::RefPtr<SketchIt> SketchIt::create() {
  return Glib::make_refptr_for_instance<SketchIt>(new SketchIt());
}

SketchIt::SketchIt() : styleSheets("../src/Styles/styleSheets/global.css") {
  // Initialize core application logic and state

  // Create default tools and initialize their categorization
  // "../lib/Tools.h"
  Tools();
}

void SketchIt::on_startup() { Gtk::Application::on_startup(); }

void SketchIt::on_activate() {
  Gtk::Application::on_activate();
  // Call add_window() and present the window.
  // Set up logic for when window is shown
}

}  // namespace SketchItApplication