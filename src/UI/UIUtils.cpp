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

#include "UIUtils.h"

#include <gtkmm.h>

#include <iostream>

namespace SketchItApplication {
namespace UI {

UIUtils::UIUtils() {}

void UIUtils::addBtns(const std::vector<Gtk::Button*>& btns, Gtk::Box* container) {
  // Adding buttons to a container and
  // container to parent
  for (Gtk::Button* btn : btns) {
    if (!btn) {
      std::cout << "Error, your button can "
                   "not be appended to the "
                   "parent in "
                   "UIUtils::addBtn method. "
                   "Btn "
                   "is nullptr"
                << "\n";
      continue;
    }
    container->append(*btn);
  }
}

Gtk::Box* UIUtils::grabChildAtIndex(Gtk::Widget* parent, const int& index) {
  auto* child = parent->get_first_child();
  for (int i = 1; i <= index; i++) {
    child = child->get_next_sibling();
  }
  return dynamic_cast<Gtk::Box*>(child);
}
}  // namespace UI
}  // namespace SketchItApplication