#ifndef MY_COLUMN_HPP
#define MY_COLUMN_HPP

#include <gtkmm.h>

class myColumn : public Gtk::TreeModel::ColumnRecord
{
public:
	myColumn();
	Gtk::TreeModelColumn<Glib::ustring> m_col_name;
	Gtk::TreeModelColumn<Glib::ustring> value_1;
	Gtk::TreeModelColumn<Glib::ustring> value_2;
	Gtk::TreeModelColumn<Glib::ustring> value_3;
	Gtk::TreeModelColumn<Glib::ustring> value_4;
};

#endif