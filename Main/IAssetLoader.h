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


		virtual IAsset* Load(string path, void* pArg /*= nullptr*/) = 0;
		virtual void	Save(IAsset* pAsset){};

		IAsset* m_pAsset;
	};

}