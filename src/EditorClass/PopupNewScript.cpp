#include "PopupNewScript.hpp"

PopupNewScript::PopupNewScript(Gtk::Window* parent) 
: Gtk::Dialog("Scripts", *parent),
boiteV(get_content_area()),
btnNew ("New"),
btnDelete ("Remove"),
selection (nullptr)
{
	btnNew.signal_clicked().connect(sigc::mem_fun(*this, &PopupNewScript::ButtonNewScript));
	btnDelete.signal_clicked().connect(sigc::mem_fun(*this, &PopupNewScript::ButtonDeleteScript));
	Hbox.add(btnNew);
	Hbox.add(btnDelete);
	
	boiteV->add(Hbox);
	boiteV->add(treeView);

	list = Gtk::ListStore::create(model2);
	treeView.set_model(list);
	treeView.append_column("List :", model2.m_col_name);
	treeView.get_column_cell_renderer(0)->set_fixed_size(200,0);

	RefreshComponents();

	Glib::RefPtr<Gtk::TreeSelection> treeSelection = treeView.get_selection();
	treeSelection->signal_changed().connect(sigc::mem_fun(*this, &PopupNewScript::OnSelection));
	
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all();
	
}

Script*			PopupNewScript::GetSelection()
{
	if (selection)
	{
		std::stringstream ss;
	 	ss << (*selection)[model2.m_col_name];
		return scriptFactory.Create(ss.str());
	}
	return nullptr;
}

void			PopupNewScript::OnSelection()
{
	selection = treeView.get_selection()->get_selected();
}

void			PopupNewScript::ButtonNewScript()
{
	std::string scriptName = PopupGetText("New Script", "Name ");
	
	if (scriptName.length() == 0)
		return;
	
	ScriptManager			scriptManager;
	scriptManager.NewScript(scriptName);
	
	RefreshComponents();
}

void			PopupNewScript::ButtonDeleteScript()
{
	if (!selection)
		return;
			
	std::stringstream ss;
	ss << (*selection)[model2.m_col_name];

	ScriptManager			scriptManager;
	scriptManager.RemoveScript( ss.str() );
	
	RefreshComponents();
}

void			PopupNewScript::RefreshComponents()
{
	ScriptManager			scriptManager;
	std::list<std::string> 	scriptNames;
	Gtk::TreeModel::iterator row;
	
	list->clear();

	scriptNames = scriptManager.GetScriptsNames();
	for (std::string name : scriptNames)
	{
		row = list->append();
		(*row)[model2.m_col_name] = name;
	}
}

std::string		PopupNewScript::PopupGetText(std::string win_name, std::string label)
{
	int		ret;

	Popup	pop = Popup(win_name, this, label);
	while ((ret = pop.run()) != Gtk::RESPONSE_CANCEL)
	{
		if (ret == Gtk::RESPONSE_OK && pop.getText().length())
			return pop.getText();
	}
	return std::string("");
}