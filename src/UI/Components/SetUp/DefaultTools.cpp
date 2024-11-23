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
#include "../../Layouts.h"
#include "../../Widgets.h"

namespace SketchItApplication {
namespace UI {
namespace Components {

DefaultTools::DefaultTools() {}

void DefaultTools::create(Gtk::Box* contentContainer) {
  std::vector<Tools::ToolDef> tools = Tools::defaultTools;

  std::unordered_map<std::string, std::vector<Tools::ToolDef>>
      categorizedTools;  // Don't forget to parse the users config for custom built tools

  // Fill in the categorized map with tools from each category sorted
  for (int i = 0; i < tools.size(); i++) {
    categorizedTools[ tools[ i ].category ].push_back(tools[ i ]);
  }

  buildCategoryGUI(categorizedTools);

  // sections->attach(*child, column, row, width, height);
}

void DefaultTools::buildCategoryGUI(
    std::unordered_map<std::string, std::vector<Tools::ToolDef>>& categorizedTools
) {
  Gtk::Grid* sections = Widgets::Grid(20, 20, "default-tools-grid");

  for (int i = 0; i < categorizedTools.size(); i++) {
    Gtk::Box* container = Widgets::Box(
        Layouts::LayoutProps(
            Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        ),
        "default-tools-grid-child"
    );
  }
}

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication