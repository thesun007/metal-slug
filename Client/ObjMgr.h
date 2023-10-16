#pragma once

#include "Obj.h"

class CObjMgr
{
	SINGLETON(CObjMgr);
private:
	map<wstring, list<CObj*>> m_mapObject;
	multimap<float, CObj*> m_mapRender[LAYER_END];
public:
	list<CObj*>* GetObjectList(wstring TagKey);
public:
	HRESULT PushObject(wstring TagKey, CObj* pObj);
	int OnUpdate();
	void OnRender();
	void OnRelease();
public:
	CObjMgr(void);
	~CObjMgr(void);
};

