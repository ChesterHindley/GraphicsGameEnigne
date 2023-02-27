#pragma once
#include <vector>
#include <fstream>
#include <string_view>
class PPMImage
{
	int width, height;
public:
	struct Pixel { char r; char g; char b; char alpha; };
	PPMImage(std::string_view);
	PPMImage() = default;
	void* data();
	int getWidth() const;
	int getHeight() const;

private:
	class PPMImageLoader
	{
		

	public:
		std::vector<Pixel> operator()(std::string_view filename);
		int height, width;
		auto load(std::string_view filename);

	};
	
	std::vector<Pixel> pixels;









};


