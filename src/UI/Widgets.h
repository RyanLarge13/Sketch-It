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

#ifndef WIDGETS
#define WIDGETS

#include "Layouts.h"

namespace SketchItApplication {
namespace UI {

class Widgets {
 public:
  Widgets();

  struct WidgetNotebookTabs {
    Gtk::Box* page;
    Gtk::Label* tabLabel;
    WidgetNotebookTabs(Gtk::Box* page, Gtk::Label* tabLabel) : page(page), tabLabel(tabLabel) {}
  };

  static const std::vector<std::string> setupTabs;

  static Gtk::Notebook* Notebook(
      const std::string& className,
      const std::vector<WidgetNotebookTabs>& tabs,
      const Layouts::LayoutProps& props
  );

  static Gtk::Box* Box(const Layouts::LayoutProps& props, const std::string& className);

  static Gtk::Label* Label(
      const std::string& label, const std::string& className, const Layouts::LayoutProps& props
  );

  static Gtk::TextView* LongText(
      const std::string& text,
      const std::string& className,
      const std::pair<int, int>& size,
      const Gtk::WrapMode& wrapMode,
      const bool& editable,
      const Layouts::LayoutProps& props
  );

  static Gtk::Button* Button(
      const std::string& label,
      const std::string& className,
      std::function<void()> func,
      const Layouts::LayoutProps& props
  );

  static Gtk::ScrolledWindow* ScrollWin(
      const std::pair<int, int>& size,
      const std::string& className,
      const Layouts::LayoutProps& props,
      const bool& horizontal
  );

  static Gtk::Image* Img(
      const std::string& imgPath,
      const std::string& className,
      const int& pixelSize,
      const Layouts::LayoutProps& props
  );

  static Gtk::Grid* Grid(const size_t& rowSpacing, const size_t& columnSpacing);

  static Gtk::Box* GestureBtn(const std::string& className, const Layouts::LayoutProps& props);

 protected:
 private:
};

}  // namespace UI
}  // namespace SketchItApplication

#endif