#include "shiprenderer.h"

static void renderAt(GfxWrapper *gfx, double x, double y, double radius, double rotation, RGB &colour)
{
	double cx = x;
	double cy = y;

	double tpx = cx + cos(rotation) * radius;
	double tpy = cy + sin(rotation) * radius;

	double blx = cx + cos(rotation - M_PI * 0.75) * radius;
	double bly = cy + sin(rotation - M_PI * 0.75) * radius;

	double brx = cx + cos(rotation + M_PI * 0.75) * radius;
	double bry = cy + sin(rotation + M_PI * 0.75) * radius;

	gfx->drawLine(cx, cy, blx, bly, colour);
	gfx->drawLine(cx, cy, brx, bry, colour);

	gfx->drawLine(blx, bly, tpx, tpy, colour);
	gfx->drawLine(brx, bry, tpx, tpy, colour);
}


void ShipRenderer::render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction, RGB &colour)
{
	renderAt(gfx, position.X(), position.Y(), shape.Radius(), direction.Angle(), colour);
	if (position.X() + shape.Radius() > 640)
	{
		renderAt(gfx, position.X() - 640, position.Y(), shape.Radius(), direction.Angle(), colour);
	}

	if (position.X() - shape.Radius() < 0)
	{
		renderAt(gfx, position.X() + 640, position.Y(), shape.Radius(), direction.Angle(), colour);
	}

	if (position.Y() + shape.Radius() > 480)
	{
		renderAt(gfx, position.X(), position.Y() - 480, shape.Radius(), direction.Angle(), colour);
	}

	if (position.Y() - shape.Radius() < 0)
	{
		renderAt(gfx, position.X(), position.Y() + 480, shape.Radius(), direction.Angle(), colour);
	}
}