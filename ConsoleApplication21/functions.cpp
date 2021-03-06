#include "CImg.h"
#include "pch.h"
#include "source.h"
#include <iostream>
#include <math.h>
#include <string>
#include <cmath>

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
		<< "--dflip" << endl
		<< "--cmean <OrderOfFilter> <WindowSize>" << endl
		<< "--mse <image2>" << endl
		<< "--pmse <image2>" << endl
		<< "--snr <image2>" << endl
		<< "--psnr <image2>" << endl
		<< "--md <image2>" << endl << endl;
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



CImg <double> Contrast(CImg<double> image, float value)
{
	float cont_factor;
	cont_factor = (259 * (value + 255)) / (255 * (259 - value));

	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				image(i, j, k) = ((image(i, j, k) - 127) * cont_factor) + 127;
				if (image(i, j, k) > 255) image(i, j, k) = 255;
				else if (image(i, j, k) < 0) image(i, j, k) = 0;
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
				image(i, (image.height() - 1) - j, k) = temp;
			}
		}
	}
	return image;
}



CImg <double> DiagonalFlip(CImg <double> image)
{
	
	return VerticalFlip(HorizontalFlip(image));
}



CImg <double> Resize(CImg <double> image, int n_widht, int n_height)
{
	CImg <double> n_image(n_widht, n_height, 1, 3, 0);
	float frac_x = (float)image.width() / (float)n_widht;
	float frac_y = (float)image.height() / (float)n_height;


	for (int i = 0; i < n_widht; i++)
	{
		for (int j = 0; j < n_height; j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				n_image(i, j, k) = image((int)(i*frac_x), (int)(j*frac_y), k);
			}

		}

	}
	return   n_image;
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



double MeanSquareError(CImg <double> image, CImg <double> image2)
{
	double diff_sum = 0;

	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				diff_sum += pow((image(i, j, k) - image2(i, j, k)), 2);
			}
		}
	}
	double mse = diff_sum / (image.width()*image.height());
	cout << "Mean square error : " << mse << endl;

	return mse;
}



double PeakMeanSquareError(CImg <double> image, CImg <double> image2)
{
	double maximum = 0;
	double diff_sum = 0;

	for (int i = 0; i < image.width(); i++)	//MAXIMUM
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				if (maximum < image(i, j, k))
				{
					maximum = image(i, j, k);
				}
			}
		}
	}

	for (int i = 0; i < image.width(); i++)	//MSE
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				diff_sum += pow((image(i, j, k) - image2(i, j, k)), 2);
			}
		}
	}
	double mse = diff_sum / (image.width()*image.height());
	double pmse = (mse) / (pow(maximum, 2));
	cout << "Peak Mean square error : " << pmse << endl;

	return pmse;
}



double SignalNoiseRatio(CImg <double> image, CImg <double> image2)
{
	double sum = 0;
	double diff_sum = 0;
	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				sum += pow(image(i, j, k), 2);
				diff_sum += pow((image(i, j, k) - image2(i, j, k)), 2);
			}
		}
	}
	double snr = 10 * log10(sum / diff_sum);

	cout << "Signal to noise ratio : " << snr << "[dB]" <<  endl;
	return snr;
}



double PeakSignalNoiseRatio(CImg <double> image, CImg <double> image2)
{
	double diff_sum = 0;
	double maximum = 0;

	for (int i = 0; i < image.width(); i++)	//MAXIMUM
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				if (maximum < image(i, j, k))
				{
					maximum = image(i, j, k);
				}
			}
		}
	}

	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				diff_sum += pow((image2(i, j, k) - image(i, j, k)), 2);
			}
		}
	}
	double psnr = 10 * log10((maximum*maximum) / diff_sum);

	cout << "Peak signal to noise ratio : " << psnr << "[dB]" << endl;
	return psnr;
}



double MaximumDifference(CImg <double> image, CImg <double> image2)
{

	double difference, max;

	for (int i = 0; i < image.width(); i++)
	{
		for (int j = 0; j < image.height(); j++)
		{
			for (int k = 0; k < image.spectrum(); k++)
			{
				max = image(0, 0, k) - image2(0, 0, k);
				difference = abs(image(i, j, k) - image2(i, j, k));

				if (max < difference)
				{
					difference = max;
				}
			}
		}
	}

	cout << "Max difference : " << abs(max) << endl;
	return max;
}



CImg <double> Contraharmonic(CImg <double> image, int order, int windowsize)
{
	
	
	CImg <double> result (image.width(), image.height(), image.depth(), image.spectrum(), 0);
	double temp = 0;
	double temp2 = 0;
	float size_temp = ((windowsize / 2) + (1 / 2));
	
	for (float i = 0; i < image.width(); i++)
	{	
		for (float j = 0; j < image.height(); j++)
		{		
			for (int k = 0; k < image.spectrum(); k++)
			{
				temp = 0;
				temp2 = 0;
				for (float x = i - size_temp; x <= i + size_temp; x++)
				{
					if (x < 0 || x >= image.width()) { continue; }

					for (float y = j - size_temp; y <= j + size_temp; y++)
					{
						if (y < 0 || y >= image.height()) { continue; }
						
						temp += pow(image(x, y, k), order + 1);
						temp2 += pow(image(x, y, k), order);
					}
				}
				result(i, j, k) = temp / temp2;
			}
		}
	}

	return result;
}



CImg <double> Mean(CImg <double> image, int order)
{

	cout << "checkpoint" << endl;
	CImg <double> result(image.width(), image.height(), image.depth(), image.spectrum(), 0);
	double temp = 0;
	int counter = 0;

	for (int i = 0; i < image.width(); i++)
	{
		cout << i << "/" << image.width() << endl;

		for (int j = 0; j < image.height(); j++)
		{

			for (int k = 0; k < image.spectrum(); k++)
			{
				counter = 0;
				temp = 0;
				for (int x = i - 1; x <= i + 1; x++)
				{
					if (x < 0 || x >= image.width()) { continue; }

					for (int y = j - 1; y <= j + 1; y++)
					{
						if (y < 0 || y >= image.height()) { continue; }
						counter++;
						temp += image(x, y, k);
					}
				}

				result(i, j, k) = temp / counter;

			}
		}
	}

	return result;
}