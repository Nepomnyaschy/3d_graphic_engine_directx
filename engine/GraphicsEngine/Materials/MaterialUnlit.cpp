#include "MaterialUnlit.h"
#include "../GraphicsEngine.h"
#include "../Camera/Camera.h"
#include "../Transform.h"
#include "../MathUtils.h"
#include "../SceneUtils.h"
#include "MaterialUnlitVS.h"


void MaterialUnlit::Init(LPDIRECT3DDEVICE9 pDevice, Object * pObject)
{
	Material::Init(pDevice, pObject);

	m_pVertexShader	= new VertexShader(pDevice, (const DWORD *) MaterialUnlitVS);	
}

void MaterialUnlit::Deinit()
{
	delete m_pVertexShader;
	m_pVertexShader = NULL;
}

void MaterialUnlit::SetMaterial()
{
	// Заполняем матрицы World, View, Proj
	const D3DXMATRIX & matWorld	= SceneUtils::GetMatrixWorld(m_pObject);
	const D3DXMATRIX & matView	= SceneUtils::GetMatrixView();
	const D3DXMATRIX & matProj	= SceneUtils::GetMatrixProj();
	
	const D3DXMATRIX matWorldViewProjT	= MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

	m_pVertexShader->SetShaderBegin();
	{
		m_pVertexShader->SetShaderMatrix4x4(matWorldViewProjT);
		m_pVertexShader->SetShaderVector4(D3DXVECTOR4(1,1,0,1));
	}
	m_pVertexShader->SetShaderEnd();
}