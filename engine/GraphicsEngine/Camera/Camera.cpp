#include "Camera.h"
#include "..\MathConstants.h"
#include "..\Object.h"
#include "..\Transform.h"

Camera::Camera()
{
	m_fovY		= 45.0f;
	m_aspect	= 1.0f;
	m_nearPlane	= 0.1f;
	m_farPlane	= 1000.0f;

	m_shouldRecalc = true;
}


// ��������� ������������� ���� ������ (� ��������)
void Camera::SetFovY( float fovY )
{
	//TODO: �������� �������� �� �������� [1, 179]
	m_fovY = fovY;
	m_shouldRecalc = true;
}

// ��������� ������� - ��������� ������ ���� � ��� ������
void Camera::SetAspect( float aspect )
{
	//TODO: �������� �������� �� ���������������
	m_aspect = aspect;
	m_shouldRecalc = true;
}

// ��������� ������� ���������� ���������
void Camera::SetNearPlane( float nearPlane )
{
	//TODO: �������� �������� �� ��������������� � far > near
	m_nearPlane = nearPlane;
	m_shouldRecalc = true;
}

// ��������� ������� ���������� ��������
void Camera::SetFarPlane( float farPlane )
{
	//TODO: �������� �������� �� ��������������� � far > near
	m_farPlane = farPlane;
	m_shouldRecalc = true;
}

const D3DXMATRIXA16 & Camera::GetMatrixView()
{
	return m_pObject->m_pTransform->GetMatView();
}

const D3DXMATRIXA16 & Camera::GetMatrixProj()
{
	if (m_shouldRecalc)
	{
		RecalculateMatrixProj();
		m_shouldRecalc = false;
	}

	return m_matProj;
}

void Camera::RecalculateMatrixProj()
{
	D3DXMatrixPerspectiveFovLH( &m_matProj, m_fovY * DEC2PI, m_aspect, m_nearPlane, m_farPlane );
}