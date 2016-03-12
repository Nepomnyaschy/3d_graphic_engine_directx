#pragma once
#include <d3dx9.h>
#include "..\Component.h"


class Camera : public Component
{
public:
	Camera();
	
	// ��������� ������������� ���� ������ (� ��������)
	void SetFovY		(float fovY);
	// ��������� ������� - ��������� ������ ���� � ��� ������
	void SetAspect		(float aspect);
	// ��������� ������� ���������� ���������
	void SetNearPlane	(float nearPlane);
	// ��������� ������� ���������� ��������
	void SetFarPlane	(float farPlane);
	
	const D3DXMATRIXA16 & GetMatrixView();
	const D3DXMATRIXA16 & GetMatrixProj();

private:

	void RecalculateMatrixProj();

	// ������������ ���� ������ � ��������
	float m_fovY;
	float m_aspect;
	float m_nearPlane;
	float m_farPlane;

	D3DXMATRIXA16 m_matProj;

	bool m_shouldRecalc;
};