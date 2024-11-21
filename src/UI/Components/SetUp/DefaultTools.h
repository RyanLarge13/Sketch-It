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

#ifndef DEFAULT_TOOLS
#define DEFAULT_TOOLS

#include <gtkmm.h>

namespace SketchItApplication {
namespace UI {
namespace Components {

// TODO:
// How do I want to define the application default drawing tools?
// Think about this one and probably store these in a more global
// setting

class DefaultTools {
 public:
  DefaultTools();

  struct defaultTools() {
    std::string icon;
    std::string name;
    std::pair<double, double>

    defaultTools() : {}
  };

  static void create(Gtk::Box* contentContainer);

 protected:
 private:
};

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication

#endif