// Credit: https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/sec-helloworld.html
#ifndef TEST_H
#define TEST_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class Test: public Gtk::Window
{
	public:
	Test();
	~Test() override;
	
	protected:
	void on_button_clicked();
	Gtk::Button m_button;
};

#endif
