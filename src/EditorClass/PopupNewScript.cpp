#include "PopupNewScript.hpp"

PopupNewScript::PopupNewScript(Gtk::Window* parent, Application* app) 
: Gtk::Dialog("Scripts", *parent),
boiteV(get_content_area()),
btnNew ("New"),
btnDelete ("Remove"),
selection (nullptr),
_app(app)
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
		return new Script(ss.str());
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

	if (PopupGetConfirm("Delete Script", "Warning:\n\n\tScript \"" + ss.str() + "\" will be fully deleled and removed from all GameObjects\n\n\tContinue ?") == true)
	{
		ApplicationRemoveScripts(ss.str());
		ScriptManager			scriptManager;
		scriptManager.RemoveScript( ss.str() );
	
		RefreshComponents();
	}
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

bool			PopupNewScript::PopupGetConfirm(std::string win_name, std::string question)
{
	int		ret;
	
	PopupConfirmation confim(win_name, this, question);
	while ((ret = confim.run()) != Gtk::RESPONSE_CANCEL)
	{
		if (ret == Gtk::RESPONSE_OK)
			return true;
	}
	return false;
}

std::string		PopupNewScript::PopupGetText(std::string win_name, std::string label)
{
	int		ret;

	Popup	pop(win_name, this, label);
	while ((ret = pop.run()) != Gtk::RESPONSE_CANCEL)
	{
		if (ret == Gtk::RESPONSE_OK && pop.getText().length())
			return pop.getText();
	}
	return std::string("");
}

void 			PopupNewScript::ApplicationRemoveScripts(std::string name)
{
	std::list<GameObject*>	gameObjects = _app->GetListPrefab();
	std::list<GameObject*>::iterator it = gameObjects.begin();
	for(; it != gameObjects.end() ; it++)
		(*it)->DeleteComponent(name);

	std::list<Scene*> scenes = _app->GetListScene();
	std::list<Scene*>::iterator it_scene = scenes.begin();

	for (; it_scene != scenes.end(); it_scene++)
	{
		gameObjects = (*it_scene)->GetBindGameObjectList();
		it = gameObjects.begin();
		for(; it != gameObjects.end() ; it++)
			(*it)->DeleteComponent(name);
		
		gameObjects = (*it_scene)->GetGameObjectList();
		it = gameObjects.begin();
		for(; it != gameObjects.end() ; it++)
			(*it)->DeleteComponent(name);
	}
}