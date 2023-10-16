#pragma once

#include "Defines.h"

class CMainApp
{
public:
	HRESULT OnInit();
	int OnUpdate();
	void OnRender();
	void OnRelease();
public:
	CMainApp(void);
	~CMainApp(void);
};

