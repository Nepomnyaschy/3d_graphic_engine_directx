#include "PixelShader.h"
#include "VertexDeclaration.h"


PixelShader::PixelShader(LPDIRECT3DDEVICE9 pDevice, LPCWSTR fileName)
{
	m_pDevice = pDevice;

	m_pDevice->CreateVertexDeclaration(Declaration, &m_pVD);

	LPD3DXBUFFER code = NULL;
	D3DXAssembleShaderFromFile(fileName, 0, 0, 0, &code, 0);	
	m_pDevice->CreatePixelShader((DWORD*) code->GetBufferPointer(), &m_pPShader);
	code->Release();
}

PixelShader::PixelShader(LPDIRECT3DDEVICE9 pDevice, const DWORD * pFunction)
{
	m_pDevice = pDevice;

	HRESULT hr = m_pDevice->CreatePixelShader(pFunction, &m_pPShader);
	int m = 0;
}

void PixelShader::SetShaderBegin()
{
	m_pDevice->SetPixelShader(m_pPShader);
	//m_pDevice->SetVertexDeclaration(m_pVD);
	
	m_startRegister		= 0;
	m_textureRegister	= 0;
}

void PixelShader::SetShaderVector4(D3DXVECTOR4 vector)
{
	m_pDevice->SetPixelShaderConstantF(m_startRegister, vector, 1);
	
	m_startRegister += 1;
}

void PixelShader::SetShaderVector4(D3DXVECTOR3 vector)
{
	SetShaderVector4(D3DXVECTOR4(vector, 1.0f));
}

void PixelShader::SetShaderMatrix4x4(D3DXMATRIX matrix)
{
	m_pDevice->SetPixelShaderConstantF(m_startRegister, matrix, 4);

	m_startRegister += 4;
}

void PixelShader::SetShaderMatrix4x3(D3DXMATRIX matrix)
{
	m_pDevice->SetPixelShaderConstantF(m_startRegister, matrix, 3);

	m_startRegister += 3;
}

// Передача на видеокарту Текстуры и Способа фильтрации (билинейная, анизотропная)
void PixelShader::SetTexture(LPDIRECT3DTEXTURE9 pTexture, D3DTEXTUREFILTERTYPE filterType)
{
	m_pDevice->SetTexture( m_textureRegister, pTexture );

	// Включение фильтрации
	m_pDevice->SetSamplerState( m_textureRegister, D3DSAMP_MINFILTER, filterType );
	m_pDevice->SetSamplerState( m_textureRegister, D3DSAMP_MAGFILTER, filterType );
	m_pDevice->SetSamplerState( m_textureRegister, D3DSAMP_MIPFILTER, filterType );
	
	m_textureRegister += 1;
}

void PixelShader::SetShaderEnd()
{
	// умышленно оставлено пустым, 
	// чтобы сначала вызывали функцию SetShaderBegin()
	// потом функции SetShaderVector4(), SetShaderMatrix4x4(), SetTexture()
}