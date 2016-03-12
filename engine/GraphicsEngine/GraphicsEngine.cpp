#include "GraphicsEngine.h"
#include"../Tasks/CleverControll.h"

/*LRESULT WINAPI MsgProc1( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:			
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}*/
float MouseRotY = 0;
bool						MoveForward = 0,	MoveBack = 0,
							MoveLeft = 0,
							MoveRight = 0,
							fast = 0,
							turnUp = 0,
							turnDown = 0,
							turnLeft = 0,
							turnRight = 0,
							MoveSpace = 0;
void OnKey(WPARAM vk, bool down)
{
	switch (vk)
	{

	case 'W':      GraphicsEngine::Instance().GetScene().getCameraController()->setMoveForward(); break;
	case 'S':       GraphicsEngine::Instance().GetScene().getCameraController()->setMoveBack(); break;
	case 'A':        GraphicsEngine::Instance().GetScene().getCameraController()->setMoveLeft(); break;
	case 'D':       GraphicsEngine::Instance().GetScene().getCameraController()->setMoveRight(); break;
	case ' ':		MoveSpace = down ? true : false; break;
	case VK_SHIFT: fast = down ? true : false; break;
	case VK_NUMPAD8: turnUp = down ? true : false; break;
	case VK_NUMPAD2: turnDown = down ? true : false; break;
	case VK_NUMPAD4: turnLeft = down ? true : false; break;
	case VK_NUMPAD6: turnRight = down ? true : false; break;
	}
}

GraphicsEngine * GraphicsEngine::pEngine = NULL;

LRESULT CALLBACK MsgProc1(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;
	PAINTSTRUCT pc;
	RECT rc;
	GetClientRect(hwnd, &rc);
	POINT WindowCenter = { rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2 };
	switch (message)
	{

	case WM_MOUSEMOVE: {
		// Convert mouse motion to be relative
		// (report the offset and re-center).
		POINT newPos = { LOWORD(lparam), HIWORD(lparam) };
		::ClientToScreen(hwnd, &newPos);
		if ((newPos.x == WindowCenter.x) && (newPos.y == WindowCenter.y))
			break;
		SetCursorPos(WindowCenter.x, WindowCenter.y);
		const float                Sensitivity = 1.0f;
		MouseRotY -= (Sensitivity * (newPos.x - WindowCenter.x)) / 360.0f;
		if (newPos.x <  WindowCenter.x)
		{
			GraphicsEngine::Instance().GetScene().getCameraController()->setLeftRotation();
		}
		else
		{
			GraphicsEngine::Instance().GetScene().getCameraController()->setRightRotation();
		}
		break;
	}
	case WM_KEYDOWN:    OnKey(wparam, true);    break;
	case WM_KEYUP:      OnKey(wparam, false);   break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &pc);
		EndPaint(hwnd, &pc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
	return 0;
}






GraphicsEngine & GraphicsEngine::Instance()
{
	if (NULL == pEngine)
	{
		pEngine = new GraphicsEngine();
	}

	return *pEngine;
}

GraphicsEngine::GraphicsEngine()
{
	
}

void GraphicsEngine::Init()
{
	// Register the window class
    wc.cbSize			= sizeof( WNDCLASSEX );
	wc.style			= CS_CLASSDC;
	wc.lpfnWndProc		= MsgProc1;
	wc.cbClsExtra		= 0L;
	wc.cbWndExtra		= 0L;
	wc.hInstance		= GetModuleHandle( NULL );
	wc.hIcon			= NULL;
	wc.hCursor			= NULL;
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= L"Graphics Engine";
	wc.hIconSm			= NULL;
    
	RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"Graphics Engine", L"Graphics Engine",
                              WS_OVERLAPPEDWINDOW, 0, 0, 1920, 1024,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
		// Show the window
		ShowWindow( hWnd, SW_SHOWDEFAULT );
		UpdateWindow( hWnd );

		// Enter the message loop
		ZeroMemory( &msg, sizeof( msg ) );        
    }

	m_scene.Init(m_pDevice);
}

void GraphicsEngine::Deinit()
{
	m_scene.Deinit();

	if( m_pDevice != NULL )
        m_pDevice->Release();

    if( m_pDevice != NULL )
        m_pDevice->Release();

	UnregisterClass( L"Graphics Engine", wc.hInstance );
}

void GraphicsEngine::Render()
{
	while (DoCycle() && PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
    {
		TranslateMessage( &msg );
        DispatchMessage( &msg );
    }
    
	if (DoCycle())
	{
		// Clear the backbuffer to a black color
		m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
		m_pDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 );

		// Begin the scene
		if( SUCCEEDED( m_pDevice->BeginScene() ) )
		{
			m_scene.Update();
			m_scene.Render();

			// End the scene
			m_pDevice->EndScene();
		}

		// Present the backbuffer contents to the display
		m_pDevice->Present( NULL, NULL, NULL, NULL );
	}
}

bool GraphicsEngine::DoCycle()
{
	return (msg.message != WM_QUIT);
}

Scene & GraphicsEngine::GetScene()
{
	return m_scene;
}

HRESULT GraphicsEngine::InitD3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed			= TRUE;
    d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat	= D3DFMT_UNKNOWN;

	d3dpp.EnableAutoDepthStencil	= TRUE;
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;

    // Create the D3DDevice
    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &m_pDevice ) ) )
    {
        return E_FAIL;
    }
	
	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

    // Turn off culling, so we see the front and back of the triangle
    m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting, since we are providing our own vertex colors
    m_pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// Turn on the z-buffer
	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
    return S_OK;
}