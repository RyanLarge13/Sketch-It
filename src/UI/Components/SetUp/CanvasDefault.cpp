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

// TODO
// Why store index information on the iconsAndSizes vector if I am not going to use them?
// Use it and clean up your code, or get rid of it

#include "./CanvasDefault.h"

#include <gtkmm.h>

#include <iostream>

#include "../../Layouts.h"
#include "../../Widgets.h"

namespace SketchItApplication {
namespace UI {
namespace Components {

std::vector<Gtk::Box*> CanvasDefault::canvasBtns;
Gtk::SpinButton* CanvasDefault::widthInput;
Gtk::SpinButton* CanvasDefault::heightInput;
std::pair<double, double> prevSelection = {8.0, 11.0};

std::vector<CanvasDefault::ImageAndSizes> iconsAndSizes = {
    CanvasDefault::ImageAndSizes("null", {5.0, 5.0}, 0),
    CanvasDefault::ImageAndSizes("null", {5.0, 7.0}, 1),
    CanvasDefault::ImageAndSizes("null", {7.0, 7.0}, 2),
    CanvasDefault::ImageAndSizes("null", {7.0, 10.0}, 3),
    CanvasDefault::ImageAndSizes("null", {10.0, 10.0}, 4),
    CanvasDefault::ImageAndSizes("null", {8.0, 11.0}, 5),
    CanvasDefault::ImageAndSizes("null", {11.0, 8.0}, 6),
    CanvasDefault::ImageAndSizes("null", {10.0, 7.0}, 7),
    CanvasDefault::ImageAndSizes("null", {10.0, 5.0}, 8),
    CanvasDefault::ImageAndSizes("null", {7.0, 4.0}, 9),
};

CanvasDefault::CanvasDefault() {}

void CanvasDefault::create(Gtk::Box* contentContainer) {
  canvasBtns.reserve(10);

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
      "canvas-default-size-input-container",
      false
  );

  addInputsAndSelect(inputContainer);

  contentContainer->set_orientation(Gtk::Orientation::VERTICAL);

  contentContainer->append(*scrollHWin);
  contentContainer->append(*inputContainer);
}

void CanvasDefault::addButtons(Gtk::Grid* gridContainer) {
  for (int i = 0; i < iconsAndSizes.size(); i++) {
    Gtk::Box* customBtn = Widgets::Box(
        Layouts::LayoutProps(
            Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
        ),
        "canvas-default-select-btn",
        true
    );

    std::ostringstream ss;
    ss << iconsAndSizes[ i ].size.first << "in X " << iconsAndSizes[ i ].size.second << "in";

    std::string sizeStr = ss.str();

    Gtk::Label* sizeTxt = Widgets::Label(
        sizeStr,
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

    if (i == 5) {
      customBtn->add_css_class("selected");
    }

    canvasBtns.push_back(customBtn);
  }

  addGestures();

  for (int i = 0; i < canvasBtns.size(); i++) {
    gridContainer->attach(*canvasBtns[ i ], i, 0, 1, 1);
  }
}

void CanvasDefault::addGestures() {
  for (int i = 0; i < canvasBtns.size(); i++) {
    Glib::RefPtr<Gtk::GestureClick> gesture_click = Gtk::GestureClick::create();
    Glib::RefPtr<Gtk::EventControllerMotion> gesture_hover = Gtk::EventControllerMotion::create();

    auto click = [ i ](const int& z, const double& x, const double& y) {
      for (int j = 0; j < canvasBtns.size(); j++) {
        if (j == i) {
          canvasBtns[ j ]->add_css_class("selected");
          updateInput(iconsAndSizes[ j ].size.first, iconsAndSizes[ j ].size.second);
          // TODO:
          // Update user data to include selected btn
        } else {
          canvasBtns[ j ]->remove_css_class("selected");
        }
      }
    };

    auto hover = [](const double& x, const double& y) {
      for (int j = 0; j < canvasBtns.size(); j++) {
        canvasBtns[ j ]->set_cursor("pointer");
      }
    };

    gesture_click->signal_released().connect(click);

    gesture_hover->signal_enter().connect(hover);

    canvasBtns[ i ]->add_controller(gesture_click);
    canvasBtns[ i ]->add_controller(gesture_hover);
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
      "null",
      false
  );
  Gtk::Box* hBox = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, false, false, Gtk::Align::START, Gtk::Align::START
      ),
      "null",
      false
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

  widthInput = Widgets::SpinButton(
      Gtk::Adjustment::create(8.0, 5.0, 30.0, 0.5), 1.0, 8.0, "canvas-default-input"
  );
  heightInput = Widgets::SpinButton(
      Gtk::Adjustment::create(11.0, 5.0, 30.0, 0.5), 1.0, 11.0, "canvas-default-input"
  );

  widthInput->signal_value_changed().connect([]() {
    for (int i = 0; i < canvasBtns.size(); i++) {
      canvasBtns[ i ]->remove_css_class("selected");
    }
    updateBtns(widthInput->get_value(), heightInput->get_value());
  });

  heightInput->signal_value_changed().connect([]() {
    for (int i = 0; i < canvasBtns.size(); i++) {
      canvasBtns[ i ]->remove_css_class("selected");
    }
    updateBtns(widthInput->get_value(), heightInput->get_value());
  });

  widthInput->set_halign(Gtk::Align::START);
  heightInput->set_halign(Gtk::Align::START);

  wBox->append(*wLabel);
  wBox->append(*widthInput);

  hBox->append(*hLabel);
  hBox->append(*heightInput);

  inputContainer->append(*title);
  inputContainer->append(*wBox);
  inputContainer->append(*hBox);
}

// Updating methods for input and custom buttons that can be attached to elements via signals for
// easy updates

void CanvasDefault::updateBtns(const double& width, const double& height) {
  // Search formatching dimension being input with an existing custom button dimension
  for (int i = 0; i < canvasBtns.size(); i++) {
    if (iconsAndSizes[ i ].size.first == width && iconsAndSizes[ i ].size.second == height) {
      canvasBtns[ i ]->add_css_class("selected");
    }
  }
}

void CanvasDefault::updateInput(const double& width, const double& height) {
  widthInput->set_value(width);
  heightInput->set_value(height);
}

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication
