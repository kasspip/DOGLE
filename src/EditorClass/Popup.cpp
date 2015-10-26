#include "Popup.hpp"

Popup::Popup(std::string title, Gtk::Window* parent, std::string msg) : Gtk::Dialog(title, *parent), boiteV(get_vbox()), label(msg)
{
	boiteV->pack_start(label);
	boiteV->pack_start(zoneText);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all();
}

std::string Popup::getText(){return zoneText.get_text();}

void Popup::setText(std::string text){zoneText.set_text(text);}
