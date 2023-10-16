#pragma once

#include "Defines.h"

class CKeyMgr
{
	SINGLETON(CKeyMgr);
private:
	LPDIRECTINPUT8       m_pInput;
	LPDIRECTINPUTDEVICE8 m_pKeyBoard;
	LPDIRECTINPUTDEVICE8 m_pMouse;
	BYTE                 m_byState[256];
	DIMOUSESTATE         m_MState;
public:
	void OnSet();
public:
	const BYTE& GetKeyBoardState(short nKey) 
		const {return m_byState[nKey];}
	const DIMOUSESTATE& GetMouseState() const {return m_MState;}
public:
	HRESULT OnInit();
	void OnRelease();
public:
	CKeyMgr(void);
	~CKeyMgr(void);
};

