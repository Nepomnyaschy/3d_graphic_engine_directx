#include "MeshTriangle.h"


// A structure for our custom vertex type
struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	FLOAT nx, ny, nz;
	DWORD color;
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)


HRESULT MeshTriangle::Init(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT result = Mesh::Init(pDevice);

	// Initialize three vertices for rendering a triangle
	CUSTOMVERTEX g_Vertices[] =
	{
	    { -1.0f,-1.0f, 0.0f,	0.0f, 0.0f, -1.0f,	0xffff0000, },	// 0
	    {  1.0f,-1.0f, 0.0f,	0.0f, 0.0f, -1.0f,	0xff0000ff, },	// 1
	    {  0.0f, 1.0f, 0.0f,	0.0f, 0.0f, -1.0f,	0xffffffff, },	// 2
	};

	int g_Indices[] = 
	{
		0,1,2
	};
	
	result &= CreateVertexBuffer(g_Vertices, sizeof(g_Vertices), sizeof(g_Vertices) / sizeof(CUSTOMVERTEX), D3DFVF_CUSTOMVERTEX);		
	result &= CreateIndexBuffer (g_Indices,  sizeof(g_Indices),  sizeof(g_Indices) / sizeof(int), D3DPT_TRIANGLESTRIP);	
    
	return result;
}

void MeshTriangle::Deinit()
{
	Mesh::Deinit();
}