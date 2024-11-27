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

#include "./SetUp.h"

#include <gtkmm.h>

#include "../../../SketchIt/SketchItWindow.h"
#include "../../Layouts.h"
#include "../../UIUtils.h"
#include "../../Widgets.h"
#include "../ErrorModal.h"
#include "./CanvasDefault.h"
#include "./CustomTools.h"
#include "./DefaultSession.h"
#include "./DefaultTools.h"
#include "./SetUpNotebookTab.h"

namespace SketchItApplication {
namespace UI {
namespace Components {

Gtk::Window* SetUp::setUpWindow = nullptr;

SetUp::SetUp() {
  // Create default set up window information and initializes
  setUpWindow = Gtk::make_managed<Gtk::Window>();
  setUpWindow->set_default_size(1300, 500);
  setUpWindow->set_title("Set Up Sketch It");

  initSetUpWindow();
}

void SetUp::initSetUpWindow() {
  // Grab the pre defined notebook tabs for set up notebook
  const std::vector<Widgets::WidgetNotebookTabs> tabs = getSetUpTabs();

  // Build the notebook
  Gtk::Notebook* notebook = Widgets::Notebook(
      "set-up-notebook",
      {},
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, false, false, Gtk::Align::FILL, Gtk::Align::FILL
      )
  );

  // Build the window navigation buttons
  buildNavigation(notebook, tabs);

  // Append tabs to notebook
  for (int i = 0; i < tabs.size(); i++) {
    notebook->append_page(*tabs[ i ].page, *tabs[ i ].tabLabel);
  }

  // Append notebook to main window
  setUpWindow->set_child(*notebook);
  setUpWindow->set_focus(*notebook);

  // Create tab specific content
  addMainContent(notebook);
}

std::vector<Widgets::WidgetNotebookTabs> SetUp::getSetUpTabs() {
  return {
      Widgets::WidgetNotebookTabs(
          Components::SetUpNotebookTab::createTab(
              "Welcome",
              "Welcome to sketch it! Where you will "
              "learn how to draw like a true "
              "artist. You can exit this modal at any time and immediately"
              "start using this software, but it is highly recommended "
              "that you take a minute or to to configure your setup "
              "and gain the most out of this application"
          ),
          Widgets::Label(
              "Welcome",
              "set-up-tab-title",
              Layouts::LayoutProps(
                  Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START
              )
          )
      ),
      Widgets::WidgetNotebookTabs(
          Components::SetUpNotebookTab::createTab(
              "Default Session",
              "Let us set up your default session when "
              "loading the application. Here you can choose from two different options when you "
              "open the app. Starting in drawing mode or training mode. "
              "If you choose drawing mode, your canvas will load up as a blank slate, a larger "
              "selection of tools "
              "will be available, and other free hand drawing utilities. "
              "On the other hand, if you choose training, the app will default to opening on your "
              "last "
              "training session where you left off.\n\n You can change or switch between different "
              "kinds of sessions at any time when using the application, so Do not worry about "
              "picking the wrong choice"
          ),
          Widgets::Label(
              "Default Session",
              "set-up-tab-title",
              Layouts::LayoutProps(
                  Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START
              )
          )
      ),
      Widgets::WidgetNotebookTabs(
          Components::SetUpNotebookTab::createTab(
              "Canvas",
              "Of course, you can always change this later as you draw or before any time you open "
              "the application, but let's take the time to set up a default canvas for you that "
              "you will have loaded up automatically as the page loads. This will be the size of "
              "canvas you are most comfortable working in on a daily basis. You can always change "
              "your default canvas size later down the road as well within your own settings"
          ),
          Widgets::Label(
              "Canvas Setup",
              "set-up-tab-title",
              Layouts::LayoutProps(
                  Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START
              )
          )
      ),
      Widgets::WidgetNotebookTabs(
          Components::SetUpNotebookTab::createTab(
              "Default Tools",
              "Configure your drawing and painting tools. These tools will be "
              "accessible to you via quick toolbox while using the "
              "application. Here you can define what kind of tool you want available "
              "to you durring each kind of session (free draw or lessons). "
              "You can also build your own tools at the bottom."
          ),
          Widgets::Label(
              "Default Tools",
              "set-up-tab-title",
              Layouts::LayoutProps(
                  Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START
              )
          )
      ),
      Widgets::WidgetNotebookTabs(
          Components::SetUpNotebookTab::createTab(
              "Build Tools",
              "Skip this section if you do not want to build your own custom tools to draw with "
              "and are happy with the built in tools provided with the app. Otherwise, get "
              "creative with your tooling and give yourself the best possible experience within "
              "the app and your learning adventure. Here you can configure every aspect your your "
              "tool and how it meets the canvas and it will be saved in your settings.\n\n You can "
              "build new tools at anytime under your art set tab."
          ),
          Widgets::Label(
              "Custom Tools",
              "set-up-tab-title",
              Layouts::LayoutProps(
                  Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START
              )
          )
      ),
      Widgets::WidgetNotebookTabs(
          Components::SetUpNotebookTab::createTab(
              "Lesson Packs",
              "Usually each lesson is split into different sections based on experience or how far "
              "you have gone through completing your education within the app. With these lessons "
              "and the mini lessons within each section there are hundreds of different training "
              "images that will be used. To incorporate them into the application it is best to "
              "install them in sets.\n\n When first installing the application it comes with a "
              "default set of training images to get you started and automatically installs sets "
              "as you progress and deletes old ones to help prevent taking up too much room on "
              "your hard drive. You can configure this behavior in many ways in this tab."
          ),
          Widgets::Label(
              "Lesson Packs",
              "set-up-tab-title",
              Layouts::LayoutProps(
                  Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START
              )
          )
      ),
      Widgets::WidgetNotebookTabs(
          Components::SetUpNotebookTab::createTab(
              "Misc Settings",
              "Here you can define miscellaneous settings that are important to consider when "
              "using the application in either the free draw mode or the lesson mode.\n\n Such "
              "as\n - measurement units\n - themes\n - styling and more."
          ),
          Widgets::Label(
              "Miscellaneous",
              "set-up-tab-title",
              Layouts::LayoutProps(
                  Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START
              )
          )
      ),
      Widgets::WidgetNotebookTabs(
          Components::SetUpNotebookTab::createTab(
              "Finish",
              "Your setup is complete!!! Take some time getting comfortable with the application "
              "and if at any time you would like to update these settings, go to preferences -> "
              "settings"
          ),
          Widgets::Label(
              "Finish",
              "set-up-tab-title",
              Layouts::LayoutProps(
                  Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START
              )
          )
      )
  };
}

void SetUp::buildNavigation(
    Gtk::Notebook* notebook, const std::vector<Widgets::WidgetNotebookTabs>& tabs
) {
  // Add navigation buttons appending next, cancel, finish and back buttons depending on the tab
  // that is navigated

  for (int i = 0; i < tabs.size(); i++) {
    Gtk::Box* btnHolder = UIUtils::grabChildAtIndex<Gtk::Box>(tabs[ i ].page, 2);

    std::vector<Gtk::Button*> btnsToAdd = {Widgets::Button(
        "Close",
        "set-up-btn-cancel",
        []() {
          // TODO
          //  Make sure this also happens when the user exits the window by native x button

          // Check which parts of the configuration have not been finished
          Gtk::Window* confirmQuitSetUpModal = Components::ErrorModal::create(
              "Quit Set Up?",
              "You have not finished setting up your enviornment. Are you sure you want to stop "
              "now? It will only take a few seconds"
          );

          std::vector<Gtk::Button*> modalBtns = {
              Widgets::Button(
                  "Confirm",
                  "error-modal-accept",
                  [ confirmQuitSetUpModal ]() {
                    // TODO:
                    //  Save configuration that has been done at least
                    confirmQuitSetUpModal->close();
                    setUpWindow->close();
                  },
                  Layouts::LayoutProps(
                      Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
                  )
              ),
              Widgets::Button(
                  "Cancel",
                  "error-modal-decline",
                  [ confirmQuitSetUpModal ]() { confirmQuitSetUpModal->close(); },
                  Layouts::LayoutProps(
                      Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
                  )
              )
          };

          UIUtils::addBtns(
              modalBtns, UIUtils::grabChildAtIndex<Gtk::Box>(confirmQuitSetUpModal, 0)
          );

          confirmQuitSetUpModal->set_transient_for(*setUpWindow);
          confirmQuitSetUpModal->show();
        },
        Layouts::LayoutProps(
            Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::END
        )
    )};

    if (i > 0) {
      btnsToAdd.push_back(Widgets::Button(
          "Back",
          "set-up-btn-back",
          [ notebook ]() { notebook->prev_page(); },
          Layouts::LayoutProps(
              Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::END
          )
      ));
    }

    if (i < tabs.size() - 1) {
      btnsToAdd.push_back(Widgets::Button(
          "Next",
          "set-up-btn-next",
          [ notebook ]() { notebook->next_page(); },
          Layouts::LayoutProps(
              Gtk::Orientation::VERTICAL, false, false, Gtk::Align::END, Gtk::Align::END
          )
      ));
    }

    if (i == tabs.size() - 1) {
      btnsToAdd.push_back(Widgets::Button(
          "Finish",
          "set-up-btn-finish",
          []() {
            SketchItApplication::SketchItWindow::saveConfig();
            setUpWindow->close();
          },
          Layouts::LayoutProps(
              Gtk::Orientation::VERTICAL, false, false, Gtk::Align::END, Gtk::Align::END
          )
      ));
    }

    UIUtils::addBtns(btnsToAdd, btnHolder);

    // Create and append a spacer between cancel and other buttons for
    // an intuitive and safe user layout
    Gtk::Box* spacer = Widgets::Box(
        Layouts::LayoutProps(
            Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        ),
        "null",
        false
    );

    UIUtils::addWidget(btnHolder, spacer, 0);
  }
}

void SetUp::addMainContent(Gtk::Notebook* notebook) {
  for (int i = 0; i < notebook->get_n_pages() - 1; i++) {
    // Traverse three layers of children to reach the
    // container meant for carrying the tab content
    Gtk::Widget* container = notebook->get_nth_page(i);
    if (container == nullptr) {
      continue;
    }
    Gtk::Box* mainContentContainer = UIUtils::grabChildAtIndex<Gtk::Box>(container, 1);
    if (mainContentContainer == nullptr) {
      continue;
    }
    Gtk::Box* contentContainer = UIUtils::grabChildAtIndex<Gtk::Box>(mainContentContainer, 1);
    if (contentContainer == nullptr) {
      continue;
    }

    switch (i) {
      case 0: {
        Gtk::Image* img = Widgets::Img(
            "assets/images/test1.png",
            "null",
            500,
            Layouts::LayoutProps(
                Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::CENTER, Gtk::Align::CENTER
            )
        );
        Gtk::Box* imgContainer = Widgets::Box(
            Layouts::LayoutProps(
                Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::CENTER, Gtk::Align::CENTER
            ),
            "img-container",
            false
        );
        if (contentContainer == nullptr) {
          std::cout << "NULL content container when appending image to Welcome tab" << "\n";
        }
        imgContainer->append(*img);
        contentContainer->append(*imgContainer);
      } break;
      case 1: {
        Components::DefaultSession::create(contentContainer);
      } break;
      case 2: {
        Components::CanvasDefault::create(contentContainer);
      } break;
      case 3: {
        Components::DefaultTools::create(contentContainer);
      }
      case 4: {
        Components::CustomTools::create(contentContainer);
      }
    }
  }
}

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication