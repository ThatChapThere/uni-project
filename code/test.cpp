// Credit: https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/sec-helloworld.html
#include "test.h"
#include <iostream>

Test::Test(): m_button("Hello World")
{
	m_button.set_margin(10);
	m_button.signal_clicked().connect(sigc::mem_fun(*this, &Test::on_button_clicked));
	set_child(m_button);
}

Test::~Test()
{
}

void Test::on_button_clicked()
{
	std::cout << "Hello World" << std::endl;
}
