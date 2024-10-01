#include <GL/gl.h>
#include <gtkmm.h>

#include <iostream>

#include "../includes/gl.h"

class MyWindow : public Gtk::Window {
 public:
  enum USER_STATE {
    FREE_HAND,
    LEARN,
  };
  struct MenuButtons {
    std::string label;
    std::string classname;
    void (MyWindow::*onClick)(Gtk::Button*);

    MenuButtons(const std::string& lbl, const std::string& cls,
        void (MyWindow::*func)(Gtk::Button*))
        : label(lbl), classname(cls), onClick(func) {}
  };

  MyWindow() {
    set_title("Sketch it");
    signal_realize().connect(
        sigc::mem_fun(*this, &MyWindow::setDefaultScreenSize));
    Glib::RefPtr<Gtk::GestureClick> gesture = Gtk::GestureClick::create();
    gesture->set_button(0);
    gesture->signal_pressed().connect(
        sigc::mem_fun(*this, &MyWindow::mouseClickGeneric));
    applyCSS();
    Gtk::Box* mainBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    set_child(*mainBox);
    buildMenuBar(mainBox);
    setUpWorkArea(mainBox);
    add_controller(gesture);
    initializeWorkArea(*this);
  }

 private:
  // class globals
  MyGLCanvas gl_canvas;
  Glib::RefPtr<Gtk::CssProvider> css_provider;
  Gtk::Popover popover;
  Gtk::Box* workAreaBox;
  Gtk::Box* sidebar;
  Gtk::Box* toolbar;
  Gtk::Box* topBar;
  Gtk::Box* bottomBar;
  Gtk::Button* menu_btn_clicked = nullptr;
  Gtk::FileChooserDialog* fileChooser;
  std::pair<int, int> dems = std::make_pair(1250, 900);

  bool sidebarShow = true;
  bool toolbarShow = true;
  bool fullScreenOn = false;
  bool topBarShow = true;
  bool bottomBarShow = true;

  void setDefaultScreenSize() {
    auto display = Gdk::Display::get_default();
    if (!display) {
      set_default_size(dems.first, dems.second);
      return;
    }
    auto monitor = display->get_monitor_at_surface(get_surface());
    if (!monitor) {
      set_default_size(dems.first, dems.second);
      return;
    }
    Gdk::Rectangle monitor_geometry;
    monitor->get_geometry(monitor_geometry);
    const size_t width = monitor_geometry.get_width();
    const size_t height = monitor_geometry.get_height();
    set_default_size(width, height);
    dems.first = width;
    dems.second = height;
  }

  void applyCSS() {
    css_provider = Gtk::CssProvider::create();
    try {
      css_provider->load_from_path("../styles/global.css");
    } catch (const Glib::Error& err) {
      std::cerr << "Error loading css files: " << err.what() << "\n";
    }
    auto display = Gdk::Display::get_default();
    Gtk::StyleContext::add_provider_for_display(
        display, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
  }

  void buildMenuBar(Gtk::Box* mainBox) {
    Gtk::Box* menuBar =
        Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    menuBar->get_style_context()->add_class("custom-menu-bar");
    mainBox->append(*menuBar);
    static const std::vector<MenuButtons> btns = {
        {"File", "menu-item", &MyWindow::on_file_clicked},
        {"Edit", "menu-item", &MyWindow::on_edit_clicked},
        {"View", "menu-item", &MyWindow::on_view_clicked}};
    for (const MenuButtons& btn : btns) {
      Gtk::Button* newBtn = Gtk::make_managed<Gtk::Button>(btn.label);
      newBtn->get_style_context()->add_class(btn.classname);
      newBtn->signal_clicked().connect(
          sigc::bind(sigc::mem_fun(*this, btn.onClick), newBtn));
      menuBar->append(*newBtn);
    }
  }

  void setUpWorkArea(Gtk::Box* mainBox) {
    workAreaBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    buildTopBar(mainBox);
    mainBox->append(*workAreaBox);
    buildToolBar();
    buildCanvas();
    buildSideBar();
    buildBottomBar(mainBox);
  }

  void buildTopBar(Gtk::Box* mainBox) {
    topBar = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    topBar->set_size_request(-1, 40);
    topBar->set_hexpand(true);
    topBar->set_vexpand(false);
    topBar->get_style_context()->add_class("top-bar");
    mainBox->append(*topBar);
  }

  void buildBottomBar(Gtk::Box* mainBox) {
    topBar = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    topBar->set_size_request(-1, 40);
    topBar->set_hexpand(true);
    topBar->set_vexpand(false);
    topBar->get_style_context()->add_class("bottom-bar");
    mainBox->append(*topBar);
  }

  void buildToolBar() {
    toolbar = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    toolbar->set_size_request(80, -1);
    toolbar->set_hexpand(false);
    toolbar->set_vexpand(true);
    toolbar->get_style_context()->add_class("tool-bar");
    workAreaBox->append(*toolbar);
  }

  void buildCanvas() {
    Gtk::Box* canvas =
        Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    canvas->set_hexpand(true);
    canvas->set_vexpand(true);
    canvas->set_size_request(-1, -1);
    canvas->get_style_context()->add_class("canvas");
    gl_canvas.set_hexpand(true);
    gl_canvas.set_vexpand(true);
    canvas->append(gl_canvas);
    workAreaBox->append(*canvas);
  }

  void buildSideBar() {
    sidebar = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    sidebar->set_size_request(dems.first / 3, -1);
    sidebar->set_hexpand(false);
    sidebar->set_vexpand(true);
    sidebar->get_style_context()->add_class("tool-bar");
    workAreaBox->append(*sidebar);
  }

  void setUpPopover(Gtk::Box* menu, const std::vector<MenuButtons>& menuBtns) {
    for (const MenuButtons& btn : menuBtns) {
      Gtk::Button* newBtn = Gtk::make_managed<Gtk::Button>(btn.label);
      newBtn->get_style_context()->add_class(btn.classname);
      newBtn->signal_clicked().connect(
          sigc::bind(sigc::mem_fun(*this, btn.onClick), newBtn));
      menu->append(*newBtn);
    }
    popover.set_child(*menu);
    popover.set_parent(*menu_btn_clicked);
    popover.set_position(Gtk::PositionType::BOTTOM);
    popover.signal_hide().connect([ this ] {
      popover.unparent();
      menu_btn_clicked = nullptr;
    });
    popover.show();
  }

  void on_file_clicked(Gtk::Button* clicked_btn) {
    menu_btn_clicked = clicked_btn;
    Gtk::Box* fileMenu =
        Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    static const std::vector<MenuButtons> fileMenuBtns = {
        {"New File", "menu-item-small", &MyWindow::new_file},
        {"Open File", "menu-item-small", &MyWindow::open_file},
        {"Save File", "menu-item-small", &MyWindow::save},
        {"Quit", "menu-item-small", &MyWindow::quit_app}};
    setUpPopover(fileMenu, fileMenuBtns);
  }

  void on_edit_clicked(Gtk::Button* clicked_btn) {
    menu_btn_clicked = clicked_btn;
    Gtk::Box* editMenu =
        Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    static const std::vector<MenuButtons> editMenuBtns = {
        {"Copy", "menu-item-small", &MyWindow::cop},
        {"Paste", "menu-item-small", &MyWindow::paste},
        {"Cut", "menu-item-small", &MyWindow::cut},
        {"Delete", "menu-item-small", &MyWindow::del}};
    setUpPopover(editMenu, editMenuBtns);
  }

  void on_view_clicked(Gtk::Button* clicked_btn) {
    menu_btn_clicked = clicked_btn;
    Gtk::Box* editMenu =
        Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    static const std::vector<MenuButtons> editMenuBtns = {
        {fullScreenOn ? "Exit Full Screen" : "Full Screen", "menu-item-small",
            &MyWindow::full_screen},
        {sidebarShow ? "Hide Sidebar" : "Show Sidebar", "menu-item-small",
            &MyWindow::toggle_side_bar},
        {toolbarShow ? "Hide Toolbar" : "Show Toolbar", "menu-item-small",
            &MyWindow::hide_tool_bar}};
    setUpPopover(editMenu, editMenuBtns);
  }

  // File menu button signals
  void new_file(Gtk::Button* btnClicked) {
    popover.hide();
    // Is the user in a new window context or have changes been made?
    Glib::RefPtr<Gtk::AlertDialog> dialog = Gtk::AlertDialog::create(
        "Are you sure you want to open a new file before saving?");
    dialog->set_buttons({{"Cancel"}, {"Confirm"}});
    dialog->set_cancel_button(0);
    dialog->set_default_button(0);
    dialog->choose(
        *this, [ dialog ](const Glib::RefPtr<Gio::AsyncResult>& result) {
          int response = dialog->choose_finish(result);
          std::cout << response << "\n";
          if (response == 1) {
            // Clear canvas do not save file reset the board
          }
          if (response == 0) {
            return;
          }
        });
  }

  void open_file(Gtk::Button* btnClicked) {
    popover.hide();
    fileChooser = new Gtk::FileChooserDialog(
        *this, "Open an image file", Gtk::FileChooser::Action::OPEN);
    fileChooser->add_button("_Cancel", Gtk::ResponseType::CANCEL);
    fileChooser->add_button("_Open", Gtk::ResponseType::ACCEPT);
    fileChooser->signal_response().connect(
        sigc::mem_fun(*this, &MyWindow::handle_file_open_new));
    fileChooser->present();
  }

  void save(Gtk::Button*) { std::cout << "Save File clicked!" << std::endl; }

  void quit_app(Gtk::Button*) { MyWindow::close(); }

  // Edit button signals

  void cop(Gtk::Button*) {}

  void paste(Gtk::Button*) {}

  void cut(Gtk::Button*) {}

  void del(Gtk::Button*) {}

  // View button signals

  void full_screen(Gtk::Button* clickedBtn) {
    if (fullScreenOn == false) {
      fullscreen();
      clickedBtn->set_label("Exit Full Screen");
      fullScreenOn = true;
    } else {
      unfullscreen();
      clickedBtn->set_label("Full Screen");
      fullScreenOn = false;
    }
  }

  void toggle_side_bar(Gtk::Button* clickedBtn) {
    if (sidebarShow) {
      clickedBtn->set_label("Show Sidebar");
      sidebar->set_visible(false);
      sidebarShow = false;
      return;
    } else {
      clickedBtn->set_label("Hide Sidebar");
      sidebar->set_visible(true);
      sidebarShow = true;
      return;
    }
  }

  void hide_tool_bar(Gtk::Button* clickedBtn) {
    if (toolbarShow) {
      clickedBtn->set_label("Show Toolbar");
      toolbar->set_visible(false);
      toolbarShow = false;
    } else {
      clickedBtn->set_label("Hide Toolbar");
      toolbar->set_visible(true);
      toolbarShow = true;
    }
  }

  // Handle various file chooser methods

  void handle_file_open_new(int responseId) {
    if (responseId == Gtk::ResponseType::ACCEPT) {
      std::cout << "Open new file from explorer!!" << "\n";
      auto file = fileChooser->get_file();
    } else {
      fileChooser->close();
      fileChooser = nullptr;
      std::cout << "Closed file explorer" << "\n";
    }
  }

  // Handling generic events

  void mouseClickGeneric(int pressed, double x, double y) {
    std::cout << "generic mouse click" << "\n";
  }

  // Handling work area setup with user input

  void initializeWorkArea(Gtk::Window& window) {
    Gtk::Dialog setUpDialog = Gtk::Dialog("Set Up", window, true);
    setUpDialog.set_default_size(600, 400);
    setUpDialog.show();
    std::cout << "Running dialog" << "\n";
  }
};

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("org.gtkmm.example");
  MyWindow window;
  return app->make_window_and_run<MyWindow>(argc, argv);
}
