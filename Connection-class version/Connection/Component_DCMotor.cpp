#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

DCMotor::DCMotor()
{
	name_Object = "DCMotor";
}

DCMotor::DCMotor(string filename)
{
	construct(filename, "DCMotor");
}




