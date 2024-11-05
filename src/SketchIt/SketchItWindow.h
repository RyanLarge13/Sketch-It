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

#ifndef SKETCH_IT_WINDOW
#define SKETCH_IT_WINDOW

#include "gtkmm.h"

namespace SketchItApplication {
class SketchItWindow : public Gtk::Window {
 public:
  // Define global main window object for access across application
  static Gtk::Window* win;

  // Constructor
  SketchItWindow();

 protected:
 private:
  void setUp();
  void loadMainAppUI();
  void checkConfig();
  void saveConfig();
  void guideSetUp(Gtk::Window* setUpInstance);
};
}  // namespace SketchItApplication

#endif