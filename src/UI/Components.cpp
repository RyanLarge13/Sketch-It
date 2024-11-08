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

#include "Components.h"

#include <gtkmm.h>

#include "../SketchIt/SketchItWindow.h"
#include "Layouts.h"
#include "UIUtils.h"
#include "Widgets.h"

namespace SketchItApplication {
namespace UI {

Components::Components() {}

Gtk::Window* Components::ErrorDialog(const std::string& title, const std::string& message) {
  // Custom error modal widget returns
  // transient window of main
  Gtk::Window* errWin = Gtk::make_managed<Gtk::Window>();
  Gtk::Box* container = Widgets::Box(Layouts::H_FILL, "error-modal-message-container");
  Gtk::Label* label = Gtk::make_managed<Gtk::Label>(message);

  label->add_css_class("error-modal-message");
  container->add_css_class("error-modal");
  errWin->set_title(title);

  container->append(*label);
  errWin->set_child(*container);

  return errWin;
};

Gtk::Window* Components::SetUp() {
  // Build the window that will be
  // returned and contain the layout
  Gtk::Window* setUpWindow = Gtk::make_managed<Gtk::Window>();

  // Defining all notebook pages here
  // for custom setup component. Large
  // variable
  // clang-format off
  std::vector<Widgets::WidgetNotebookTabs> tabs = {
      Widgets::WidgetNotebookTabs(
        Components::StaticSetUpPage(
          "Welcome",
          "Welcome to sketch it! Where you will "
          "learn how to draw like a true "
          "artist. You can exit this modal at any time and immediately" 
          "start using this software, but it is highly recommended "
          "that you take a minute or to to configure your setup "
          "and gain the most out of this application"
        ),
        Widgets::Label("Welcome", "set-up-tab-title", Layouts::V_CONTAIN)
      ),
      Widgets::WidgetNotebookTabs(
        Components::StaticSetUpPage(
          "Default Session",
          "Let us set up your default session when "
          "loading the application. Here you can choose from two different options when you "
          "open the app. Starting in drawing mode or training mode. "
          "If you choose drawing mode, your canvas will load up as a blank slate, a larger selection of tools "
          "will be available, and other free hand drawing utilities. "
          "On the other hand, if you choose training, the app will default to opening on your last "
          "training session where you left off."
        ),
        Widgets::Label("Default Session", "set-up-tab-title", Layouts::V_CONTAIN)
      ),
      Widgets::WidgetNotebookTabs(
          Components::StaticSetUpPage(
            "Default Tools",
            "Configure your drawing and painting tools. These tools will be "
            "accessible to you via quick toolbox while using the "
            "application. Here you can define what kind of tool you want available "
            "to you durring each kind of session (free draw or lessons). "
            "You can also build your own tools at the bottom."
          ),
          Widgets::Label("Default Tools", "set-up-tab-title", Layouts::V_CONTAIN)
      ),
      Widgets::WidgetNotebookTabs(
          Components::StaticSetUpPage(
            "Finish",
            "Your setup is complete!!! Take some time getting comfortable with the application "
            "and if at any time you would like to update these settings, go to preferences -> settings"
          ),
          Widgets::Label("Finish", "set-up-tab-title", Layouts::V_CONTAIN)
      )
  };
  // clang-format on

  // Build notebook with defined static page content above
  Gtk::Notebook* notebook = Widgets::Notebook("set-up-notebook", {}, Layouts::V_FILL);

  // Add navigation buttons to notebook tabs
  for (int i = 0; i < tabs.size(); i++) {
    Gtk::Box* btnHolder = UIUtils::grabChildAtIndex(tabs[ i ].page, 2);

    std::vector<Gtk::Button*> btnsToAdd = {Widgets::Button(
        "Close",
        "set-up-btn-cancel",
        [ setUpWindow ]() { setUpWindow->close(); },
        Layouts::H_CONTAIN
    )};

    if (i > 0) {
      btnsToAdd.push_back(Widgets::Button(
          "Back", "set-up-btn-back", [ notebook ]() { notebook->prev_page(); }, Layouts::H_CONTAIN
      ));
    }

    if (i < tabs.size() - 1) {
      btnsToAdd.push_back(Widgets::Button(
          "Next", "set-up-btn-next", [ notebook ]() { notebook->next_page(); }, Layouts::H_CONTAIN
      ));
    }

    if (i == tabs.size() - 1) {
      btnsToAdd.push_back(Widgets::Button(
          "Finish",
          "set-up-btn-finish",
          [ setUpWindow ]() {
            SketchItApplication::SketchItWindow::saveConfig();
            setUpWindow->close();
          },
          Layouts::H_CONTAIN
      ));
    }
  }

  // Add to the notebook the latest update to tabs after appending buttons
  for (int i = 0; i < tabs.size(); i++) {
    notebook->append_page(*tabs[ i ].page, *tabs[ i ].tabLabel);
  }

  setUpWindow->set_title("Set Up Sketch It");
  setUpWindow->set_child(*notebook);

  return setUpWindow;
};

Gtk::Box* Components::StaticSetUpPage(const std::string& titleTxt, const std::string& descTxt) {
  // Build containers
  Gtk::Box* page = Widgets::Box(Layouts::V_FILL, "set-up-page");
  Gtk::Box* pageContainer = Widgets::Box(Layouts::H_FILL, "set-up-container");
  Gtk::Box* descContainer = Widgets::Box(Layouts::V_CONTAIN, "set-up-desc-container");
  Gtk::Box* contentContainer = Widgets::Box(Layouts::V_FILL, "set-up-content-container");
  Gtk::Box* btnContainer = Widgets::Box(Layouts::H_FILL, "set-up-btn-container");

  // Create text elements
  Gtk::Label* title = Widgets::Label(titleTxt, "set-up-title", Layouts::H_FILL);

  Gtk::TextView* desc = Widgets::LongText(
      descTxt, "set-up-desc-text", {200, 400}, Gtk::WrapMode::WORD, false, Layouts::V_FILL
  );

  // Append and return page
  descContainer->append(*desc);

  pageContainer->append(*descContainer);
  pageContainer->append(*contentContainer);

  page->append(*title);
  page->append(*pageContainer);
  page->append(*btnContainer);

  return page;
};

}  // namespace UI
}  // namespace SketchItApplication