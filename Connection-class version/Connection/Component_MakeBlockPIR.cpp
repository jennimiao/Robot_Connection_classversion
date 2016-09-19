#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

MakeBlockPIR::MakeBlockPIR()
{
	name_Object = "MakeBlockPIR";
}

MakeBlockPIR::MakeBlockPIR(string filename)
{
	construct(filename, "MakeBlockPIR");
}

