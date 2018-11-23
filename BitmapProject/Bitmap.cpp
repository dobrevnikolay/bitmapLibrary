#include <fstream>

#include "Bitmap.h"
#include "BitmapFile.h"

namespace BitmapProject
{
	static bool hasEnding(std::string const &fullString, std::string const &ending) {
		if (fullString.length() >= ending.length()) {
			return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
		}
		else {
			return false;
		}
	}

	Bitmap::Bitmap(Bitmap &&other)
	{
		_width = other._width;
		_heigth = other._heigth;
		_pixels = std::move(other._pixels);
	}

	Bitmap& Bitmap::operator = (Bitmap && other)
	{
		_width = other._width;
		_heigth = other._heigth;
		_pixels = std::move(other._pixels);
		return *this;
	}


	Bitmap::Bitmap(unsigned width, unsigned heigth) : _width(width), _heigth(heigth),
		_pixels(std::make_unique<uint8_t[]>(width * heigth * 3)) //multiplied by 3 for each color
	{
	}

	Bitmap::Bitmap(const std::string& fileName)
	{
		read(fileName);
	}


	bool Bitmap::compare(Bitmap&& other)
	{
		if(_width != other._width || _heigth != other._heigth)
		{
			return false;
		}
		for(unsigned x{};x<_width; ++x)
		{
			for(unsigned y{}; y<_heigth; ++y)
			{
				if(getPixel(x,y) != other.getPixel(x,y))
				{
					return false;
				}
			}
		}

		return true;
	}

	Bitmap Bitmap::applyIfDifferent(Bitmap&& other, std::function<color(color, color)> applyToPixel)
	{
		if (_width != other._width || _heigth != other._heigth)
		{
			return Bitmap{_width,_heigth};
		}

		Bitmap newBitmap{ _width,_heigth };

		for (unsigned x{}; x < _width; ++x)
		{
			for (unsigned y{}; y < _heigth; ++y)
			{
				if (getPixel(x, y) != other.getPixel(x, y))
				{
					newBitmap.setPixel(x, y, applyToPixel(getPixel(x, y), other.getPixel(x, y)));
				}
			}
		}
		return newBitmap;
	}



	bool Bitmap::read(const std::string& fileName)
	{
		if (!hasEnding(fileName, ".bmp"))
		{
			return false;
		}
		BitmapFileHeader bitmap_file_header;
		BitmapInfoHeader bitmap_info_header;

		//std::basic_ifstream<unsigned char> file;

		std::ifstream file;
		file.open(fileName, std::ios::binary);
		if(!file)
		{
			return false;
		}
		
		file.read(( char*)&bitmap_file_header, sizeof(BitmapFileHeader));
		file.read(( char*)&bitmap_info_header, sizeof(BitmapInfoHeader));

		_width = bitmap_info_header.width;
		_heigth = bitmap_info_header.height;

		_pixels = std::make_unique<uint8_t[]>(_width * _heigth * 3);

		unsigned char * it = _pixels.get();

		file.read((char*)it, _width*_heigth * 3);
		file.close();
	}


	bool Bitmap::write(const std::string& fileName)
	{
		if(!hasEnding(fileName,".bmp"))
		{
			return false;
		}
		BitmapFileHeader bitmap_file_header;
		BitmapInfoHeader bitmap_info_header;

		bitmap_file_header.fileSize = sizeof(BitmapFileHeader) +
			sizeof(BitmapInfoHeader) + (_width * _heigth * 3);
		bitmap_file_header.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

		bitmap_info_header.width = _width;
		bitmap_info_header.height = _heigth;

		std::ofstream file;
		file.open(fileName, std::ios::out | std::ios::binary);

		if(!file)
		{
			return false;
		}

		file.write((const char *)&bitmap_file_header, sizeof(bitmap_file_header));
		file.write((const char *)&bitmap_info_header, sizeof(bitmap_info_header));
		file.write((const char *)_pixels.get(), _width * _heigth * 3);

		file.close();
		return true;
	}

	color Bitmap::getPixel(unsigned x, unsigned y)
	{
		color result;
		if (x < _width &&  y < _heigth)
		{			
			uint8_t *pixel = _pixels.get();
			pixel += y * 3 * _width + x * 3;	//* _width in order to go to the line, where this pixel is

			//bitmap is little endian file format
			result.blue = *pixel;
			result.green = *(pixel + 1);
			result.red = *(pixel + 2);			
		}
		return result;
	}


	void Bitmap::setPixel(unsigned x, unsigned y, color color)
	{
		if(x < _width &&  y < _heigth)
		{
			uint8_t *pixel = _pixels.get();
			pixel += y * 3 * _width + x * 3;	//* _width in order to go to the line, where this pixel is

			//bitmap is little endian file format
			*pixel = color.blue;
			*(pixel + 1) = color.green;
			*(pixel + 2) = color.red;
		}

	}


	Bitmap::~Bitmap()
	{
	}

}


