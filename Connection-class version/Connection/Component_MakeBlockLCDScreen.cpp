#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

MakeBlockLCDScreen::MakeBlockLCDScreen()
{
	name_Object = "MakeBlockLCDScreen";
}

MakeBlockLCDScreen::MakeBlockLCDScreen(string filename)
{
	construct(filename, "MakeBlockLCDScreen");
}




