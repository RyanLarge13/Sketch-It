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

#ifndef CUSTOM_TOOLS
#define CUSTOM_TOOLS

#include <gtkmm.h>

#include "../../../lib/ToolBuilder.h"
#include "../../../lib/Tools.h"

namespace SketchItApplication {
namespace UI {
namespace Components {

class CustomTools {
 public:
  CustomTools();

  ToolBuilder myTool;

  static void create(Gtk::Box* contentContainer);
  static bool addProp(const Tools::ToolProp& prop);

 protected:
  static void buildImgContainer(Gtk::Box* customImgContainer);
  static void buildToolPropsContainer(Gtk::Grid* toolPropsContainer);
  static void buildInputContainer(Gtk::Box* inputContainer);

 private:
};

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication

#endif
