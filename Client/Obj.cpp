#include "StdAfx.h"
#include "Obj.h"
#include "Include.h"

CObj::CObj(void)
	:m_pLine(NULL)
{}

CObj::~CObj(void)
{}

bool CObj::FrameMove()
{
	m_tFrame.fFrameTimeNow += DeltaTime;
	if(m_tFrame.fFrameTimeNow >= m_tFrame.fFrameTime)
	{
		++m_tFrame.iFrame;
		m_tFrame.fFrameTimeNow -= m_tFrame.fFrameTime;
		if(m_tFrame.iFrame >= 
			SINGLE(CTextureMgr)->GetFrameCnt(m_tKey.Option + m_tKey.szRenderKey,
			m_tKey.szSecondKey))
		{
			m_tFrame.iFrame = 0;
			return true;
		}
	}
	return false;
}

bool CObj::FrameMoveone()
{
	m_tFrame.fFrameTimeNow += DeltaTime;
	if (m_tFrame.fFrameTimeNow >= m_tFrame.fFrameTime)
	{
		++m_tFrame.iFrame;
		m_tFrame.fFrameTimeNow -= m_tFrame.fFrameTime;
		if (m_tFrame.iFrame >=
			SINGLE(CTextureMgr)->GetFrameCnt(m_tKey.Option+m_tKey.szRenderKey,
				m_tKey.szSecondKey))
		{
			m_tFrame.iFrame = SINGLE(CTextureMgr)->GetFrameCnt(m_tKey.Option+m_tKey.szRenderKey,
				m_tKey.szSecondKey)-1;
			return true;
		}
	}
	return false;
}

bool CObj::FrameMoveReverse()
{
	m_tFrame.fFrameTimeNow += DeltaTime;

	if (m_tFrame.fFrameTimeNow >= m_tFrame.fFrameTime)
	{
		--m_tFrame.iFrame;
		m_tFrame.fFrameTimeNow -= m_tFrame.fFrameTime;
		if (m_tFrame.iFrame < 0)
		{
			m_tFrame.iFrame = 0;
			return true;
		}
	}
	
	return false;
}

void CObj::ChangeAnimation(wstring StateKey)
{
	if (m_tKey.szSecondKey == StateKey + L"R")
	{
		return;
	}
	else if (m_tKey.szSecondKey == StateKey)
		return;
	m_tKey.szSecondKey = StateKey;
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTimeNow = 0;
}

void CObj::ChangeAnimationR(wstring StateKey)
{
	if (m_tKey.szSecondKey == StateKey)
	{
		return;
	}
	m_tKey.szSecondKey = StateKey;
	m_tFrame.iFrame = SINGLE(CTextureMgr)->GetFrameCnt(m_tKey.Option+m_tKey.szRenderKey,
		m_tKey.szSecondKey)-1;
	m_tFrame.fFrameTimeNow = 0;
}

void CObj::ChangeAnimationS(wstring StateKey)
{
	m_tKey.szSecondKey = StateKey;
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTimeNow = 0;
}

vector<RECT> CObj::GetRect(void)
{
	vector<RECT> vecRect;
	RECT	rt =
	{
		int(m_tInfo.vPos.x - m_tInfo.vSize.x / 2.f),
		int(m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f),
		int(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f),
		int(m_tInfo.vPos.y + m_tInfo.vSize.y / 2.f)
	};
	vecRect.push_back(rt);
	return vecRect;
}

//bool CObj::InTile(const D3DXVECTOR3& vPos, 
//		const TILE* pTile)
//{
//	float fGrad = (68 / 2.0f) / (130 / 2.0f);
//
//	D3DXVECTOR2 vPoint[4];
//	vPoint[0] = D3DXVECTOR2(
//		pTile->vPos.x,
//		pTile->vPos.y + 68 / 2.0f);
//	vPoint[1] = D3DXVECTOR2(
//		pTile->vPos.x + 130 / 2.0f,
//		pTile->vPos.y);
//	vPoint[2] = D3DXVECTOR2(
//		pTile->vPos.x,
//		pTile->vPos.y - 68 / 2.0f);
//	vPoint[3] = D3DXVECTOR2(
//		pTile->vPos.x - 130 / 2.0f,
//		pTile->vPos.y);
//
//	float fB[4] = 
//	{
//		vPoint[0].y - fGrad * vPoint[0].x,
//		vPoint[1].y + fGrad * vPoint[1].x,
//		vPoint[2].y - fGrad * vPoint[2].x,
//		vPoint[3].y + fGrad * vPoint[3].x
//	};
//
//	if( vPos.y -  fGrad * vPos.x - fB[0] < 0 &&
//		vPos.y - -fGrad * vPos.x - fB[1] < 0 &&
//		vPos.y -  fGrad * vPos.x - fB[2] >= 0 &&
//		vPos.y - -fGrad * vPos.x - fB[3] >= 0)
//		return true;
//	return false;
//}
