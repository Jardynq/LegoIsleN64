#include "math.h"

template <class T>
T Min(T a, T b) {
	return a < b ? a : b;
}
template <class T>
T Min(T a, T b, T c) {
	return Min(a, Min(b, c));
}
template <class T>
T Max(T a, T b) {
	return a > b ? a : b;
}
template <class T>
T Max(T a, T b, T c) {
	return Max(a, Max(b, c));
}

template <class T>
T Abs(T x) {
	return x < 0 ? -x : x;
}

template <class T>
T DToR(T deg) {
	return deg * 3.1416F / 180.0F;
}
template <class T>
T RToD(T rad) {
	return rad * 180.0F / 3.1416F;
}

template <class T>
void Swap(T& a, T& b) {
	T t = a;
	a = b;
	b = t;
}
