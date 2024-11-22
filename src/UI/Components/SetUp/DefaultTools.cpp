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

#include "./DefaultTools.h"

#include <gtkmm.h>

#include "../../../lib/Tools.h"
#include "../../Widgets.h"

namespace SketchItApplication {
namespace UI {
namespace Components {

DefaultTools::DefaultTools() {}

void DefaultTools::create(Gtk::Box* contentContainer) {
  // Build a grid for tool categories that a user will be able to select easily tools to their tool
  // belt
  Gtk::Grid* sections = Widgets::Grid(20, 20, "default-tools-grid");

  std::vector<Tools::ToolDef> tools = Tools::defaultTools;

  std::vector<std::string> categories = {};
  for (int i = 0; i < tools.size(); i++) {
    if (std::find(categories.begin(), categories.end(), tools[ i ].category) != categories.end()) {
      // Push new category to the list to sort tools
      categories.push_back(tools[ i ].category);
    }
  }

  // sections->attach(*child, column, row, width, height);
}
}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication