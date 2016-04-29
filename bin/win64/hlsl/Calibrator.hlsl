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
	float4 col : TEXCOORD;
};

struct VOut
{
	float4 pos : SV_POSITION;
	float4 col : TEXCOORD;
};

VOut main(VInput input)
{
	VOut output;

	float4x4 mvp = mul(entity_Xform, camera_VP);

	output.pos = mul(input.pos, mvp);
	output.col = input.col;

	return output;
}

float4 PShader(VOut input) : SV_TARGET
{
	return float4(0, 1, 0, 1);
}