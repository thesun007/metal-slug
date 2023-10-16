#pragma once

#include "Defines.h"

class CPathMgr
{
	SINGLETON(CPathMgr);
private:
	list<PATHNODE*> m_Open; // 내가 앞으로 조사해야할 대상
	list<PATHNODE*> m_Close; // 내가 이미 조사한 대상
	list<int>* m_Path; // 내가 찾은길
public:
	int m_iStart;
	int m_iEnd;
public:
	static bool Compare(PATHNODE* pDest, PATHNODE* pSour)
	{
		return pDest->fCost < pSour->fCost;
	}
public:
	void PathBegin(int iStart, int iEnd, 
		list<int>* Path);
	void MakePath(const vector<TILE*>& vecTile);
	bool CheckList(int iIndex);
	PATHNODE* MakePathNode(int iIndex, PATHNODE* pParent
		, const vector<TILE*>& vecTile);
	void OnRelease();
public:
	CPathMgr(void);
	~CPathMgr(void);
};

