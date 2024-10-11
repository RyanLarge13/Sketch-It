#ifndef CUSTOM_WINDOW
#define CUSTOM_WINDOW

#include <gtkmm.h>

#include <iostream>

class CustomWindow : Gtk::Window {
 public:
  // Member variables
  struct Size {
    int height;
    int width;
    Size(int w, int h) : width(w), height(h) {}
  };
  bool decorated;
  Size defaultSize;
  Gtk::Window* window;
  std::vector<Gtk::Widget*> children;
  std::string title;
  std::string iconName;

  // Constructor
  CustomWindow(const std::string& title, const std::string& iconName,
      const Size& defaultSize, const bool& decorated,
      std::vector<Gtk::Widget*> children);

  // Methods
  bool setChild();
  bool setChildren(const std::vector<Gtk::Widget*>& children);
  bool removeChild();
  Gtk::Widget* getChild();
  Gtk::Window* getWindow();

 private:
  // Constructor methods
  // Member variables
  // Methods
};

#endif