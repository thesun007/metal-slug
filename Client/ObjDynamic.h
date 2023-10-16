#pragma once

#include "Obj.h"

class CObjDynamic : public CObj
{
protected:
	bool m_bJump;
	/*bool m_bCJump;*/
	float m_fV;
	float m_fTimeNow;
	float m_fTime;

	//Á×¾úÀ»¶§ ±ô¹ÚÀÓ
	int m_iDeathCount;
	int m_iAlpha;
public:
	virtual vector<RECT> GetRect(void);
	void Jump();
	bool LineCol();
public:
	virtual HRESULT OnInit()PURE;
	virtual int OnUpdate()PURE;
	virtual void OnRender()PURE;
	virtual void OnRelease()PURE;
public:
	CObjDynamic(void);
	virtual ~CObjDynamic(void);
};

