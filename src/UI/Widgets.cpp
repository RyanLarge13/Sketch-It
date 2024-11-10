/*
Sketch It - A learn to draw program
Copyright (C) 2024 Ryan Large

This program is free software: you can
redistribute it and/or modify it under
the terms of the GNU General Public
License as published by the Free
Software Foundation, either version 3 of
the License, or (at your option) any
later version.

This program is distributed in the hope
that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the
GNU General Public License along with
this program. If not, see
<https://www.gnu.org/licenses/>.
*/

#include "Widgets.h"

#include <gtkmm.h>

#include <iostream>

#include "Layouts.h"

namespace SketchItApplication {
namespace UI {

// Constant strings for defining set up
// window notebook tabs
const std::vector<std::string> Widgets::setupTabs = {
    "Welcome", "Default Learning", "Default Tools", "Theme", "Installing Drawing Packs", "Finish"
};
// Constant strings for defining set up
// window notebook tabs

// Constant file menu button strings
const std::vector<std::string> fileMenuButtons = {"File", "Edit", "Insert", "View"};
// Constant file menu button strings

Widgets::Widgets() {}

// Custom Widgets
// ------------------------------------------------

Gtk::Box* Widgets::Box(const Layouts::LayoutProps& props, const std::string& className) {
  // Build layout for a custom Gtk::Box
  // and return it
  Gtk::Box* box = Gtk::make_managed<Gtk::Box>(props.orientation);

  box->add_css_class(className);

  box->set_hexpand(props.hexpand);
  box->set_vexpand(props.vexpand);
  box->set_halign(props.halign);
  box->set_valign(props.valign);

  return box;
}

Gtk::Button* Widgets::Button(
    const std::string& label,
    const std::string& className,
    std::function<void()> func,
    const Layouts::LayoutProps& props
) {
  // Custom button method. Returns a
  // button with initialized props
  Gtk::Button* myCustomBtn = Gtk::make_managed<Gtk::Button>(label);

  myCustomBtn->set_hexpand(props.hexpand);
  myCustomBtn->set_vexpand(props.vexpand);
  myCustomBtn->set_halign(props.halign);
  myCustomBtn->set_valign(props.valign);
  myCustomBtn->add_css_class(className);

  myCustomBtn->signal_clicked().connect([ func ]() { func(); });

  return myCustomBtn;
}

Gtk::Label* Widgets::Label(
    const std::string& label, const std::string& className, const Layouts::LayoutProps& props
) {
  // Create and build a custom label

  Gtk::Label* customLabel = Gtk::make_managed<Gtk::Label>(label);

  customLabel->add_css_class(className);
  customLabel->set_hexpand(props.hexpand);
  customLabel->set_vexpand(props.vexpand);
  customLabel->set_halign(props.halign);
  customLabel->set_valign(props.valign);

  return customLabel;
}

Gtk::TextView* Widgets::LongText(
    const std::string& text,
    const std::string& className,
    const std::pair<int, int>& size,
    const Gtk::WrapMode& wrapMode,
    const bool& editable,
    const Layouts::LayoutProps& props
) {
  Glib::RefPtr<Gtk::TextBuffer> buffer = Gtk::TextBuffer::create();

  buffer->set_text(text);

  Gtk::TextView* textArea = Gtk::make_managed<Gtk::TextView>();

  textArea->set_buffer(buffer);
  textArea->set_wrap_mode(Gtk::WrapMode::WORD);
  textArea->set_size_request(300, 20);
  textArea->set_editable(false);
  textArea->add_css_class(className);

  return textArea;
}

// Gtk::ScrolledWindow*
// Widgets::ScrollWindow() {}

Gtk::Notebook* Widgets::Notebook(
    const std::string& className,
    const std::vector<Widgets::WidgetNotebookTabs>& tabs,
    const Layouts::LayoutProps& props
) {
  // Create and return a Gtk Notebook
  // with tabs
  Gtk::Notebook* notebook = Gtk::make_managed<Gtk::Notebook>();

  for (const Widgets::WidgetNotebookTabs& tab : tabs) {
    notebook->append_page(*tab.page, *tab.tabLabel);
  }

  notebook->add_css_class(className);

  return notebook;
}

Gtk::ScrolledWindow* Widgets::ScrollWin(
    const std::pair<int, int>& size,
    const std::string& className,
    const Layouts::LayoutProps& props,
    const bool& horizontal
) {
  Gtk::ScrolledWindow* win = Gtk::make_managed<Gtk::ScrolledWindow>();
  win->add_css_class(className);
  win->set_size_request(size.first, size.second);

  return win;
}

}  // namespace UI
}  // namespace SketchItApplication
