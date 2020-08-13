#ifndef SPHEREH
#define SPHEREH

#include"Hitable.h"
#include"Material.h"

class Sphere : public Hitable {
public:
	Vec3 center;
	float radius;
	Material* mat;
	Sphere() {}
	Sphere(Vec3 cen, float r, Material* m) : center(cen), radius(r) { mat = m; }
	~Sphere() { delete mat; }
	bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec);
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, Hit_record& rec) {
	Vec3 oc = r.origine() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0.0f) {
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat;
			return true;
		}

		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat;
			return true;
		}

	}
	return false;
}


#endif // !SPHEREH
