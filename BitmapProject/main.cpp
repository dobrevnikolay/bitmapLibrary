#include <iostream>
#include "Bitmap.h"
#include <algorithm>

#define WIDTH 800
#define HEIGHT 600

int main()
{
	BitmapProject::Bitmap bitmap{ WIDTH,HEIGHT };

	BitmapProject::color mycolor{ 0xff,0xff,0xff };

	double min = std::numeric_limits<double>::max();
	double max = std::numeric_limits<double>::min();

	for(int x{}; x< WIDTH; ++x)
	{
		for(int y{};y< HEIGHT; ++y)
		{
			double xFractal = (x - WIDTH / 2) *2.0 / WIDTH;
			double yFractal = (x - HEIGHT / 2) *2.0 / HEIGHT;;

			if(xFractal < min)
			{
				min = xFractal;
			}
			if(xFractal > max)
			{
				max = xFractal;
			}
			bitmap.setPixel(x, y, {0xff,0,0});
		}
	}
	
	
	std::cout<<bitmap.write("test.bmp");

	BitmapProject::Bitmap readBitmap{ "test.bmp" };

	

	for (int x{}; x < 800; ++x)
	{
		for (int y{}; y < 600; ++y)
		{
			readBitmap.setPixel(x, y, { 0,0xFF,0 });
		}
	}


	readBitmap.write("new.bmp");

	std::cout << "Finished";
}
