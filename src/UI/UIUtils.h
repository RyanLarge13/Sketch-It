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

#include <iostream>

namespace SketchItApplication {
namespace UI {

class UIUtils {
 public:
  UIUtils();

  static void addBtns(const std::vector<Gtk::Button*>& btns, Gtk::Box* container);

  template <typename T, typename U>
  static T* grabChildAtIndex(U* parent, const int& index) {
    auto* child = parent->get_first_child();

    if (index == 0) {
      if (child == nullptr) {
        std::cout << "null child " << "\n";
        return nullptr;
      }
      return dynamic_cast<T*>(child);
    }

    for (int i = 1; i <= index; i++) {
      child = child->get_next_sibling();
    }
    return dynamic_cast<T*>(child);
  };

  static void addWidget(Gtk::Box* parent, Gtk::Widget* child, const int& index);

  template <typename W>
  static void hasCssClass(const std::string& className, W* widget) {
    std::vector<Glib::ustring> classes = widget->get_css_classes();

    if (std::find(classes.begin(), classes.end(), className) != classes.end()) {
      return true;
    } else {
      return false;
    }
  };

 protected:
 private:
};

}  // namespace UI
}  // namespace SketchItApplication