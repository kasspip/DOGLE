#include "PopupInstancePrefab.hpp"

PopupInstancePrefab::PopupInstancePrefab(Gtk::Window* parent, Application *app) : Gtk::Dialog("Instantiate", *parent), boiteV(get_vbox())
{
	application = app;
	ToggleColumn					model2;


	boiteV->add(treeView);

	list = Gtk::ListStore::create(model2);
	treeView.set_model(list);
	
	treeView.append_column("Prefabs :", model2.m_col_name);
	treeView.get_column_cell_renderer(0)->set_fixed_size(200,0);
	

	for (GameObject* go : app->GetListPrefab())
	{
		Gtk::TreeModel::iterator iter = list->append();
		(*iter)[model2.m_col_name] = go->name;
	}

	Glib::RefPtr<Gtk::TreeSelection> treeSelection = treeView.get_selection();
	treeSelection->signal_changed().connect(sigc::mem_fun(*this, &PopupInstancePrefab::CloseWindow));
	
	show_all();

	Gtk::TreeModel::iterator selection = treeView.get_selection()->get_selected();
	if (selection)
		treeView.get_selection()->unselect(selection);
}

GameObject*		PopupInstancePrefab::GetSelection()
{
	ToggleColumn					model2;
	Gtk::TreeModel::iterator selection = treeView.get_selection()->get_selected();
	
	GameObject *prefab = nullptr;
	if(selection)
	{
		std::stringstream ss;
	 	ss << (*selection)[model2.m_col_name];
	 	try {
 	  		prefab = application->FindPrefab( ss.str() );
	 	}
	 	catch (DError & e) {
	 		std::cout << "application->FindPrefab() failed." << std::endl;
	 	}
	}
	return prefab;
}

void 			PopupInstancePrefab::CloseWindow()
{
	close ();
}
