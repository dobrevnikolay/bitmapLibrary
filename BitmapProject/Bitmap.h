#pragma once
#include <string>
#include <functional>

namespace BitmapProject
{
	struct color
	{
		uint8_t red;
		uint8_t green;
		uint8_t blue;

		bool operator ==(const color& other) const
		{
			if(red == other.red && green == other.green && blue == other.blue)
			{
				return true;
			}
			return false;
		}
		bool operator != (const color& other) const
		{
			return !(other == *this);
		}
	};

	class Bitmap
	{
	private:
		unsigned _width{};
		unsigned _heigth{};
		std::unique_ptr<uint8_t[]> _pixels{nullptr};
	public:
		Bitmap(Bitmap && other);
		Bitmap(unsigned width, unsigned height);
		Bitmap(const std::string& fileName);
		bool read(const std::string& fileName);
		bool write(const std::string& fileName);
		void setPixel(const unsigned x, const unsigned y, const color color);
		color getPixel(unsigned x, unsigned y);
		bool compare(Bitmap && other);
		Bitmap applyIfDifferent(Bitmap && other, std::function<color(color, color)>);
		Bitmap& operator = (Bitmap&& other);
		~Bitmap();
	};
}


