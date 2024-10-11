#include "./CustomWindow.h"

#include <gtkmm.h>

#include <iostream>

// Constructor methods
CustomWindow::CustomWindow(const std::string& title,
    const std::string& iconName, const CustomWindow::Size& defaultSize,
    const bool& decorated, const std::vector<Gtk::Widget*>& children)
    : title(title),
      iconName(iconName),
      defaultSize(defaultSize),
      decorated(decorated),
      children(children) {}

// Public methods

bool CustomWindow::setChild(const Gtk::Widget*& child) { return false };

bool CustomWindow::setChildren(const std::vector<Gtk::Widget*>& children) {
  return false;
}

bool CustomWindow::removeChild() { return false; }

Gtk::Window* CustomWindow::getWindow() { return window; }

Gtk::Widget* CustomWindow::getChild() { return Gtk::Button("Test return"); }

// Private methods
