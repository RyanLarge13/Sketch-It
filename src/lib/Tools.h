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

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace SketchItApplication {

class Tools {
 public:
  Tools();

  // total values within struct 25
  struct ToolDef {
    // Add data type to variant list if future properties are added / remove if tool properties no
    // longer include type after updating
    using ToolPropertiesVariant = std::variant<int, double, bool, std::string>;

    // This map will be used to create a loop-able interface for each tool definition, such as
    // looping over the tool properties and creating widgets for each property. This map includes
    // the variant type defined above

    std::unordered_map<std::string, ToolPropertiesVariant> toolPropsMap;

    // Tool properties ---------------------------------------------------------------
    std::string icon;         // Path to tool icon
    std::string name;         // Tool name
    std::string toolTip;      // Short description
    std::string toolShape;    // circle, fixed, custom, square, triangle, etc....
    std::string toolProfile;  // Defines the shape of the tool tip from the holder, canonical,
                              // pointed, rounded etc...
    std::string rgba;         // color in rgba
    std::string hsl;          // color in hsl
    std::string hex;          // Color in hex
    std::string texture;      // Give each tool a texture. imperfect pencil strokes, smooth marker
                              // strokes, etc..
    std::string desc;         // Tool description
    std::string category;     // pencil, marker, paint brush etc..
    std::string strokeType;   // Solid, dotted, hashed
    std::string drawType;     // vector, stroke, point
    int opacity;              // General purpose opacity
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
    // Tool properties -------------------------------------------------------------

    ToolDef(
        std::string icon,
        std::string name,
        std::string toolTip,
        std::string toolShape,
        std::string toolProfile,
        std::string rgba,
        std::string hsl,
        std::string hex,
        std::string texture,
        std::string desc,
        std::string category,
        std::string strokeType,
        std::string drawType,
        int opacity,
        double minPressure,
        double maxPressure,
        double minWidth,
        double maxWidth,
        double tipDiam,
        double edgeSharpness,
        double smoothing,
        bool additive,
        bool transformative,
        bool subtractive,
        bool custom
    )
        : icon(icon)
        , name(name)
        , toolTip(toolTip)
        , toolShape(toolShape)
        , toolProfile(toolProfile)
        , rgba(rgba)
        , hsl(hsl)
        , hex(hex)
        , texture(texture)
        , desc(desc)
        , category(category)
        , strokeType(strokeType)
        , drawType(drawType)
        , opacity(opacity)
        , minPressure(minPressure)
        , maxPressure(maxPressure)
        , minWidth(minWidth)
        , maxWidth(maxWidth)
        , tipDiam(tipDiam)
        , edgeSharpness(edgeSharpness)
        , smoothing(smoothing)
        , additive(additive)
        , transformative(transformative)
        , subtractive(subtractive)
        , custom(custom)
        , toolPropsMap(
              {{"Icon", icon},
               {"Name", name},
               {"Tool Tip", toolTip},
               {"Tool Shape", toolShape},
               {"Tool Profile", toolProfile},
               {"rgba", rgba},
               {"hsl", hsl},
               {"hex", hex},
               {"Texture", texture},
               {"Description", desc},
               {"Category", category},
               {"StrokeType", strokeType},
               {"DrawType", drawType},
               {"Opacity", opacity},
               {"Min Pressure", minPressure},
               {"Max Pressure", maxPressure},
               {"Min Width", minWidth},
               {"Max Width", maxWidth},
               {"Tip Diam", tipDiam},
               {"Edge Sharpness", edgeSharpness},
               {"Smoothing", smoothing},
               {"Additive", additive},
               {"Transformative", transformative},
               {"Subtractive", subtractive},
               {"Custom", custom}}
          ) {}
  };

  static std::unordered_map<std::string, std::vector<std::shared_ptr<ToolDef>>> categorizedTools;
  static std::vector<ToolDef> defaultTools;
  static std::vector<std::string> toolCategories;
  static void toolsNew();

 protected:
 private:
};

}  // namespace SketchItApplication

#endif