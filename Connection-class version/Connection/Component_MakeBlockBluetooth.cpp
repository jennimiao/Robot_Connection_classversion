#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

MakeBlockBluetooth::MakeBlockBluetooth()
{
	name_Object = "MakeBlockBluetooth";
}

MakeBlockBluetooth::MakeBlockBluetooth(string filename)
{
	construct(filename, "MakeBlockBluetooth");
}



