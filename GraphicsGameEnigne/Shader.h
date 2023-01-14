#pragma once
#include <fstream>
#include <filesystem>
#include <vector>
#include "Bindable.h"
#include <tuple>


template <class T>
concept shader_type = std::same_as<T, ID3D11VertexShader> || std::same_as<T, ID3D11PixelShader>;
template <shader_type T>
class Shader : public Bindable
{

	Microsoft::WRL::ComPtr<T> shader;
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
	Shader(const std::string& fileName,Graphics& g)
		:
		Bindable(g),
		byteCode(size = std::filesystem::file_size(fileName))  //dang how cool is this
	{
		readShader(fileName);
		auto arguments = std::make_tuple(gfx.pDevice.Get(), byteCode.data(), size, nullptr, shader.GetAddressOf());
		if constexpr (std::same_as<T, ID3D11VertexShader>)
		{
			std::apply(&ID3D11Device::CreateVertexShader, arguments); // callable object, arguments for it
			//gfx.pDevice->CreateVertexShader(byteCode.data(), size, nullptr, shader.GetAddressOf());
		}
		else if constexpr (std::same_as<T, ID3D11PixelShader>)
		{
			std::apply(&ID3D11Device::CreatePixelShader, arguments);
			//gfx.pDevice->CreatePixelShader(byteCode.data(), size, nullptr, shader.GetAddressOf());
		}

	};

	auto data() const
	{
		return byteCode.data();
	};
	
	auto Get() 
	{
		return shader.Get();
	}

	auto operator&() { return &shader; }

	const std::size_t& getSize() const { return size; };
	
	void bind() override 
	{
		if constexpr (std::same_as<T, ID3D11VertexShader>)
		{
			gfx.pDeviceContext->VSSetShader(shader.Get(), nullptr, 0);

		}
		else if constexpr (std::same_as<T, ID3D11PixelShader>)
		{
			gfx.pDeviceContext->PSSetShader(shader.Get(), nullptr, 0);
		}

			
	}
	

};
