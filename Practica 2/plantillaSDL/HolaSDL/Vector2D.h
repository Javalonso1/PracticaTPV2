#pragma once
#include "checkML.h"
template <typename T>

class Vector2D
{	
private:
	T x;
	T y;
public:
	Vector2D() : x(), y() {}
	Vector2D(T a, T b) : x(a), y(b) {}
	T getX() const {
		return x;
	}
	T getY() const {
		return y;
	}
	Vector2D<T> operator+(const Vector2D<T>& a) {
		Vector2D res = Vector2D(x + a.getX(), y + a.getY());
		return res;
	}
	Vector2D<T> operator-(const Vector2D<T>& a) {
		Vector2D res = Vector2D(x - a.getX(), y - a.getY());
		return res;
	}
	T operator*(const Vector2D<T>& a) {
		T res = x * a.getX() + y * a.getY();
		return res;
	}
	Vector2D<T> operator*(T a) {
		Vector2D res = Vector2D(x * a, y * a);
		return res;
	}
};
template <typename T>
using Point2D = Vector2D<T>;

