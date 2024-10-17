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

#ifndef NEW_USER
#define NEW_USER

#include <gtkmm.h>

#include <vector>

#include "../Layouts.h"

class NewUser : public Layouts {
 public:
  NewUser();
  void initLayout();

  enum NewUserStage : int {
    USER_CONF_DEFAULTS = 1,
    SESSION_DEFAULTS,
    CANVAS_DEFAULTS,
    IMAGE_PACKS,
    TOOL_DEFAULTS,
  };

  int currentStage = 1;
  Gtk::Window* win;
  Gtk::Box* mainContainer;
  Gtk::Box* titleContainer;
  Gtk::Box* contentContainer;
  Gtk::Box* btnContainer;

  void setStage(const NewUserStage& stage);

 private:
};

#endif