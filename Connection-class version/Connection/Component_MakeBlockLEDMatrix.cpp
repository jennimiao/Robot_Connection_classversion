#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

MakeBlockLEDMatrix::MakeBlockLEDMatrix()
{
	name_Object = "MakeBlockLEDMatrix";
}

MakeBlockLEDMatrix::MakeBlockLEDMatrix(string filename)
{
	construct(filename, "MakeBlockLEDMatrix");
}




