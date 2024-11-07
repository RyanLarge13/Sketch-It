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

#include "Layouts.h"

namespace SketchItApplication {
namespace UI {
Layouts::Layouts() {}

// Static constants widget props that
// can be used from outside of the class
// in a easy matter for defining simple
// layouts
Layouts::LayoutProps Layouts::H_FILL = Layouts::LayoutProps(
    Gtk::Orientation::HORIZONTAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
);

Layouts::LayoutProps Layouts::V_FILL = Layouts::LayoutProps(
    Gtk::Orientation::VERTICAL, true, true, Gtk::Align::FILL, Gtk::Align::FILL
);

Layouts::LayoutProps Layouts::H_CONTAIN = Layouts::LayoutProps(
    Gtk::Orientation::HORIZONTAL, false, false, Gtk::Align::START, Gtk::Align::START
);

Layouts::LayoutProps Layouts::V_CONTAIN = Layouts::LayoutProps(
    Gtk::Orientation::VERTICAL, false, false, Gtk::Align::START, Gtk::Align::START
);
// Static constants widget props that
// can be used from outside of the class
// in a easy matter for defining simple
// layouts

}  // namespace UI
}  // namespace SketchItApplication