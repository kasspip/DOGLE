#ifndef FILEFINDER_HPP
#define FILEFINDER_HPP

// #include <gtkmm.h>

class FileFinder :  public Gtk::Dialog
{
public:
  FileFinder();
  virtual ~FileFinder();

protected:
  //Signal handlers:
  void on_button_file_clicked();
  void on_button_folder_clicked();

  //Child widgets:
  Gtk::ButtonBox m_ButtonBox;
  Gtk::Button m_Button_File, m_Button_Folder;
};

#endif //FILEFINDER_HPP