#pragma once
#include <d3dx9.h>
#include "../GraphicsEngine/Component.h"
#include "../GraphicsEngine/Object.h"
#include "../GraphicsEngine/Transform.h"


class Object1Controller : public Component
{
public:
	virtual ~Object1Controller() {}

	virtual void Update() 
	{
		if ((NULL == m_pObject) || (NULL == m_pObject->m_pTransform))
		{
			return;
		}

		m_pObject->m_pTransform->Rotate(0, 0.5, 0);
	}
};