#pragma once
#include "Vector2.h"
#include "Color.h"
//enum ENUMSAMPLERATTRIBUTE
//{
//	ESA_ADDRESSU,
//	ESA_ADDRESV,
//	ESA_ADDRESW,
//	ESA_BORDERCOLOR,
//	ESA_MAGFILTER,
//	ESA_MINFILTER,
//	ESA_MIPFILTER,
//	ESA_MIPMAPLODBIAS,
//	ESA_MAXMIPLEVEL,
//	ESA_MAXANISTROPY,
//	ESA_SRGBTEXTURE
//};
namespace ZG
{
	enum ETEXADDRESS
	{
		ETA_WRAP = 1,
		ETA_MIRROR = 2,
		ETA_CLAMP = 3,
		ETA_BORDER = 4,
		ETA_MIRRORONCE
	};
	enum ETEXFILTERTYPE
	{
		ETF_NONE = 0,
		ETF_POINT = 1,
		ETF_LINEAR = 2,
		ETF_ANISTROPIC = 3,
		ETF_PYRAMIDALQUAD = 4,
		ETF_GAUSSIANQUAD = 5,
		ETF_CONVOLUTIONMONO = 6
	};
	enum ETEXUSETYPE
	{
		ETU_DEFAULT = 0,
		ETU_NORMAL = 1
	};
	class Texture;
	class MAIN_API TextureSampler
	{
	public:
		TextureSampler();
		virtual ~TextureSampler();


		SmartPointer<Texture> m_pTexture;
		ETEXADDRESS m_EAddressU;
		ETEXADDRESS m_EAddressV;
		ETEXADDRESS m_EAddressW;
		GameColor		m_BorderColor;
		ETEXFILTERTYPE m_EMinFilter;
		ETEXFILTERTYPE m_EMagFilter;
		ETEXFILTERTYPE m_EMipFilter;
		int			m_nAnistropy;
		bool		m_bUseMipmap;

		unsigned char m_byRegisterIndex;	//¼Ä´æÆ÷±àºÅ
		Vector2		m_UVTiling;
		Vector2		m_UVOffset;
		ETEXUSETYPE m_eTextureUseType;
	};

}