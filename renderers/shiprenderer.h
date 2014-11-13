#ifndef __SHIPRENDERER_H__
#define __SHIPRENDERER_H__

#include "renderer.h"
#include "gfx.h"

class ShipRenderer : public Renderer
{
public:
	void render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction) 
	{
		double tp_x = position.X()+cos(direction.Angle())*shape.Radius();
		double tp_y = position.Y()+sin(direction.Angle())*shape.Radius();
		double br_x = position.X()+cos((direction.Angle())+shape.Radius()/5)*(shape.Radius()*0.6);
		double bl_x = position.X()+cos((direction.Angle())+shape.Radius()/2)*(shape.Radius()*0.6);
		double br_y = position.Y()+sin((direction.Angle())+shape.Radius()/5)*(shape.Radius()*0.6);
		double bl_y = position.Y()+sin((direction.Angle())+shape.Radius()/2)*(shape.Radius()*0.6);

		gfx->drawLine(tp_x, tp_y, br_x, br_y, RGB::white);
		gfx->drawLine(tp_x, tp_y, bl_x, bl_y, RGB::white);
		gfx->drawLine(br_x, br_y, position.X(), position.Y(), RGB::white);
		gfx->drawLine(bl_x, bl_y, position.X(), position.Y(), RGB::white);
	}
};

#endif