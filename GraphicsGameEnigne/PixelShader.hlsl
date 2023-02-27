Texture2D tex;

SamplerState s;

float4 main(float2 tc :TexCoord) : SV_TARGET
{
	return tex.Sample(s,tc);
}