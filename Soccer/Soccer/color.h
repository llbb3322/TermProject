#pragma once

class Color {
public:
	double r;
	double g;
	double b;
	double a;
public:
	Color(double r, double g, double b) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 1.0;
	}

	Color(double r, double g, double b, double a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

const Color GOALNET_POINT_COLOR = Color(0.95, 0.95, 0.95);
const Color GOALNET_SPRING_COLOR = Color(1.0, 1.0, 1.0);

