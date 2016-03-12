#pragma once
#include <d3dx9.h>
#include "../GraphicsEngine/Component.h"
#include "../GraphicsEngine/Object.h"
#include "../GraphicsEngine/Transform.h"


class CleverController : public Component
{
private :
		float movY;
		bool						MoveForward = 0,
									MoveBack = 0,
									MoveLeft = 0,
									MoveRight = 0,
									MouseRotateRight = 0,
									MouseRotateLeft = 0;

public:
	virtual ~CleverController() {}

	virtual void Update()
	{
		if ((NULL == m_pObject) || (NULL == m_pObject->m_pTransform))
		{
			return;
		}
		if (MouseRotateRight) {
			m_pObject->m_pTransform->Rotate(0, 2, 0);
			MouseRotateRight = false;
		}
		if (MouseRotateLeft) {
			m_pObject->m_pTransform->Rotate(0, -2, 0);
			MouseRotateLeft = false;
		}
		float k = 0.07;
		if (MoveBack)
		{
			D3DXVECTOR3 back = - m_pObject->m_pTransform->GetForward();
			D3DXVECTOR3 pos = m_pObject->m_pTransform->GetPosition();
			pos.x += back.x*k;
			pos.y += back.y * k;
			pos.z += back.z *k;
			m_pObject->m_pTransform->SetPosition(pos);
			MoveBack = false;
		}
		if (MoveForward)
		{
			D3DXVECTOR3 back = m_pObject->m_pTransform->GetForward();
			D3DXVECTOR3 pos = m_pObject->m_pTransform->GetPosition();
			pos.x += back.x*k;
			pos.y += back.y * k;
			pos.z += back.z *k;
			m_pObject->m_pTransform->SetPosition(pos);
			MoveForward = false;
		}
		if (MoveLeft)
		{
			D3DXVECTOR3 back = -m_pObject->m_pTransform->GetRight();
			D3DXVECTOR3 pos = m_pObject->m_pTransform->GetPosition();
			pos.x += back.x*k;
			pos.y += back.y * k;
			pos.z += back.z *k;
			m_pObject->m_pTransform->SetPosition(pos);
			MoveLeft = false;
		}
		if (MoveRight)
		{
			D3DXVECTOR3 back = m_pObject->m_pTransform->GetRight();
			D3DXVECTOR3 pos = m_pObject->m_pTransform->GetPosition();
			pos.x += back.x*k;
			pos.y += back.y * k;
			pos.z += back.z *k;
			m_pObject->m_pTransform->SetPosition(pos);
			MoveRight = false;
		}
	}
	void setRightRotation()
	{
		MouseRotateRight= true;
	}
	void setLeftRotation()
	{
		MouseRotateLeft = true;
	}
	void setMoveForward()
	{
		MoveForward = true;
	}
	void setMoveBack()
	{
		MoveBack = true;
	}
	void setMoveLeft()
	{
		MoveLeft = true;
	}
	void setMoveRight()
	{
		MoveRight = true;
	}
};