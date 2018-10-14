#include "CImg.h"
#include "pch.h"
#include "source.h"
#include <iostream>
#include <string>
using namespace std;
using namespace cimg_library;
void Help()
{
	cout << endl << "[ProgramName] [Picturename] --SomeOption" << endl;
	cout << "Program that implements a picture and changes it" << endl;
	cout << "Possible options:" << endl;
	cout << "--We_Have_None_Up_Until_Now" << endl << endl;
}

CImg<double> Brightness(CImg<double> image, int x)
{
	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if ((image(i, j, k) + x) >= 255) image(i, j, k) = 255;
				if ((image(i, j, k) + x) <= 0) image(i, j, k) = 0;
				else image(i, j, k) += x;
			}
		}
	}
	return image;
}

CImg<double> Negative(CImg<double> image)
{
	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < 3; k++)
			{
				image(i, j, k) = 255 - image(i, j, k);
			}
		}
	}
	return image;
}