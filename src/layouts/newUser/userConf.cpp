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

#include "userConf.h"

#include <gtkmm.h>

#include "newUser.h"

UserConf::UserConf() : NewUser() {
  // Define containers for main content
  Gtk::Box* descContainer =
      Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  Gtk::Box* contentContainer =
      Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);

  addDescription(descContainer);
  addContent(contentContainer);

  this->contentContainer->append(*descContainer);
  this->contentContainer->append(*contentContainer);
}

void UserConf::addDescription(Gtk::Box* descContainer) {
  Gtk::Label* descTitle =
      Gtk::make_managed<Gtk::Label>("Creating Configuration");
  descTitle->add_css_class("new-user-desc-title");

  Gtk::TextView* desc = Gtk::make_managed<Gtk::TextView>();
  desc->set_editable(false);
  desc->get_buffer()->set_text(UserConf::descriptionText);

  Gtk::ScrolledWindow* scrollContainer =
      Gtk::make_managed<Gtk::ScrolledWindow>();
  scrollContainer->set_child(*desc);

  descContainer->append(*descTitle);
  descContainer->append(*scrollContainer);
}

void UserConf::addContent(Gtk::Box* contentContainer) {}