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
  static void addBtns(const std::vector<Gtk::Button*>& btns, Gtk::Box* container);
  static Gtk::Box* grabChildAtIndex(Gtk::Widget* parent, const int& index);

  static Gtk::Notebook* Notebook(
      const std::string& className,
      const std::vector<WidgetNotebookTabs>& tabs,
      const LayoutProps& props
  );

  static Gtk::Box* Box(const LayoutProps& props, const std::string& className);

  static Gtk::Label* Label(
      const std::string& label, const std::string& className, const LayoutProps& props
  );

  static Gtk::TextView* LongText(
      const std::string& text,
      const std::string& className,
      const std::pair<int, int>& size,
      const Gtk::WrapMode& wrapMode,
      const bool& editable,
      const LayoutProps& props
  );

  static Gtk::Button* Button(
      const std::string& label,
      const std::string& className,
      std::function<void()> func,
      const LayoutProps& props
  );

 protected:
 private:
}
}  // namespace UI
}  // namespace SketchItApplication

#endif