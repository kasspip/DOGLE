#ifndef TOGGLECOLUMN_HPP
#define TOGGLECOLUMN_HPP

#include <gtkmm/treemodel.h>
#include <gtkmm/treemodel.h>

class ToggleColumn : public Gtk::TreeModel::ColumnRecord
{
public:
	ToggleColumn();
	Gtk::TreeModelColumn<Glib::ustring> m_col_name;
	Gtk::TreeModelColumn<bool>			del;
};

#endif