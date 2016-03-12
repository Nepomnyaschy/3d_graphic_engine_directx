#pragma once
#include <d3dx9.h>
#include "Material.h"


class MaterialTask01 : public Material
{
public:
	virtual void Init(LPDIRECT3DDEVICE9 pDevice, Object * pObject);
	virtual void Deinit();
	virtual void SetMaterial();
};