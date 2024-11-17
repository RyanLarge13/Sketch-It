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
#include "../UI/Components/ErrorModal.h"
#include "../UI/Components/SetUp/SetUp.h"
#include "../UI/Layouts.h"
#include "../UI/UIUtils.h"
#include "../UI/Widgets.h"
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

void SketchItWindow::loadMainAppUI() {
  Gtk::Box* mainWinContainer = UI::Widgets::Box(
      UI::Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "main-win-container"
  );

  this->set_child(*mainWinContainer);
}

void SketchItWindow::checkConfig() {
  using namespace Files;

  // Check logs after config initialization in SketchIt Application
  std::vector<ConfigManager::EventLog> logs = SketchIt::config.getLog();

  for (const ConfigManager::EventLog& log : logs) {
    if (log.status < 3) {
      std::cout << "Error detected: " << log.status << "\n" << log.message << "\n";

      // Show error dialog for failed configuration file read/write/create
      Gtk::Window* error = UI::Components::ErrorModal::create("Configuration Error", log.message);

      Gtk::Box* btnContainer = UI::Widgets::Box(
          UI::Layouts::LayoutProps(
              Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::END
          ),
          "error-modal-btn-container"
      );

      UI::UIUtils::addBtns(
          {UI::Widgets::Button(
               "Okay",
               "error-modal-btn",
               [ this ]() { this->close(); },
               UI::Layouts::LayoutProps(
                   Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::CENTER
               )
           ),
           UI::Widgets::Button(
               "Close",
               "error-modal-btn",
               [ this ]() { this->close(); },
               UI::Layouts::LayoutProps(
                   Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::CENTER
               )
           )},
          btnContainer
      );

      dynamic_cast<Gtk::Box*>(error->get_child())->append(*btnContainer);

      error->set_transient_for(*this);
      error->show();
      break;
    }
    if (log.status == ConfigManager::StatusCodes::NEW_USER) {
      // Load setup window for new users
      UI::Components::SetUp();

      UI::Components::SetUp::setUpWindow->set_transient_for(*this);
      UI::Components::SetUp::setUpWindow->show();
    }
  }
}

void SketchItWindow::saveConfig() { return; }

}  // namespace SketchItApplication
