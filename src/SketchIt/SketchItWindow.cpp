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

#include "SketchItWindow.h"

#include <iostream>

#include "../Files/Config.h"
#include "../Monitor/Monitor.h"
#include "SketchIt.h"

namespace SketchItApplication {

SketchItWindow::SketchItWindow() {
  // Set the global main window to the current instance
  win = this;

  set_title("Sketch It");
  signal_realize().connect(sigc::mem_fun(*this, &SketchItWindow::setUp));
}

void SketchItWindow::setUp() {
  // Set up window size && load configuration
  MonitorManager::Monitor monitor;
  monitor.init(this);
  set_default_size(monitor.width, monitor.height);

  SketchItWindow::loadMainAppUI();
  SketchItWindow::checkConfig();
}

void SketchItWindow::loadMainAppUI() {}

void SketchItWindow::checkConfig() {
  using namespace Files;

  // Check logs after config initialization in SketchIt Application
  std::vector<ConfigManager::EventLog> logs = SketchIt::config.getLog();

  for (const ConfigManager::EventLog& log : logs) {
    if (log.status < 3) {
      std::cout << "Error detected: " << log.status << "\n"
                << log.message << "\n";

      // Show error dialog for failed configuration file read/write/create
      Gtk::Window* error =
          UI::Widgets::ErrorDialog("Configuration Error", log.message);

      std::vector<Gtk::Button*> btns = {UI::Widgets::Button(
                                            "Okay",
                                            "error-modal-btn",
                                            [ this ]() { this->close(); },
                                            UI::Widgets::H_FILL),
          UI::Widgets::Button(
              "Close",
              "error-modal-btn",
              [ this ]() { this->close(); },
              UI::Widgets::H_FILL)};

      Gtk::Box* btnContainer =
          UI::Widgets::Box(UI::Widgets::H_FILL, "error-modal-btn-container");

      UI::Widgets::addBtns(btns, btnContainer);

      dynamic_cast<Gtk::Box*>(error->get_child())->append(btnContainer);

      error->set_transient_for(*this);
      error->show();
      break;
    }
    if (log.status == ConfigManager::StatusCodes::NEW_USER) {
      // Load setup window for new users
      Gtk::Window* setupWin = UI::Widgets::SetUp();

      setupWin->set_transient_for(*this);
      setupWin->show();

      SketchItWindow::guideSetUp(setUpWin);
    }
  }
}

SketchItWindow::guideSetUp(Gtk::Window* setUpInstance) {
  Gtk::Notebook* notebook = setUpInstance->get_child();

  // Grab number of pages in the static notebook set up from Widgets::Notebook
  // iterate and add btn logic
  for (int i = 0; i < notebook->get_n_pages; i++) {
    Gtk::Box* btnContainer =
        Widgets::grabChildAtIndex(*notebook->get_nth_page(i), 2);

    // Append buttons with click logic to the current notebook page
    // clang-format off
    Widgets::addBtns(
      { Widgets::Button(
          "Close",
          "set-up-btn-close",
          [ setUpInstance ]() { setUpInstance->close(); },
          Widgets::H_CONTAIN
        ),
        Widgets::Button(
          "Next",
          "set-up-btn-next",
          [ notebook ]() { notebook->next_page() },
          Widgets::H_CONTAIN
        )
      },
      *btnContainer);
    // clang-format on
  }
}

}  // namespace SketchItApplication