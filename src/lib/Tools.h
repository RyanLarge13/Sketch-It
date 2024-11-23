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

#ifndef TOOLS
#define TOOLS

#include <string>
#include <vector>

namespace SketchItApplication {

class Tools {
 public:
  Tools();

  struct ToolDef {
    std::string icon;        // Path to tool icon
    std::string name;        // Tool name
    std::string toolTip;     // Short description
    std::string toolShape;   // circle, fixed, custom, square, triangle, etc....
    std::string rgba;        // color in rgba
    std::string hsl;         // color in hsl
    std::string hex;         // Color in hex
    std::string texture;     // Give each tool a texture. imperfect pencil strokes, smooth marker
                             // strokes, etc..
    std::string desc;        // Tool description
    std::string category;    // pencil, marker, paint brush etc..
    std::string strokeType;  // Solid, dotted, hashed
    std::string drawType;    // vector, stroke, point
    int opacity;             // General purpose opacity
    double minPressure;  // Give each tool a min pressure, regulate different tool material, metal,
                         // led, etc..
    double maxPressure;  // Give each tool a max pressure, regulate different tool material, metal,
                         // led, etc..
    double minWidth;     // Give each tool a min width
    double maxWidth;  // Give each tool a max width, Limit the growth in size when pressed down hard
    double tipDiam;
    double edgeSharpness;  // Wil the stokes appear perfect, jagged, smooth, or blurry
    double smoothing;      // Adjust natural smoothness around the outlines of the stroke
    bool additive;         // Does the tool draw
    bool transformative;   // Does the tool manipulate current paths
    bool subtractive;      // Does the tool erase paths
    bool custom;           // is this tool a default tool or custom made?

    // UI Feedback give small GIF of stroke
    // tilt effects?
    // Speed effects
    // Hot keys
  };

  static std::vector<ToolDef> defaultTools;
  static std::vector<std::string> toolCategories;
  static void toolsNew();

 protected:
 private:
};

}  // namespace SketchItApplication

#endif