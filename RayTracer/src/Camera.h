#ifndef CAMERAH
#define CAMERAH

#include"Ray.h"

class Camera {
public:
	Vec3 origin;
	Vec3 lower_left_corner;
	Vec3 horizontal;
	Vec3 vertical;

	Camera() {
		lower_left_corner = Vec3(-2.0f, -1.0f, -1.0f);
		horizontal = Vec3(4.0f, 0.0f, 0.0f);
		vertical = Vec3(0.0f, 2.0f, 0.0f);
		origin = Vec3(0.0f, 0.0f, 0.0f);
	}

	Ray get_ray(float u, float v) {
		return Ray(origin, lower_left_corner + u * horizontal + v * vertical);
	}

};

#endif // !CAMERAH