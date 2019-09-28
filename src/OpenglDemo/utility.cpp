#pragma once
#include "utility.h"

using namespace std;

void coutCurrentDir()
{
	char buffer[1000];
	GetCurrentDirectory(1000, buffer);
	cout <<"currentDirectory: "<< buffer << endl;
}
