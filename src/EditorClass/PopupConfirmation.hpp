#ifndef POPUPCONFIRMATION_HPP
#define POPUPCONFIRMATION_HPP

#include <string>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/stock.h>
#include <gtkmm/window.h>


class PopupConfirmation :  public Gtk::Dialog
{
public:
	PopupConfirmation(std::string title, Gtk::Window* parent, std::string msg);

private:
	Gtk::Box	*boiteV;
	Gtk::Label	label;
};

#endif