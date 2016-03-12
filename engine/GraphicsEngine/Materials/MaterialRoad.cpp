#include "MaterialRoad.h"
#include "../GraphicsEngine.h"
#include "../Camera/Camera.h"
#include "../Transform.h"
#include "../MathUtils.h"
#include "../SceneUtils.h"
#include "MaterialRoadVS.h"
#include "MaterialRoadPS.h"
#include "../Lights/Light.h"


MaterialRoad::MaterialRoad(std::vector<LPCWSTR> pathes)
{
    for (int i = 0; i < pathes.size(); ++i) {
        m_pTexturesFilepathes.push_back(pathes[i]);
    }
    m_pTextures = new LPDIRECT3DTEXTURE9[pathes.size()];
    m_pTextureCount = pathes.size();
}


void MaterialRoad::Init(LPDIRECT3DDEVICE9 pDevice, Object * pObject)
{
	Material::Init(pDevice, pObject);

	m_pVertexShader	= new VertexShader(pDevice, (const DWORD *) MaterialRoadVS);
	m_pPixelShader  = new PixelShader (pDevice, (const DWORD *) MaterialRoadPS);

    //создание текстур
    for (int i = 0; i < m_pTexturesFilepathes.size(); ++i)
    {
        D3DXCreateTextureFromFile(m_pDevice, m_pTexturesFilepathes[i], &(m_pTextures[i]));
    }
}

void MaterialRoad::Deinit()
{
	if (NULL != m_pPixelShader)
	{
		delete m_pPixelShader;
		m_pPixelShader = NULL;
	}

	if (NULL != m_pVertexShader)
	{
		delete m_pVertexShader;
		m_pVertexShader = NULL;
	}
}

void MaterialRoad::SetMaterial()
{
	// Заполняем матрицы World, View, Proj
	const D3DXMATRIX & matWorld	= SceneUtils::GetMatrixWorld(m_pObject);
	const D3DXMATRIX & matView	= SceneUtils::GetMatrixView();
	const D3DXMATRIX & matProj	= SceneUtils::GetMatrixProj();
	
	const D3DXMATRIX matWorldViewProjT	= MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	const D3DXMATRIX matWorldNormal = MathUtils::GetMatrixInverse(matWorld);

	m_pVertexShader->SetShaderBegin();
	{
		m_pVertexShader->SetShaderMatrix4x4(matWorldViewProjT);
		m_pVertexShader->SetShaderMatrix4x3(matWorldNormal);				
		m_pVertexShader->SetShaderVector4(D3DXVECTOR4(1,1,0,1));
	}
	m_pVertexShader->SetShaderEnd();

	
	m_pPixelShader->SetShaderBegin();
	{
        //Передаем текстуру на видеокарту и указываем способо фильтрации
        for (int i = 0; i < m_pTextureCount;++i)
          m_pPixelShader->SetTexture(m_pTextures[i], D3DTEXF_ANISOTROPIC);
		//Cюда нужно передать параметры источника света.

		std::list<const Light *> lights = SceneUtils::GetLights();
		std::list<const Light *>::iterator iter;
		for (iter = lights.begin(); iter != lights.end(); ++iter)
		{
			const Light * pLight = *iter;
			// 1 0 0  0.7 -0.7 0		1 1 0 1
			// Позиция
			m_pPixelShader->SetShaderVector4(pLight->GetPosition());
			// Направление
			m_pPixelShader->SetShaderVector4(pLight->GetDirection());
			// (Цвет.r, Цвет.g, Цвет.b, интенсивность)
			m_pPixelShader->SetShaderVector4(pLight->GetColor());
		}

	}
	m_pPixelShader->SetShaderEnd();
}