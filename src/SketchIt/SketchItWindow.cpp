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

#include "../Monitor/Monitor.h"

namespace SketchItApplication {

SketchItWindow::SketchItWindow() {
  win = this;
  set_title("Sketch It");
  signal_realize().connect(sigc::mem_fun(*this, &SketchItWindow::setUpMonitor));
}

void SketchItWindow::setUpMonitor() {
  MonitorManager::Monitor monitor;
  set_default_size(monitor.width, monitor.height);
}

}  // namespace SketchItApplication