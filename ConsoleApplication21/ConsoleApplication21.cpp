#include "CImg.h"
#include "pch.h"
#include "source.h"
#include <iostream>
#include <string>

//TODO :

//		 (G4)Image shrinking(--shrink).
//		 (G5)Image enlargement(--enlarge).

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
	string operation(argv[2]);
	
	if (operation == "--negative")
	{
		Negative(image).save(argv[3]);
	}

	else if (operation == "--brightness")
	{
		Brightness(image, stoi(argv[3])).save(argv[4]);
	}

	else if (operation == "--contrast")
	{
		Contrast(image, stoi(argv[3])).save(argv[4]);
	}
	
	else if (operation == "--hflip")
	{
		HorizontalFlip(image).save(argv[3]);
	}
	
	else if (operation == "--vflip")
	{
		VerticalFlip(image).save(argv[3]);
	}

	else if (operation == "--dflip")
	{
		DiagonalFlip(image).save(argv[3]);
	}

	else if (operation == "--alpha")
	{
		AlphaTrimmedMeanFilter(image).save(argv[3]);
	}
	return 0;
}

//blinear linear polation 
//denoiaing image 
//