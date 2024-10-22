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

// Constant strings for defining set up notebook tabs
const std::vector<std::string> Widgets::setupTabs = {"Welcome",
    "Default Learning", "Default Tools", "Theme", "Installing Drawing Packs",
    "Finish"};
// Constant strings for defining set up notebook tabs

// Static constants widget props that can be used from outside of the class in a
// easy matter for defining simple layouts
Widgets::WidgetLayoutProps Widgets::H_FILL =
    Widgets::WidgetLayoutProps(Gtk::Orientation::HORIZONTAL, true, true,
        Gtk::Align::FILL, Gtk::Align::FILL);

Widgets::WidgetLayoutProps Widgets::V_FILL = Widgets::WidgetLayoutProps(
    Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL);

Widgets::WidgetLayoutProps Widgets::CONTAIN =
    Widgets::WidgetLayoutProps(Gtk::Orientation::HORIZONTAL, false, false,
        Gtk::Align::START, Gtk::Align::START);
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

Gtk::Label* Widgets::Label(const std::string& label,
    const std::string& className, const Widgets::WidgetLayoutProps& props) {
  // Create a build a custom label

  Gtk::Label* customLabel = Gtk::make_managed<Gtk::Label>(label);

  customLabel->add_css_class(className);
  customLabel->set_hexpand(props.hexpand);
  customLabel->set_vexpand(props.vexpand);
  customLabel->set_halign(props.halign);
  customLabel->set_valign(props.valign);

  return customLabel;
}

Gtk::TextView* Widgets::LongText(const std::string& text,
    const std::string& className, const Widgets::WidgetLayoutProps& props) {
  Glib::RefPtr<Gtk::TextBuffer> buffer = Gtk::TextBuffer::create();

  buffer->set_text(text);

  Gtk::TextView* textArea = Gtk::make_managed<Gtk::TextView>();

  textArea->set_buffer(buffer);
  textArea->set_editable(false);
  textArea->add_css_class(className);

  return textArea;
}

Gtk::Window* Widgets::SetUp() {
  // Build the window that will be returned and contain the layout
  Gtk::Window* setUpWindow = Gtk::make_managed<Gtk::Window>();

  Gtk::Notebook* notebook = Gtk::make_managed<Gtk::Notebook>();

  for (const std::string title : Widgets::setupTabs) {
    Gtk::Label* label =
        Widgets::Label(title, "set-up-tab-title", Widgets::H_FILL);

    Gtk::Box* page = Widgets::Box(Widgets::H_FILL, "set-up-page");
    Gtk::Box* pageContentContainer =
        Widgets::Box(Widgets::H_FILL, "set-up-content-container");

    Gtk::Box* descContainer =
        Widgets::Box(Widgets::V_FILL, "set-up-desc-container");

    Gtk::Label* descTitle =
        Widgets::Label("Description", "desc-title", Widgets::CONTAIN);

    descContainer->append(*descTitle);

    pageContentContainer->append(*descContainer);

    page->append(*pageContentContainer);
    page->append(*Widgets::Label(title, "set-up-title", Widgets::CONTAIN));

    Gtk::TextView* desc = Widgets::LongText(
        "Welcome to Sketch It!!! This is going to be a lot of fun beggining "
        "your journey to becoming a professional artist. Open up a world you "
        "never new existed",
        "set-up-desc-text", Widgets::CONTAIN);

    descContainer->append(*desc);

    notebook->append_page(*page, *label);
  }

  notebook->add_css_class("set-up-notebook");
  setUpWindow->set_title("Set Up");
  setUpWindow->set_child(*notebook);

  return setUpWindow;
}

Gtk::Window* Widgets::ErrorDialog(
    const std::string& title, const std::string& message) {
  // Custom error modal widget returns transient window of main
  Gtk::Window* errWin = Gtk::make_managed<Gtk::Window>();
  Gtk::Box* container =
      Widgets::Box(Widgets::H_FILL, "error-modal-message-container");
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
