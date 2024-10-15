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

#ifndef MODAL_BTN
#define MODAL_BTN

#include <gtkmm.h>

class ModalBtn : Gtk::Button {
 public:
  struct ModalBtnProps {
    const std::string& txt;
    const std::string& iconName;
    const bool& vexpand;
    const bool& hexpand;
    const Gtk::Align& valign;
    const Gtk::Align& halign;
    const std::function<void()>& onClick

    ModalBtnProps(const std::string& txt, const std::string& iconName,
        const bool& vexpand, const bool& hexpand, const Gtk::Align& valign,
        const Gtk::Align& halign, const std::function<void()>& onClick)
        : txt(txt),
          iconName(iconName),
          vexpand(vector),
          hexpand(hexpand),
          valign(valign),
          halign(halign),
          onClick(onClick) {}
  };

  ModalBtn(const ModalBtnProps& props);

 private:
}

#endif  // !MODAL_BTN