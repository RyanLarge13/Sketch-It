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

#include "./DefaultSession.h"

#include <gtkmm.h>

#include "../../Layouts.h"
#include "../../Widgets.h"

namespace SketchItApplication {
namespace UI {
namespace Components {

DefaultSession::DefaultSession() {}

void DefaultSession::create(Gtk::Box* contentContainer) {
  Gtk::Box* lessons = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::CENTER, Gtk::Align::CENTER
      ),
      "default-session-lesson-container",
      true
  );

  Gtk::Box* freeDraw = Widgets::Box(
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::CENTER, Gtk::Align::CENTER
      ),
      "default-session-free-draw-container",
      true
  );

  Glib::RefPtr<Gtk::GestureClick> gesture_click_lessons = Gtk::GestureClick::create();
  Glib::RefPtr<Gtk::GestureClick> gesture_click_freehand = Gtk::GestureClick::create();

  gesture_click_lessons->signal_released().connect(
      [ lessons, freeDraw ](const int& z, const double& x, const double& y) {
        lessons->add_css_class("selected");
        freeDraw->remove_css_class("selected");
      }
  );

  gesture_click_freehand->signal_released().connect(
      [ lessons, freeDraw ](const int& z, const double& x, const double& y) {
        freeDraw->add_css_class("selected");
        lessons->remove_css_class("selected");
      }
  );

  lessons->add_controller(gesture_click_lessons);
  freeDraw->add_controller(gesture_click_freehand);

  Gtk::Label* lessonHeading = Widgets::Label(
      "Lessons",
      "default-session-heading",
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::START, Gtk::Align::START
      )
  );
  Gtk::Label* freeDrawHeading = Widgets::Label(
      "FreeHand",
      "default-session-heading",
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::START, Gtk::Align::START
      )
  );

  Gtk::ScrolledWindow* lessonTxtContainer = Widgets::ScrollWin(
      {300, 200},
      "default-session-desc-text-container",
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::START, Gtk::Align::END
      ),
      false
  );

  Gtk::ScrolledWindow* freehandTxtContainer = Widgets::ScrollWin(
      {300, 200},
      "default-session-desc-text-container",
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::START, Gtk::Align::END
      ),
      false
  );

  Gtk::Image* lessonImg = Widgets::Img(
      "assets/images/lesson-img.png",
      "lesson-desc-img",
      200,
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::CENTER, Gtk::Align::CENTER
      )
  );

  Gtk::TextView* lessonDesc = Widgets::LongText(
      "Choose this option if you are looking to seriously learn the in's and out's of creating "
      "beautiful drawings. Refine your eyes and hands to bring your imagination to life on a piece "
      "of paper, on the computer or anywhere!",
      "default-session-desc-text",
      {200, 400},
      Gtk::WrapMode::WORD,
      false,
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::START, Gtk::Align::END
      )
  );

  Gtk::Image* freeHandImg = Widgets::Img(
      "assets/images/freehand-img.png",
      "free-hand-desc-img",
      200,
      Layouts::LayoutProps(
          Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::CENTER, Gtk::Align::CENTER
      )
  );

  // Size, classname props horizontal

  Gtk::TextView* freeHandDesc = Widgets::LongText(
      "Learn how to draw using the computer and a mouse, or if you're really lucky, maybe "
      "you have "
      "a drawing pad to make this experience even more fun. By selecting this option the "
      "application will automatically open up in a blank canvas with your custom tooling "
      "in hand",
      "default-session-desc-text",
      {200, 400},
      Gtk::WrapMode::WORD,
      false,
      Layouts::LayoutProps(
          Gtk::Orientation::VERTICAL, true, true, Gtk::Align::START, Gtk::Align::END
      )
  );

  lessonTxtContainer->set_child(*lessonDesc);
  freehandTxtContainer->set_child(*freeHandDesc);

  lessons->append(*lessonImg);
  lessons->append(*lessonHeading);
  lessons->append(*lessonTxtContainer);

  freeDraw->append(*freeHandImg);
  freeDraw->append(*freeDrawHeading);
  freeDraw->append(*freehandTxtContainer);

  contentContainer->append(*lessons);
  contentContainer->append(*freeDraw);
}

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication