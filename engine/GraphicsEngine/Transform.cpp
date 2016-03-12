#include "Transform.h"
#include "MathConstants.h"


Transform::Transform()
:	m_position		( D3DXVECTOR3(0,0,0) ),
	m_eulerAngles	( D3DXVECTOR3(0,0,0) ),
	m_scale			( D3DXVECTOR3(1,1,1) )
{
	m_shouldRecalc = true;
}

Transform::Transform(float x, float y, float z)
:	m_position		( D3DXVECTOR3(x,y,z) ),
	m_eulerAngles	( D3DXVECTOR3(0,0,0) ),
	m_scale			( D3DXVECTOR3(1,1,1) )
{
	m_shouldRecalc = true;
}

Transform::Transform(float px, float py, float pz, float ex, float ey, float ez, float sx, float sy, float sz)
:	m_position		( D3DXVECTOR3(px,py,pz) ),
	m_eulerAngles	( D3DXVECTOR3(ex,ey,ez) ),
	m_scale			( D3DXVECTOR3(sx,sy,sz) )
{
	m_shouldRecalc = true;
}

Transform::Transform(D3DXVECTOR3 position, D3DXVECTOR3 eulerAngles, D3DXVECTOR3 scale)
:	m_position		( position ),
	m_eulerAngles	( eulerAngles ),
	m_scale			( scale )
{
	m_shouldRecalc = true;
}


const D3DXVECTOR3 & Transform::GetForward()
{
	if (m_shouldRecalc)
	{
		Recalc();
	}

	return m_forward;
}

const D3DXVECTOR3 & Transform::GetRight()
{
	if (m_shouldRecalc)
	{
		Recalc();
	}

	return m_right;
}

const D3DXVECTOR3 & Transform::GetUp()
{
	if (m_shouldRecalc)
	{
		Recalc();
	}

	return m_up;
}


void Transform::SetPosition( D3DXVECTOR3 position )
{
	m_position = position;
	m_shouldRecalc = true;
}

void Transform::SetEulerAngles( D3DXVECTOR3 eulerAngles )
{
	m_eulerAngles = eulerAngles;
	m_shouldRecalc = true;
}

void Transform::SetScale( D3DXVECTOR3 scale )
{
	m_scale = scale;
	m_shouldRecalc = true;
}

void Transform::Translate( D3DXVECTOR3 vec )
{
	m_position += vec;
	m_shouldRecalc = true;
}


void Transform::Translate( float x, float y, float z )
{
	m_position += D3DXVECTOR3(x, y, z);
	m_shouldRecalc = true;
}


void Transform::Rotate( float x, float y, float z )
{
	m_eulerAngles += D3DXVECTOR3(x,y,z);
	//m_eulerAngles.y = fmod(m_eulerAngles.y, 360);
	m_shouldRecalc = true;
}


const D3DXVECTOR3 & Transform::GetPosition() const
{
	return m_position;
}

const D3DXVECTOR3 & Transform::GetEulerAngles() const
{
	return m_eulerAngles;
}

const D3DXVECTOR3 & Transform::GetScale() const
{
	return m_scale;
}

const D3DXMATRIXA16 & Transform::GetMatWorld()
{
	if (m_shouldRecalc)
	{
		Recalc();
	}

	return m_matWorld;
}

const D3DXMATRIXA16 & Transform::GetMatView()
{
	if (m_shouldRecalc)
	{
		Recalc();
	}

	return m_matView;
}

void Transform::Recalc()
{
	// Пересчитаем матрицу World
	{
		D3DXMATRIXA16 matTrans;
		D3DXMatrixTranslation(&matTrans, m_position.x, m_position.y, m_position.z);

		D3DXMATRIXA16 matRot;
		D3DXMatrixRotationYawPitchRoll(&matRot, m_eulerAngles.y * DEC2PI, 
			m_eulerAngles.x  * DEC2PI, 
			m_eulerAngles.z  * DEC2PI);

		D3DXMATRIXA16 matScale;
		D3DXMatrixScaling(&matScale, m_scale.x, m_scale.y, m_scale.z);

		m_matWorld = matScale * matRot * matTrans;
	}

	// Пересчитаем вектора m_forward, m_right, m_up
	{
		D3DXVECTOR4 forward;
		D3DXVec4Transform(&forward, &D3DXVECTOR4(0,0,1,0), &m_matWorld);
		m_forward = D3DXVECTOR3(forward);
		D3DXVec3Normalize(&m_forward, &m_forward);

		D3DXVECTOR4 right;
		D3DXVec4Transform(&right, &D3DXVECTOR4(1,0,0,0), &m_matWorld);
		m_right = D3DXVECTOR3(right);
		D3DXVec3Normalize(&m_right, &m_right);

		D3DXVECTOR4 up;
		D3DXVec4Transform(&up, &D3DXVECTOR4(0,1,0,0), &m_matWorld);
		m_up = D3DXVECTOR3(up);
		D3DXVec3Normalize(&m_up, &m_up);
	}

	// Пересчитываем матрицу View
	{
		D3DXVECTOR3 vEyePt		= m_position;
		D3DXVECTOR3 vLookatPt	= vEyePt + m_forward;
		D3DXVECTOR3 vUpVec		= m_up;

		D3DXMatrixLookAtLH( &m_matView, &vEyePt, &vLookatPt, &vUpVec );
	}

	m_shouldRecalc = false;
}