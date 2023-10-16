#include "StdAfx.h"
#include "Device.h"

CDevice::CDevice(void)
	:m_p3D(0)
	,m_pDevice(0)
{}

CDevice::~CDevice(void)
{
	OnRelease();
}

HRESULT CDevice::OnInit(WINMODE Mode)
{
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(D3DCAPS9));

	if(FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT
		, D3DDEVTYPE_HAL, &caps)))
		return E_FAIL;

	DWORD Flag = 0;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		Flag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		Flag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth  = WINSIZEX;
	d3dpp.BackBufferHeight = WINSIZEY;
	d3dpp.BackBufferCount  = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	d3dpp.MultiSampleType    = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = true;

	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = Mode;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if(FAILED(m_p3D->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		g_hWnd, Flag, &d3dpp, &m_pDevice)))
		return E_FAIL;

	if(FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
		return E_FAIL;

	return S_OK;
}

void CDevice::OnBegin()
{
	m_pDevice->Clear(0, 0, 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL
		, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::OnEnd()
{
	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(0, 0, 0, 0);
}

void CDevice::OnRelease()
{
	if(m_pSprite)
	{
		m_pSprite->Release();
		m_pSprite = 0;
	}
	if(m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = 0;
	}
	if(m_p3D)
	{
		m_p3D->Release();
		m_p3D = 0;
	}
}
