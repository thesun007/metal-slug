#pragma once

#include "Defines.h"

class CTexture;
class CTextureMgr
{
	SINGLETON(CTextureMgr);
private:
	map<wstring, CTexture*> m_mapTexture;
public:
	int GetFrameCnt(wstring ObjKey, wstring StateKey = L"");
	const TEXINFO* GetTexture(
		wstring ObjKey, wstring StateKey = L"",
		const int iCnt = 0);
public:
	HRESULT InsertTexture(wstring FileName,
		wstring ObjKey, wstring StateKey = L"",
		const int iCnt = 1);
	void OnRelease();
public:
	CTextureMgr(void);
	~CTextureMgr(void);
};

