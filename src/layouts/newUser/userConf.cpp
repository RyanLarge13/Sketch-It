#include "userConf.h"

UserConf::UserConf() {
  // Define containers for main content
  Gtk::Box* descContainer =
      Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  Gtk::Box* contentContainer =
      Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);

  addDescription(*descContainer);
  addContent(*contentContainer);

  NewUser::contentContainer->append(descContainer);
  NewUser::contentContainer->append(contentBox);
}

UserConf::addDescription(Gtk::Box* descContainer) {
  Gtk::Label* descTitle =
      Gtk::make_managed<Gtk::Label>("Creating Configuration");
  descTitle->add_css_class("new-user-desc-title");

  Gtk::TextView* desc = Gtk::make_managed<Gtk::TextView>();
  desc->set_editable(false);
  desc->getBuffer()->set_text(UserConf::descriptionText);

  Gtk::ScrolledWindow* scrollContainer =
      Gtk::make_managed<Gtk::ScrolledWindow>();
  scrollContainer->set_child(desc);

  descContainer->append(descTitle);
  descContainer->append(scrollContainer);
}

UserConf::addContent(Gtk::Box* contentContainer) {}