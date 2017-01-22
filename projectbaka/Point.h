#pragma once
#include<math.h>
class Point {
public:
	double x;
	double y;
	void SetPointX(double p_x) {
		this->x = p_x;
	}
	void SetPointY(double p_y) {
		this->y = p_y;
	}
	void SetPosition(double x, double y) {
		this->y = y;
		this->x = x;
	}
	double DistanceTo(Point *p) {
		return DistanceTo(p->x, p->y);
	}
	double DistanceTo(double x1, double y1) {
		return sqrt((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y));
	}
};			