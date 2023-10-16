#pragma once

#include "Defines.h"

class CObj
{
protected:
	OBJINFO   m_tInfo;
	RENDERKEY m_tKey;
	LAYER     m_eLayer;
	FRAME     m_tFrame;

	int		  m_iFootposY;
	bool	  m_bMove;
	BYTE	  m_byState;
	int		  m_iHp;
protected:
	list<LINE*> *m_plistLine;
	LINE* m_pLine;
public:
	void SetLine(list<LINE*>* _pLineList) { m_plistLine = _pLineList; }
	list<LINE*>* GetListLine() { return m_plistLine; }
	LINE* GetLine() { return m_pLine; }
public:
	void SetRenderKey(wstring SecondKey)
	{ m_tKey.szSecondKey = SecondKey; }
	void SetPos(D3DXVECTOR3& Pos)
	{ m_tInfo.vPos = Pos; }
	void SetCenter(D3DXVECTOR3& Center)
	{ m_tInfo.vCenter = Center; }

	BYTE& GetState() { return m_byState; }

	void SetHp(int damage) { m_iHp += damage; }
//protected:
//	bool InTile(const D3DXVECTOR3& vPos, 
//		const TILE* pTile);
public:
	bool FrameMove();
	bool FrameMoveone();
	bool FrameMoveReverse();
	void ChangeAnimation(wstring StateKey);
	void ChangeAnimationR(wstring StateKey);
	void ChangeAnimationS(wstring StateKey);
public:
	 LAYER& GetLayer() {return m_eLayer;}
	 OBJINFO& GetInfo() {return m_tInfo;}
	 RENDERKEY& GetKey() { return m_tKey; }
	 FRAME&	GetFrame() { return m_tFrame; }
	virtual vector<RECT> GetRect(void);
public:
	virtual HRESULT OnInit()PURE;
	virtual int OnUpdate()PURE;
	virtual void OnRender()PURE;
	virtual void OnRelease()PURE;
public:
	CObj(void);
	virtual ~CObj(void);
};

