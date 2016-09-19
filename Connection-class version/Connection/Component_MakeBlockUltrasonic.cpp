#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

MakeBlockUltrasonic::MakeBlockUltrasonic()
{
	name_Object = "MakeBlockUltrasonic";
}

MakeBlockUltrasonic::MakeBlockUltrasonic(string filename)
{
	construct(filename, "MakeBlockUltrasonic");
}

