TextureCube cubeMap;
SamplerState diffuseSampler;

SamplerState samTriLinearSam
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

cbuffer CameraConstantsBuffer : register(b0)
{
	float4x4 camera_VP;
}

cbuffer EntityConstantsBuffer : register(b1)
{
	float4x4 entity_Xform;
}

struct VInput
{
	float4 pos : POSITION;
};

struct VOut
{
	float4 pos      : SV_POSITION;
	float3 posLocal : TEXCOORD;
};

VOut main(VInput input)
{
	VOut output;

	float4x4 mvp = mul(entity_Xform, camera_VP);

	output.pos = mul(input.pos, mvp).xyww;
	output.posLocal = input.pos.xyz;

	return output;
}

float4 PShader(VOut input) : SV_TARGET
{
	return cubeMap.Sample(samTriLinearSam, input.posLocal);
}