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

//		 (E1) Mean square error (--mse).
//		 (E2)Peak mean square error(--pmse).
//		 (E3)Signal to noise ratio(--snr).
//		 (E4)Peak signal to noise ratio(--psnr).
//		 (E5)Maximum difference(--md)


using namespace std;
using namespace cimg_library;

void main(int argc, char *argv[])
{
	if (argc < 2) 
	{ 
		cout << "Incorrect number of arguments!" << endl;
		return;
	}

	//====================================================
	string im(argv[1]);
	if (im == "--help")
	{
		Help();
		return;
	}
	//====================================================== 


	//===================================================
	CImg<double> image(argv[1]);
	string fun(argv[2]);
	//====================================================


	//============================================================
	if (fun == "--negative")
	{
		Negative(image).save(argv[3]);
	}

	if (fun == "--brightness")
	{
		Brightness(image, atoi(argv[3])).save(argv[4]);
	}

	if (fun == "--contrast")
	{
		Contrast(image, atoi(argv[3])).save(argv[4]);
	}
	
	if (fun == "--hflip")
	{
		HorizontalFlip(image).save(argv[3]);
	}
	
	if (fun == "--vflip") 
	{
		VercicalFlip(image).save(argv[3]);
	}

	if (fun == "--dflip")
	{
		DiagonalFlip(image).save(argv[3]);
	}
	//=============================================================
}

//blinear linear polation 
//denoiaing image 
//