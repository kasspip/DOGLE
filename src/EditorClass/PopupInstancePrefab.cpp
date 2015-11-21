#include "PopupInstancePrefab.hpp"

PopupInstancePrefab::PopupInstancePrefab(Gtk::Window* parent, Application *app) : 
Gtk::Dialog("Instantiate", *parent), 
boiteV(get_vbox())
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
		(*iter)[model2.del] = false;
	}

	add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	show_all();
}

GameObject*		PopupInstancePrefab::GetSelection()
{
	ToggleColumn					model2;
	Gtk::TreeModel::iterator selection = treeView.get_selection()->get_selected();

	if(selection)
	{
		GameObject *prefab;
		std::stringstream ss;
	 	ss << (*selection)[model2.m_col_name];
	 	try {
 	  		prefab = application->FindPrefab( ss.str() );
	 	}
	 	catch (DError & e) {
	 		std::cout << "application->FindPrefab() failed." << std::endl;
	 	}
	 	return prefab;
	}
	return nullptr;
}