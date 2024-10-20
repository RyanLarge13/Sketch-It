
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

#include "Styles.h"

#include <gtkmm.h>

#include <iostream>

namespace SketchItApplication {
namespace UI {
Styles::Styles(const std::string& cssFilePath) {
  Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
  try {
    css_provider->load_from_path(cssFilePath);
  } catch (const Glib::Error& err) {
    std::cerr << "Error loading css files: " << err.what() << "\n";
  }
  Glib::RefPtr<Gdk::Display> display = Gdk::Display::get_default();
  Gtk::StyleContext::add_provider_for_display(
      display, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
}
}  // namespace UI
}  // namespace SketchItApplication