#pragma once
#include "Mesh.h"


class MeshQuad : public Mesh
{
public:

	virtual HRESULT	Init(LPDIRECT3DDEVICE9 pDevice);
	virtual void	Deinit();
};