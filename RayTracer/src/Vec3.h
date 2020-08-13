#ifndef VEC3H
#define VEC3H

#include<math.h>
#include<iostream>

class Vec3 {
public:
	float e[3];

	Vec3() { e[0] = 0; e[1] = 0; e[2] = 0; }
	Vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
	Vec3(float x) { e[0] = x; e[1] = x; e[2] = x; }

	inline float x() { return e[0]; }
	inline float y() { return e[1]; }
	inline float z() { return e[2]; }
	inline float r() { return e[0]; }
	inline float g() { return e[1]; }
	inline float b() { return e[2]; }

	inline const Vec3& operator+() const { return *this; }
	inline Vec3 operator-() { return Vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](int n) { return e[n]; }
	
	inline Vec3& operator+=(const Vec3& v2);
	inline Vec3& operator-=(const Vec3& v2);
	inline Vec3& operator*=(const Vec3& v2);
	inline Vec3& operator/=(const Vec3& v2);
	inline Vec3& operator*=(const float t);
	inline Vec3& operator/=(const float t);

	inline float length() const {
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}
	inline float squared_length() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	inline void normalize();

};

inline Vec3& Vec3::operator+=(const Vec3& v2) {
	e[0] += v2.e[0];
	e[1] += v2.e[1];
	e[2] += v2.e[2];
	return *this;
}
inline Vec3& Vec3::operator-=(const Vec3& v2) {
	e[0] -= v2.e[0];
	e[1] -= v2.e[1];
	e[2] -= v2.e[2];
	return *this;
}
inline Vec3& Vec3::operator*=(const Vec3& v2) {
	e[0] *= v2.e[0];
	e[1] *= v2.e[1];
	e[2] *= v2.e[2];
	return *this;
}
inline Vec3& Vec3::operator/=(const Vec3& v2) {
	e[0] /= v2.e[0];
	e[1] /= v2.e[1];
	e[2] /= v2.e[2];
	return *this;
}
inline Vec3& Vec3::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}
inline Vec3& Vec3::operator/=(const float t) {
	e[0] /= t;
	e[1] /= t;
	e[2] /= t;
	return *this;
}
inline void Vec3::normalize() {
	float d = this->length();
	*this /= d;
}

inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.e[0] + v2.e[0], 
				v1.e[1] + v2.e[1], 
				v1.e[2] + v2.e[2]);
}
inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.e[0] - v2.e[0],
				v1.e[1] - v2.e[1],
				v1.e[2] - v2.e[2]);
}
inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.e[0] * v2.e[0],
				v1.e[1] * v2.e[1],
				v1.e[2] * v2.e[2]);
}
inline Vec3 operator/(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.e[0] / v2.e[0],
				v1.e[1] / v2.e[1],
				v1.e[2] / v2.e[2]);
}
inline Vec3 operator*(float t, const Vec3& v1) {
	return Vec3(v1.e[0] * t,
				v1.e[1] * t,
				v1.e[2] * t);
}
inline Vec3 operator/(const Vec3& v1, float t) {
	return Vec3(v1.e[0] / t,
				v1.e[1] / t,
				v1.e[2] / t);
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& v1) {
	os << v1.e[0] << " " << v1.e[1] << " " << v1.e[2];
	return os;
}

inline std::istream& operator>>(std::istream& is, Vec3& v1) {
	is >> v1.e[0] >> v1.e[1] >> v1.e[2];
	return is;
}

inline Vec3 unit_vector(Vec3 v) {
	return v / v.length();
}

inline float dot(const Vec3& v1, const Vec3& v2) {
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}
inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
				v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
				v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

#endif // !VEC3H