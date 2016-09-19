#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

pin::pin()
{
	name = "";
	position[0] = 0.0;
	position[1] = 0.0;
	position[2] = 0.0;
	occupied = 0;
	head_connect = new pinConnectableList;
	connected_Pin = "";
	type_Pins = "";
	next = NULL;
}

pin::~pin()
{
	;
}