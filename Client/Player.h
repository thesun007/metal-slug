#pragma once

#include "ObjDynamic.h"

class CPlayer : public CObjDynamic
{
protected:
	bool Jumptime;
	bool Attacktime;
	bool Grenadetime;
	bool DownTime;				//앉을때 중심제어
	bool MoveTime;				//뛸때 중심제어
	bool DeathTime;

	bool FrameEnd;
	bool FrameReverse;
	bool FrameOne;
	bool FrameStop;			//특정 상태일때 프레임 잠깐 멈추기

	float Heavy;			// 헤비상태일때 프레임 속도 변경용도
	wstring SitMotion;
	bool	Landing;
	int		ShotStack;
		
	//총알
	int m_iHBullets;
	int m_iGrenades;
	float m_fAngle;				
	D3DXVECTOR3 m_vBulletPos;
	bool m_bShot;		//총알 제어
	float m_fHeavyAngle;	
public:
	void Motion();
	void Action();
	void Attack();
	void CreateBullet(float angle, int d = 1, D3DXVECTOR3 pos= D3DXVECTOR3(0,0,0));
	void CreateGrenade(D3DXVECTOR3 pos = D3DXVECTOR3(0, 0, 0));
	void SetEquip(wstring equipment);
public:
	void SetFrameTime(float time);		//텍스쳐 프레임 재생 속도
	bool GetJump() {return m_bJump;}
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CPlayer(void);
	virtual ~CPlayer(void);
};

