#include "myarea.h"
#include <cairomm/context.h>

MyArea::MyArea()
{
  set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea()
{
}

void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
  // coordinates for the center of the window
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

  cr->set_line_width(10.0);

  // draw red lines out from the center of the window
  cr->set_source_rgb(0.8, 0.0, 0.0);
  cr->move_to(0, 0);
  cr->line_to(xc, yc);
  cr->line_to(0, height/2);
  cr->move_to(xc, yc);
  cr->line_to(width, yc);
  cr->stroke();
}
