#pragma once
#include "Mesh.h"


class MeshSphere : public Mesh
{
public:

	MeshSphere(int levelCount = 3);

	virtual HRESULT	Init(LPDIRECT3DDEVICE9 pDevice);
	virtual void	Deinit();

private:
	int m_levelCount;
};