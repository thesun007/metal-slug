#pragma once
#include "ObjDynamic.h"
class CBBullet :
	public CObjDynamic
{
private:
	CObj* m_pParent;

	D3DXVECTOR3 m_vPos;
	bool FrameEnd;
	bool FrameReverse;
	bool FrameOne;
	int FrameStack;		//Ready3 ¹Ýº¹È½¼ö

	float AttackTimeNow;
	float AttackTime;
	float GenTimeNow;
	float GenTime;
public:
	void SetParent(CObj* pParent)
	{
		m_pParent = pParent;
	}
	void CreateBlast();
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CBBullet(D3DXVECTOR3 _pos, wstring _renderkey, DIRECTION _dir);
	~CBBullet();
};

