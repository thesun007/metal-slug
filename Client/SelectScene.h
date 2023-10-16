#pragma once

#include "Defines.h"
#include "Scene.h"

class CSelectScene :
	public CScene
{
private:
	int m_iChoice;
	float m_fTime;
	float m_fSelectTime;
	bool m_bSelect;
	bool m_bNext;
	bool m_bKey;

public:
	void CreateObject();
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CSelectScene();
	~CSelectScene();
};

