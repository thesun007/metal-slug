#pragma once

#include "Defines.h"
#include "Scene.h"

class CLogoScene : public CScene
{
private:
	float m_fSceneChangeTime;
public:
	HRESULT CreatePlayerImage();
	HRESULT CreateBulletImage();
	HRESULT CreateEnemyImage();
	HRESULT CreateNpcImage();
	HRESULT CreateItemImage();
	HRESULT CreateEffectImage();
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CLogoScene(void);
	virtual ~CLogoScene(void);
};

