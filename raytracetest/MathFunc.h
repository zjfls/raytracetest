#pragma once


float AngleToRad(float angle);
float Saturate(float fIn);
float Interpolate(float f1,float f2,float fInterp);

//fresnel effect
Vector3 GetRefracionDir(float fInRefraIndex, float fTransRefraIndex, const Vector3& vecInDir, const Vector3& vecNormal);
Vector3 GetReflectionDir(const Vector3& vecNormal, const Vector3& vecInDir);
float GetFresnelReflectance(float fInRefraIndex,float fTransRefraIndex,const Vector3& vecInDir,const Vector3& vecNormal);
float GetTransmitRadianceCoef(float fR,float fInRefraIndex,float fTransRefraIndex);