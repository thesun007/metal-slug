#pragma once
#include "ObjDynamic.h"
#include "NpcWait.h"

class CNpc :
	public CObjDynamic
{
private:
	CAi* m_pAI;
	int m_iLevel;			//성향 0:점프x, 1:점프o

	bool FrameEnd;
	bool FrameReverse;
	bool FrameOne;

	bool	Landing;
	float   JumpTime;
	bool	DownTime;	//앉아있을때 위치제어
	bool	FreeTime;

	//선물
	int	 m_iGift;			//선물 종류 (0:헤비, 1:수류탄)
	bool m_bGive;			//선물 제어 (특정모션에서 한번만 실행하게끔)

public:
	bool& GetFrameEnd() { return FrameEnd; }
	bool& GetLanding() { return Landing; }
	void SetFrame(bool reverse, bool one) { FrameReverse = reverse; FrameOne = one; }
public:
	void SetLevel(int level) { m_iLevel = level; }
	int GetLevel()const { return m_iLevel; }
	void SetItem(int item) { m_iGift = item; }
public:
	void Motion();
	void Action();
	void Give();
	void CreateItem(D3DXVECTOR3 pos, wstring name);
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CNpc();
	~CNpc();
};

