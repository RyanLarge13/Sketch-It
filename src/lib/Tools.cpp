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
    "Pencils",
    "Paints",
    "Pastels",
    "Water Colors",
    "Shaders",
    "Erasers",
    "Oil Paints",
    "Modifiers",
    "Charcols",
    "Markers",
    "Pens",
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
    "Pencils",  // Category
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

Tools::ToolDef charcolPencil = Tools::ToolDef(
    "/assets/charcol-pencil",                               // Icon path
    "Charcol Pencil",                                       // Tool name
    "Charcol pencil that simulates smearing and textures",  // Short description
    "circle",                                               // Tool tip shape
    "pointed",                                              // Tool profile shape to ip from holder
    "0,0,0,1",                                              // RGBA
    "255,255,255",                                          // HSL
    "#000",                                                 // HEX
    "charcol",                                              // Texture
    "Allows artists to simulate closely the charcol smearing and wiping effects in a pencil "
    "shape",    // Long description
    "Pencils",  // Category
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
    "Paints",   // Category
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

Tools::ToolDef pastel = Tools::ToolDef(
    "/assets/2-pencil",   // Icon path
    "Pastel",             // Tool name
    "Standard pastel",    // Short description
    "circle",             // Tool tip shape
    "cylindrical",        // Tool profile shape to ip from holder
    "0,0,0,1",            // RGBA
    "255,255,255",        // HSL
    "#000",               // HEX
    "pastel",             // Texture
    "Oil based pastel ",  // Long description
    "Pastels",            // Category
    "solid",              // Stroke type
    "stroke",             // Drawing type eg: drawing, vector, point
    1,                    // Opacity
    0,                    // Min pressure
    5000,                 // Max pressure
    1,                    // Min width
    50,                   // max width
    2,                    // Tip diameter
    0.25,                 // Edge sharpness
    0.1,                  // Smoothing
    true,                 // Additive
    false,                // Transformative
    false,                // Subtractive
    false                 // Custom
);

Tools::ToolDef eraser = Tools::ToolDef(
    "/assets/eraser",         // Icon path
    "Eraser",                 // Tool name
    "Standard Round Eraser",  // Short description
    "circle",                 // Tool tip shape
    "cylindrical",            // Tool profile shape to ip from holder
    "0,0,0,1",                // RGBA
    "255,255,255",            // HSL
    "#000",                   // HEX
    "null",                   // Texture
    "Standard eraser removes all types of additive material",  // Long description
    "Erasers",                                                 // Category
    "solid",                                                   // Stroke type
    "stroke",  // Drawing type eg: drawing, vector, point
    1,         // Opacity
    0,         // Min pressure
    5000,      // Max pressure
    1,         // Min width
    500,       // max width
    20,        // Tip diameter
    1,         // Edge sharpness
    1,         // Smoothing
    false,     // Additive
    false,     // Transformative
    true,      // Subtractive
    false      // Custom
);

Tools::ToolDef eraserRect = Tools::ToolDef(
    "/assets/eraser",               // Icon path
    "Rectangular Eraser",           // Tool name
    "Standard Rectangular Eraser",  // Short description
    "rect",                         // Tool tip shape
    "canonical",                    // Tool profile shape to ip from holder
    "0,0,0,1",                      // RGBA
    "255,255,255",                  // HSL
    "#000",                         // HEX
    "null",                         // Texture
    "Standard eraser removes all types of additive material with straight edges",  // Long
                                                                                   // description
    "Erasers",                                                                     // Category
    "solid",                                                                       // Stroke type
    "stroke",  // Drawing type eg: drawing, vector, point
    1,         // Opacity
    0,         // Min pressure
    5000,      // Max pressure
    1,         // Min width
    500,       // max width
    20,        // Tip diameter
    1,         // Edge sharpness
    1,         // Smoothing
    false,     // Additive
    false,     // Transformative
    true,      // Subtractive
    false      // Custom
);

Tools::ToolDef shader = Tools::ToolDef(
    "/assets/Shader",                                        // Icon path
    "Shading Tool",                                          // Tool name
    "Standard shading tool",                                 // Short description
    "circle",                                                // Tool tip shape
    "pointed",                                               // Tool profile shape to ip from holder
    "0,0,0,1",                                               // RGBA
    "255,255,255",                                           // HSL
    "#000",                                                  // HEX
    "shader",                                                // Texture
    "Shading tool for creating realistic shading textures",  // Long description
    "Pencils",                                               // Category
    "solid",                                                 // Stroke type
    "stroke",  // Drawing type eg: drawing, vector, point
    1,         // Opacity
    0,         // Min pressure
    5000,      // Max pressure
    1,         // Min width
    50,        // max width
    2,         // Tip diameter
    0.5,       // Edge sharpness
    0.25,      // Smoothing
    true,      // Additive
    false,     // Transformative
    false,     // Subtractive
    false      // Custom
);
// Create the list of default drawing tools for the application

std::vector<Tools::ToolDef> Tools::defaultTools = {
    number2Pencil, paintBrush, pastel, eraser, shader, charcolPencil, eraserRect
};

// Create the list of default drawing tools for the application

Tools::Tools() {}

void Tools::toolsNew() {}

}  // namespace SketchItApplication