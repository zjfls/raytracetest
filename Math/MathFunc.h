#pragma once
#include "Vector3.h"
namespace ZG
{
	MATH_API float AngleToRad(float angle);
	MATH_API float Saturate(float fIn);
	MATH_API float Interpolate(float f1, float f2, float fInterp);

	template<class T>
	__declspec(dllexport) T Interpolate(T t1, T t2, float fInterp);
	//fresnel effect
	MATH_API Vector3 GetRefracionDir(float fInRefraIndex, float fTransRefraIndex, const Vector3& vecInDir, const Vector3& vecNormal);
	MATH_API Vector3 GetReflectionDir(const Vector3& vecInDir, const Vector3& vecNormal);
	MATH_API float GetFresnelReflectance(float fInRefraIndex, float fTransRefraIndex, const Vector3& vecInDir, const Vector3& vecNormal);
	MATH_API float GetTransmitRadianceCoef(float fR, float fInRefraIndex, float fTransRefraIndex);
	MATH_API float GetTransmitRadianceCoef(float fInRefraIndex, float fTransRefraIndex, const Vector3& vecInDir, const Vector3& vecNormal);

	template<class T>
	__declspec(dllexport) T ZG::Interpolate(T t1, T t2, float fInterp)
	{
		return t1 * (1 - fInterp) + t2 * fInterp;
	}

}

