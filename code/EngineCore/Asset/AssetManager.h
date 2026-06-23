/***************************************************************************************
Author: lvke
Date:2022/9/18 12:26
Description:
AssetManager, load shader, load texture
****************************************************************************************/
#ifndef CYBER_ASSETMANAGER
#define CYBER_ASSETMANAGER

#include <string>
#include "../Core/base/SingletonInterface.h"
#include "../Core/base/ManagerInterface.h"
#include <vector>

namespace EngineCore
{

	class AssetManager : public ISingleton<AssetManager>, public IManager
	{
	public:
		virtual void init() override;

		ComPtr<ID3D11VertexShader> loadVsShaderAsset(const std::string& relativeVsShaderPath, ComPtr<ID3DBlob>& blob);
		ComPtr<ID3D11GeometryShader>  loadGsShaderAsset(const std::string& relativePsShaderPath);
		ComPtr<ID3D11PixelShader>  loadPsShaderAsset(const std::string& relativePsShaderPath);
		ComPtr<ID3D11ShaderResourceView> loadTextureAsset(const std::string& relativeTexturePath);
		ComPtr<ID3D11ShaderResourceView> loadTextureArrayAsset(const std::vector<std::wstring>&);
		ComPtr<ID3D11ShaderResourceView> loadSkyBoxTextureAsset(const std::string& relativeTexturePath);

		HRESULT CreateWICTexture2DCubeFromFile(
			ID3D11Device* d3dDevice, 
			ID3D11DeviceContext* d3dDeviceContext, 
			const std::wstring& cubeMapFileName,
			ID3D11Texture2D** textureArray,
			ID3D11ShaderResourceView** textureCubeView,
			bool generateMips);

	};
}
#endif