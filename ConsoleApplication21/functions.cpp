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
		 << "--negative" <<  endl;
}

CImg <double> Brightness(CImg<double> image, int value)
{
	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				if ((image(i, j, k) + value) >= 255) image(i, j, k) = 255;
				if ((image(i, j, k) + value) <= 0) image(i, j, k) = 0;
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
			for (int k = 0; k < image.spectrum(); k++)
			{
				image(i, j, k) = 255 - image(i, j, k);
			}
		}
	}
	return image;
}

CImg <double> Contrast(CImg<double> image, float value)
{
	float cont_factor;

	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				cont_factor = (259 * (value + 255)) / (255 * (259 - value));
				image(i, j, k) = ((image(i, j, k) - 127) * cont_factor) + 127;
			}
		}
	}
	return image;
}

CImg <double> HorizontalFlip(CImg <double> image)
{
	for (int i = 0; i < image.width() / 2; i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				double temp = image(i, j, k);

				image(i, j, k) = image((image.width() - 1) - i, j, k);
				image((image.width() - 1) - i, j, k) = temp;
			}
		}
	}
	return image;
}

CImg <double> VerticalFlip(CImg <double> image)
{
	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height() / 2; j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				double temp = image(i, j, k);

				image(i, j, k) = image(i, (image.height() - 1) - j, k);
				image(i,(image.height() - 1) - j, k) = temp;
			}
		}
	}
	return image;
}

CImg <double> DiagonalFlip(CImg <double> image)
{
	for (int i = 0; i < image.width() / 2; i++)
	{
		for (int j = 0; j < image.height() / 2; j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				double temp = image(i, j, k);

				image(i, j, k) = image((image.width() - 1) - i, (image.height() - 1) - j, k);
				image((image.width() - 1) - i, (image.height() - 1) - j, k) = temp;
			}
		}
	}
	return image;
}