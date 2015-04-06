struct SurfaceOutput
{
	float3 DiffuseColor;
	float3 Normal;
	float3 Emission;
	float3 SpeculatColor;
	float  SpecularPower;
	//float  Gloss;
	half   Alpha;
}


float3 CalLight(SurfaceOutput o,float atten,float3 lightDir,float lightIntensity,float3 lightColor)
{
	float3	Hn = normalize(lightDir + viewDir);
	float 	hdn = dot(Hn,o.Normal);
    float 	ldn = dot(lightDir,o.Normal);
    float3 spec = pow (hdn, o.SpecularPower * 32) * o.SpecularColor;
    
    
    return (DiffuseColor * ldn + spec) * lightIntensity * lightColor;
}


float4 fMain(PS_INPUT in):Color0
{
	in = (in)0;
	SurfaceOutput o = Surface(in);
#ifdef POINTLIGHT
	float atten = lightPointAtten(lightPos);
#endif
#ifdef SPOTLIGHT
	float atten = lightSpotAtten(lightPos);
#endif
#ifdef DIRLIGHT
	float atten = 1;
#endif
	float color = CalLight(o,atten,lightDir,lightIntensity,lightColor);
}