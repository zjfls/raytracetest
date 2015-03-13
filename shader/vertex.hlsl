float4x4 mWorldViewProj;  // World * View * Projection transformatio
//-----------------------------------------------------------------------------
// Vertex shader output structure
//-----------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Position   : POSITION;   // vertex position 
    float2	Texture		:TEXCOORD0;
};

VS_OUTPUT Ripple( in float2 vPosition : POSITION )
{
	VS_OUTPUT Output;
    Output.Position = mul( float4( vPosition.x, fSin * 0.1f, vPosition.y, 1.0f ), mWorldViewProj );   
    return Output;
}


