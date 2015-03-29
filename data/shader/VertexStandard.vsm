float4x4 mWorld;	// World * View * Projection transformatio
float4x4 mViewProj;			//Projection
//-----------------------------------------------------------------------------
// Vertex shader output structure
//-----------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 	Position   		: POSITION;   // vertex position
    float4	Normal			: NORMAL; 
    float2	TC		  		: TEXCOORD0;
	float3	worldPosition	: TEXCOORD1;
};
struct VS_INPUT
{
	float3	Position	:POSITION;
	float3	Normal		:NORMAL;
	float2	TC			:TEXCOORD0;
};


VS_OUTPUT vMain( VS_INPUT input )
{
	VS_OUTPUT Output;
	Output.worldPosition	=	mul(float4(input.Position, 1.0f), mWorld);
	Output.Position			=	mul(float4(Output.worldPosition, 1.0f), mViewProj);
    Output.Normal			=   float4(input.Normal,0.0f);
    Output.TC				=	input.TC;
    return Output;
}


