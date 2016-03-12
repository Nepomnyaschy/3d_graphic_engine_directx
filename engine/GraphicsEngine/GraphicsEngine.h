#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "Scene.h"


class GraphicsEngine
{
public:
	static GraphicsEngine & Instance();

	void Init();
	void Deinit();

	void Render();
	bool DoCycle();

	Scene & GetScene();

private:
	GraphicsEngine();
	GraphicsEngine( const GraphicsEngine & );
	static GraphicsEngine * pEngine;

	HRESULT InitD3D( HWND hWnd );

	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pDevice;

	WNDCLASSEX wc;
	MSG msg;

	Scene m_scene;
};