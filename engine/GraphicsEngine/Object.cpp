#include "Object.h"
#include "Component.h"
#include "Materials/Material.h"
#include "Meshes/Mesh.h"
#include "Transform.h"


Object::Object()
{
	m_pTransform	= NULL;
	m_pMesh			= NULL;
	m_pMaterial		= NULL;	
}

Object::~Object()
{
	// Очищаем список компонент
	{
		std::list<Component *>::iterator iter;
		for (iter = m_components.begin(); iter != m_components.end(); iter++)
		{
			Component * pComponent = (*iter);
			if (NULL != pComponent)
			{
				delete pComponent;
			}
		}

		m_components.clear();
	}

	if (NULL != m_pMaterial)
	{
		m_pMaterial->Deinit();
		delete m_pMaterial;
		m_pMaterial = NULL;
	}

	if (NULL != m_pMesh)
	{
		m_pMesh->Deinit();
		delete m_pMesh;
		m_pMesh = NULL;
	}

	if (NULL != m_pTransform)
	{
		delete m_pTransform;
		m_pTransform = NULL;
	}	
}

void Object::Init(LPDIRECT3DDEVICE9 pDevice)
{
	if (NULL != m_pMesh)
	{
		m_pMesh->Init(pDevice);
	}

	if (NULL != m_pMaterial)
	{
		m_pMaterial->Init(pDevice, this);
	}
}

void Object::AddComponent(Component * pComponent)
{
	m_components.push_back(pComponent);
	pComponent->Init(this);
}

void Object::Update() const
{
	std::list<Component *>::const_iterator iter;
	for (iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		Component * pComponent = (*iter);
		if (NULL != pComponent)
		{
			pComponent->Update();
		}
	}
}