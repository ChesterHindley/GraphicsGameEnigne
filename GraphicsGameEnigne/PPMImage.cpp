#include "PPMImage.h"
#include <string>
#include <filesystem>
#include <ranges>
std::vector<PPMImage::Pixel> PPMImage::PPMImageLoader::operator()(std::string_view filename)
{

	std::ifstream file(filename.data(),std::ios::binary | std::ios::in);

	std::vector<char> unformatted(std::filesystem::file_size(filename));
	file.read(&unformatted[0], unformatted.size());
	if (file.gcount() != unformatted.size()) exit(-1);
	if (file.eof())
		exit(-1);
	auto split = std::views::split(unformatted, '\n');
	auto iter = split.begin(); // iterator on view of subrange
	auto format = *iter++;

	std::vector<Pixel> test;
	std::vector<PPMImage::Pixel> ret;

	if (std::string_view(format.begin(),format.end()) == "P6")
	{
		
		for (int i = 0; i < 2; ++i,++iter) //2 dictated by structure of header, skip all comments + max pixel's element value (cos it's always 255 right? ??)
		{
			auto line = std::string_view((*iter).begin(), (*iter).end());
			if (line.starts_with('#')) // comment deteced
			{
				--i;
				continue;
			}

			int scanwidth, scanheight;
			if (2 == sscanf_s(line.data(), "%d %d", &scanwidth, &scanheight)) 
			{
				width = scanwidth;
				height = scanheight;
				continue;
			}
		}

		
		unsigned long long byte_index = 0;
		char r, g, b;

		test.resize((long long)height * width);
		auto fillfn = [&byte_index, &r, &g, &b,&test](char i)
		{
			switch (byte_index % 3)
			{
			case 0:
				r = i;
				break;

			case 1:
				g = i;
				break;

			case 2:
				b = i;
				//ret
				test[byte_index/3] = { r, g, b,static_cast<char>(0xFF) };
				break;
			}
			byte_index++;


		};


#ifdef _DEBUG
		
		for (char* i = (*iter).data(); i != unformatted.data() + unformatted.size(); ++i)
		{
			fillfn(*i);
		}
#endif // DEBUG



		//for (; iter != split.end(); ++iter, fillfn('\n'))
		//{
		//	for (auto i: std::string_view((*iter).begin(), (*iter).end()))
		//	{
		//		fillfn(i);
		//	}
		//	
		//}
	}
	//for (;;);
	return test;
}

auto PPMImage::PPMImageLoader::load(std::string_view filename)
{
	return operator()(filename);
}

PPMImage::PPMImage(std::string_view filename)
{
	PPMImageLoader loader{};
	pixels = loader.load(filename);
	width = loader.width;
	height = loader.height;
}

void* PPMImage::data()
{
	return pixels.data();
}

int PPMImage::getWidth() const
{
	return width;
}

int PPMImage::getHeight() const
{
	return height;
}
