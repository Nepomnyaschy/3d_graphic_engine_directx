#pragma once
#include <d3dx9.h>


class VertexShader
{
public:
	VertexShader(LPDIRECT3DDEVICE9 pDevice, LPCWSTR fileName);
	VertexShader(LPDIRECT3DDEVICE9 pDevice, const DWORD * pFunction);

	void SetShaderBegin();
	
	void SetShaderVector4(D3DXVECTOR4	vector);
	void SetShaderVector4(D3DXVECTOR3	vector);
	void SetShaderVector4(D3DCOLORVALUE	color, float intensity);	

	void SetShaderMatrix4x4(D3DXMATRIX matrix);
	void SetShaderMatrix4x3(D3DXMATRIX matrix);
	
	void SetShaderEnd();

private:
	LPDIRECT3DDEVICE9				m_pDevice;
	LPDIRECT3DVERTEXDECLARATION9	m_pVD;
	LPDIRECT3DVERTEXSHADER9			m_pVShader;
	int								m_startRegister;
};