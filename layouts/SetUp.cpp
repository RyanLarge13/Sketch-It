#include "SetUp.h"

#include <vector>

SetUp::SetUp() {
  setUpCanvasSelect();
  setUpImageSelect();
  setUpButtons();
}

void setUpCanvasSelect() {
  canvasSelectContainer =
      Gtk::make_managed<Gtk::Box*>(Gtk::ORIENTATION::VERTICAL);
}

void setUpImageSelect() {
  drawingSelectContainer =
      Gtk::make_managed<Gtk::Box*>(Gtk::ORIENTATION::VERTICAL);
}

void setUpButtons() {
  btnContainer = Gtk::make_managed<Gtk::Box*>(Gtk::ORIENTATION::HORIZONTAL);
  buttonCancel = Gtk::make_managed<Gtk::Button>("Cancel");
  buttonAccept = Gtk::make_managed<Gtk::Button>("Accept");
}

std::vector<Gtk::Widget*> getLayout() {}