#include "CImg.h"
#include "pch.h"
#include "source.h"
#include <iostream>
#include <string>
#include <vector>

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
		<< "--dflip" << endl << endl;
	cout << "ImgProc Application made by Mariusz Pisarski & Jakub Sztompka IT" << endl << "Ver. 0.1" << endl;
}

CImg <double> Brightness(CImg<double> image, int value)
{
	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				image(i, j, k) += value;
				if ((image(i, j, k)) > 255) image(i, j, k) = 255;
				else if ((image(i, j, k)) < 0) image(i, j, k) = 0;
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

CImg <double> Contrast(CImg<double> image, int value)
{
	float cont_factor;

	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				cont_factor = (259 * (value + 255)) / (255 * (259 - value));
				image(i, j, k) = ((image(i, j, k) - 127) * value) + 127;
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

CImg <double> AlphaTrimmedMeanFilter(CImg <double> image)
{
	CImg <double> result;
	typedef double element;

	int alpha = 4;
	//Start of the trimmed ordered set
	const int start = alpha >> 1;

	//End of trimmed, ordered set
	const int end = (image.width() * image.height()) - (alpha >> 1);

	//MASK MOVEMENT THROUGH ALL PIXELS OF IMAGE
	for (int m = 1; m < image.height() - 1; ++m)
	{
		for (int n = 1; n < image.width() - 1; ++n)
		{

			//Picking up mask elements
			int c = 0;
			element window[9];
			for (int j = m - 1; j < m + 2; ++j)
			{
				for (int i = n - 1; i < n + 2; ++i)
				{
					window[c++] = image(j * image.width() + i);
				}
			}

			//Ordering elements (necesary ones)
			for (int j = 0; j < end; ++j)
			{
				//Finding position of min element
				int min = j;
				for (int l = j + 1; l < 9; ++l)
				{
					if (window[l] < window[min])
					{
						min = l;
					}

					//Putting minimum element at its place
					const element temp = window[j];
					window[j] = window[min];
					window[min] = temp;
				}

				//Target index in resulting img
				const int target = (m - 1) * (image.width() - 2) + n - 1;

				//Getting result - mean value of the elements in trimmed set
				result[target] = window[start];
				for (int j = start + 1; j < end; ++j)
				{
					result[target] += window[j];
				}
				result[target] /= 9 - alpha;
			}
		}
	}
	return result;
}