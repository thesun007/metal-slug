#include "StdAfx.h"
#include "MainApp.h"
#include "Include.h"

CMainApp::CMainApp(void)
{}

CMainApp::~CMainApp(void)
{
	OnRelease();
}

HRESULT CMainApp::OnInit()
{
	if(FAILED((*CDevice::GetInst())->OnInit(WIN_WINDOW)))
		return E_FAIL;

	if(FAILED(SINGLE(CSceneMgr)->LoadScene(SCENEID_LOGO)))
		return E_FAIL;

	if(FAILED(SINGLE(CKeyMgr)->OnInit()))
		return E_FAIL;

	SINGLE(CCamMgr)->OnInit();
	SINGLE(CTimeMgr)->OnInit();
	SINGLE(CTimeMgr)->SetTimeScale(1.0f);

	srand(unsigned(time(NULL)));

	return S_OK;
}

int CMainApp::OnUpdate()
{
	SINGLE(CTimeMgr)->SetTime();
	SINGLE(CKeyMgr)->OnSet();
	switch(SINGLE(CSceneMgr)->OnUpdate())
	{
	case RESULT_SCENE_LOGO:
		if (FAILED(SINGLE(CSceneMgr)->LoadScene(SCENEID_LOGO)))
			return RESULT_GAME_EXIT;
		break;
	case RESULT_SCENE_SELECT:
		if (FAILED(SINGLE(CSceneMgr)->LoadScene(SCENEID_SELECT)))
			return RESULT_GAME_EXIT;
		break;
	case RESULT_SCENE_STAGE:
		if(FAILED(SINGLE(CSceneMgr)->LoadScene(SCENEID_STAGE)))
			return RESULT_GAME_EXIT;
		break;
	case RESULT_SCENE_OVER:
		if (FAILED(SINGLE(CSceneMgr)->LoadScene(SCENEID_OVER)))
			return RESULT_GAME_EXIT;
		break;
	case RESULT_GAME_EXIT:
		return RESULT_GAME_EXIT;
		break;
	}
	SINGLE(CCamMgr)->OnUpdate();
	return RESULT_NONE;
}

void CMainApp::OnRender()
{
	(*CDevice::GetInst())->OnBegin();
	SINGLE(CSceneMgr)->OnRender();
	(*CDevice::GetInst())->OnEnd();
}

void CMainApp::OnRelease()
{
	CCollisionMgr::Destroy();
	CKeyMgr::Destroy();
	CCamMgr::Destroy();
	CSceneMgr::Destroy();
	CTimeMgr::Destroy();
	CTextureMgr::Destroy();
	CDevice::Destroy();
}
