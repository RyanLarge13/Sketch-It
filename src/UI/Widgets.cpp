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

// Static constants widget props that can be used from outside of the class in a
// easy matter for defining simple layouts
Widgets::WidgetLayoutProps Widgets::EXPAND_FILL =
    Widgets::WidgetLayoutProps(Gtk::Orientation::HORIZONTAL, true, true,
        Gtk::Align::FILL, Gtk::Align::FILL);

Widgets::WidgetLayoutProps Widgets::CONTAIN =
    Widgets::WidgetLayoutProps(Gtk::Orientation::HORIZONTAL, false, false,
        Gtk::Align::CENTER, Gtk::Align::CENTER);
// Static constants widget props that can be used from outside of the class in a
// easy matter for defining simple layouts

Widgets::Widgets() {}

Gtk::Button* Widgets::Button(const std::string& label,
    const std::string& className, std::function<void()> func,
    const Widgets::WidgetLayoutProps& props) {
  // Custom button method. Returns a button with initialized props
  Gtk::Button* myCustomBtn = Gtk::make_managed<Gtk::Button>(label);

  myCustomBtn->set_hexpand(props.hexpand);
  myCustomBtn->set_vexpand(props.vexpand);
  myCustomBtn->set_halign(props.halign);
  myCustomBtn->set_valign(props.valign);
  myCustomBtn->add_css_class(className);

  myCustomBtn->signal_clicked().connect([ func ]() { func(); });

  return myCustomBtn;
}

Gtk::Window* Widgets::SetUp() {
  // Build the window that will be returned and contain the layout
  Gtk::Widnow* setUpWindow = Gtk::make_managed<Gtk::Widnow>();
}

Gtk::Window* Widgets::ErrorDialog(
    const std::string& title, const std::string& message) {
  // Custom error modal widget returns transient window of main
  Gtk::Window* errWin = Gtk::make_managed<Gtk::Window>();
  Gtk::Box* container =
      Widgets::Box(Widgets::EXPAND_FILL, "error-modal-message-container");
  Gtk::Label* label = Gtk::make_managed<Gtk::Label>(message);

  label->add_css_class("error-modal-message");
  container->add_css_class("error-modal");
  errWin->set_title(title);

  container->append(*label);
  errWin->set_child(*container);

  return errWin;
};

Gtk::Box* Widgets::Box(
    const Widgets::WidgetLayoutProps& props, const std::string& className) {
  // Custom box method, returns a container initialized with specified props
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
  // Adding buttons to a container and container to parent
  for (Gtk::Button* btn : btns) {
    if (!btn) {
      std::cout << "Error, your button can not be appended to the parent in "
                   "Widgets::addBtn method. Btn "
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
