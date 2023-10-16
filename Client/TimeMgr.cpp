#include "StdAfx.h"
#include "TimeMgr.h"


CTimeMgr::CTimeMgr(void)
	:m_fTime(0)
	,m_fTimeScale(0)
{}

CTimeMgr::~CTimeMgr(void)
{}

void CTimeMgr::OnInit()
{
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceFrequency(&m_CpuTime);
}

void CTimeMgr::SetTime()
{
	QueryPerformanceCounter(&m_FrameTime);

	if(m_FrameTime.QuadPart - m_LastTime.QuadPart > 
		m_CpuTime.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTime);
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	m_fTime = (float(m_FrameTime.QuadPart
		- m_FixTime.QuadPart) / m_CpuTime.QuadPart) * m_fTimeScale;
	m_FixTime = m_FrameTime;
}