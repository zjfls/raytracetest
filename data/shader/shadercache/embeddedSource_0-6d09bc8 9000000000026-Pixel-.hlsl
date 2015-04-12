float4 GAMEAMBIENTCOLOR;
float GAMELIGHTINTENSITY;
float4 GAMELIGHTCOLOR;
float3 GAMELIGHTPOS;
float lightPointAtten(float3 lightPos,float3 worldPos)
{
	float r = distance(lightPos,worldPos);
	float atten = 1 / ((r * r) * 0.001 + r * 0.02 + 0.5);
	return atten;
}
struct SurfaceOutput
{
	float3 DiffuseColor;
	float3 Normal;
	float3 Emission;
	float3 SpecularColor;
	float  SpecularPower;
	float   Alpha;
};

float3 CalLight(SurfaceOutput o,float atten,float3 viewDir,float3 lightDir,float lightIntensity,float3 lightColor)
{
	                                 
	float3	Hn = normalize(lightDir + viewDir);
	float 	hdn = saturate(dot(Hn,o.Normal)) ;
    float 	ldn = saturate(dot(lightDir,o.Normal));
    float3 spec = pow (hdn, o.SpecularPower) * o.SpecularColor * ldn;
                 
  	return (o.DiffuseColor * ldn + spec) * lightIntensity * lightColor;

    
    
}
sampler DiffuseColor = sampler_state
{
};
sampler EmissiveColor = sampler_state
{
};
sampler NormalMap = sampler_state
{
};
sampler SpecularColor = sampler_state
{
};
float specPower;
struct PS_INPUT
{
    float4	Normal			: TEXCOORD0; 
    float2	TC		  		: TEXCOORD1;
	float3	worldPosition	: TEXCOORD2;
	float3	Tangent			: TEXCOORD3;
	float3	Binormal		: TEXCOORD4;
	float3	WorldEyeVec		: TEXCOORD5;
};
     
              

SurfaceOutput Surface(PS_INPUT input)
{
	SurfaceOutput o;
	float4 diffTex = tex2D(DiffuseColor,input.TC.xy).rgba;
	o.DiffuseColor = diffTex.rgb * 0.7;
	o.SpecularColor = tex2D(SpecularColor,input.TC.xy).rgb * 1.5;
	                              
	o.Emission = tex2D(EmissiveColor,input.TC.xy).rgb;
	float3 Nt = tex2D(NormalMap,input.TC.xy).xyz * 2 - 1;
    float3 Nn = normalize(input.Normal);
    float3 Tn = normalize(input.Tangent);
    float3 Bn = normalize(input.Binormal);
    float3x3 tbn  = float3x3(Tn,Bn,Nn);
	float3 Nb = mul(Nt,tbn);
	o.Normal = normalize(Nb);
	
	o.Alpha = diffTex.a;
	  
	o.SpecularPower = 32;
	return o;
}
float4 pMain(PS_INPUT input):Color0
{
	//input = (PS_INPUT)0;
	SurfaceOutput o = Surface(input);
float atten = lightPointAtten(GAMELIGHTPOS,input.worldPosition);
float3 lightdir = GAMELIGHTPOS - input.worldPosition;
lightdir = normalize(lightdir);
float4 Color;
//float3 eyevec = normalize(input.WorldEyeVec);
Color.rgb = CalLight(o,atten,input.WorldEyeVec,lightdir,GAMELIGHTINTENSITY,GAMELIGHTCOLOR.rgb).rgb;
Color.rgb += o.DiffuseColor * GAMEAMBIENTCOLOR;
Color.a = o.Alpha;
return Color;
}
