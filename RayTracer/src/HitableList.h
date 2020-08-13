#ifndef HITABLELISTH
#define HITABLELISTH

#include"Hitable.h"

class Hitable_list : public Hitable {
public:
	Hitable** list;
	int list_size;

	Hitable_list() {}
	Hitable_list(Hitable** l, int n) { list = l; list_size = n; }

	bool hit(const Ray& r, float t_min, float t_max, Hit_record& rec);
};

bool Hitable_list::hit(const Ray& r, float t_min, float t_max, Hit_record& rec) {
	Hit_record temp_rec;
	bool hit_anything = false;
	float closest_so_far = t_max;
	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}

#endif // !HITABLELISTH
