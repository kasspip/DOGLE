#include "PopupConfirmation.hpp"

PopupConfirmation::PopupConfirmation(std::string title, Gtk::Window* parent, std::string msg) 
: Gtk::Dialog(title, *parent), boiteV(get_vbox()), label(msg)
{
	boiteV->pack_start(label);
	add_button("NO", Gtk::RESPONSE_CANCEL);
	add_button("YES", Gtk::RESPONSE_OK);
	show_all();
}
