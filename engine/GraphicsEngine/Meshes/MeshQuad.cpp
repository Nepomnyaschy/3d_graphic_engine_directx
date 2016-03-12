#include "MeshQuad.h"


// A structure for our custom vertex type
struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	FLOAT nx, ny, nz;
	DWORD color;
	FLOAT u1, v1;
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2 | D3DFVF_TEXCOORDSIZE4(0) | D3DFVF_TEXCOORDSIZE4(1))


HRESULT MeshQuad::Init(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT result = Mesh::Init(pDevice);

	// Initialize three vertices for rendering a triangle
	CUSTOMVERTEX g_Vertices[] =
	{
		{ -1.0f,-1.0f, 0.0f,	0.0f, 0.0f, -1.0f,	0xffff0000, 0,0, },	// 0
		{ -1.0f, 1.0f, 0.0f,	0.0f, 0.0f, -1.0f,	0xff00ff00, 0,1, },	// 1
		{  1.0f,-1.0f, 0.0f,	0.0f, 0.0f, -1.0f,	0xff0000ff, 1,0, },	// 2
		{  1.0f, 1.0f, 0.0f,	0.0f, 0.0f, -1.0f,	0xffffffff, 1,1, },	// 3
	};

	int g_Indices[] = 
	{
		0,1,2,3
	};
	
	result &= CreateVertexBuffer(g_Vertices, sizeof(g_Vertices), sizeof(g_Vertices) / sizeof(CUSTOMVERTEX), D3DFVF_CUSTOMVERTEX);		
	result &= CreateIndexBuffer (g_Indices,  sizeof(g_Indices),  sizeof(g_Indices) / sizeof(int), D3DPT_TRIANGLESTRIP);	
    
	return result;
}

void MeshQuad::Deinit()
{
	Mesh::Deinit();
}