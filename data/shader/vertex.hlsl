float4x4 mWorldViewProj;  // World * View * Projection transformatio
//-----------------------------------------------------------------------------
// Vertex shader output structure
//-----------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 	Position   	: POSITION;   // vertex position
    float4	Normal		: NORMAL; 
    float2	TC		  	: TEXCOORD0;
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
    Output.Position 	= 	mul( float4( input.Position, 1.0f ), mWorldViewProj ); 
    Output.Normal		=   float4(input.Normal,0.0f);
    Output.TC			=	input.TC;
    return Output;
}


