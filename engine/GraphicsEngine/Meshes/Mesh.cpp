#include "Mesh.h"


HRESULT Mesh::Init(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;
	    
	return S_OK;
}

void Mesh::Deinit()
{
	if( m_pVertexBuffer != NULL )
        m_pVertexBuffer->Release();
}

void Mesh::Render()
{
	// Render the vertex buffer contents
	m_pDevice->SetStreamSource( 0, m_pVertexBuffer, 0, m_vertexSize );
	m_pDevice->SetFVF( m_fvf );
	m_pDevice->SetIndices( m_pIndexBuffer );
	m_pDevice->DrawIndexedPrimitive( m_primitiveType, 0, 0, m_verticesCount, 0, m_primitiveCount );
}

HRESULT Mesh::CreateVertexBuffer(void * p_gVertices, UINT vertexArraySize, int vertexCount, DWORD fvf)
{
	m_verticesCount = vertexCount;
	m_fvf = fvf;
	m_vertexSize = vertexArraySize / vertexCount;
	
	// Create the vertex buffer.
	if( FAILED( m_pDevice->CreateVertexBuffer( vertexArraySize, 0, m_fvf, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL ) ) )
	{
	    return E_FAIL;
	}
	
	// Fill the vertex buffer.
	VOID* pVertices;
	if( FAILED( m_pVertexBuffer->Lock( 0, vertexArraySize, ( void** )&pVertices, 0 ) ) )
	{
	    return E_FAIL;
	}
	memcpy( pVertices, p_gVertices, vertexArraySize );
	m_pVertexBuffer->Unlock();
	
	return S_OK;
}

HRESULT	Mesh::CreateIndexBuffer(void * p_gIndices, UINT size, int indexCount, D3DPRIMITIVETYPE primitiveType)
{
	m_primitiveType = primitiveType;
	m_indicesCount = indexCount;

	switch (primitiveType)
	{
	case D3DPT_TRIANGLELIST:
		m_primitiveCount = m_indicesCount / 3;
		break;

	case D3DPT_TRIANGLESTRIP:
		m_primitiveCount = m_indicesCount - 2;
		break;
	}
	
	// Create the index buffer.
	if( FAILED( m_pDevice->CreateIndexBuffer( size, 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIndexBuffer, NULL ) ) )
	{
	    return E_FAIL;
	}
	
	// Fill the index buffer.
	VOID* pIndices;
	if( FAILED( m_pIndexBuffer->Lock(0, size, (void**)&pIndices, 0 ) ) )
	{
	    return E_FAIL;
	}
	memcpy( pIndices, p_gIndices, size );
	m_pIndexBuffer->Unlock();
	
	return S_OK;
}