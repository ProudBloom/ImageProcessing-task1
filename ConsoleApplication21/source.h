#include "CImg.h"
#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
using namespace cimg_library;

extern void Help();

CImg<double> Brightness(CImg<double> image, int x);

CImg<double> Negative(CImg<double> image);

CImg <double> Contrast(CImg<double> image, int value);

CImg <double> HorizontalFlip(CImg <double> image);

CImg <double> VerticalFlip(CImg <double> image);

CImg <double> DiagonalFlip(CImg <double> image);

CImg <double> Resize(CImg <double> image, int n_widht, int n_height);