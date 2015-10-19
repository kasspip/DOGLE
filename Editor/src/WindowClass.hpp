#ifndef WINDOWCLASS_HPP
#define WINDOWCLASS_HPP

#define TITLE "DogleEditor v1"

#include <gtkmm/window.h>

class Window : public Gtk::Window
{
public:
	Window(void);
	~Window(void);
};

#endif
