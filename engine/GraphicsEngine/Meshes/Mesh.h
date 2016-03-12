#pragma once
#include <d3dx9.h>


class Mesh
{
public:

	virtual HRESULT	Init(LPDIRECT3DDEVICE9 pDevice);
	virtual void	Deinit();

	void	Render();

protected:

	HRESULT	CreateVertexBuffer	(void * p_gVertices, UINT size, int vertexCount, DWORD fvf);
	HRESULT	CreateIndexBuffer	(void * p_gIndices,  UINT size, int indexCount, D3DPRIMITIVETYPE primitiveType);

	LPDIRECT3DDEVICE9		m_pDevice;
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;
	int						m_verticesCount;
	int						m_indicesCount;
	DWORD					m_fvf;
	D3DPRIMITIVETYPE		m_primitiveType;
	UINT					m_primitiveCount;
	UINT					m_vertexSize;
};