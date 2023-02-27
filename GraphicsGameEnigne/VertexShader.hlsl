struct Vertex
{
	float2 tex: TexCoord;
	float4 v : SV_POSITION;
};

cbuffer buf
{
	matrix transform;

};


Vertex main(float3 pos : POSITION,float2 tex: TexCoord)
{
	Vertex v;
	v.v = mul(float4(pos, 1.0f), transform);
	v.tex = tex;

	return v;
}