#include "CImg.h"
#include "pch.h"
#include "source.h"
#include <iostream>
#include <string>

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

	return 0;
}

//blinear linear polation 
//denoiaing image 
//