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

#include "./Tools.h"

namespace SketchItApplication {

std::vector<std::string> Tools::toolCategories = {
    "Pencil",
    "Paint",
    "Pastel",
    "Water Colors",
    "Shaders",
    "Erasers",
    "Oil Paints",
    "Modifiers",
    "Charcol",
    "Markers",
    "Pen",
    "Colored Pencils"
};

// Create the list of default drawing tools for the application
Tools::ToolDef number2Pencil = Tools::ToolDef(
    "/assets/2-pencil",
    "Basic Pencil",
    "Standard number 2 pencil",
    "circle",
    "0,0,0,1",
    "255,255,255",
    "#000",
    "Pencil",
    "A basic number 2 pencil for drawing and sketching effects, simulates real life most closely",
    "pencil",
    "solid",
    "stroke",
    1,
    0,
    5000,
    1,
    50,
    2,
    0.5,
    0.25,
    true,
    false,
    false,
    false
);

std::vector<Tools::ToolDef> Tools::defaultTools = {number2Pencil};

// Create the list of default drawing tools for the application

Tools::Tools() {}

void Tools::toolsNew() {}

}  // namespace SketchItApplication