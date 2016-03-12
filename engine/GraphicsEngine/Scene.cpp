#include "Scene.h"
#include "Materials/Material.h"
#include "Camera/Camera.h"
#include "Meshes/Mesh.h"
#include "Lights/Light.h"


void Scene::Init(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;

	m_pCamera = NULL;
}

void Scene::Deinit()
{
	// Удаляем объекты
	{
		std::list<const Object *>::iterator iter;
		for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
		{
			const Object * pObject = (*iter);
			delete pObject;
		}
	}

	m_lights.clear();
	m_objects.clear();	

	// Удаляем камеру
	m_pCamera = NULL;
}

void Scene::AddObject(Object * pObject)
{
	if (NULL == pObject)
	{
		return;
	}

	pObject->Init(m_pDevice);
	m_objects.push_back(pObject);
}

void Scene::AddLight(Light * pLight)
{
	if (NULL == pLight)
	{
		return;
	}

	m_lights.push_back(pLight);

	if (NULL != pLight->GetObjectPtr())
	{
		AddObject(pLight->GetObjectPtr());
	}
}

void Scene::SetCamera(Camera * pCamera)
{
	if (NULL != pCamera)
	{
		m_pCamera = pCamera;
		m_objects.push_back(m_pCamera->GetObjectPtr());
	}
}

Camera & Scene::GetCamera() const
{
	return (*m_pCamera);
}

const std::list<const Light *> & Scene::GetLights() const
{
	return m_lights;
}

void Scene::Update()
{
	std::list<const Object *>::iterator iter;
	for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		const Object * pObject = (*iter);
		if (NULL != pObject)
		{
			pObject->Update();
		}
	}
}

void Scene::Render()
{
	std::list<const Object *>::iterator iter;
	for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		const Object * pObject = (*iter);
		if ((NULL != pObject) && (NULL != pObject->m_pMaterial) && (NULL != pObject->m_pMesh))
		{
			pObject->m_pMaterial->SetMaterial();			
			pObject->m_pMesh->Render();
		}
	}
}