#pragma once
namespace ZG
{
	class IAsset;
	class MAIN_API IAssetLoader
	{
	public:

		IAssetLoader()
		{
			m_pAsset = nullptr;
		}

		virtual ~IAssetLoader()
		{
		}


		virtual IAsset* Load(std::string path, void* pArg /*= nullptr*/) = 0;
		virtual bool	Save(IAsset* pAsset){ return false; };

		IAsset* m_pAsset;
	};

}