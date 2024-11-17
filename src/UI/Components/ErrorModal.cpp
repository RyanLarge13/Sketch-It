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

#include "./ErrorModal.h"

#include <gtkmm.h>

#include "../Widgets.h"

namespace SketchItApplication {
namespace UI {
namespace Components {

ErrorModal::ErrorModal() {}

Gtk::Window* ErrorModal::create(const std::string& title, const std::string& message) {
  // Custom error modal widget
  Gtk::Window* errWin = Gtk::make_managed<Gtk::Window>();
  Gtk::Box* container = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "error-modal-message-container"
  );
  Gtk::Label* label = Widgets::Label(
      message,
      "error-modal-label",
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::CENTER, Gtk::Align::CENTER
      )
  );

  label->add_css_class("error-modal-message");
  container->add_css_class("error-modal");
  errWin->set_title(title);

  container->append(*label);
  errWin->set_child(*container);

  return errWin;
}

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication
