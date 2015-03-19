#pragma once
enum EMATARGTYPE
{
	EMATARGTYPEINVALID = 0,
	EMATARGTYPEFLOAT1 = 1,
	EMATARGTYPEFLOAT2 = 2,
	EMATARGTYPEFLOAT3 = 3,
	EMATARGTYPEFLOAT4 = 4,
	EMATARGTYPECOLOR = 5,
	EMATARGTYPEINT	= 6,
	EMATARGTYPESAMPLER = 7,
	EMATARGTYPENUM
};
class MaterialArg
{
public:
	MaterialArg();
	virtual ~MaterialArg();


	template<class T>
	T* GetData()
	{
		TMatArg<T>* pMatArg = (TMatArg<T>*)this;
		return &pMatArg->m_Data;
	};
	string m_strName;
	EMATARGTYPE m_EType;
};
template < class T >
class TMatArg:public MaterialArg
{
public:
	TMatArg(EMATARGTYPE eArgType){ m_EType = eArgType; };
	virtual ~TMatArg();
	//template<class T1>
	//virtual T* GetValue() const{ return (T1*)&m_Data; };
	T m_Data;
};


//template<class T>
//TMatArg<T>* Material_Cast(MaterialArg* p)
//{
//
//}