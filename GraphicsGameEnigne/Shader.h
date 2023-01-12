#pragma once
#include <fstream>
#include <filesystem>
#include <vector>
#include <wrl/client.h>
#include <d3d11.h>


namespace
{
	class Bindable;
	template<class T>
	class shader_gfx : protected Bindable{
		Microsoft::WRL::ComPtr<T> s;
	};
}

template <class T>
class Shader
{
	shader_gfx pShader;
	//Microsoft::WRL::ComPtr<T> s;
	std::vector<char> byteCode;
	std::size_t size;

private:
	void readShader(const std::string& fileName) {

		std::ifstream shaderFile;
		shaderFile.open(fileName, std::ios::binary | std::ios::in);

		shaderFile.read(byteCode.data(), size);
		shaderFile.close();
	};
	Shader& operator=(const Shader&) = delete;
	Shader() = delete;
	Shader(const Shader&) = delete;

public:
	Shader(const std::string& fileName)
		:byteCode(size = std::filesystem::file_size(fileName))  //dang how cool is this
	{
		readShader(fileName);
	};

	void* data()
	{
		return byteCode.data();
	};
	
	auto Get() 
	{
		return shader.Get();
	}

	auto operator&() { return &shader; }

	const std::size_t& getSize() { return size; };


};
