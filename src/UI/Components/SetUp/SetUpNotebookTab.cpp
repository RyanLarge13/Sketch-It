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

#include "./SetUpNotebookTab.h"

#include <gtkmm.h>

#include "../../Layouts.h"
#include "../../Widgets.h"

namespace SketchItApplication {
namespace UI {
namespace Components {

SetUpNotebookTab::SetUpNotebookTab() {}

Gtk::Box* SetUpNotebookTab::createTab(const std::string& titleTxt, const std::string& descTxt) {
  // Build containers
  Gtk::Box* page = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "set-up-page",
      false
  );
  Gtk::Box* pageContainer = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "set-up-container",
      false
  );
  Gtk::ScrolledWindow* descContainer = Widgets::ScrollWin(
      {300, 200},
      "set-up-desc-container",
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START
      ),
      false
  );
  Gtk::Box* contentContainer = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "set-up-content-container",
      false
  );
  Gtk::Box* btnContainer = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "set-up-btn-container",
      false
  );

  // Create text elements
  Gtk::Label* title = Widgets::Label(
      titleTxt,
      "set-up-title",
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, false, Gtk::Align::CENTER, Gtk::Align::CENTER
      )
  );

  Gtk::TextView* desc = Widgets::LongText(
      descTxt,
      "set-up-desc-text",
      {200, 600},
      Gtk::WrapMode::WORD,
      false,
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START
      )
  );

  // Append and return page
  descContainer->set_child(*desc);

  pageContainer->append(*descContainer);
  pageContainer->append(*contentContainer);

  page->append(*title);
  page->append(*pageContainer);
  page->append(*btnContainer);

  return page;
};

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication