#ifndef SETUP_LAYOUT
#define SETUP_LAYOUT

#include "gtkmm.h"

class SetUpLayout {
 public:
  Gtk::Widget* container;
  Gtk::Widget* sidebar;
  Gtk::Widget* btnContainer;
  Gtk::Widget* buttonCancel;
  Gtk::Widget* buttonAccept;
  Gtk::Widget* canvasSelectContainer;
  Gtk::Widget* canvasSizeBox;
  Gtk::Widget* drawingSelectContainer;
  Gtk::Widget* drawing;

 private:
  void setUpCanvasSelect();
  void setUpImageSelect();
  void setUpButtons();
  std::vector<Gtk::Widget*> getLayout();
};

#endif