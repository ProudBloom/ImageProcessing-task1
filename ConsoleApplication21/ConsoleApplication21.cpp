#include "CImg.h"
#include "pch.h"
#include "source.h"
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

//TODO :



//		 (N3) Alpha-trimmed mean filter (--alpha),
//			  contraharmonic mean filter (--cmean).

//		 (E1)Mean square error (--mse).
//		 (E2)Peak mean square error(--pmse).
//		 (E3)Signal to noise ratio(--snr).
//		 (E4)Peak signal to noise ratio(--psnr).
//		 (E5)Maximum difference(--md).


using namespace std;
using namespace cimg_library;

int main(int argc, char *argv[])
{
	if (argc < 2) 
	{ 
		cout << "Incorrect number of arguments!" << endl;
	}

	string im(argv[1]);
	if (im == "--help")
	{
		Help();
		return 0;
	}

	CImg<double> image(argv[1]);
	string fun(argv[2]);
	
	if (fun == "--negative")
	{
		Negative(image).save(argv[3]);
	}

	else if (fun == "--brightness")
	{
		Brightness(image, stoi(argv[3])).save(argv[4]);
	}

	else if (fun == "--contrast")
	{
		Contrast(image, stoi(argv[3])).save(argv[4]);
	}

	else if (fun == "--hflip")
	{
		HorizontalFlip(image).save(argv[3]);
	}

	else if (fun == "--vflip")
	{
		VerticalFlip(image).save(argv[3]);
	}

	else if (fun == "--dflip")
	{
		DiagonalFlip(image).save(argv[3]);
	}

	else if (fun == "--resize")
	{
		Resize(image, atoi(argv[3]), atoi(argv[4])).save(argv[5]);
	}

	else if (fun == "--cmean")
	{
		if (atoi(argv[4])<1)
		{
			cout << "Incorrect windowsize!!!" << endl;
			return 0;
		}
		
		Contraharmonic(image, atoi(argv[3]), atoi(argv[4])).save(argv[5]);
	}

	else if (fun == "--mmean")
	{
		cout << "checkpoint 1" << endl;
		Mean(image, atoi(argv[3])).save(argv[4]);
	}

	else if (fun == "--mse")
	{
		CImg <double> image2(argv[3]);

		MeanSquareError(image, image2);
	}
		
	else if (fun == "--pmse")
	{
		CImg <double> image2(argv[3]);

		PeakMeanSquareError(image, image2);
	}

	else if (fun == "--snr")
	{
		CImg <double> image2(argv[3]);

		SignalNoiseRatio(image, image2);
	}

	else if (fun == "--psnr")
	{
		CImg <double> image2(argv[3]);

		PeakSignalNoiseRatio(image, image2);
	}

	return 0;
}