#pragma once
#include <d3dx9.h>
#include "../Component.h"
#include "../Object.h"
#include "../Transform.h"


enum LightType
{
	LIGHT_DIRECTIONAL,
	LIGHT_POINT,
	LIGHT_SPOT,
};

class Light : public Component
{
public:
	Light(LightType type)
	{
		switch (type)
		{
			case LIGHT_DIRECTIONAL:
				m_type = 1;
				break;
			case LIGHT_POINT:
				m_type = 2;
				break;
			case LIGHT_SPOT:
				m_type = 3;
				break;
			
			default:
				m_type = 1;
				break;
		}
	}
	virtual ~Light() {}
	
	virtual D3DXVECTOR4 GetType() const
	{
		return D3DXVECTOR4((FLOAT)m_type,0,0,0);
	}

	virtual D3DXVECTOR4 GetColor() const
	{
		return D3DXVECTOR4(m_color, m_intensity);
	}
	
	virtual D3DXVECTOR4 GetPosition() const
	{
		D3DXVECTOR4 position = D3DXVECTOR4( m_pObject->m_pTransform->GetPosition(), 1 );
		return position;
	}

	virtual D3DXVECTOR4 GetDirection() const
	{
		D3DXVECTOR4 direction = D3DXVECTOR4( m_pObject->m_pTransform->GetForward(), 0 );
		return direction;
	}

	// color.x, color.y, color.z в диапазоне [0,1]
	virtual void SetColor(D3DXVECTOR3 color)
	{
		//TODO: обрезать по диапазону [0,1]
		m_color = color;
	}

	// r,g,b в диапазоне [0,1]
	virtual void SetColor(float r, float g, float b)
	{
		//TODO: обрезать по диапазону [0,1]
		m_color = D3DXVECTOR3(r, g, b);
	}

	virtual void SetIntensity(float intensity)
	{
		//TODO: обрезать по диапазону [0, +бесконечность]
		m_intensity = intensity;
	}
	
protected:
	int			m_type;
	D3DXVECTOR3	m_color;
	float		m_intensity;

private:
	Light();
};