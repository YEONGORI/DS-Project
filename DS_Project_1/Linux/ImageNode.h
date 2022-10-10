#include <string>
#include <iostream>

#ifndef IMAGENODE_H
#define IMAGENODE _H

using namespace std;

class ImageNode
{
public:
	string file_name;
	string dir_name;
	int index;

	ImageNode(string file_name, string dir_name, int index) :
	file_name(file_name), dir_name(dir_name), index(index) {};
};

#endif