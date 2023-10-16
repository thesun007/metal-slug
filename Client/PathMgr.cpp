#include "StdAfx.h"
#include "PathMgr.h"
#include "Include.h"

CPathMgr::CPathMgr(void)
	:m_Path(0)
{}

CPathMgr::~CPathMgr(void)
{
	OnRelease();
}

void CPathMgr::PathBegin(int iStart, int iEnd
	, list<int>* Path)
{
	if(iStart == iEnd)
		return;
	if(Path == 0)
		return;
	m_Path = Path;
	const vector<TILE*>& Tile = 
		((CTerrain*)SINGLE(CObjMgr
		)->GetObjectList(L"Terrain").front())->GetVector();

	if(Tile[iEnd]->byOption & OPTION_DONMOVE)
		return;

	m_iStart = iStart;
	m_iEnd = iEnd;
	m_Path->clear();
	OnRelease();

	MakePath(Tile);
}

void CPathMgr::MakePath(const vector<TILE*>& vecTile)
{
	PATHNODE* pParent = new PATHNODE;
	pParent->iIndex = m_iStart;
	pParent->pParent = NULL;
	pParent->fCost = 0;
	

	PATHNODE* pNode = NULL;
	int iIndex = 0;
	while(true)
	{
		// ����
		iIndex = pParent->iIndex - 
			(TILECNTX - (pParent->iIndex / TILECNTX) % 2);
		// ���� �� Ÿ������ üũ
		if(pParent->iIndex >= TILECNTX)
		{
			// ¦����° ���� ������ �� Ÿ������ üũ
			if(pParent->iIndex % (TILECNTX * 2) != 
				TILECNTX * 2 - 1)
			{
				// �����ϼ� �ִ� Ÿ������
				if(!(vecTile[iIndex]->byOption & OPTION_DONMOVE))
				{
					// ���� �̹� üũ�� Ÿ������ 
					if(CheckList(iIndex))
					{
						pNode = MakePathNode(iIndex, pParent, vecTile);
						m_Open.push_back(pNode);
					}
				}
			}
		}

		// ����
		iIndex = pParent->iIndex + 
			(TILECNTX + (pParent->iIndex / TILECNTX) % 2);
		// ����Ʒ�������
		if(pParent->iIndex < TILECNTX * TILECNTY - TILECNTX)
		{
			// ¦����°�� ���� ������ Ÿ������ üũ
			if(pParent->iIndex % (TILECNTX * 2) !=
				TILECNTX * 2 - 1)
			{
				if(!(vecTile[iIndex]->byOption & OPTION_DONMOVE))
				{
					if(CheckList(iIndex))
					{
						pNode = MakePathNode(iIndex, pParent, vecTile);
						m_Open.push_back(pNode);
					}
				}
			}
		}

		// �޾�
		iIndex = pParent->iIndex + (TILECNTX - 1
			+ (pParent->iIndex / TILECNTX) % 2);
		// ���� �Ʒ�������
		if(pParent->iIndex < TILECNTX * TILECNTY - TILECNTX)
		{
			// ���� Ȧ����° �� ����Ÿ������ üũ
			if(pParent->iIndex % (TILECNTX * 2) != 0)
			{
				if(!(vecTile[iIndex]->byOption & OPTION_DONMOVE))
				{
					if(CheckList(iIndex))
					{
						pNode = MakePathNode(iIndex, pParent, vecTile);
						m_Open.push_back(pNode);
					}
				}
			}
		}

		// ����
		iIndex = pParent->iIndex - (TILECNTX + 1 - 
			(pParent->iIndex / TILECNTX) % 2);
		if(pParent->iIndex >= TILECNTX)
		{
			if(pParent->iIndex % (TILECNTX * 2) != 0)
			{
				if(!(vecTile[iIndex]->byOption & OPTION_DONMOVE))
				{
					if(CheckList(iIndex))
					{
						pNode = MakePathNode(iIndex, pParent, vecTile);
						m_Open.push_back(pNode);
					}
				}
			}
		}

		// ���ø��Լ�
		// list<Type>.sort(bool Function(Type,Type));
		m_Open.sort(Compare);
		auto iter = m_Open.begin();
		pParent = *iter;
		m_Close.push_back(*iter);
		iter = m_Open.erase(iter);
		if(pParent->iIndex == m_iEnd)
		{
			while(true)
			{
				(*m_Path).push_front(pParent->iIndex);
				pParent = pParent->pParent;
				if(pParent->iIndex == m_iStart)
					break;
			}
			break;
		}
	}
}

PATHNODE* CPathMgr::MakePathNode(int iIndex
	, PATHNODE* pParent
	, const vector<TILE*>& Tile)
{
	PATHNODE* pNode = new PATHNODE;
	pNode->iIndex = iIndex;
	pNode->pParent = pParent;

	// ����Ÿ�Ϻ��� ����Ÿ�ϱ��� �Ÿ�
	D3DXVECTOR3 vDir = Tile[iIndex]->vPos - 
		Tile[pParent->iIndex]->vPos;
	float fPCost = D3DXVec3Length(&vDir);

	// ����Ÿ�Ϻ��� ��ǥŸ�ϱ��� �Ÿ�
	vDir = Tile[iIndex]->vPos - 
		Tile[m_iEnd]->vPos;
	float fGCost = D3DXVec3Length(&vDir);
	pNode->fCost = fPCost + fGCost;
	return pNode;
}

bool CPathMgr::CheckList(int iIndex)
{
	for(auto iter = m_Open.begin();
		iter != m_Open.end(); ++iter)
	{
		if((*iter)->iIndex == iIndex)
			return false;
	}
	for(auto iter = m_Close.begin();
		iter != m_Close.end(); ++iter)
	{
		if((*iter)->iIndex == iIndex)
			return false;
	}
	return true;
}

void CPathMgr::OnRelease()
{
	for(auto iter = m_Open.begin();
		iter != m_Open.end(); ++iter)
	{
		delete *iter;
	}
	for(auto iter = m_Close.begin();
		iter != m_Close.end(); ++iter)
	{
		delete *iter;
	}
	m_Open.clear();
	m_Close.clear();
}
