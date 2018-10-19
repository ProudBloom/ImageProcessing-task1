#include "CImg.h"
#include "pch.h"
#include "source.h"
#include <iostream>
#include <string>
using namespace std;
using namespace cimg_library;

void Help()
{
<<<<<<< HEAD
	cout << endl;
	cout << "================HELP MENU================" << endl;
	cout << "Following program loads a picture and changes it in a desired way." << endl;
	cout << "Syntax: <ProgramName> <InputPictureName> --SomeOption <value> <OutputPictureName>" << endl << endl;
	cout << "Possible options:" << endl
		<< "--brightness <value>" << endl
=======
	cout << "=====HELP MENU=====\n" << endl;
	cout << "Following program implements a picture and changes it in a desired way.\n" << endl;
	cout << "Syntax : " << endl;
	cout << endl << "<ProgramName> <InputPictureName> --SomeOption <value> <OutputPictureName>\n" << endl;
	cout << "Possible options:\n" << endl;
	cout << "--brightness <value>" << endl
>>>>>>> 99e4f3d19d03f733c6628da7e05810bb5ac45eba
		<< "--negative" << endl
		<< "--contrast <value>" << endl
		<< "--hflip" << endl
		<< "--vflip" << endl
<<<<<<< HEAD
		<< "--dflip" << endl << endl;
	cout << "ImgProc Application made by Mariusz Pisarski & Jakub Sztompka IT" << endl << "Ver. 0.1" << endl;
=======
		<< "--dflip" << endl;
>>>>>>> 99e4f3d19d03f733c6628da7e05810bb5ac45eba
}

CImg <double> Brightness(CImg<double> image, int value)
{
	

	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
<<<<<<< HEAD
				image(i, j, k) += value;
				if ((image(i, j, k)) > 255) image(i, j, k) = 255;
				else if ((image(i, j, k)) < 0) image(i, j, k) = 0;
=======
				if ((image(i, j, k) + value) >= 255)
				{
					image(i, j, k) = 255;
				}
				else if ((image(i, j, k) + value) <= 0) 
				{
					image(i, j, k) = 0;
				}
				else image(i, j, k) += value;
>>>>>>> 99e4f3d19d03f733c6628da7e05810bb5ac45eba
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

<<<<<<< HEAD
CImg <double> Contrast(CImg<double> image, int value)
{
	//float cont_factor;
=======
CImg <double> Contrast(CImg<double> image, float value)
{
	float cont_factor;
>>>>>>> 99e4f3d19d03f733c6628da7e05810bb5ac45eba

	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
<<<<<<< HEAD
				//cont_factor = (259 * (value + 255)) / (255 * (259 - value));
				image(i, j, k) = ((image(i, j, k) - 127) * value) + 127;
=======
				cont_factor = (259 * (value + 255)) / (255 * (259 - value));
				image(i, j, k) = ((image(i, j, k) - 127) * cont_factor) + 127;
>>>>>>> 99e4f3d19d03f733c6628da7e05810bb5ac45eba
			}
		}
	}
	return image;
}

CImg <double> HorizontalFlip(CImg <double> image)
{
<<<<<<< HEAD
	for (int i = 0; i < image.width() / 2; i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				double temp = image(i, j, k);

				image(i, j, k) = image((image.width() - 1) - i, j, k);
				image((image.width() - 1) - i, j, k) = temp;
=======
	for (int i = 0; i < (image.width()/2); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < 3; k++)
			{
				double temp = image(i, j, k);
				image(i, j, k) = image( (image.width()-1) - i, j, k);
				image( (image.width() - 1) - i, j, k) = temp;
>>>>>>> 99e4f3d19d03f733c6628da7e05810bb5ac45eba
			}
		}
	}
	return image;
}

<<<<<<< HEAD
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
=======
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
>>>>>>> 99e4f3d19d03f733c6628da7e05810bb5ac45eba
			}
		}
	}
	return image;
}

CImg <double> DiagonalFlip(CImg <double> image)
{
<<<<<<< HEAD
	for (int i = 0; i < image.width(); i++)
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
=======
	return  HorizontalFlip(VercicalFlip(image));
}

>>>>>>> 99e4f3d19d03f733c6628da7e05810bb5ac45eba
