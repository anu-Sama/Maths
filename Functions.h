 #pragma once

#define pi 3.14159265359
#define e 2.718281828459

template<typename T>
constexpr auto ToDegree(T x) { return x*pi/180; }


template <typename T>
T factorial(T num) {
	if (num <= 1)
		return num;

	return num * factorial(num - 1);

};

template <typename T>
static T power(T base, int index) {
	if (index == 0) return 1;
	if (index == 1) return base;

	bool bInverted = false;
	T raisedNum = base;
	if (index < 0) bInverted = true;
	// Calculating the power
	for (int i = 1; i < index; i++) {
		raisedNum *= base;
	}
	if (bInverted) return 1 / raisedNum;

	return raisedNum;

}

template <typename T>
T mod(T num) {
	if (num < 0) return -num;
	
	return num;
}

template <typename T>
T floor(T num) {

	T n;
	return n;
}

template <typename T>
T hypotenuse(T length, T breadth) {
	return sqrt(power(length, 2) + power(breadth, 2));
}

template <typename T>
T max(T num1, T num2) {
	return num1 > num2 ? num1 : num2;
}

template <typename T>
T min(T num1, T num2) {
	return num1 < num2 ? num1 : num2;
}

double exponent(int index) {
	return power(e, index);
}

// Trigonometric functions
template <typename T>
T sine(T degree) {
	T x = ToDegree(degree);
	int precesion = 19;
	T value = 0;

	// Using the taylor's series to calculate the value of sine(x) with precision = 19 for approx accurate value
	for (uint64_t i = 0; i < precesion; i++) {
		value += power(-1, i) * power(x, 2 * i + 1) / factorial(2 * i + 1);
	}

	return value;
}

template <typename T>
T cosine(T degree) {
	T x = ToDegree(degree);
	int precesion = 19;
	T value = 1;

	for (uint64_t  i= 1; i < precesion; i++) {
		value += power(-1, i) * power(x, i * 2) / factorial(2 * i);
	}

	return value;
}

template <typename T>
T tangent(T degree) {
	
	T sinOfX = sine(degree);
	T cosOfX = cosine(degree);

	return sinOfX / cosOfX;
}

template <typename T>
T cotangent(T degree) {

	T cot = 1 / tangent(degree);
	return cot;
}

template <typename T>
T Log2(T number) {
	double value = 0;
	T i = 1;
	while (value < number) {
		value = power(2, i);
		if (value == number)
			break;
		i++;
	}

	return i;
}

template <typename T>
T logarithm(T base, T index) {
	return Log2(index) / Log2(base);
}
