#pragma once
#include "Defines.h"
#include "Scene.h"

class CStageScene : public CScene
{
public:
	/*HDC m_hdc;*/
	list<LINE*> m_listLine;
	float m_fTime;
public:
	void ReadLine();
	void CreateGround();
	void CreateEnemy();
	void CreateNpc();
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CStageScene(void);
	virtual ~CStageScene(void);
};

