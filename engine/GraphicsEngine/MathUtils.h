#pragma once
#include <d3dx9.h>


class MathUtils
{
public:
	
	static const D3DXMATRIX GetMatrixWorldViewProjT(const D3DXMATRIX & matWorld, const D3DXMATRIX & matView, const D3DXMATRIX & matProj)
	{
		D3DXMATRIX matWorldViewProj = matWorld * matView * matProj;

		D3DXMATRIX matWorldViewProjT;
		D3DXMatrixTranspose(&matWorldViewProjT, &matWorldViewProj);
	
		return matWorldViewProjT;
	}
	
	static const D3DXMATRIX GetMatrixTranspose(const D3DXMATRIX & mat)
	{
		D3DXMATRIX matT;	
		D3DXMatrixTranspose(&matT, &mat);	

		return matT;
	}

	static const D3DXMATRIX GetMatrixInverse(const D3DXMATRIX & mat)
	{
		D3DXMATRIXA16 matInverse;
		D3DXMatrixInverse(&matInverse, NULL, &mat);

		return matInverse;
	}
};