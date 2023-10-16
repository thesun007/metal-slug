#pragma once

#include "Defines.h"

class CPathMgr
{
	SINGLETON(CPathMgr);
private:
	list<PATHNODE*> m_Open; // ���� ������ �����ؾ��� ���
	list<PATHNODE*> m_Close; // ���� �̹� ������ ���
	list<int>* m_Path; // ���� ã����
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

