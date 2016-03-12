#pragma once
#include <d3dx9.h>


class PixelShader
{
public:
	PixelShader(LPDIRECT3DDEVICE9 pDevice, LPCWSTR fileName);
	PixelShader(LPDIRECT3DDEVICE9 pDevice, const DWORD * pFunction);

	void SetShaderBegin();

	void SetShaderVector4(D3DXVECTOR4	vector);
	void SetShaderVector4(D3DXVECTOR3	vector);

	void SetShaderMatrix4x4(D3DXMATRIX matrix);
	void SetShaderMatrix4x3(D3DXMATRIX matrix);

	// Передача на видеокарту Текстуры и Способа фильтрации (билинейная, анизотропная)
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture, D3DTEXTUREFILTERTYPE filterType = D3DTEXF_LINEAR);

	void SetShaderEnd();

private:
	LPDIRECT3DDEVICE9				m_pDevice;
	LPDIRECT3DVERTEXDECLARATION9	m_pVD;
	LPDIRECT3DPIXELSHADER9			m_pPShader;

	int m_startRegister;
	int m_textureRegister;
};