#include "MeshSphere.h"


// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z;
	FLOAT nx, ny, nz;
    DWORD color;
	FLOAT u1, v1;
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE4(0))

CUSTOMVERTEX GetVertexOnSphere(int i, int iMax, int j, int jMax)
{
	const FLOAT radius = 0.5f;

	FLOAT theta = (FLOAT) D3DXToRadian(180.0 * j / (jMax - 1));
	FLOAT phi = (FLOAT) D3DXToRadian(360.0 * (i % iMax) / iMax);

	CUSTOMVERTEX v;
	{
		v.x		= radius * sinf(theta) * cosf(phi);
		v.z		= radius * cosf(theta);
		v.y		= radius * sinf(theta) * sinf(phi);

		D3DXVECTOR3 normal(v.x, v.y, v.z);
		D3DXVec3Normalize(&normal, &normal);
		v.nx	= normal.x;
		v.ny	= normal.y;
		v.nz	= normal.z;

		//v.color	= D3DCOLOR_COLORVALUE(1.0f * (rand() % 255) / 255, 1.0f * (rand() % 255) / 255, 1.0f * (rand() % 255) / 255, 1);		
		v.color	= D3DCOLOR_COLORVALUE(1, 1, 1, 1);
		v.u1 = ((float)(i)) / iMax;
		v.v1 = 1 - (float)j / (jMax - 1);
	}

	return v;
}


MeshSphere::MeshSphere(int levelCount)
{
	m_levelCount = (levelCount < 3) ? 3 : levelCount;
}

HRESULT MeshSphere::Init(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT result = Mesh::Init(pDevice);

	int vertexInRowCount = m_levelCount + 1 + 2;
	int vertexCount = vertexInRowCount * m_levelCount;
	// Initialize three vertices for rendering a triangle
    CUSTOMVERTEX * g_Vertices = new CUSTOMVERTEX[vertexCount];
    
	for (int j = 0; j < m_levelCount; ++j)
	{
		for (int i = 0; i < m_levelCount + 1; ++i)
		{
			g_Vertices[vertexInRowCount * j + i] = GetVertexOnSphere(i, m_levelCount, j, m_levelCount);
		}

		// Добавляем вершины для вырожденных треугольников
		g_Vertices[vertexInRowCount * j + (m_levelCount + 1 + 0)] = g_Vertices[vertexInRowCount * j + (m_levelCount + 0)];
		
		// Последний раз добавлять не нужно
		if (j < m_levelCount - 1)
		{			
			g_Vertices[vertexInRowCount * j + (m_levelCount + 1 + 1)] = GetVertexOnSphere(0, m_levelCount, j + 1, m_levelCount);
		}
		else
		{
			g_Vertices[vertexInRowCount * j + (m_levelCount + 1 + 1)] = g_Vertices[vertexInRowCount * j + (m_levelCount + 0)];
		}
	}
	
	int indexCount = (m_levelCount - 1) * vertexInRowCount * 2;
	int * g_Indices = new int[indexCount];
	
	for (int j = 0; j < (m_levelCount - 1); ++j)
	{
		for (int i = 0; i < vertexInRowCount; ++i)
		{
			g_Indices[j * vertexInRowCount * 2 + i * 2 + 0] = j * vertexInRowCount + i;
			g_Indices[j * vertexInRowCount * 2 + i * 2 + 1] = j * vertexInRowCount + vertexInRowCount + i;
		}
	}
			
	result &= CreateVertexBuffer(g_Vertices, sizeof(CUSTOMVERTEX) * vertexCount, vertexCount, D3DFVF_CUSTOMVERTEX);		
	result &= CreateIndexBuffer (g_Indices,  sizeof(int) * indexCount,  indexCount, D3DPT_TRIANGLESTRIP);

	delete g_Indices;
	delete g_Vertices;
    
	return result;
}

void MeshSphere::Deinit()
{
	Mesh::Deinit();
}