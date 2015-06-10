#pragma once
//#include "VertexShader.h"
//#include "FragShader.h"
namespace ZG
{
	enum EMATARGTYPE
	{
		EMATARGTYPEINVALID = 0,
		EMATARGTYPEFLOAT1 = 1,
		EMATARGTYPEFLOAT2 = 2,
		EMATARGTYPEFLOAT3 = 3,
		EMATARGTYPEFLOAT4 = 4,
		EMATARGTYPECOLOR = 5,
		EMATARGTYPEINT = 6,
		EMATARGMATRIX33 = 7,
		EMATARGMATRIX44 = 8,
		EMATARGTYPESAMPLER = 9,
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
		virtual MaterialArg* clone(){ return nullptr; };
		void SetShaderType(EMATARGSHADERTYPE eShadertype){ m_EShaderType = eShadertype; }
		string m_strName;
		EMATARGTYPE m_EType;
		EMATARGSHADERTYPE m_EShaderType;
	protected:
		MaterialArg();
	};
	template < class T >
	class TMatArg :public MaterialArg
	{
	public:
		TMatArg(EMATARGTYPE eArgType){ m_EType = eArgType; m_EShaderType = (EMATARGSHADERTYPE)(EMATSHADERVERTE | EMATSHADERFRAG); };
		TMatArg()
		{
			m_EType = EMATARGTYPEINVALID; m_EShaderType = (EMATARGSHADERTYPE)(EMATSHADERVERTE | EMATSHADERFRAG);
		}
		MaterialArg* clone();
		virtual ~TMatArg(){};
		//template<class T1>
		//virtual T* GetValue() const{ return (T1*)&m_Data; };
		T m_Data;
	};

	template < class T >
	MaterialArg* TMatArg<T>::clone()
	{
		TMatArg<T>* pCloneObj = new TMatArg<T>();
		pCloneObj->m_Data = m_Data;
		pCloneObj->m_EType = m_EType;
		pCloneObj->m_strName = m_strName;
		pCloneObj->m_EShaderType = m_EShaderType;
		return pCloneObj;
	}

}
//template<class T>
//TMatArg<T>* Material_Cast(MaterialArg* p)
//{
//
//}