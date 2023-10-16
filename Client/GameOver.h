#pragma once
#include "Defines.h"
#include "Scene.h"

class CGameOver :
	public CScene
{
private:
	float m_fTime;
	float m_fWaitTime;
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CGameOver();
	~CGameOver();
};

