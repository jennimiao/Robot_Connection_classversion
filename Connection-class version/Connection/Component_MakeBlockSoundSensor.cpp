#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

MakeBlockSoundSensor::MakeBlockSoundSensor()
{
	name_Object = "MakeBlockSoundSensor";
}

MakeBlockSoundSensor::MakeBlockSoundSensor(string filename)
{
	construct(filename, "MakeBlockSoundSensor");
}




