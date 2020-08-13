#ifndef MATERIALH
#define MATERIALH



#include"Sphere.h"
#include"HitableList.h"

Vec3 random_in_unit_sphere();
float random();

Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2.0f * dot(v, n) * n;
}

bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted) {
	Vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
	if (discriminant > 0) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
		return false;

}

float schlick(float cosine, float ref_idx) {
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

class Material {
public:
	virtual bool scatter(const Ray& r, const Hit_record& rec, Vec3& attenuation, Ray& scattered) const = 0;
};

class Lambertion : public Material {
public:
	Vec3 albedo;

	Lambertion(const Vec3& a) : albedo(a) {}

	virtual bool scatter(const Ray& r, const Hit_record& rec, Vec3& attenuation, Ray& scattered) const {
		Vec3 target = rec.normal + random_in_unit_sphere();
		scattered = Ray(rec.p, target);
		attenuation = albedo;
		return true;
	}
};

class Metal : public Material {
public:
	Vec3 albedo;
	float fuzz;
	Metal(const Vec3& a, float f) : albedo(a) { fuzz = f < 1 ? f : 1; }
	virtual bool scatter(const Ray& r, const Hit_record& rec, Vec3& attenuation, Ray& scattered) const {
		Vec3 reflected = reflect(unit_vector(r.direction()), rec.normal);
		scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
};

class Dielectric : public Material {
public:
	float ref_idx;
	Dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(const Ray& r, const Hit_record& rec, Vec3& attenuation, Ray& scattered) const {
		Vec3 outward_normal;
		Vec3 reflected = reflect(r.direction(), rec.normal);
		float ni_over_nt;
		attenuation = Vec3(1.0f);

		float reflect_prob;
		float cosine;

		Vec3 refracted;
		if (dot(r.direction(), rec.normal) > 0.0f) {
			outward_normal = -Vec3(rec.normal);
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r.direction(), rec.normal) / r.direction().length();
		}
		else {
			outward_normal = rec.normal;
			ni_over_nt = 1.0f / ref_idx;
			cosine = -dot(r.direction(), rec.normal) / r.direction().length();
		}

		if (refract(r.direction(), outward_normal, ni_over_nt, refracted)) {
			scattered = Ray(rec.p, refracted);
			reflect_prob = schlick(cosine, ref_idx);
		}
		else {
			scattered = Ray(rec.p, reflected);
			reflect_prob = 1.0f;
		}

		if (random() < reflect_prob) {
			scattered = Ray(rec.p, reflected);
		}
		else {
			scattered = Ray(rec.p, refracted);
		}

		return true;

		
	}
};

#endif // !MATERIALH
