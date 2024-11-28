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

#include "./CustomTools.h"

#include <gtkmm.h>

#include "../../../lib/ToolBuilder.h"
#include "../../../lib/Tools.h"
#include "../../Layouts.h"
#include "../../UIUtils.h"
#include "../../Widgets.h"
#include "../ToolProperty.h"

namespace SketchItApplication {
namespace UI {
namespace Components {

CustomTools::CustomTools() { CustomTools::myTool = ToolBuilder(); }

void CustomTools::create(Gtk::Box* contentContainer) {
  contentContainer->set_orientation(Gtk::Orientation::VERTICAL);

  // Define container widgets
  Gtk::Box* customImgContainer = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "custom-tools-img-container",
      false
  );

  Gtk::Grid* toolPropsContainer = Widgets::Grid(5, 5, "custom-tools-props-container");

  Gtk::Box* inputContainer = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "custom-tools-input-container",
      false
  );

  // Fill in container widget UI && logic
  buildImgContainer(customImgContainer);
  buildToolPropsContainer(toolPropsContainer);
  buildInputContainer(inputContainer);

  // Append containers
  contentContainer->append(*customImgContainer);
  contentContainer->append(*toolPropsContainer);
  contentContainer->append(*inputContainer);
}

// Protected
void CustomTools::buildImgContainer(Gtk::Box* customImgContainer) {
  // Build tool image containers. One image for each part of the tool
  // e.g tip, collar, body, ferrule, eraser
  Gtk::Box* tip = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "custom-tools-img-tip",
      false
  );
  Gtk::Box* collar = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "custom-tools-img-tip",
      false
  );
  Gtk::Box* body = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "custom-tools-img-tip",
      false
  );
  Gtk::Box* ferrule = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "custom-tools-img-tip",
      false
  );
  Gtk::Box* eraser = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "custom-tools-img-tip",
      false
  );
}

void CustomTools::buildToolPropsContainer(Gtk::Grid* toolPropsContainer) {
  // Remove all props from the container, then update them
  UI::UIUtils::removeAllChildren(toolPropsContainer);

  // Grab custom tool properties that have been defined and create the boxes to be displayed
  //   int colIndex = 0;
  //   int rowIndex = 0;
  //   for (const Tools::ToolProp& toolProp : CustomTools::toolProps) {
  //     Gtk::Box* prop = Components::ToolProperty::create(
  //         toolProp.property, std::any_cast<std::string>(toolProp.value)
  //     );

  //     toolPropsContainer->attach(*prop, colIndex, rowIndex, 1, 1);

  //     if (colIndex == 3) {
  //       colIndex = 0;
  //       rowIndex++;
  //       continue;
  //     }

  //     colIndex++;
  //   }
}

void CustomTools::buildInputContainer(Gtk::Box* inputContainer) {}

bool CustomTools::addProp(const Tools::ToolProp& prop) { return true; }

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication
