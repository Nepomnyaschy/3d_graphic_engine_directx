#include "MaterialDiffuse.h"
#include "../GraphicsEngine.h"
#include "../Camera/Camera.h"
#include "../Transform.h"
#include "../MathUtils.h"
#include "../SceneUtils.h"
#include "../Lights/Light.h"
#include "MaterialDiffuseVS.h"


void MaterialDiffuse::Init(LPDIRECT3DDEVICE9 pDevice, Object * pObject)
{
	Material::Init(pDevice, pObject);

	m_pVertexShader	= new VertexShader(pDevice, (const DWORD *) MaterialDiffuseVS);	
}

void MaterialDiffuse::Deinit()
{
	delete m_pVertexShader;
	m_pVertexShader = NULL;
}

void MaterialDiffuse::SetMaterial()
{
	// ��������� ������� World, View, Proj
	const D3DXMATRIX & matWorld	= SceneUtils::GetMatrixWorld(m_pObject);
	const D3DXMATRIX & matView	= SceneUtils::GetMatrixView();
	const D3DXMATRIX & matProj	= SceneUtils::GetMatrixProj();
	const D3DXVECTOR3 & cameraPosition = SceneUtils::GetEyePosition();
	
	const D3DXMATRIX matWorldViewProjT	= MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	const D3DXMATRIX matWorldT			= MathUtils::GetMatrixTranspose(matWorld);
	const D3DXMATRIX matWorldNormal		= MathUtils::GetMatrixInverse(matWorld);

	m_pVertexShader->SetShaderBegin();
	{
		m_pVertexShader->SetShaderMatrix4x4(matWorldViewProjT);				// : register(c0);
		m_pVertexShader->SetShaderMatrix4x3(matWorldNormal);				// : register(c4);
		m_pVertexShader->SetShaderMatrix4x3(matWorldT);						// : register(c7);

		// �������� ������ ���� ���������� ����� � �����
		std::list<const Light *> lights = SceneUtils::GetLights();
		
		const size_t count = lights.size();
		// �������� ���-�� ���������� �����
		m_pVertexShader->SetShaderVector4(D3DXVECTOR4((FLOAT)count,0,0,0));	// : register(c10);

		// ������� ��������� ������� ��������� �����
		std::list<const Light *>::iterator iter;
		for (iter = lights.begin(); iter != lights.end(); ++iter)
		{
			const Light * pLight = *iter;

			// ��� ��������� �����
			m_pVertexShader->SetShaderVector4( pLight->GetType() );
			// �������
			m_pVertexShader->SetShaderVector4( pLight->GetPosition() );
			// �����������
			m_pVertexShader->SetShaderVector4( pLight->GetDirection() );
			// (����.r, ����.g, ����.b, �������������)
			m_pVertexShader->SetShaderVector4( pLight->GetColor() );
		}
	}
	m_pVertexShader->SetShaderEnd();
}