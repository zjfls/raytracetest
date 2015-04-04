#pragma once
enum EMATARGTYPE
{
	EMATARGTYPEINVALID = 0,
	EMATARGTYPEFLOAT1 = 1,
	//EMATARGTYPEFLOAT2 = 2,
	//EMATARGTYPEFLOAT3 = 3,
	EMATARGTYPEFLOAT4 = 2,
	EMATARGTYPECOLOR = 3,
	EMATARGTYPEINT	= 4,
	EMATARGMATRIX33 = 5,
	EMATARGMATRIX44 = 6,
	EMATARGTYPESAMPLER = 7,
	EMATARGTYPENUM
};
enum EMATARGSHADERTYPE
{
	EMATSHADERVERTE = 1 << 0,
	EMATSHADERFRAG = 1 << 1
};
class RESOURCE_API MaterialArg
{
public:
	
	virtual ~MaterialArg();


	template<class T>
	T* GetData()
	{
		TMatArg<T>* pMatArg = (TMatArg<T>*)this;
		return &pMatArg->m_Data;
	};
	void SetShaderType(EMATARGSHADERTYPE eShadertype){ m_EShaderType = eShadertype; }
	string m_strName;
	EMATARGTYPE m_EType;
	EMATARGSHADERTYPE m_EShaderType;
protected:
	MaterialArg();
};
template < class T >
class TMatArg:public MaterialArg
{
public:
	TMatArg(EMATARGTYPE eArgType){ m_EType = eArgType; m_EShaderType = (EMATARGSHADERTYPE)(EMATSHADERVERTE | EMATSHADERFRAG); };
	virtual ~TMatArg(){};
	//template<class T1>
	//virtual T* GetValue() const{ return (T1*)&m_Data; };
	T m_Data;
};


//template<class T>
//TMatArg<T>* Material_Cast(MaterialArg* p)
//{
//
//}