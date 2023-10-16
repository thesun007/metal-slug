#pragma once
#include "ObjDynamic.h"
class CEnemy :
	public CObjDynamic
{
protected:
	CObj* m_pPlayer;
	int m_iLevel;			//공격성향 레벨
public:
	virtual vector<RECT> GetRect(void);
	void SetLevel(int level) { m_iLevel = level; }
	int GetLevel()const { return m_iLevel; }
	void SetParentObj(CObj* pParent) { m_pPlayer = pParent; }
	CObj* GetParentObj() { return m_pPlayer; }
public:
	virtual HRESULT OnInit()PURE;
	virtual int OnUpdate()PURE;
	virtual void OnRender()PURE;
	virtual void OnRelease()PURE;
public:
	CEnemy();
	~CEnemy();
};

