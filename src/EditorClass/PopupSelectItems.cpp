#include "PopupSelectItems.hpp"

PopupSelectItems::PopupSelectItems(Gtk::Window* parent, std::list<std::string> listItems) : Gtk::Dialog("Select Item", *parent), boiteV(get_vbox())
{
	ToggleColumn					model2;

	boiteV->add(treeView);

	items = Gtk::ListStore::create(model2);
	treeView.set_model(items);
	
	treeView.append_column("Items :", model2.m_col_name);
	treeView.get_column_cell_renderer(0)->set_fixed_size(300,0);
	

	for (std::string name : listItems)
	{
		Gtk::TreeModel::iterator iter = items->append();
		(*iter)[model2.m_col_name] = name;
	}

	Glib::RefPtr<Gtk::TreeSelection> treeSelection = treeView.get_selection();
	treeSelection->signal_changed().connect(sigc::mem_fun(*this, &PopupSelectItems::CloseWindow));
	
	show_all();

	Gtk::TreeModel::iterator selection = treeView.get_selection()->get_selected();
	if (selection)
		treeView.get_selection()->unselect(selection);
}

std::string		PopupSelectItems::GetSelection()
{
	ToggleColumn					model2;
	Gtk::TreeModel::iterator selection = treeView.get_selection()->get_selected();
	
	if(selection)
	{
		std::stringstream ss;
	 	ss << (*selection)[model2.m_col_name];
		return ss.str();
	}
	return "";
}

void 			PopupSelectItems::CloseWindow()
{
	close ();
}