#include "Triangle.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "InputLayout.h"
Triangle::Triangle(Graphics& g) : Drawable(g)
{
	struct Vertex { float x; float y; float z; float r; float g; float b; };
	std::vector<Vertex> vertices{
	   {-0.5,-0.5,  0.5  ,1,0,0},
		{0,0.5,  0  ,0,1,0},
		{0.5,-0.5,  0.5  ,0,0,1},
		{0,-0.5,  -0.5  ,1,0,1},
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
		{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	auto sh = std::make_unique<Shader<ID3D11VertexShader>>("..\\x64\\Debug\\VertexShader.cso", gfx.graphics);
	auto layout = std::make_unique<InputLayout>(idc, *sh, gfx.graphics);
	addBind(std::move(layout));

	addBind(std::move(sh));
	addBind(std::make_unique<Shader<ID3D11PixelShader>>("..\\x64\\Debug\\PixelShader.cso", gfx.graphics));


}


void Triangle::self_draw(float t)
{

	DirectX::XMFLOAT4X4 matrix;
	// put into matrix factory functions position information ie rotations , translations stored in class
	auto translation = DirectX::XMMatrixTranslation(0, 0, 3);
	auto rotation = DirectX::XMMatrixRotationRollPitchYaw(t / 1000.f, t / 1000.f, 0);
	auto projection = DirectX::XMMatrixPerspectiveLH(1, 1, 0.5, 10);
	DirectX::XMStoreFloat4x4(&matrix, DirectX::XMMatrixTranspose(rotation * translation * projection));

	updateTransformation(matrix);
	Drawable::draw();
}

std::size_t Triangle::indicesCount() const
{
	return idxCount;
}
