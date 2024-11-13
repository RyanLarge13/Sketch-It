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

#include "../Monitor/Monitor.h"
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
        Widgets::Label("Welcome", "set-up-tab-title", Layouts::LayoutProps(Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START))
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
          "training session where you left off.\n\n You can change or switch between different kinds of sessions at any time when using the application, so Do not worry about picking the wrong choice"
        ),
        Widgets::Label("Default Session", "set-up-tab-title", Layouts::LayoutProps(Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START))
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
          Widgets::Label("Default Tools", "set-up-tab-title", Layouts::LayoutProps(Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START))
      ),
      Widgets::WidgetNotebookTabs(
          Components::StaticSetUpPage(
            "Finish",
            "Your setup is complete!!! Take some time getting comfortable with the application "
            "and if at any time you would like to update these settings, go to preferences -> settings"
          ),
          Widgets::Label("Finish", "set-up-tab-title", Layouts::LayoutProps(Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START))
      )
  };
  // clang-format on

  // Build notebook with defined static page content above
  Gtk::Notebook* notebook = Widgets::Notebook(
      "set-up-notebook",
      {},
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, false, false, Gtk::Align::FILL, Gtk::Align::FILL
      )
  );

  // Add navigation buttons to notebook tabs
  for (int i = 0; i < tabs.size(); i++) {
    Gtk::Box* btnHolder = UIUtils::grabChildAtIndex<Gtk::Box>(tabs[ i ].page, 2);

    std::vector<Gtk::Button*> btnsToAdd = {Widgets::Button(
        "Close",
        "set-up-btn-cancel",
        [ setUpWindow ]() { setUpWindow->close(); },
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
          [ setUpWindow ]() {
            SketchItApplication::SketchItWindow::saveConfig();
            setUpWindow->close();
          },
          Layouts::LayoutProps(
              Gtk::Orientation::VERTICAL, false, false, Gtk::Align::END, Gtk::Align::END
          )
      ));
    }

    UIUtils::addBtns(btnsToAdd, btnHolder);

    Gtk::Box* spacer = Widgets::Box(
        Layouts::LayoutProps(
            Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        ),
        "null"
    );

    UIUtils::addWidget(btnHolder, spacer, 0);
  }

  // Add to the notebook the latest update to tabs after appending buttons
  for (int i = 0; i < tabs.size(); i++) {
    notebook->append_page(*tabs[ i ].page, *tabs[ i ].tabLabel);
  }

  setUpWindow->set_default_size(
      MonitorManager::Monitor::width * 0.75, MonitorManager::Monitor::height * 0.75
  );
  setUpWindow->set_title("Set Up Sketch It");
  setUpWindow->set_child(*notebook);
  setUpWindow->set_focus(*notebook);

  addMainContent(notebook);

  return setUpWindow;
};

void Components::addMainContent(Gtk::Notebook* notebook) {
  for (int i = 0; i < notebook->get_n_pages() - 1; i++) {
    // Traverse three layers of children to reach the
    // container meant for carrying the page content
    std::cout << "Index in notebook " << i << "\n";
    Gtk::Widget* container = notebook->get_nth_page(i);
    if (container == nullptr) {
      std::cout << "Notebook container does not exist" << "\n";
      continue;
    }
    Gtk::Box* mainContentContainer = UIUtils::grabChildAtIndex<Gtk::Box>(container, 1);
    if (mainContentContainer == nullptr) {
      std::cout << "Main content container does not exist in notebook" << "\n";
      continue;
    }
    Gtk::Box* contentContainer = UIUtils::grabChildAtIndex<Gtk::Box>(mainContentContainer, 1);
    if (contentContainer == nullptr) {
      std::cout << "Content container does not exist in notebook" << "\n";
      continue;
    }

    switch (i) {
      case 0: {
        std::cout << "creating image" << "\n";
        Gtk::Image* img = Gtk::make_managed<Gtk::Image>("assets/images/test1.png");
        std::cout << "inserting image" << "\n";
        Gtk::Box* imgContainer = Widgets::Box(
            Layouts::LayoutProps(
                Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::CENTER, Gtk::Align::CENTER
            ),
            "img-container"
        );
        if (contentContainer == nullptr) {
          std::cout << "NULL content container" << "\n";
        }
        img->set_halign(Gtk::Align::CENTER);
        img->set_valign(Gtk::Align::CENTER);
        img->set_pixel_size(500);
        contentContainer->set_hexpand(true);
        contentContainer->set_vexpand(true);
        imgContainer->append(*img);
        contentContainer->append(*imgContainer);
      } break;
      case 1: {
        defaultSession(contentContainer);
      } break;
      case 2:
        std::cout << "Case 2" << "\n";
        break;
      case 3:
        std::cout << "Case 3" << "\n";
        break;
    }
  }
  return;
}

void Components::defaultSession(Gtk::Box* contentContainer) {
  Gtk::Box* lessons = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::CENTER, Gtk::Align::CENTER
      ),
      "default-session-lesson-container"
  );

  Gtk::Box* freeDraw = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::CENTER, Gtk::Align::CENTER
      ),
      "default-session-free-draw-container"
  );

  Gtk::ScrolledWindow* lessonTxtContainer = Widgets::ScrollWin(
      {300, 200},
      "default-session-desc-text-container",
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::START, Gtk::Align::START
      ),
      false
  );

  Gtk::ScrolledWindow* freehandTxtContainer = Widgets::ScrollWin(
      {300, 200},
      "default-session-desc-text-container",
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::START, Gtk::Align::START
      ),
      false
  );

  Gtk::Image* lessonImg = Gtk::make_managed<Gtk::Image>("assets/images/lesson-learn.png");

  Gtk::TextView* lessonDesc = Widgets::LongText(
      "Choose this option if you are looking to seriously learn the in's and out's of creating "
      "beautiful drawings. Refine your eyes and hands to bring your imagination to life on a piece "
      "of paper, on the computer or anywhere!",
      "default-session-desc-text",
      {200, 400},
      Gtk::WrapMode::WORD,
      false,
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::START, Gtk::Align::START
      )
  );

  Gtk::Image* freeHandImg = Gtk::make_managed<Gtk::Image>("assets/images/free-hand.png");

  // Size, classname props horizontal

  Gtk::TextView* freeHandDesc = Widgets::LongText(
      "Learn how to draw using the computer and a mouse, or if you're really lucky, maybe "
      "you have "
      "a drawing pad to make this experience even more fun. By selecting this option the "
      "application will automatically open up in a blank canvas with your custom tooling "
      "in hand",
      "default-session-desc-text",
      {200, 400},
      Gtk::WrapMode::WORD,
      false,
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::START, Gtk::Align::START
      )
  );

  lessonImg->set_pixel_size(200);
  freeHandImg->set_pixel_size(200);

  lessonTxtContainer->set_child(*lessonDesc);
  freehandTxtContainer->set_child(*freeHandDesc);

  lessons->append(*lessonImg);
  lessons->append(*lessonTxtContainer);

  freeDraw->append(*freeHandImg);
  freeDraw->append(*freehandTxtContainer);

  contentContainer->append(*lessons);
  contentContainer->append(*freeDraw);
}

Gtk::Box* Components::StaticSetUpPage(const std::string& titleTxt, const std::string& descTxt) {
  // Build containers
  Gtk::Box* page = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "set-up-page"
  );
  Gtk::Box* pageContainer = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "set-up-container"
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
      "set-up-content-container"
  );
  Gtk::Box* btnContainer = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "set-up-btn-container"
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
      {200, 400},
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

}  // namespace UI
}  // namespace SketchItApplication