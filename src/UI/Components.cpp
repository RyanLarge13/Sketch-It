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

#include "Layouts.h"
#include "Widgets.h"

namespace SketchItApplication {
namespace UI {
static Gtk::Window* Components::ErrorDialog(const std::string& title, const std::string& message) {
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

static Gtk::Window* Components::SetUp() {
  // Build the window that will be
  // returned and contain the layout
  Gtk::Window* setUpWindow = Gtk::make_managed<Gtk::Window>();

  // Defining all notebook pages here
  // for custom setup component. Large
  // variable
  // clang-format off
  std::vector<Widgets::WidgetNotebookTabs> tabs = {
      Widgets::WidgetNotebookTabs(
        Widgets::StaticSetUpPage(
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
        Widgets::StaticSetUpPage(
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
          Widgets::StaticSetUpPage(
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
          Widgets::StaticSetUpPage(
            "Finish",
            "Your setup is complete!!! Take some time getting comfortable with the application "
            "and if at any time you would like to update these settings, go to preferences -> settings"
          ),
          Widgets::Label("Finish", "set-up-tab-title", Layouts::V_CONTAIN)
      )
  };
  // clang-format on

  Gtk::Notebook* notebook = Widgets::Notebook("set-up-notebook", tabs, Layouts::V_FILL);

  setUpWindow->set_title("Set Up Sketch It");
  setUpWindow->set_child(*notebook);

  return setUpWindow;
};

static Gtk::Box* Components::StaticSetUpPage(
    const std::string& titleTxt, const std::string& descTxt
) {
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