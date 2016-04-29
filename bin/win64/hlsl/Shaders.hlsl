Texture2D diffuseTexture;
SamplerState diffuseSampler;

cbuffer CameraConstantsBuffer : register(b0)
{
	float4x4 camera_VP;
}

cbuffer EntityConstantsBuffer : register(b1)
{
	float4x4 entity_Xform;	// 4x16
	float1 alpha;			// 1x16
}

struct VInput
{
	float4 position : POSITION;
	float2 uvR : TEXCOORD0;
	float2 uvG : TEXCOORD1;
	float2 uvB : TEXCOORD2;
	float2 chroma : TEXCOORD3;
};

struct VOut
{
	float4 position : SV_POSITION;
	float2 uvR : TEXCOORD0;
	float2 uvG : TEXCOORD1;
	float2 uvB : TEXCOORD2;
	float2 chromalpha : TEXCOORD3;	// chroma and alpha
};

VOut main(VInput input)
{
	VOut output;

	float4x4 mvp = mul(entity_Xform, camera_VP);

		output.position = mul(input.position, mvp);
	output.uvR = input.uvR;
	output.uvB = input.uvB;
	output.uvG = input.uvG;
	output.chromalpha.x = input.chroma.x;
	output.chromalpha.y = alpha;

	return output;
}

float4 PShader(VOut input) : SV_TARGET
{
	float r = diffuseTexture.Sample(diffuseSampler, input.uvR).r;
	float g = diffuseTexture.Sample(diffuseSampler, input.uvG).g;
	float b = diffuseTexture.Sample(diffuseSampler, input.uvB).b;

	float4 outColor = float4(r, g, b, 1.0) * input.chromalpha.x;
	outColor.a = input.chromalpha.y;
	
	return outColor;
}