#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )


#include "../Tasks/Task03.h"
#include "../Tasks/Task04.h"
#include "GraphicsEngine.h"




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	//Task & task = Task03();
	Task & task = Task04();
	{
		GraphicsEngine & engine = GraphicsEngine::Instance();

		engine.Init();
		task.Init();

		while (engine.DoCycle())
		{
			task.Update();
			engine.Render();
		}

		engine.Deinit();
	}

    return 0;
}
