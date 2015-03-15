struct PS_OUTPUT
{
	float4 Color:Color0;
};
struct PS_INPUT
{
    float4	Normal			: NORMAL; 
    float2	TC		  		: TEXCOORD0;
	float3	worldPosition	: TEXCOORD1;
};
static const float3 ambientColor = {0.3f,0.3f,0.3f};
uniform float3 lightDir;
static const float3	lightColor = {1.0f,1.0f,1.0f};
static const float	lightIntensity = 1.0f;
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
	output.Color = 0.0f;
	float3 radianceColor = ambientColor + dot(input.Normal,lightDir)* lightColor * lightIntensity;
	//float3 lightDir = 
	output.Color.rgb = tex2D(diffuseMap, input.TC).rgb * radianceColor;
	return output;
}