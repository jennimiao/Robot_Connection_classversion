#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

MakeBlockOrionBoard::MakeBlockOrionBoard()
{
	name_Object = "MakeBlockOrionBoard";
}

MakeBlockOrionBoard::MakeBlockOrionBoard(string filename)
{
	construct(filename, "MakeBlockOrionBoard");
}
