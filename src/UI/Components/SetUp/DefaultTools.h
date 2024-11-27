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

#ifndef DEFAULT_TOOLS
#define DEFAULT_TOOLS

#include <gtkmm.h>

#include "../../../lib/Tools.h"

namespace SketchItApplication {
namespace UI {
namespace Components {

// TODO:
// How do I want to define the application default drawing tools?
// Think about this one and probably store these in a more global
// setting

class DefaultTools {
 public:
  DefaultTools();

  struct StringFromVariantVisitor {
    std::string operator()(int value) const { return std::to_string(value); }

    std::string operator()(double value) const { return std::to_string(value); }

    std::string operator()(bool value) const { return value ? "true" : "false"; }

    std::string operator()(const std::string& value) const { return value; }
  };

  static void create(Gtk::Box* contentContainer);
  static std::vector<std::shared_ptr<Tools::ToolDef>> selectedTools;
  static std::vector<Gtk::Box*> toolTips;

 protected:
  static Gtk::ScrolledWindow* buildCategoryGUI();
  static Gtk::Box* buildToolBtn(const std::shared_ptr<Tools::ToolDef>& tool);
  static void buildToolTip(Gtk::Box* toolBtn, const std::shared_ptr<Tools::ToolDef>& tool);
  static Gtk::Grid* buildToolTipProperties(const std::shared_ptr<Tools::ToolDef>& tool);
  static void buildSelectableBtn(Gtk::Box* toolBtn, const std::shared_ptr<Tools::ToolDef>& tool);

 private:
};

}  // namespace Components
}  // namespace UI
}  // namespace SketchItApplication

#endif