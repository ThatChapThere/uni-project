#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm/applicationwindow.h>
#include "graph_area.h"

class Window: public Gtk::ApplicationWindow
{
public:
	Window();
	~Window() override;
protected:
	// This will create a graph area
	GraphArea ga;
	GraphArea ga2;
	void screenshot();
};

#endif
