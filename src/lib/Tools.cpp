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

// List available default categories all default tools should have
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
    "/assets/2-pencil",          // Icon path
    "Basic Pencil",              // Tool name
    "Standard number 2 pencil",  // Short description
    "circle",                    // Tool tip shape
    "pointed",                   // Tool profile shape to ip from holder
    "0,0,0,1",                   // RGBA
    "255,255,255",               // HSL
    "#000",                      // HEX
    "pencil",                    // Texture
    "A basic number 2 pencil for drawing and sketching effects, simulates real life most "
    "closely",  // Long description
    "Pencil",   // Category
    "solid",    // Stroke type
    "stroke",   // Drawing type eg: drawing, vector, point
    1,          // Opacity
    0,          // Min pressure
    5000,       // Max pressure
    1,          // Min width
    50,         // max width
    2,          // Tip diameter
    0.5,        // Edge sharpness
    0.25,       // Smoothing
    true,       // Additive
    false,      // Transformative
    false,      // Subtractive
    false       // Custom
);

Tools::ToolDef paintBrush = Tools::ToolDef(
    "/assets/2-pencil",     // Icon path
    "Paintbrush",           // Tool name
    "Standard paintbrush",  // Short description
    "circle",               // Tool tip shape
    "pointed",              // Tool profile shape to ip from holder
    "0,0,0,1",              // RGBA
    "255,255,255",          // HSL
    "#000",                 // HEX
    "paint",                // Texture
    "A basic number 2 pencil for drawing and sketching effects, simulates real life most "
    "closely",  // Long description
    "Paint",    // Category
    "solid",    // Stroke type
    "stroke",   // Drawing type eg: drawing, vector, point
    1,          // Opacity
    0,          // Min pressure
    5000,       // Max pressure
    1,          // Min width
    50,         // max width
    2,          // Tip diameter
    0.5,        // Edge sharpness
    0.25,       // Smoothing
    true,       // Additive
    false,      // Transformative
    false,      // Subtractive
    false       // Custom
);
// Create the list of default drawing tools for the application

std::vector<Tools::ToolDef> Tools::defaultTools = {number2Pencil, paintBrush};

// Create the list of default drawing tools for the application

Tools::Tools() {}

void Tools::toolsNew() {}

}  // namespace SketchItApplication