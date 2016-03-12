#pragma once
#include <d3dx9.h>


class Transform
{
public:
	Transform();
	Transform(float x, float y, float z);
	Transform(float px, float py, float pz, float ex, float ey, float ez, float sx, float sy, float sz);
	Transform(D3DXVECTOR3 position, D3DXVECTOR3 eulerAngles = D3DXVECTOR3(0,0,0), D3DXVECTOR3 scale = D3DXVECTOR3(1,1,1));
	
	const D3DXVECTOR3 & GetForward();
	const D3DXVECTOR3 & GetRight();
	const D3DXVECTOR3 & GetUp();

	void SetPosition	(D3DXVECTOR3 position);
	void SetEulerAngles	(D3DXVECTOR3 eulerAngles);
	void SetScale		(D3DXVECTOR3 scale);

	void Translate		(D3DXVECTOR3 vec);
	void Translate		(float x, float y, float z);

	void Rotate			(float x, float y, float z);

	const D3DXVECTOR3 & GetPosition() const;
	const D3DXVECTOR3 & GetEulerAngles() const;
	const D3DXVECTOR3 & GetScale() const;

	const D3DXMATRIXA16 & GetMatWorld();
	const D3DXMATRIXA16 & GetMatView();

	D3DXVECTOR3 getRight()
	{
		return m_right;
	}

	D3DXVECTOR3 getforward()
	{
		return m_forward;
	}
private:

	void Recalc();

	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_eulerAngles;
	D3DXVECTOR3 m_scale;

	// Вектор "вперёд" в глобальной с.к. (равен (0,0,1) в локальной с.к.)
	D3DXVECTOR3 m_forward;
	// Вектор "вправо" в глобальной с.к. (равен (1,0,0) в локальной с.к.)
	D3DXVECTOR3 m_right;
	// Вектор "вверх" в глобальной с.к. (равен (0,1,0) в локальной с.к.)
	D3DXVECTOR3 m_up;

	D3DXMATRIXA16 m_matWorld;
	D3DXMATRIXA16 m_matView;

	bool m_shouldRecalc;
};