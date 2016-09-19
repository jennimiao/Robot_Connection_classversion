#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

MakeBlockConverter::MakeBlockConverter()
{
	name_Object = "MakeBlockConverter";
}

MakeBlockConverter::MakeBlockConverter(string filename)
{
	construct(filename, "MakeBlockConverter");
}




