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

#include "./CanvasDefault.h"

#include <gtkmm.h>

#include "../../Layouts.h"
#include "../../Widgets.h"

namespace SketchItApplication {
namespace UI {
namespace Components {

std::vector<CanvasDefault::ImageAndSizes> iconsAndSizes = {
    CanvasDefault::ImageAndSizes("null", "5in x 5in", 0),
    CanvasDefault::ImageAndSizes("null", "5in x 7in", 1),
    CanvasDefault::ImageAndSizes("null", "7in x 7in", 2),
    CanvasDefault::ImageAndSizes("null", "7in x 10in", 3),
    CanvasDefault::ImageAndSizes("null", "10in x 10in", 4),
    CanvasDefault::ImageAndSizes("null", "8in x 11in", 5),
    CanvasDefault::ImageAndSizes("null", "11in x 8in", 6),
    CanvasDefault::ImageAndSizes("null", "10in x 7in", 7),
    CanvasDefault::ImageAndSizes("null", "10in x 5in", 8),
    CanvasDefault::ImageAndSizes("null", "7in x 4in", 9),
};

CanvasDefault::CanvasDefault() {}

void CanvasDefault::create(Gtk::Box* contentContainer) {
  Gtk::ScrolledWindow* scrollHWin = Widgets::ScrollWin(
      {0, 0},
      "canvas-default-select",
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      true
  );

  Gtk::Grid* gridContainer = Widgets::Grid(10, 10);

  addButtons(gridContainer);

  scrollHWin->set_child(*gridContainer);

  contentContainer->append(*scrollHWin);
}

void CanvasDefault::addButtons(Gtk::Grid* gridContainer) {
  for (int i = 0; i < iconsAndSizes.size(); i++) {
    Gtk::Box* customBtn = Widgets::GestureBtn(
        "canvas-default-select-button",
        Layouts::LayoutProps(
            Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        )
    );

    Gtk::Label* sizeTxt = Widgets::Label(
        iconsAndSizes[ i ].size,
        "canvas-default-size-text",
        Layouts::LayoutProps(
            Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        )
    );

    Gtk::Image* canvasImage = Widgets::Img(
        "assets/images/canvas-size.png",
        "null",
        200,
        Layouts::LayoutProps(
            Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        )
    );

    customBtn->set_size_request(200, 250);
    customBtn->append(*canvasImage);
    customBtn->append(*sizeTxt);

    gridContainer->attach(*customBtn, i, 0, 1, 1);
  }
}

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication
