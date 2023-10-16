#pragma once

#include "Defines.h"

class CDevice
{
	SINGLETON(CDevice);
private:
	LPDIRECT3D9       m_p3D;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE      m_pSprite;
public:
	LPDIRECT3DDEVICE9 GetDevice() const {return m_pDevice;}
	LPD3DXSPRITE      GetSprite() const {return m_pSprite;}
public:
	HRESULT OnInit(WINMODE Mode);
	void OnBegin();
	void OnEnd();
	void OnRelease();
public:
	CDevice(void);
	~CDevice(void);
};

