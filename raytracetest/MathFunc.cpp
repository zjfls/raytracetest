#include "stdafx.h"
#include "MathFunc.h"


float AngleToRad(float angle)
{
	return angle * PI / 180.0f;
}

Vector3 GetReflectionDir(const Vector3& vecNormal, const Vector3& vecInDir)
{
	Vector3 vecReflect;
	vecReflect = vecNormal * (vecNormal.dot(-vecInDir)) * 2 - (-vecInDir);
	return vecReflect;
}

Vector3 GetRefracionDir(float fInRefraIndex, float fTransRefraIndex, const Vector3& vecInDir, const Vector3& vecNormal)
{
	Vector3 vecRefract;
	float cosi = vecNormal.dot(-vecInDir);
	float cosi2 = cosi * cosi;
	float sini2 = 1 - cosi2;
	float sini = sqrt(sini2);
	float sint = sini * fInRefraIndex / fTransRefraIndex;
	float sint2 = sint * sint;
	float cost2 = 1 - sint2;
	float cost = sqrt(cost2);


	Vector3 vecVertDir = vecInDir - vecNormal*cosi;
	vecVertDir.normalize();
	vecRefract = -vecNormal * cost + vecVertDir * sint;
	vecRefract.normalize();
	return vecRefract;

}

float GetFresnelReflectance(float fInRefraIndex, float fTransRefraIndex, const Vector3& vecInDir, const Vector3& vecNormal)
{
	float fIndexRatio = fTransRefraIndex / fInRefraIndex;
	float fR0 = pow((1- fIndexRatio)/(1 + fIndexRatio),2);
	float fCosi = Saturate(vecNormal.dot(-vecInDir));
	return fR0 + (1 - fR0) * pow(1-fCosi,5);

}

float Saturate(float fIn)
{
	if (fIn <= 0.0f)
	{
		return 0.0f;
	}
	if (fIn >= 1.0f)
	{
		return 1.0f;
	}
	return fIn;
}

float GetTransmitRadianceCoef(float fR, float fInRefraIndex, float fTransRefraIndex)
{
	float fIndexRatio = fTransRefraIndex / fInRefraIndex;
	return (1 - fR) * fIndexRatio * fIndexRatio;
}

float Interpolate(float f1, float f2, float fInterp)
{
	return f1 * (1 - fInterp) + f2 * fInterp;
}


