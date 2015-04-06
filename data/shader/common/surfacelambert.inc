struct SurfaceOutput
{
	float3 DiffuseColor;
	float3 Normal;
	float3 Emission;
	float  Alpha;
}


float3 CalLight(SurfaceOutput o,float atten,float3 lightDir,float lightIntensity,float3 lightColor)
{
	float ldn = dot(lightDir,o.Normal);
	return ldn * DiffuseColor * lightIntensity * lightColor * atten + Emission;
}
