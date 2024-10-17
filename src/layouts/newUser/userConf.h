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

#ifndef USER_CONF
#define USER_CONF

#include <gtkmm.h>

#include "newUser.h"

class UserConf : public NewUser {
 protected:
  UserConf();

 private:
  void addDescription(Gtk::Box* descContainer);
  void addContent(Gtk::Box* contentContainer);

  std::string descriptionText =
      "Welcome to Sketch It. You are now in the setup wizard. We Will help you "
      "go through all the steps necessary to make sure that you gain the most "
      "out of using this application. Please follow through the wizard before "
      "entering the application. We will begin be filling out a few fields to "
      "give us an idea of what you are looking for out of this app";
};

#endif