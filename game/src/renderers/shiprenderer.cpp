#include <cmath>

#include "shiprenderer.h"
#ifdef __WII__
#define M_PI        3.14159265358979323846264338327950288   /* pi             */
#define M_PI_2      1.57079632679489661923132169163975144   /* pi/2           */
#define M_PI_4      0.785398163397448309615660845819875721  /* pi/4           */
#endif

static void renderAt(Gfx &gfx, double x, double y, double radius, double rotation, RGB &colour)
{
	double cx = x;
	double cy = y;

	double tpx = cx + cos(rotation) * radius;
	double tpy = cy + sin(rotation) * radius;

	double blx = cx + cos(rotation - M_PI * 0.75) * radius;
	double bly = cy + sin(rotation - M_PI * 0.75) * radius;

	double brx = cx + cos(rotation + M_PI * 0.75) * radius;
	double bry = cy + sin(rotation + M_PI * 0.75) * radius;

    gfx.drawLine(cx, cy, blx, bly, colour);
    gfx.drawLine(cx, cy, brx, bry, colour);

    gfx.drawLine(blx, bly, tpx, tpy, colour);
    gfx.drawLine(brx, bry, tpx, tpy, colour);
}


void ShipRenderer::render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour) const
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
