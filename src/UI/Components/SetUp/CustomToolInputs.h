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

#ifndef CUSTOM_TOOL_INPUT
#define CUSTOM_TOOL_INPUT

namespace SketchItApplication {
namespace UI {
namespace Components {
namespace SetUp {

class CustomToolInputs {
 public:
  CustomToolInputs();

  static void create(Gtk::Grid* container);

 protected:
 private:
};

}  // namespace SetUp
}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication

#endif