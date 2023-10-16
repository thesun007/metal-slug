#pragma once

#include "Scene.h"

class CSceneMgr
{
	SINGLETON(CSceneMgr);
private:
	CScene* m_pScene;
public:
	HRESULT LoadScene(SCENEID ID);
	int OnUpdate();
	void OnRender();
	void OnRelease();
public:
	CSceneMgr(void);
	~CSceneMgr(void);
};

