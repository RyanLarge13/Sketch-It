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

// Constant strings for defining set up window notebook tabs
const std::vector<std::string> Widgets::setupTabs = {"Welcome",
    "Default Learning", "Default Tools", "Theme", "Installing Drawing Packs",
    "Finish"};
// Constant strings for defining set up window notebook tabs

// Static constants widget props that can be used from outside of the class in a
// easy matter for defining simple layouts
Widgets::WidgetLayoutProps Widgets::H_FILL =
    Widgets::WidgetLayoutProps(Gtk::Orientation::HORIZONTAL, true, true,
        Gtk::Align::FILL, Gtk::Align::FILL);

Widgets::WidgetLayoutProps Widgets::V_FILL = Widgets::WidgetLayoutProps(
    Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL);

Widgets::WidgetLayoutProps Widgets::H_CONTAIN =
    Widgets::WidgetLayoutProps(Gtk::Orientation::HORIZONTAL, false, false,
        Gtk::Align::START, Gtk::Align::START);

Widgets::WidgetLayoutProps Widgets::V_CONTAIN =
    Widgets::WidgetLayoutProps(Gtk::Orientation::VERTICAL, false, false,
        Gtk::Align::START, Gtk::Align::START);
// Static constants widget props that can be used from outside of the class in a
// easy matter for defining simple layouts

Widgets::Widgets() {}

// Custom Widgets ------------------------------------------------

Gtk::Box* Widgets::Box(
    const WidgetLayoutProps& props, const std::string& className) {
  // Build layout for a custom Gtk::Box and return it
  Gtk::Box* box = Gtk::make_managed<Gtk::Box>(props.orientation);

  box->add_css_class(className);

  box->set_hexpand(props.hexpand);
  box->set_vexpand(props.vexpand);
  box->set_halign(props.halign);
  box->set_valign(props.valign);

  return box;
}

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
  textArea->set_wrap_mode(static_cast<Gtk::WrapMode>(2));
  textArea->set_size_request(200, 400);
  textArea->set_editable(false);
  textArea->add_css_class(className);

  return textArea;
}

// Gtk::ScrolledWindow* Widgets::ScrollWindow() {}

Gtk::Notebook* Widgets::Notebook(const std::string& className,
    const std::vector<Widgets::WidgetNotebookTabs>& tabs,
    const Widgets::WidgetLayoutProps& props) {
  // Create and return a Gtk Notebook with tabs
  Gtk::Notebook* notebook = Gtk::make_managed<Gtk::Notebook>();

  for (const Widgets::WidgetNotebookTabs& tab : tabs) {
    notebook->append_page(*tab.page, *tab.tabLabel);
  }

  notebook->add_css_class(className);

  return notebook;
}

// Application Default windows && widgets
// ----------------------------------------------------------------

Gtk::Box* Widgets::StaticSetUpPage(
    const std::string& titleTxt, const std::string& descTxt) {
  // Build containers
  Gtk::Box* page = Widgets::Box(Widgets::V_FILL, "set-up-page");
  Gtk::Box* pageContainer = Widgets::Box(Widgets::H_FILL, "set-up-container");
  Gtk::Box* descContainer =
      Widgets::Box(Widgets::V_CONTAIN, "set-up-desc-container");
  Gtk::Box* contentContainer = Widgets::Box(V_FILL, "set-up-content-container");
  Gtk::Box* btnContainer = Widgets::Box(H_FILL, "set-up-btn-container");

  // Create text elements
  Gtk::Label* title = Widgets::Label(titleTxt, "set-up-title", Widgets::H_FILL);

  Gtk::TextView* desc =
      Widgets::LongText(descTxt, "set-up-desc-text", Widgets::V_FILL);

  // Append and return page
  descContainer->append(*desc);

  pageContainer->append(*descContainer);
  pageContainer->append(*contentContainer);

  page->append(*title);
  page->append(*pageContainer);
  page->append(*btnContainer);

  return page;
}

Gtk::Window* Widgets::SetUp() {
  // Build the window that will be returned and contain the layout
  Gtk::Window* setUpWindow = Gtk::make_managed<Gtk::Window>();

  std::vector<Widgets::WidgetNotebookTabs> tabs = {
      Widgets::WidgetNotebookTabs(Widgets::StaticSetUpPage("Welcome",
                                      "Welcome to sketch it! Where you will "
                                      "learn how to draw like a true "
                                      "artist"),
          Widgets::Label("Welcome", "set-up-tab-title", Widgets::V_CONTAIN)),
      Widgets::WidgetNotebookTabs(Widgets::StaticSetUpPage("Default Session",
                                      "Let us set up your default session when "
                                      "loading the application"),
          Widgets::Label(
              "Default Session", "set-up-tab-title", Widgets::V_CONTAIN)),
      Widgets::WidgetNotebookTabs(
          Widgets::StaticSetUpPage("Default Tools",
              "Configure your drawing and painting tools. These tools will be "
              "accessible to you via quick toolbox while using the "
              "application"),
          Widgets::Label(
              "Default Tools", "set-up-tab-title", Widgets::V_CONTAIN))};

  Gtk::Notebook* notebook =
      Widgets::Notebook("set-up-notebook", tabs, Widgets::V_FILL);

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

// Static methods --------------------------------------------------------
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
