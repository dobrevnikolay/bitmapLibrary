#pragma once
//https://en.wikipedia.org/wiki/BMP_file_format

namespace BitmapProject
{

	#pragma pack(2)

	struct BitmapFileHeader
	{
		char header[2]{ 'B','M' };
		int32_t fileSize;
		int32_t reserved{};
		int32_t dataOffset;
	};

	#pragma  pack(2)

	struct BitmapInfoHeader
	{
		int32_t headerSize{40};
		int32_t width;
		int32_t height;
		int16_t planes{ 1 };
		int16_t bitsPerPixel{ 24 };
		int32_t compression{};
		int32_t dataSize{};
		int32_t horizontalResolution{ 2400 };
		int32_t verticalResolution{ 2400 };
		int32_t colors{};
		int32_t importantColors{};
	};

}
