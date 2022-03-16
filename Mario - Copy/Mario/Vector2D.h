#pragma once
#include "Constants.h"
#include <iostream>
#include <map>
using namespace std;



class Vector2D
{
public:
	int X, Y;// public variables so they don't require m_... 

public:
	Vector2D(float x = 0, float y = 0) : X(x), Y(y) {}
	~Vector2D(){}

public:
	//addition operator overloading
	inline Vector2D operator+(const Vector2D& v2) const {
		return Vector2D(X + v2.X, Y + v2.Y);
	}

	//subtraction operator
	inline Vector2D operator-(const Vector2D& v2) const {
		return Vector2D(X - v2.X, Y - v2.Y);
	}

	//multiplication operator
	inline Vector2D operator*(const float scalar) const {
		return Vector2D(X * scalar, Y * scalar);
	}

	void Log(string msg = "") {
		cout << msg << "(X Y)    (" << X << " " << Y << ")" << endl;
	}

private:


};

