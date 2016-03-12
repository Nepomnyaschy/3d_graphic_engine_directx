#pragma once
#include <d3dx9.h>
#include<vector>
#include "Material.h"
#include "../Shaders/VertexShader.h"
#include "../Shaders/PixelShader.h"


// Unlit значит "неосвещаемый",
// т.е. этот материал не освещается источниками света
class MaterialRoad : public Material
{
public:
    MaterialRoad(std::vector<LPCWSTR> pathes);
    
	virtual void Init(LPDIRECT3DDEVICE9 pDevice, Object * pObject);
	virtual void Deinit();
	virtual void SetMaterial();


private:
	VertexShader * m_pVertexShader;
	PixelShader	 * m_pPixelShader;

	std:: vector <LPCWSTR>				m_pTexturesFilepathes;

	//std:: vector <LPDIRECT3DTEXTURE9>	    m_pTextures;
    LPDIRECT3DTEXTURE9*	    m_pTextures;
    int m_pTextureCount;
};