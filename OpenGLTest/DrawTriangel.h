#pragma once
class DrawTriangel
{
private:
	void initTriangleWithDifVAO();
	void drawTriangleWithDifVAO();
	void initTriangleWithEBO();
	void drawTriangleWithEBO();
public:
	DrawTriangel();
	void toDrawTriangle(int type);
	~DrawTriangel();
};

