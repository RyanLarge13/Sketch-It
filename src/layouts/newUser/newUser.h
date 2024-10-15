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

class NewUser {
 public:
  NewUser(Gtk::Window* window);
  void initLayout();
  void setTitle(const std::string& newTitle);
  void setBtns(const std::vector<std::string>& btns);

  Gtk::Window* win;
  Gtk::Box* mainContainer;
  Gtk::Box* titleContainer;
  Gtk::Box* contentContainer;
  Gtk::Box* btnContainer;

 private:
};

#endif