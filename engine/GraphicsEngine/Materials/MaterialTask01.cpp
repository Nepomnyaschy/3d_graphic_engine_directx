#include "MaterialTask01.h"
#include "../Camera/Camera.h"
#include "../Transform.h"
#include "../Object.h"
#include "../SceneUtils.h"


void MaterialTask01::Init(LPDIRECT3DDEVICE9 pDevice, Object * pObject)
{
	Material::Init(pDevice, pObject);
}

void MaterialTask01::Deinit()
{
	Material::Deinit();
}

void MaterialTask01::SetMaterial()
{
	// Заполняем матрицы World, View, Proj
	const D3DXMATRIX & matWorld	= SceneUtils::GetMatrixWorld(m_pObject);
	const D3DXMATRIX & matView	= SceneUtils::GetMatrixView();
	const D3DXMATRIX & matProj	= SceneUtils::GetMatrixProj();
	
	m_pDevice->SetTransform( D3DTS_PROJECTION,	&matProj );
	m_pDevice->SetTransform( D3DTS_VIEW,		&matView );
	m_pDevice->SetTransform( D3DTS_WORLD,		&matWorld );
}