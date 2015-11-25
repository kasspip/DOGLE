#ifndef POPUPNEWSCRIPT_HPP
#define POPUPNEWSCRIPT_HPP

#include <string>
#include <list>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/stock.h>
#include <gtkmm/window.h>
#include "ToggleColumn.hpp"
#include "Application.hpp"
#include "ScriptFactory.hpp"
#include "ScriptManager.hpp"
#include "Popup.hpp"
#include "PopupConfirmation.hpp"

class PopupNewScript :  public Gtk::Dialog
{
public:
	PopupNewScript(Gtk::Window* parent, Application* app);
	
	void			RefreshComponents();
	Script*			GetSelection();
	void			OnSelection();
	void			ButtonNewScript();
	void			ButtonDeleteScript();
	void 			ApplicationRemoveScripts(std::string name);

	std::string		PopupGetText(std::string win_name, std::string label);
	bool			PopupGetConfirm(std::string win_name, std::string question);


	ScriptFactory	scriptFactory;

	Gtk::Box						*boiteV;
	Glib::RefPtr<Gtk::ListStore>	list;
	Gtk::TreeView					treeView;
	Gtk::HBox						Hbox;
	Gtk::Button 					btnNew;
	Gtk::Button 					btnDelete;

	Gtk::TreeModel::iterator 		selection;
	ToggleColumn					model2;
	std::list<std::string>			compiledScripts;

private:
	Application*					_app;

};

#endif