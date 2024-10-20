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

#ifndef UI_H
#define UI_H

#include <gtkmm.h>

namespace SketchItApplication {
namespace UI {

class Widgets {
 public:
  Widgets();

  struct WidgetLayoutProps {
    Gtk::Orientation orientation;
    bool hexpand;
    bool vexpand;
    Gtk::Align halign;
    Gtk::Align valign;
    WidgetLayoutProps(const Gtk::Orientation& orientation, const bool& hexpand,
        const bool& vexpand, const Gtk::Align& halign, const Gtk::Align& valign)
        : orientation(orientation),
          hexpand(hexpand),
          vexpand(vexpand),
          halign(halign),
          valign(valign) {}
  };

  static WidgetLayoutProps EXPAND_FILL;
  static WidgetLayoutProps CONTAIN;

  static Gtk::Window* ErrorDialog(
      const std::string& title, const std::string& message);

  static Gtk::Box* Box(
      const WidgetLayoutProps& props, const std::string& className);

  static Gtk::Button* Button(const std::string& label,
      const std::string& className, std::function<void()> func,
      const WidgetLayoutProps& props);

  static void addBtns(const std::vector<Gtk::Button*>& btns,
      Gtk::Box* container, Gtk::Box* parent);

 protected:
 private:
};

class Themes {
 public:
  Themes();

  std::string getSystemTheme();

 protected:
 private:
};
}  // namespace UI
}  // namespace SketchItApplication

#endif