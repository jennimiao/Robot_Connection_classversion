#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

MakeBlockServoMG995::MakeBlockServoMG995()
{
	name_Object = "MakeBlockServoMG995";
}

MakeBlockServoMG995::MakeBlockServoMG995(string filename)
{
	construct(filename, "MakeBlockServoMG995");
}



