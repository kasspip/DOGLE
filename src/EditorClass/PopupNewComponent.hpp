#ifndef POPUPNEWCOMPONENT_HPP
#define POPUPNEWCOMPONENT_HPP

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


class PopupNewComponent :  public Gtk::Dialog
{
public:
	PopupNewComponent(Gtk::Window* parent);
	
	void			AppendComponents();
	std::string		GetSelection();
	void 			CloseWindow();

private:

	Gtk::Box						*boiteV;
	Glib::RefPtr<Gtk::ListStore>	list;
	Gtk::TreeView					treeView;
};

#endif