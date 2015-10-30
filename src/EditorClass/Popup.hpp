#ifndef POPUP_HPP
#define POPUP_HPP

#include <string>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/stock.h>
#include <gtkmm/window.h>

class Popup :  public Gtk::Dialog
{
public:
	Popup(std::string title, Gtk::Window* parent, std::string msg);
	std::string	getText();
	void		setText(std::string text);

private:
	Gtk::Box	*boiteV;
	Gtk::Label	label;
	Gtk::Entry	zoneText;
};

#endif
