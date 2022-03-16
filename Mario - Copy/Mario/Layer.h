#pragma once
#include <vector>
#include <iostream>
#include "Commons.h"
using namespace std;



class Layer
{
public:
	Layer(){}

	virtual void Update() {}//update stuff on the screen whenever you want to build a destructible map, to update it and the new states
	virtual void Render() {}// to draw the map on the screen

	~Layer(){}

private:

};


