cbuffer MatrixBuffer
{
	matrix world;
	matrix view;
	matrix projection;
};

struct VertexInput
{
	float4 position : POSITION;
	float4 colour : COLOR;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 colour : COLOR;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

PixelInput main(VertexInput input)
{
	PixelInput output;
	input.position.w = 1.0f;
	
	// Model to world space
	float4 position = mul(input.position, world);

	// World space to view space
	position = mul(position, view);

	// Apply projection matrix
	position = mul(position, projection);

	// Pass through transformed position into pixel shader
	output.position = position;

	// Transform normal from model to world space
	// Lighting calculations need world space normals otherwise lighting won't change when the object rotates
	output.normal = mul(input.normal, (float3x3)world);

	// Pass through colour and texture coordinates unchanged
	output.colour = input.colour;
	output.uv = input.uv;
	
	return output;
}