struct PS_OUTPUT
{
	float4 Color:Color0;
};
struct PS_INPUT
{
    float4	Normal		: NORMAL; 
    float2	TC		  	: TEXCOORD0;
};
sampler diffuseMap:register( s0 ) = sampler_state
{
    Texture   = NULL;
    AddressU = Wrap;
    AddressV = Wrap;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};
PS_OUTPUT pMain(PS_INPUT input)
{
	PS_OUTPUT output;
	output.Color = tex2D(diffuseMap,input.TC);
	return output;
}