#include "PopupNewComponent.hpp"

PopupNewComponent::PopupNewComponent(Gtk::Window* parent) : Gtk::Dialog("New Component", *parent), boiteV(get_vbox())
{
	ToggleColumn					model2;

	boiteV->add(treeView);

	list = Gtk::ListStore::create(model2);
	treeView.set_model(list);
	
	treeView.append_column("Components :", model2.m_col_name);
	treeView.get_column_cell_renderer(0)->set_fixed_size(200,0);
	
	AppendComponents();

	Glib::RefPtr<Gtk::TreeSelection> treeSelection = treeView.get_selection();
	treeSelection->signal_changed().connect(sigc::mem_fun(*this, &PopupNewComponent::CloseWindow));
	
	show_all();

	Gtk::TreeModel::iterator selection = treeView.get_selection()->get_selected();
	if (selection)
		treeView.get_selection()->unselect(selection);
}



std::string		PopupNewComponent::GetSelection()
{
	ToggleColumn					model2;
	Gtk::TreeModel::iterator selection = treeView.get_selection()->get_selected();
	
	std::stringstream ss;
	ss.str("");
	if(selection)
	 	ss << (*selection)[model2.m_col_name];
	return ss.str();
}

void 			PopupNewComponent::CloseWindow()
{
	close ();
}

void			PopupNewComponent::AppendComponents()
{
	ToggleColumn					model2;

	Gtk::TreeModel::iterator iter = list->append();
	(*iter)[model2.m_col_name] = "Skin";

	iter = list->append();
	(*iter)[model2.m_col_name] = "Collider";

	iter = list->append();
	(*iter)[model2.m_col_name] = "Script";

	iter = list->append();
	(*iter)[model2.m_col_name] = "Light";

	iter = list->append();
	(*iter)[model2.m_col_name] = "Camera";
}