#ifndef POPUPINSTANCEPREFAB_HPP
#define POPUPINSTANCEPREFAB_HPP

#include <string>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/stock.h>
#include <gtkmm/window.h>
#include "ToggleColumn.hpp"
#include "Application.hpp"


class PopupInstancePrefab :  public Gtk::Dialog
{
public:
	PopupInstancePrefab(Gtk::Window* parent, Application *app);
	GameObject*		GetSelection();
	void 			CloseWindow();

private:

	Gtk::Box						*boiteV;
	Glib::RefPtr<Gtk::ListStore>	list;
	Gtk::TreeView					treeView;
	Application 					*application;
};

#endif