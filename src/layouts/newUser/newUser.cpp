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

#include "newUser.h"

#include <gtkmm.h>

#include "../../widgets/ModalBtn.h"
#include "userConf.h"

NewUser::NewUser(Gtk::Window* window) : win(window) {}

void NewUser::initLayout() {
  // Create main containers to nest within NewUser->win->mainContainer;
  mainContainer = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  titleContainer = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  contentContainer = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
  btnContainer = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);

  // Set current stage UI
  setStage(1);

  // Append containers to main
  mainContainer->append(*titleContainer);
  mainContainer->append(*contentContainer);
  mainContainer->append(*btnContainer);

  // Set main container as win child
  win->set_child(*mainContainer);
}

void NewUser::setStage(const NewUser::NewUserStage& stage) {
  currentStage = stage;
  switch (currentStage) {
    case NewUser::NewUserStage::USER_CONF:
      UserConf();
      break;
    case NewUser::NewUserStage::SESSION_DEFAULTS:
      break;
    case NewUser::NewUserStage::CANVAS_DEFAULTS:
      break;
    case NewUser::NewUserStage::IMAGE_PACKS:
      break;
    case NewUser::NewUserStage::TOOL_DEFAULTS:
      break;
    default:
      break;
  }
}