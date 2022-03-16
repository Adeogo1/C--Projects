#pragma once
#include <iostream>
#include <map>
using namespace std;




class Point
{
public:
	Point(float X = 0, float Y = 0) : X(X), Y(Y) {}
	~Point() {}
	float X, Y;

public:

	//Addition operator overload
	inline Point operator+(const Point& p2)const { return Point(X + p2.X, Y + p2.Y); }

	//Addition operator overload +=
	inline friend Point operator+=(Point& p1, const Point& p2) {
		p1.X += p2.X;
		p1.Y += p2.Y;
		return p1;
	}

	//Subtraction operator overload -
	inline Point operator-(const Point& p2)const { return Point(X - p2.X, Y - p2.Y); }

	//Subtraction operator overload -=
	inline friend Point operator-=(Point& p1, const Point& p2) {
		p1.X -= p2.X;
		p1.Y -= p2.Y;
		return p1;
	}

	//Subtraction operator overload -
	inline Point operator*(const float scalar)const { return Point(X * scalar, Y * scalar); }


	void Log(string msg = "") {
		cout << msg << "(X Y)    (" << X << " " << Y << ")" << endl;
	}
};


