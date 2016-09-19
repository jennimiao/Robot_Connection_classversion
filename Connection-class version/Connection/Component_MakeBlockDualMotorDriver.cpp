#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

MakeBlockDualMotorDriver::MakeBlockDualMotorDriver()
{
	name_Object = "MakeBlockDualMotorDriver";
}

MakeBlockDualMotorDriver::MakeBlockDualMotorDriver(string filename)
{
	construct(filename, "MakeBlockDualMotorDriver");
}

