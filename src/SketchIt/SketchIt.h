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

#ifndef SKETCH_IT
#define SKETCH_IT

#include "../Files/Config.h"
#include "../Files/Files.h"
#include "../Renderer/Canvas.h"
#include "../Styles/Styles.h"
#include "../UI/UI.h"
#include "gtkmm.h"

namespace SketchItApplication {
class SketchIt : public Gtk::Application {
 public:
  static Glib::RefPtr<SketchIt> create();
  SketchIt();

 protected:
  void on_startup() override;
  void on_activate() override;

 private:
  Glib::RefPtr<Gtk::CssProvider> css_provider;
  void setUpApp();
  void setDefaultScreenSize();
  void applyGlobalCSS();
  void setUpNewUser();
  void setUpSession();
  void reloadApp();
  void loadConfig();

  // Load classes using namespaces and use them
  // throughout the app
  SketchItApplication::Files::ConfigManager config;
  SketchItApplication::UI::UIManager uiManager;
  SketchItApplication::UI::Styles styleSheets;
  SketchItApplication::CanvasManager::Canvas canvas;
};
}  // namespace SketchItApplication

#endif