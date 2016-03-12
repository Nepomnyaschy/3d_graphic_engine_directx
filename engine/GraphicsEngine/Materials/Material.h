#pragma once
#include <d3dx9.h>


class Object;


class Material
{
public:

	virtual void Init(LPDIRECT3DDEVICE9 pDevice, Object * pObject)
	{
		m_pDevice = pDevice;
		m_pObject = pObject;
	}

	virtual void Deinit()
	{
		m_pDevice = NULL;
	}

	virtual void SetMaterial() { }
	
protected:
	LPDIRECT3DDEVICE9	m_pDevice;
	Object *			m_pObject;
};