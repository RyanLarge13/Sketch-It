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

// UI namespace defines two classes, theme && widgets

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

  struct WidgetLayoutProps {
    Gtk::Orientation orientation;
    bool hexpand;
    bool vexpand;
    Gtk::Align halign;
    Gtk::Align valign;
    WidgetLayoutProps(
        const Gtk::Orientation& orientation,
        const bool& hexpand,
        const bool& vexpand,
        const Gtk::Align& halign,
        const Gtk::Align& valign
    )
        : orientation(orientation)
        , hexpand(hexpand)
        , vexpand(vexpand)
        , halign(halign)
        , valign(valign) {}
  };

  // Constant notebook tabs
  static const std::vector<std::string> setupTabs;

  // Definitions for constant WidgetLayoutProps
  static WidgetLayoutProps H_FILL;
  static WidgetLayoutProps V_FILL;
  static WidgetLayoutProps H_CONTAIN;
  static WidgetLayoutProps V_CONTAIN;

  // Application default windows -------------------------------------------
  static Gtk::Window* ErrorDialog(const std::string& title, const std::string& message);

  static Gtk::Window* SetUp();

  static Gtk::Box* StaticSetUpPage(const std::string& titleTxt, const std::string& descTxt);

  // Custom widgets ------------------------------------------

  static Gtk::Notebook* Notebook(
      const std::string& className,
      const std::vector<WidgetNotebookTabs>& tabs,
      const WidgetLayoutProps& props
  );

  static Gtk::Box* Box(const WidgetLayoutProps& props, const std::string& className);

  static Gtk::Label* Label(
      const std::string& label, const std::string& className, const WidgetLayoutProps& props
  );

  static Gtk::TextView* LongText(
      const std::string& text,
      const std::string& className,
      const std::pair<int, int>& size,
      const Gtk::WrapMode& wrapMode,
      const bool& editable,
      const WidgetLayoutProps& props
  );

  static Gtk::Button* Button(
      const std::string& label,
      const std::string& className,
      std::function<void()> func,
      const WidgetLayoutProps& props
  );

  // Methods --------------------------------------------------------
  static void addBtns(const std::vector<Gtk::Button*>& btns, Gtk::Box* container);

  static Gtk::Box* grabChildAtIndex(Gtk::Widget* parent, const int& index);

 protected:
 private:
};

// SEPARATOR BETWEEN CLASSES UNDER NAMESPACE UI (WIDGETS && THEME CLASSES)

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
