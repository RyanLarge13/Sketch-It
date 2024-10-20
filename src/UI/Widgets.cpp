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

#include "UI.h"

namespace SketchItApplication {
namespace UI {

Widgets::WidgetLayoutProps Widgets::EXPAND_FILL =
    Widgets::WidgetLayoutProps(Gtk::Orientation::HORIZONTAL, true, true,
        Gtk::Align::FILL, Gtk::Align::FILL);
Widgets::WidgetLayoutProps Widgets::CONTAIN =
    Widgets::WidgetLayoutProps(Gtk::Orientation::HORIZONTAL, false, false,
        Gtk::Align::CENTER, Gtk::Align::CENTER);

Widgets::Widgets() {}

Gtk::Button* Widgets::Button(const std::string& label,
    const std::string& className, std::function<void()> func,
    const Widgets::WidgetLayoutProps& props) {
  Gtk::Button* myCustomBtn = Gtk::make_managed<Gtk::Button>(label);
  myCustomBtn->set_hexpand(props.hexpand);
  myCustomBtn->set_vexpand(props.vexpand);
  myCustomBtn->set_halign(props.halign);
  myCustomBtn->set_valign(props.valign);
  myCustomBtn->add_css_class(className);
  myCustomBtn->signal_clicked().connect([ func ]() { func(); });
  return myCustomBtn;
}

Gtk::Window* Widgets::ErrorDialog(
    const std::string& title, const std::string& message) {
  Gtk::Window* errWin = Gtk::make_managed<Gtk::Window>();
  errWin->set_title(title);
  Gtk::Box* container = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  Gtk::Label* label = Gtk::make_managed<Gtk::Label>(message);
  container->append(*label);
  container->add_css_class("error-modal");
  label->add_css_class("error-modal-message");

  errWin->set_child(*container);

  return errWin;
};

Gtk::Box* Widgets::Box(
    const Widgets::WidgetLayoutProps& props, const std::string& className) {
  Gtk::Box* myBox = Gtk::make_managed<Gtk::Box>(props.orientation);

  myBox->set_hexpand(props.hexpand);
  myBox->set_vexpand(props.vexpand);
  myBox->set_halign(props.halign);
  myBox->set_valign(props.valign);
  myBox->add_css_class(className);

  return myBox;
}

void Widgets::addBtns(const std::vector<Gtk::Button*>& btns,
    Gtk::Box* container, Gtk::Box* parent) {
  for (Gtk::Button* btn : btns) {
    if (!btn) {
      std::cout << "Error, your button can not be appended to the parent. Btn "
                   "is nullptr"
                << "\n";
      continue;
    }
    container->append(*btn);
  }
  parent->append(*container);
}

}  // namespace UI
}  // namespace SketchItApplication
