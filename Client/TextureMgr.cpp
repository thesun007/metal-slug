#include "StdAfx.h"
#include "TextureMgr.h"
#include "Texture.h"

CTextureMgr::CTextureMgr(void)
{}

CTextureMgr::~CTextureMgr(void)
{
	OnRelease();
}

HRESULT CTextureMgr::InsertTexture(wstring FileName,
	wstring ObjKey, wstring StateKey, const int iCnt)
{
	auto iter = m_mapTexture.find(ObjKey);
	if(iter != m_mapTexture.end())
	{
		if(FAILED(iter->second->InsertTexture(
			FileName, StateKey, iCnt)))
			return E_FAIL;
	}
	else
	{
		CTexture* pTexture = new CTexture;
		if(FAILED(pTexture->InsertTexture(
			FileName, StateKey, iCnt)))
			return E_FAIL;
		m_mapTexture.insert(make_pair(ObjKey, pTexture));
	}
	return S_OK;
}

void CTextureMgr::OnRelease()
{

	for(auto iter = m_mapTexture.begin();
		iter != m_mapTexture.end(); ++iter)
	{
		delete iter->second;
	}
	m_mapTexture.clear();
}

const TEXINFO* CTextureMgr::GetTexture(
	wstring ObjKey
	, wstring StateKey /* = L"" */
	, const int iCnt /* = 0 */)
{
	auto iter = m_mapTexture.find(ObjKey);
	if(iter == m_mapTexture.end())
		return 0;
	return iter->second->GetTexture(StateKey, iCnt);
}

int CTextureMgr::GetFrameCnt(wstring ObjKey, 
	wstring StateKey /* = L"" */)
{
	auto iter = m_mapTexture.find(ObjKey);
	if(iter == m_mapTexture.end())
		return 0;
	return iter->second->GetFrameCnt(StateKey);
}
