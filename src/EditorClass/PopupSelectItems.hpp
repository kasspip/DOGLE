#ifndef POPUPSELECTITEMS_HPP
#define POPUPSELECTITEMS_HPP

#include <string>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/stock.h>
#include <gtkmm/window.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include "ToggleColumn.hpp"
#include "Application.hpp"


class PopupSelectItems :  public Gtk::Dialog
{
public:
	PopupSelectItems(Gtk::Window* parent, std::list<std::string> listItems);
	std::string		GetSelection();
	void 			CloseWindow();

private:

	Gtk::Box						*boiteV;
	Glib::RefPtr<Gtk::ListStore>	items;
	Gtk::TreeView					treeView;
};

#endif