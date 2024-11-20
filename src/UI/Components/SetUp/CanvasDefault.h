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

#ifndef CANVAS_DEFAULT
#define CANVAS_DEFAULT

#include <gtkmm.h>

namespace SketchItApplication {
namespace UI {
namespace Components {

class CanvasDefault {
 public:
  CanvasDefault();

  struct ImageAndSizes {
    std::string imgPath;
    std::pair<double, double> size;
    int index;

    ImageAndSizes(
        const std::string& imgPath, const std::pair<double, double>& size, const int& index
    )
        : imgPath(imgPath), size(size), index(index) {}
  };

  static std::vector<Gtk::Box*> canvasBtns;
  static Gtk::SpinButton* widthInput;
  static Gtk::SpinButton* heightInput;
  static std::pair<double, double> prevSelection;

  static void create(Gtk::Box* contentContainer);

 protected:
  static void addButtons(Gtk::Grid* gridContainer);
  static void addGestures();
  static void addInputsAndSelect(Gtk::Box* inputContainer);

  static void updateBtns(const double& width, const double& height);
  static void updateInput(const double& width, const double& height);

 private:
};

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication

#endif