#pragma once


class Object;


class Component
{
public:
	Component() 
	{
		m_pObject = NULL;
	}

	virtual ~Component() {}

	void Init(Object * pObject)
	{
		m_pObject = pObject;
	}
	
	Object * GetObjectPtr()
	{
		return m_pObject;
	}

	virtual void Update() { }

protected:
	Object * m_pObject;
};