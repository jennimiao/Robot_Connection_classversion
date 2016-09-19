#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

MakeBlockAccelerometer::MakeBlockAccelerometer()
{
	name_Object = "MakeBlockAccelerometer";
}

MakeBlockAccelerometer::MakeBlockAccelerometer(string filename)
{
	construct(filename, "MakeBlockAccelerometer");
}




