#include "BasicPrimitive.hlsli"

Texture2D g_Tex : register(t0);
SamplerState g_SamplerState : register(s0);
Texture2D g_ShadowMap : register(t1);
SamplerComparisonState g_SamShadow : register(s1);

float4 PS(VertexOut pIn) : SV_Target
{

	float4 color;
	if (!isUseTex)
	{
		color = texColor;
		return color;
	}
	else
	{
		color = g_Tex.Sample(g_SamplerState, pIn.texcoord);
	}
	
	return color;
	//return float4(shadow,0,0 ,1.0f);
}