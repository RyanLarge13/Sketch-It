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
      {0, 300},
      "canvas-default-select",
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      true
  );

  Gtk::Grid* gridContainer = Widgets::Grid(20, 20, "canvas-default-grid");

  addButtons(gridContainer);

  scrollHWin->set_child(*gridContainer);

  Gtk::Box* inputContainer = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
      ),
      "canvas-default-size-input-container"
  );

  addInputsAndSelect(inputContainer);

  contentContainer->set_orientation(Gtk::Orientation::VERTICAL);

  contentContainer->append(*scrollHWin);
  contentContainer->append(*inputContainer);
}

void CanvasDefault::addButtons(Gtk::Grid* gridContainer) {
  std::vector<Gtk::Box*> btns;

  for (int i = 0; i < iconsAndSizes.size(); i++) {
    Gtk::Box* customBtn = Widgets::Box(
        Layouts::LayoutProps(
            Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        ),
        "canvas-default-select-btn"
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

    btns.push_back(customBtn);
  }

  addGestures(btns);

  for (int i = 0; i < btns.size(); i++) {
    gridContainer->attach(*btns[ i ], i, 0, 1, 1);
  }
}

void CanvasDefault::addGestures(const std::vector<Gtk::Box*>& btns) {
  for (int i = 0; i < btns.size(); i++) {
    Glib::RefPtr<Gtk::GestureClick> gesture_click = Gtk::GestureClick::create();
    Glib::RefPtr<Gtk::EventControllerMotion> gesture_hover = Gtk::EventControllerMotion::create();

    auto click = [ btns, i ](const int& z, const double& x, const double& y) {
      for (int j = 0; j < btns.size(); j++) {
        if (j == i) {
          btns[ j ]->add_css_class("selected");
          // TODO:
          // Update user data to include selected btn
        } else {
          btns[ j ]->remove_css_class("selected");
        }
      }
    };

    auto hover = [ btns ](const double& x, const double& y) {
      for (int j = 0; j < btns.size(); j++) {
        btns[ j ]->set_cursor("pointer");
      }
    };

    gesture_click->signal_released().connect(click);

    gesture_hover->signal_enter().connect(hover);

    btns[ i ]->add_controller(gesture_click);
    btns[ i ]->add_controller(gesture_hover);
  }
}

void CanvasDefault::addInputsAndSelect(Gtk::Box* inputContainer) {
  Gtk::Label* title = Widgets::Label(
      "Custom Size",
      "canvas-default-input-container-title",
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START
      )
  );

  Gtk::Box* wBox = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, false, false, Gtk::Align::START, Gtk::Align::START
      ),
      "null"
  );
  Gtk::Box* hBox = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, false, false, Gtk::Align::START, Gtk::Align::START
      ),
      "null"
  );

  Gtk::Label* wLabel = Widgets::Label(
      "Width: ",
      "null",
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, false, false, Gtk::Align::START, Gtk::Align::CENTER
      )
  );

  Gtk::Label* hLabel = Widgets::Label(
      "Height: ",
      "null",
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, false, false, Gtk::Align::START, Gtk::Align::CENTER
      )
  );

  Gtk::SpinButton* width = Widgets::SpinButton(
      Gtk::Adjustment::create(5.0, 5.0, 30.0, 0.5), 1.0, 5.0, "canvas-default-input"
  );
  Gtk::SpinButton* height = Widgets::SpinButton(
      Gtk::Adjustment::create(5.0, 5.0, 30.0, 0.5), 1.0, 5.0, "canvas-default-input"
  );

  width->set_halign(Gtk::Align::START);
  height->set_halign(Gtk::Align::START);

  wBox->append(*wLabel);
  wBox->append(*width);

  hBox->append(*hLabel);
  hBox->append(*height);

  inputContainer->append(*title);
  inputContainer->append(*wBox);
  inputContainer->append(*hBox);

  // TODO:
  //  Make sure if the user goes to input any values it clears the
  //  button selection, and updates the input if one of the buttons
  //  are
  //  selected.------------------------------------------------------------------------------------------------------------------------------------------
}

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication
