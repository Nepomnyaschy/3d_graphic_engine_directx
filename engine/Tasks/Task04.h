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
#include "../GraphicsEngine/Materials/MaterialRoad.h"
#include "../GraphicsEngine/Lights/Light.h"
#include "Object1Controller.h"
#include "CleverControll.h"
#include<vector>

#pragma once


class Task04: public Task
{
public:
	virtual ~Task04() { }

	virtual void Init()
	{
		Scene & scene = GraphicsEngine::Instance().GetScene();
	
		// Камера
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform(D3DXVECTOR3(0.0f, 0.25f, -1.5f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			CleverController* cameraController = new CleverController();
            pCamera->SetAspect(1920.0 / 1024);
			pCameraObj->AddComponent( pCamera );
			pCameraObj->AddComponent(cameraController);

			scene.setCameraController(cameraController);
			scene.SetCamera( pCamera );
		}

		// объект #1 - Дорога
		{
			Object * pObject1 = new Object();

			pObject1->m_pMesh		= new MeshSphere(500);
            pObject1->m_pTransform = new Transform(0, 0, 1, 90, 0, 0, 1, 1, 1);
            {
                std::vector<LPCWSTR> pathes;
                pathes.push_back(L"../Data/Earth_Diffuse.dds");
				pathes.push_back(L"../Data/Earth_NormalMap.dds");
                pObject1->m_pMaterial = new MaterialRoad(pathes);
            }
			pObject1->AddComponent(new Object1Controller());
			scene.AddObject( pObject1 );
		}
		// Источник света #1
		{
			Light * pLight = new Light(LightType::LIGHT_DIRECTIONAL);
			pLight->SetColor(0.5, 0.5, 0.5);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform = new Transform(0.0, 0, 0,0, 0, 0, 1.0, 1.0,1.0 );
			pLightObject->AddComponent(pLight);

			scene.AddLight(pLight);
		}
	}

	virtual void Update()
	{
		
	}
};