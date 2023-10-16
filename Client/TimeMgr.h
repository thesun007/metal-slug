#pragma once

#include "Defines.h"

class CTimeMgr
{
	SINGLETON(CTimeMgr);
private:
	LARGE_INTEGER m_FrameTime;
	LARGE_INTEGER m_FixTime;
	LARGE_INTEGER m_LastTime;
	LARGE_INTEGER m_CpuTime;
	float         m_fTime;
	float         m_fTimeScale;
public:
	void OnInit();
	void SetTime();
	void SetTimeScale(float _fScale) { m_fTimeScale = _fScale; }
public:
	const float& GetTime() const { return m_fTime; }
public:
	CTimeMgr(void);
	~CTimeMgr(void);
};

