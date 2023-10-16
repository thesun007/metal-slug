#include "StdAfx.h"
#include "KeyMgr.h"
#include "Include.h"

CKeyMgr::CKeyMgr(void)
{}

CKeyMgr::~CKeyMgr(void)
{
	OnRelease();
}

HRESULT CKeyMgr::OnInit()
{
	if(FAILED(DirectInput8Create(g_hInst, DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (void**)&m_pInput, NULL)))
		return E_FAIL;

	m_pInput->CreateDevice(GUID_SysKeyboard,
		&m_pKeyBoard, NULL);
	m_pKeyBoard->SetCooperativeLevel(g_hWnd,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);
	m_pKeyBoard->Acquire();

	m_pInput->CreateDevice(GUID_SysMouse,
		&m_pMouse, NULL);
	m_pMouse->SetCooperativeLevel(g_hWnd,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_pMouse->SetDataFormat(&c_dfDIMouse);
	m_pMouse->Acquire();

	return S_OK;
}

void CKeyMgr::OnRelease()
{
	if(m_pMouse)
	{
		m_pMouse->Release();
		m_pMouse = NULL;
	}
	if(m_pKeyBoard)
	{
		m_pKeyBoard->Release();
		m_pKeyBoard = NULL;
	}
	if(m_pInput)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

void CKeyMgr::OnSet()
{
	if(m_pKeyBoard->GetDeviceState(sizeof(m_byState), m_byState) != D3D_OK)
	{
		OnRelease();
		OnInit();
	}
	m_pMouse->GetDeviceState(sizeof(m_MState), &m_MState);
}
