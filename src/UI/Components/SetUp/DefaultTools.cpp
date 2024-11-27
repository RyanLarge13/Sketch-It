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
#include "../../UIUtils.h"
#include "../../Widgets.h"

namespace SketchItApplication {
namespace UI {
namespace Components {

std::vector<std::shared_ptr<Tools::ToolDef>> DefaultTools::selectedTools = {};

DefaultTools::DefaultTools() {}

void DefaultTools::create(Gtk::Box* contentContainer) {
  Gtk::ScrolledWindow* child = buildCategoryGUI();

  contentContainer->append(*child);
}

Gtk::ScrolledWindow* DefaultTools::buildCategoryGUI() {
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
  for (const auto& [ catName, catTools ] : Tools::categorizedTools) {
    Gtk::Box* catContainer = Widgets::Box(
        Layouts::LayoutProps(
            Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        ),
        "default-tools-grid-child",
        false
    );

    Gtk::Box* toolContainer = Widgets::Box(
        Layouts::LayoutProps(
            Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        ),
        "default-tools-tool-container",
        false
    );

    for (const std::shared_ptr<Tools::ToolDef>& tool : catTools) {
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

Gtk::Box* DefaultTools::buildToolBtn(const std::shared_ptr<Tools::ToolDef>& tool) {
  Gtk::Box* toolBtn = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::CENTER
      ),
      "default-tools-tool",
      true
  );

  Gtk::Image* toolIcon = Widgets::Img(
      tool->icon,
      "default-tools-tool",
      25,
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, false, false, Gtk::Align::START, Gtk::Align::START
      )
  );

  Gtk::Label* toolName = Widgets::Label(
      tool->name,
      "default-tools-tool-name",
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::START, Gtk::Align::FILL
      )
  );

  buildToolTip(toolBtn, tool);
  buildSelectableBtn(toolBtn, tool);

  toolBtn->append(*toolIcon);
  toolBtn->append(*toolName);

  return toolBtn;
}

void DefaultTools::buildToolTip(Gtk::Box* toolBtn, const std::shared_ptr<Tools::ToolDef>& tool) {
  toolBtn->set_has_tooltip(true);

  toolBtn->signal_query_tooltip().connect(
      [ tool ](
          int x, int y, bool keyboard_mode, const Glib::RefPtr<Gtk::Tooltip>& tooltip
      ) -> bool {
        Gtk::Box* toolTipContainer = Widgets::Box(
            Layouts::LayoutProps(
                Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
            ),
            "tooltip",
            false
        );

        Gtk::Box* toolDescContainer = Widgets::Box(
            Layouts::LayoutProps(
                Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
            ),
            "tooltip-desc-container",
            false
        );

        Gtk::Label* toolName = Widgets::Label(
            tool->name,
            "tooltip-name",
            Layouts::LayoutProps(
                Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::START, Gtk::Align::START
            )
        );

        Gtk::Label* tooltipDesc = Widgets::Label(
            tool->desc,
            "tooltip-desc",
            Layouts::LayoutProps(
                Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::START, Gtk::Align::START
            )
        );

        Gtk::Image* toolIcon = Widgets::Img(
            tool->icon,
            "tooltip-img",
            100,
            Layouts::LayoutProps(
                Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
            )
        );

        Gtk::Grid* toolProperties = buildToolTipProperties(tool);

        toolDescContainer->append(*toolName);
        toolDescContainer->append(*tooltipDesc);
        toolDescContainer->append(*toolProperties);

        toolTipContainer->append(*toolIcon);
        toolTipContainer->append(*toolDescContainer);

        tooltip->set_custom(*toolTipContainer);
        return true;
      },
      false
  );
}

Gtk::Grid* DefaultTools::buildToolTipProperties(const std::shared_ptr<Tools::ToolDef>& tool) {
  Gtk::Grid* toolPropGrid = Widgets::Grid(5, 5, "tooltip-tool-prop-grid");

  // Loop through tool properties and create an information grid
  int colIndex = 0;
  int rowIndex = 0;
  for (const auto& [ toolPropName, toolProp ] : tool->toolPropsMap) {
    // Skip displaying non user friendly information
    if (toolPropName == "Description" || toolPropName == "Tool Tip" || toolPropName == "Icon" ||
        toolPropName == "rgba" || toolPropName == "hsl" || toolPropName == "hex") {
      continue;
    }

    Gtk::Box* toolPropertyBox = Widgets::Box(
        Layouts::LayoutProps(
            Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        ),
        "tooltip-property",
        false
    );

    Gtk::Label* propName = Widgets::Label(
        toolPropName + ": ",
        "tooltip-prop-title",
        Layouts::LayoutProps(
            Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::START, Gtk::Align::FILL
        )
    );

    Gtk::Label* propValue = Widgets::Label(
        // Use the variant operator overload to determine the type of toolProp being passed to the
        // Label
        std::visit(DefaultTools::StringFromVariantVisitor{}, toolProp),
        "tooltip-prop-desc",
        Layouts::LayoutProps(
            Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::END, Gtk::Align::FILL
        )
    );

    toolPropertyBox->append(*propName);
    toolPropertyBox->append(*propValue);

    toolPropGrid->attach(*toolPropertyBox, colIndex, rowIndex, 1, 1);

    if (colIndex == 3) {
      colIndex = 0;
      rowIndex++;
      continue;
    }

    colIndex++;
  }

  return toolPropGrid;
}

void DefaultTools::buildSelectableBtn(
    Gtk::Box* toolBtn, const std::shared_ptr<Tools::ToolDef>& tool
) {
  Glib::RefPtr<Gtk::GestureClick> gesture_click = Gtk::GestureClick::create();

  auto click = [ toolBtn ](const double& x, const double& y, const double& z) {
    bool hasClass = UIUtils::hasCssClass("selected", toolBtn);

    if (hasClass) {
      toolBtn->remove_css_class("selected");
      // Remove from vector of selected tools
    } else {
      toolBtn->add_css_class("selected");
      // Add to vector of selected tools
    }
  };

  gesture_click->signal_released().connect(click);

  toolBtn->add_controller(gesture_click);
}

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication