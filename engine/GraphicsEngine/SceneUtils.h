#pragma once
#include <d3dx9.h>
#include "Scene.h"
#include "GraphicsEngine.h"


class SceneUtils
{
public:

	static const D3DXMATRIX & GetMatrixWorld(const Object * pObject)
	{
		const D3DXMATRIX & matWorld = pObject->m_pTransform->GetMatWorld();

		return matWorld;
	}

	static const D3DXMATRIX & GetMatrixView()
	{
		Scene &	scene = GraphicsEngine::Instance().GetScene();
		Camera & camera = scene.GetCamera();

		const D3DXMATRIX & matView = camera.GetMatrixView();

		return matView;
	}

	static const D3DXMATRIX & GetMatrixProj()
	{
		Scene &	scene = GraphicsEngine::Instance().GetScene();
		Camera & camera = scene.GetCamera();

		const D3DXMATRIX & matProj = camera.GetMatrixProj();

		return matProj;
	}

	static const D3DXVECTOR3 GetEyePosition()
	{
		// TODO: Нужно поставить проверки, что не работает с нулевыми указателями
		const Scene &	scene = GraphicsEngine::Instance().GetScene();
		D3DXVECTOR3 eyePos = scene.GetCamera().GetObjectPtr()->m_pTransform->GetPosition();
		return eyePos;
	}

	static const std::list<const Light *> GetLights()
	{
		const Scene & scene = GraphicsEngine::Instance().GetScene();
		return scene.GetLights();
	}
};