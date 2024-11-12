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

#ifndef SKETCH_IT
#define SKETCH_IT

#include "../Files/Config.h"
#include "../Renderer/Canvas.h"
#include "../Styles/Styles.h"
#include "gtkmm.h"

namespace SketchItApplication {
class SketchIt : public Gtk::Application {
 public:
  // Define global accessible singleton instances
  static Glib::RefPtr<SketchIt> create();
  static Files::ConfigManager config;

  // Constructor
  SketchIt();

 protected:
  // Build custom logic for app load
  void on_startup() override;
  void on_activate() override;

 private:
  // Load classes using namespaces and use them
  // throughout the app
  UI::Styles styleSheets;
  CanvasManager::Canvas canvas;
};
}  // namespace SketchItApplication

#endif