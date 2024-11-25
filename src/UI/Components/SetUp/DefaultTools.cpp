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

  Gtk::ScrolledWindow* child = buildCategoryGUI(categorizedTools);

  contentContainer->append(*child);
}

Gtk::ScrolledWindow* DefaultTools::buildCategoryGUI(
    std::unordered_map<std::string, std::vector<Tools::ToolDef>>& categorizedTools
) {
  Gtk::ScrolledWindow* scrollContainer = Widgets::ScrollWin(
      {1050, 500},
      "default-tools-scroll-container",
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      false
  );

  Gtk::Grid* sections = Widgets::Grid(20, 20, "default-tools-grid");

  // Build the selectable icons for each category grid item
  int colIndex = 0;
  int rowIndex = 0;
  for (const auto& [ catName, catTools ] : categorizedTools) {
    Gtk::Box* catContainer = Widgets::Box(
        Layouts::LayoutProps(
            Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        ),
        "default-tools-grid-child"
    );

    Gtk::Box* toolContainer = Widgets::Box(
        Layouts::LayoutProps(
            Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        ),
        "default-tools-tool-container"
    );

    for (const Tools::ToolDef& tool : catTools) {
      Gtk::Box* toolBtn = buildToolBtn(tool);

      toolContainer->append(*toolBtn);
    }

    Gtk::Label* catTitle = Widgets::Label(
        catName,
        "default-tools-cat-title",
        Layouts::LayoutProps(
            Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::START, Gtk::Align::START
        )
    );

    catContainer->append(*catTitle);
    catContainer->append(*toolContainer);

    // sections->attach(*child, column, row, width, height);
    sections->attach(*catContainer, colIndex, rowIndex, 1, 1);

    if (colIndex == 1) {
      colIndex = 0;
      rowIndex++;
      continue;
    }

    colIndex++;
  }

  scrollContainer->set_child(*sections);

  return scrollContainer;
}

Gtk::Box* DefaultTools::buildToolBtn(const Tools::ToolDef& tool) {
  Gtk::Box* toolBtn = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::CENTER
      ),
      "default-tools-tool"
  );

  Gtk::Image* toolIcon = Widgets::Img(
      tool.icon,
      "default-tools-tool",
      25,
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, false, false, Gtk::Align::START, Gtk::Align::START
      )
  );

  Gtk::Label* toolName = Widgets::Label(
      tool.name,
      "default-tools-tool-name",
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::START, Gtk::Align::FILL
      )
  );

  createSignals(toolBtn, tool);

  toolBtn->append(*toolIcon);
  toolBtn->append(*toolName);

  return toolBtn;
}

void DefaultTools::createSignals(Gtk::Box* toolBtn, const Tools::ToolDef& tool) {
  toolBtn->set_has_tooltip(true);

  toolBtn->signal_query_tooltip().connect(
      [ tool ](
          int x, int y, bool keyboard_mode, const Glib::RefPtr<Gtk::Tooltip>& tooltip
      ) -> bool {
        Gtk::Box* toolTipContainer = Widgets::Box(
            Layouts::LayoutProps(
                Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
            ),
            "tooltip"
        );

        Gtk::Box* toolDescContainer = Widgets::Box(
            Layouts::LayoutProps(
                Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
            ),
            "tooltip-desc-container"
        );

        Gtk::Label* toolName = Widgets::Label(
            tool.name,
            "tooltip-name",
            Layouts::LayoutProps(
                Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::START, Gtk::Align::START
            )
        );

        Gtk::Label* tooltipDesc = Widgets::Label(
            tool.desc,
            "tooltip-desc",
            Layouts::LayoutProps(
                Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::START, Gtk::Align::START
            )
        );

        Gtk::Image* toolIcon = Widgets::Img(
            tool.icon,
            "tooltip-img",
            100,
            Layouts::LayoutProps(
                Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
            )
        );

        toolDescContainer->append(*toolName);
        toolDescContainer->append(*tooltipDesc);

        Gtk::Grid* toolProperties = buildToolTipProperties(tool);

        toolTipContainer->append(*toolIcon);
        toolTipContainer->append(*toolDescContainer);

        tooltip->set_custom(*toolTipContainer);
        return true;
      },
      false
  );
}

Gtk::Grid* DefaultTools::buildToolTipProperties(const Tools::ToolDef& tool) {
  Gtk::Grid* toolPropGrid = Widgets::Grid(20, 20, "tooltip-tool-prop-grid");

  for (int i = 0; i < 10; i++) {
    Gtk::Box* toolProp = Widgets::Box(Layouts::LayoutProps(
        Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::ALign::FILL
    ));
  }

  return toolPropGrid;
}

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication