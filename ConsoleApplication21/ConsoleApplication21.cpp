// ConsoleApplication21.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include "CImg.h"
#include "pch.h"
#include "source.h"
#include <iostream>
#include <string>

using namespace std;
using namespace cimg_library;

void main(int argc, char *argv[])
{
	if (argc < 2) 
	{ 
		cout << "Incorrect number of arguments!" << endl;
		return;
	}

	string im(argv[1]);
	if (im == "--help")
	{
		Help();
		return;
	}

	CImg<double> image(argv[1]);
	string fun(argv[2]);
	
	if (fun == "--negative")
	{
		Negative(image).save(argv[3]);
	}

	if (fun == "--brightness")
	{
		Brightness(image, atoi(argv[3])).save(argv[4]);
	}
	
	
}

//blinear linear polation 
//denoiaing image 
//