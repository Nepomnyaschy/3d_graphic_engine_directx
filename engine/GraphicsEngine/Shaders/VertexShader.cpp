#include "VertexShader.h"
#include "VertexDeclaration.h"


VertexShader::VertexShader(LPDIRECT3DDEVICE9 pDevice, LPCWSTR fileName)
{
	m_pDevice = pDevice;

	m_pDevice->CreateVertexDeclaration(Declaration, &m_pVD);

	LPD3DXBUFFER code = NULL;
	LPD3DXBUFFER errors = NULL;
	D3DXAssembleShaderFromFile(fileName, 0, 0, 0, &code, &errors);	
	m_pDevice->CreateVertexShader((DWORD*) code->GetBufferPointer(), &m_pVShader);
	code->Release();
}

VertexShader::VertexShader(LPDIRECT3DDEVICE9 pDevice, const DWORD * pFunction)
{
	m_pDevice = pDevice;

    //
	m_pDevice->CreateVertexDeclaration(Declaration, &m_pVD);

    //здесь похоже функция шейдера записывается в переменную m_pVShader
	m_pDevice->CreateVertexShader(pFunction, &m_pVShader); 
}

void VertexShader::SetShaderBegin()
{
	m_pDevice->SetVertexShader(m_pVShader);
	m_pDevice->SetVertexDeclaration(m_pVD);

	m_startRegister = 0;
}

void VertexShader::SetShaderVector4(D3DXVECTOR4 vector)
{
	m_pDevice->SetVertexShaderConstantF(m_startRegister, vector, 1);
	
	m_startRegister += 1;
}

void VertexShader::SetShaderVector4(D3DXVECTOR3 vector)
{
	SetShaderVector4(D3DXVECTOR4(vector, 1.0f));
}

void VertexShader::SetShaderVector4(D3DCOLORVALUE color, float intensity)
{
	SetShaderVector4(D3DXVECTOR4(color.r, color.g, color.b, intensity));
}

void VertexShader::SetShaderMatrix4x4(D3DXMATRIX matrix)
{
	m_pDevice->SetVertexShaderConstantF(m_startRegister, matrix, 4);

	m_startRegister += 4;
}

void VertexShader::SetShaderMatrix4x3(D3DXMATRIX matrix)
{
	m_pDevice->SetVertexShaderConstantF(m_startRegister, matrix, 3);

	m_startRegister += 3;
}

void VertexShader::SetShaderEnd()
{
	// умышленно оставлено пустым, 
	// чтобы сначала вызывали функцию SetShaderBegin()
	// потом функции SetShaderVector4(), SetShaderMatrix4x4()
}