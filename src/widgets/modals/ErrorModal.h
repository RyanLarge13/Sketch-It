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

#ifndef ERROR_MODAL
#define ERROR_MODAL

#include <gtkmm.h>

#include "../buttons/ModalBtn.h"

class ErrorModal {
 public:
  // Constructor
  ErrorModal(const std::string& t, const std::string& m, const std::vector <);
  // Member variables
  struct ErrorModalButtons {
    int id;
    std::string txt;
    std::function<void()> func;
    ErrorModalButtons(std::string txt, int id, std::function<void()> func)
        : txt(txt), id(id), func(func) {}
  };
  std::string title;
  std::string message;
  std::vector<ErrorModalButtons> buttons;
  Gtk::Window* errorModal;
  Gtk::Box* container;

  // Methods
  void addBtns(const std::vector<ErrorModalButtons>& btns);

 private:
  // Member variables

  // Methods
  void addLabel();
};

#endif