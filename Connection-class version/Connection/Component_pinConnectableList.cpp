#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;

pinConnectableList::pinConnectableList()
{
	name = "";
	next = NULL;
}

pinConnectableList::~pinConnectableList()
{
	;
}