#ifndef MATH_H
#define MATH_H

#ifndef sizeOfArray
#define sizeOfArray(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

template <class T>
T Min(T a, T b);
template <class T>
T Min(T a, T b, T c);
template <class T>
T Max(T a, T b);
template <class T>
T Max(T a, T b, T c);

template <class T>
T Abs(T x);

template <class T>
T DToR(T deg);
template <class T>
T RToD(T rad);

template <class T>
void Swap(T& a, T& b);

#endif // MATH_H
