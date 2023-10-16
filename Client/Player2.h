#pragma once
#include "ObjDynamic.h"
#include "Defines.h"

class CPlayer2 :
	public CObjDynamic
{
private:
	bool FrameEnd;
	bool FrameReverse;
	bool FrameOne;

	bool MoveTime;
	bool	Landing;
	D3DXMATRIX* m_pParentWorld;
public:
	void SetParentWorld(D3DXMATRIX* pParentWorld)
	{
		m_pParentWorld = pParentWorld;
	}
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CPlayer2();
	~CPlayer2();
};

