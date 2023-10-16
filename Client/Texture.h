#pragma once

#include "Defines.h"

class CTexture
{
private:
	map<wstring, vector<TEXINFO*>> m_mapTexture;
	map<wstring, int> m_mapFrameCnt;
public:
	int GetFrameCnt(wstring StateKey = L"");
	const TEXINFO* GetTexture(wstring StateKey = L""
		, const int iCnt = 0);
	HRESULT InsertTexture(wstring FileName
		, wstring StateKey = L"", const int iCnt = 0);
	void OnRelease();
public:
	CTexture(void);
	virtual ~CTexture(void);
};

