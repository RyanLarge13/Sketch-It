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
  win = this;
  set_title("Sketch It");
  signal_realize().connect(sigc::mem_fun(*this, &SketchItWindow::setUp));
}

void SketchItWindow::setUp() {
  MonitorManager::Monitor monitor;
  monitor.init(this);
  set_default_size(monitor.width, monitor.height);

  SketchItWindow::checkConfig();
}

void SketchItWindow::checkConfig() {
  using namespace Files;

  std::vector<ConfigManager::EventLog> logs = SketchIt::config.getLog();

  for (const ConfigManager::EventLog& log : logs) {
    if (log.status < 3) {
      std::cout << "Error detected: " << log.status << "\n"
                << log.message << "\n";

      // Show error dialog for failed configuration file read/write/create
      Gtk::Window* error =
          UI::Widgets::ErrorDialog("Configuration Error", log.message);

      std::vector<Gtk::Button*> btns = {
          UI::Widgets::Button(
              "Okay", "error-modal-btn", [ this ]() { this->close(); },
              UI::Widgets::EXPAND_FILL),
          UI::Widgets::Button(
              "Close", "error-modal-btn", [ this ]() { this->close(); },
              UI::Widgets::EXPAND_FILL)};

      Gtk::Box* btnContainer = UI::Widgets::Box(
          UI::Widgets::EXPAND_FILL, "error-modal-btn-container");

      UI::Widgets::addBtns(
          btns, btnContainer, dynamic_cast<Gtk::Box*>(error->get_child()));

      error->set_transient_for(*this);
      error->show();
      break;
    }
    if (log.status == ConfigManager::StatusCodes::NEW_USER) {
      std::cout << "New user" << "\n";
    }
  }
}

}  // namespace SketchItApplication