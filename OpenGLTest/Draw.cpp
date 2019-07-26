#include "Draw.h"
#include "DrawTriangel.h"


Draw::Draw()
{
}

void Draw::toDrawTriangle(int type)
{
	DrawTriangel draw = DrawTriangel();
	draw.toDrawTriangle(type);
}


Draw::~Draw()
{
}
