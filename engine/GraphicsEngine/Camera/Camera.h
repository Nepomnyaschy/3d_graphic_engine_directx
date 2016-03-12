#pragma once
#include <d3dx9.h>
#include "..\Component.h"


class Camera : public Component
{
public:
	Camera();
	
	// Установка вертикального угла обзора (в градусах)
	void SetFovY		(float fovY);
	// Установка аспекта - отношения ширины окна к его высоте
	void SetAspect		(float aspect);
	// Установка ближней отсекающей плоскости
	void SetNearPlane	(float nearPlane);
	// Установка дальней отсекающей плоскоси
	void SetFarPlane	(float farPlane);
	
	const D3DXMATRIXA16 & GetMatrixView();
	const D3DXMATRIXA16 & GetMatrixProj();

private:

	void RecalculateMatrixProj();

	// Вертикальный угол обзора в градусах
	float m_fovY;
	float m_aspect;
	float m_nearPlane;
	float m_farPlane;

	D3DXMATRIXA16 m_matProj;

	bool m_shouldRecalc;
};