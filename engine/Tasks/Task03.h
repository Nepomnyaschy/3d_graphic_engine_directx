#include "Task.h"
#include "../GraphicsEngine/Camera/Camera.h"
#include "../GraphicsEngine/Meshes/MeshTriangle.h"
#include "../GraphicsEngine/Meshes/MeshQuad.h"
#include "../GraphicsEngine/Meshes/MeshSphere.h"
#include "../GraphicsEngine/Transform.h"
#include "../GraphicsEngine/Object.h"
#include "../GraphicsEngine/Scene.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GraphicsEngine/Materials/MaterialTask01.h"
#include "../GraphicsEngine/Materials/MaterialUnlit.h"
#include "../GraphicsEngine/Materials/MaterialDiffuse.h"
#include "../GraphicsEngine/Materials/MaterialDiffuseSpecular.h"
#include "../GraphicsEngine/Lights/Light.h"
#include "Object1Controller.h"

#pragma once


class Task03: public Task
{
public:
	virtual ~Task03() { }

	virtual void Init()
	{
		Scene & scene = GraphicsEngine::Instance().GetScene();
	
		// Камера
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( D3DXVECTOR3(0.0f, 0.0f,-7.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCameraObj->AddComponent( pCamera );

			scene.SetCamera( pCamera );
		}

		// объект #1 - Сфера
		{
			Object * pObject1 = new Object();

			pObject1->m_pMesh		= new MeshSphere(75);
			pObject1->m_pTransform	= new Transform(0,0,0, 0,0,0, 3,3,3);
			pObject1->m_pMaterial	= new MaterialDiffuse();
			//pObject1->m_pMaterial	= new MaterialDiffuseSpecular();
			pObject1->AddComponent( new Object1Controller() );

			scene.AddObject( pObject1 );
		}

		// Источник света #1
		{
			Light * pLight = new Light(LightType::LIGHT_DIRECTIONAL);
			pLight->SetColor(1,1,0);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform	= new Transform(1,0,0, 45,90,0, 1,1,1);
			pLightObject->AddComponent(pLight);

			scene.AddLight(pLight);
		}

		// Источник света #2
		{
			Light * pLight = new Light(LightType::LIGHT_POINT);
			pLight->SetColor(0,0,1);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform	= new Transform(1.5f,0,-1.5f, 0,0,0, 1,1,1);
			pLightObject->AddComponent(pLight);

			scene.AddLight(pLight);
		}
	}

	virtual void Update()
	{
		
	}
};