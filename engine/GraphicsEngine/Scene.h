#pragma once
#include <d3dx9.h>
#include <list>
#include "Object.h"
#include "../Tasks/CleverControll.h"


class Camera;
class Light;


class Scene
{
public:

	void Init(LPDIRECT3DDEVICE9 pDevice);
	void Deinit();
	void setCameraController(CleverController* controller)
	{
		cameraContoller = controller;
	}
	CleverController* getCameraController()
	{
		return cameraContoller;
	}
	void AddObject	(Object * pObject);
	void AddLight	(Light * pLight);
	
	void SetCamera	(Camera * pCamera);	
	Camera &		GetCamera() const;
	
	const std::list<const Light *> & GetLights() const;
	
	void Update();
	void Render();

private:
	std::list<const Object *>	m_objects;
	std::list<const Light *>	m_lights;
	Camera *					m_pCamera;
	CleverController* cameraContoller;
	LPDIRECT3DDEVICE9	m_pDevice;
};