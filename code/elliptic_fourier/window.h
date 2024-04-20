#pragma once

#include <gtkmm/applicationwindow.h>
#include "graph_area.h"

class Window: public Gtk::ApplicationWindow
{
public:
	Window();
	~Window() override;
protected:
	GraphArea ga;
	void screenshot();
};
