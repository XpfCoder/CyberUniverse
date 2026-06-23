#include "../CommonShader.hlsli"

Texture2D g_Tex : register(t0);
Texture2DArray g_TexArray : register(t1);
SamplerState g_Sam : register(s0);

cbuffer CBDrawingStates : register(b4)
{
    float4 g_FogColor;
    int g_FogEnabled;
    float g_FogStart;
    float g_FogRange;
    float g_Pad2;
}


struct VertexPosNormalTex
{
    float3 posL : POSITION;
    float3 normalL : NORMAL;
    float2 tex : TEXCOORD;
};

struct VertexPosHWNormalTex
{
    float4 posH : SV_POSITION;
    float3 posW : POSITION; // 在世界中的位置
    float3 normalW : NORMAL; // 法向量在世界中的方向
    float2 tex : TEXCOORD;
};

struct PointSprite
{
    float3 posW : POSITION;
    float2 sizeW : SIZE;
};

struct BillboardVertex
{
    float4 posH : SV_POSITION;
    float3 posW : POSITION;
    float3 normalW : NORMAL;
    float2 tex : TEXCOORD;
    uint primID : SV_PrimitiveID;
};






