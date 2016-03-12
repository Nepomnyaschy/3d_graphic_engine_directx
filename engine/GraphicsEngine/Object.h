#pragma once
#include <d3dx9.h>
#include <list>


class Mesh;
class Component;
class Material;
class Transform;


class Object
{
public:
	Object();
	~Object();

	void Init			(LPDIRECT3DDEVICE9 pDevice);
	void AddComponent	(Component * pComponent);
	
	void Update() const;

	// Содержит матрицу World (position, rotation, scale)
	Transform * m_pTransform;

	// Содержит меш (vertex & index buffers)
	Mesh *		m_pMesh;

	// Содержит Vertex & Pixel Shaders
	Material *	m_pMaterial;

	// Содержит объекты пользователя
	std::list<Component *> m_components;
};