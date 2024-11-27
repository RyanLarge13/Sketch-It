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

#include <gtkmm.h>

#include "../../lib/Tools.h"
#include "../Layouts.h"
#include "../Widgets.h"


namespace SketchItApplication {
namespace UI {
namespace Components {

ToolProperty::ToolProperty();

Gtk::Box* ToolProperty::create(const std::string& name, const std::string& value) {
  Gtk::Box* prop = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "tooltip-property",
      false
  );

  Gtk::Label* propName = Widgets::Label(
      name + ": ",
      "tooltip-prop-title",
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::START, Gtk::Align::FILL
      )
  );

  Gtk::Label* propValue = Widgets::Label(
      // Use the variant operator overload to determine the type of toolProp being passed to the
      // Label
      std::visit(Tools::StringFromVariantVisitor{}, value),
      "tooltip-prop-desc",
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::END, Gtk::Align::FILL
      )
  );

  prop->append(*propName);
  prop->append(*propValue);

  return prop;
};

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication
