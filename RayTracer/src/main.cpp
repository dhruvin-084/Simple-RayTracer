#include<iostream>
#include<fstream>
#include<float.h>
#include<ctime>
#include<Windows.h>

#include"Sphere.h"
#include"HitableList.h"
#include"Camera.h"
#include"Material.h"

float random();



Vec3 random_in_unit_sphere() {
	Vec3 p;
	do {
		p = 2.0f * Vec3(random(), random(), random()) - Vec3(1.0f);
	} while (p.squared_length() >= 1.0f);
	return p;
}

float hit_sphere(const Vec3& center, float radius, const Ray& r) {
	Vec3 oc = r.origine() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0f * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0) {
		return -1.0f;
	}
	else {
		return (-b - sqrt(discriminant)) / 2.0f * a;
	}
}

Vec3 color(const Ray& r, Hitable* world, int depth) {
	Hit_record rec;
	if (world->hit(r, 0.0f, 30000.0f, rec)) {
		Ray scattered;
		Vec3 attenuation;
		try {
			if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
				return attenuation * color(scattered, world, depth + 1);
			}
			else {
				return Vec3(0.0f);
			}
		}
		catch (...) {
			return Vec3(0.0f);
		}
	}
	else {
		Vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * Vec3(1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
	}
}
float random() {
	return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}

int main() {
	std::srand(std::time(nullptr));

	HWND consoleWindow = GetConsoleWindow();
	int nScreenWidth = 10;
	int nScreenHeight = 3;
	char* screen = new char[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = ' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//Set Console Screen Buffer Size
	COORD c;
	c.X = (short)nScreenWidth;
	c.Y = (short)nScreenHeight;
	SetConsoleScreenBufferSize(hConsole, c);
	//For UnResizeble console
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwByteWritten = 0;


	std::ofstream output;
	output.open("image.ppm");

	int nx = 600;
	int ny = 300;
	int ns = 600;

	output << "P3\n" << nx << " " << ny << "\n255\n";

	Camera cam;

	Hitable* list[4];
	list[0] = new Sphere(Vec3(0, 0, -1.0f), 0.5, new Lambertion(Vec3(0.8f, 0.3f, 0.3f)));
	list[1] = new Sphere(Vec3(0, -100.5f, -1.0f), 100.0f, new Lambertion(Vec3(0.8f, 0.8f, 0.0f)));
	list[2] = new Sphere(Vec3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vec3(0.8f, 0.6f, 0.2f), 0.3f));
	list[3] = new Sphere(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vec3(1.0f), 0.5f));

	Hitable* world = new Hitable_list(list, 4);
	float frac = 1 / float(nx * ny * ns);
	float per = 0.0f;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			Vec3 col(0.0f);
			for (int s = 0; s < ns; s++) {
				float u = (float(i) + random()) / float(nx);
				float v = (float(j) + random()) / float(ny);
				Ray r = cam.get_ray(u, v);
				col += color(r, world, 0);

				per += frac;
			}
			col /= float(ns);
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99f * col.r());
			int ig = int(255.99f * col.g());
			int ib = int(255.99f * col.b());

			output << ir << " " << ig << " " << ib << "\n";
			int persentage = int(per * 100.0f);
			//std::cout << per*100.0f << "%" << std::endl;
			wsprintf(&screen[0], " %d %%", persentage);
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwByteWritten);
		}
	}

	delete world;
	delete list[0];
	delete list[1];
	delete list[2];
	delete list[3];
	output.close();
	return 0;
}