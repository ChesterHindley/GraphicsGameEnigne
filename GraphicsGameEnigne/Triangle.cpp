#include "Triangle.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "InputLayout.h"
#include "PPMImage.h" 

Triangle::Triangle(float xoffset, float yoffset, float zoffset, float xrot, float yrot, float zrot, Graphics& g) : Drawable(g), xoffset{ xoffset }, yoffset{ yoffset }, zoffset{ zoffset },
rotx{ xrot }, roty{ yrot }, rotz{zrot}
{
	struct Vertex { float x; float y; float z; float r; float g; float b; };
	std::vector<Vertex> vertices{
	   {-0.5,-0.5,  0.5  ,0.5,0.5},
		{0,0.5,  0  ,0,0.5},
		{0.5,-0.5,  0.5 ,1,1},
		{0,-0.5,  -0.5  ,0,1},
	};
	// z from 0(close) to 1(far) :skull:
	// or not :skull: I DONT FUCKING KNOW( swearing increases code quality )


	addBind(std::make_unique<VertexBuffer<Vertex>>(std::move(vertices), gfx.graphics));

	std::vector<short int> indices =
	{
		2,1,0,
		0,1,3,
		2,3,1,
		2,0,3
	};
	idxCount = indices.size();

	addBind(std::make_unique<IndexBuffer>(indices, gfx.graphics));



	const std::vector<D3D11_INPUT_ELEMENT_DESC> idc =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	auto sh = std::make_unique<Shader<ID3D11VertexShader>>("..\\x64\\Debug\\VertexShader.cso", gfx.graphics);
	auto layout = std::make_unique<InputLayout>(idc, *sh, gfx.graphics);
	addBind(std::move(layout));

	addBind(std::move(sh));
	addBind(std::make_unique<Shader<ID3D11PixelShader>>("..\\x64\\Debug\\PixelShader.cso", gfx.graphics));

	PPMImage img("obama2.ppm");

	D3D11_TEXTURE2D_DESC texdesc;
	texdesc.Width = img.getWidth();
	texdesc.Height = img.getHeight();
	texdesc.MipLevels = 1;
	texdesc.ArraySize = 1;
	texdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texdesc.SampleDesc.Count = 1;
	texdesc.SampleDesc.Quality = 0;
	texdesc.Usage = D3D11_USAGE_DEFAULT;
	texdesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texdesc.CPUAccessFlags = 0;
	texdesc.MiscFlags = 0;


	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;

	D3D11_SUBRESOURCE_DATA data{ .pSysMem = img.data(),.SysMemPitch = sizeof(PPMImage::Pixel)*img.getWidth()};

	gfx.pDevice->CreateTexture2D(&texdesc,&data,&tex);

	D3D11_SHADER_RESOURCE_VIEW_DESC texViewDesc{
		.Format = texdesc.Format,
		.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D,
		.Texture2D{.MostDetailedMip = 0,.MipLevels = 1 }
	};

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texView;
	gfx.pDevice->CreateShaderResourceView(tex.Get(), &texViewDesc, &texView);
	gfx.pDeviceContext->PSSetShaderResources(0, 1, texView.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler;
	D3D11_SAMPLER_DESC samplerdesc{.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,.AddressU = D3D11_TEXTURE_ADDRESS_WRAP,.AddressV = D3D11_TEXTURE_ADDRESS_WRAP ,.AddressW = D3D11_TEXTURE_ADDRESS_WRAP };
	gfx.pDevice->CreateSamplerState(&samplerdesc, &sampler);
	gfx.pDeviceContext->PSSetSamplers(0, 1, sampler.GetAddressOf());
		




}


void Triangle::self_draw(float t)
{

	DirectX::XMFLOAT4X4 matrix;
	// put into matrix factory functions position information ie rotations , translations stored in class
	auto translation = DirectX::XMMatrixTranslation(xoffset, yoffset, zoffset);
	auto rotation = DirectX::XMMatrixRotationRollPitchYaw(t*rotx/10000, t*roty/10000, t*rotz/1000);
	auto projection = DirectX::XMMatrixPerspectiveLH(1, 1, 0.5, 10);
	DirectX::XMStoreFloat4x4(&matrix, DirectX::XMMatrixTranspose(rotation * translation * projection));

	updateTransformation(matrix);
	Drawable::draw();
}

std::size_t Triangle::indicesCount() const
{
	return idxCount;
}
