#include "CImg.h"
#include "pch.h"
#include "source.h"
#include <iostream>
#include <string>
using namespace std;
using namespace cimg_library;

void Help()
{
	cout << "=====HELP MENU=====\n" << endl;
	cout << "Following program implements a picture and changes it in a desired way.\n" << endl;
	cout << "Syntax : " << endl;
	cout << endl << "<ProgramName> <InputPictureName> --SomeOption <value> <OutputPictureName>\n" << endl;
	cout << "Possible options:\n" << endl;
	cout << "--brightness <value>" << endl
		<< "--negative" << endl
		<< "--contrast <value>" << endl
		<< "--hflip" << endl
		<< "--vflip" << endl
		<< "--dflip" << endl;
}

CImg <double> Brightness(CImg<double> image, int value)
{
	

	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if ((image(i, j, k) + value) >= 255)
				{
					image(i, j, k) = 255;
				}
				else if ((image(i, j, k) + value) <= 0) 
				{
					image(i, j, k) = 0;
				}
				else image(i, j, k) += value;
			}
		}
	}
	return image;
}

CImg <double> Negative(CImg<double> image)
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

CImg <double> Contrast(CImg<double> image, int value)
{
	double cont_factor;

	
	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cont_factor = value * ((image(i, j, k) - 127));

				if ((value - 127) + 127 > 255)
				{
					image(i, j, k) = 255;
				}
				else if (value + 127 < 0)
				{
					image(i, j, k) = 0;
				}
				else
				{
					image(i, j, k) = cont_factor + 127;
				}
			}
		}
	}
	return image;
}

CImg <double> HorizontalFlip(CImg <double> image)
{
	for (int i = 0; i < (image.width()/2); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < 3; k++)
			{
				double temp = image(i, j, k);
				image(i, j, k) = image( (image.width()-1) - i, j, k);
				image( (image.width() - 1) - i, j, k) = temp;
			}
		}
	}
	return image;
}

CImg <double> VercicalFlip(CImg <double> image)
{
	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < (image.height()/2); j++)
		{
			for (int k = 0; k < 3; k++)
			{
				double temp = image(i, j, k);
				image(i, j, k) = image(i, (image.height() - 1) - j, k);
				image (i, (image.height() - 1) - j, k) = temp;
			}
		}
	}
	return image;
}

CImg <double> DiagonalFlip(CImg <double> image)
{
	return  HorizontalFlip(VercicalFlip(image));
}
