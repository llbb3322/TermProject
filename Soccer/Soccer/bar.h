#pragma once
#include "sphere.h"


class Bar {
public:
	vec3 position;
	vec3 rotation;
	double width;
	double height;
	bool is_crossbar;
private:
	void init() {
		this->is_crossbar = false;
		this->width = 2.0;
		this->height = 40.0;
		this->rotation = vec3(0.0, 0.0, 0.0);
	}
public:
	Bar() {
		init();
	}

	void collision_with_post(Sphere* ball) {
		vec3 bar_normal;
		bool collision = false;

		// post의 앞부분
		if (ball->position.x >= position.x - width
			&& ball->position.x <= position.x + width
			&& ball->position.z >= position.z + width
			&& ball->position.z <= position.z + width + ball->radius) {
			collision = true;
			bar_normal = vec3(0.0, 0.0, 1.0);
		// post의 왼쪽부분
		} else if (ball->position.x >= position.x - width - ball->radius
			&& ball->position.x <= position.x - width
			&& ball->position.z >= position.z - width
			&& ball->position.z <= position.z + width) {
			collision = true;
			bar_normal = vec3(-1.0, 0.0, 0.0);
		// post의 오른쪽부분
		} else if (ball->position.x >= position.x + width
			&& ball->position.x <= position.x + width + ball->radius
			&& ball->position.z >= position.z - width
			&& ball->position.z <= position.z + width) {
			collision = true;
			bar_normal = vec3(1.0, 0.0, 0.0);
		}

		if (collision
			&& ball->position.y <= position.y + height
			&& bar_normal.dot(ball->velocity) < 0) {
			vec3 vn = bar_normal.dot(ball->velocity) * bar_normal;
			vec3 vt = ball->velocity - vn;
			ball->velocity = (vt - vn) * ball->restitution;
		}
	}

	void collision_with_crossbar(Sphere* ball) {
		vec3 bar_normal;
		bool collision = false;

		// post의 앞부분
		if (ball->position.z >= position.z + width
			&& ball->position.z <= position.z + width + ball->radius
			&& ball->position.y >= position.y - width
			&& ball->position.y <= position.y + width) {
			collision = true;
			bar_normal = vec3(0.0, 0.0, 1.0);
		} else if (ball->position.z >= position.z - width
			&& ball->position.z <= position.z + width
			&& ball->position.y >= position.y + width
			&& ball->position.y <= position.y + width + ball->radius) {
			collision = true;
			bar_normal = vec3(0.0, 1.0, 0.0);
		} else if (ball->position.z >= position.z - width
			&& ball->position.z <= position.z + width
			&& ball->position.y >= position.y - width - ball->radius
			&& ball->position.y <= position.y - width) {
			collision = true;
			bar_normal = vec3(0.0, -1.0, 0.0);
		}

		if (collision
			&& ball->position.x >= position.x
			&& ball->position.x <= position.x + height
			&& bar_normal.dot(ball->velocity) < 0) {
			vec3 vn = bar_normal.dot(ball->velocity) * bar_normal;
			vec3 vt = ball->velocity - vn;
			ball->velocity = (vt - vn) * ball->restitution;
		}
	}

	void collision(Sphere* ball) {
		if (this->is_crossbar) {
			collision_with_crossbar(ball);
		} else {
			collision_with_post(ball);
		}
	}

	void draw();
};
