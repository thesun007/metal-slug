#include "StdAfx.h"
#include "Texture.h"
#include "Include.h"

CTexture::CTexture(void)
{}

CTexture::~CTexture(void)
{
	OnRelease();
}

HRESULT CTexture::InsertTexture(wstring FileName 
	, wstring StateKey /* = L"" */
	, const int iCnt /* = 0 */)
{
	m_mapFrameCnt.insert(make_pair(StateKey, iCnt));
	/* FileName == L"%d.png" */
	TCHAR szPath[128] = L"";
	vector<TEXINFO*> vecTexture;
	for(int i = 0; i < iCnt; ++i)
	{
		wsprintf(szPath, FileName.data(), i);
		TEXINFO* pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));
		if(FAILED(D3DXGetImageInfoFromFile(
			szPath, &pTexInfo->Info)))
			return E_FAIL;
		if(FAILED(D3DXCreateTextureFromFileEx(
			(*CDevice::GetInst())->GetDevice(),
			szPath, pTexInfo->Info.Width, pTexInfo->Info.Height,
			pTexInfo->Info.MipLevels,  0, pTexInfo->Info.Format,
			D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
			D3DCOLOR_ARGB(255,248,0,248),
			&pTexInfo->Info, NULL, &pTexInfo->pTexture)))
			return E_FAIL;

		vecTexture.push_back(pTexInfo);
	}
	m_mapTexture.insert(make_pair(StateKey, vecTexture));

	return S_OK;
}

void CTexture::OnRelease()
{
	for(auto iter = m_mapTexture.begin();iter != m_mapTexture.end();++iter)
	{
		for(int i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->pTexture->Release();
			delete iter->second[i];
		}
		iter->second.clear();
	}
	m_mapTexture.clear();
}

const TEXINFO* CTexture::GetTexture(wstring StateKey /* = L""  */
	, const int iCnt /* = 0 */)
{
	auto iter = m_mapTexture.find(StateKey);
	if(iter == m_mapTexture.end())
		return 0;
	return iter->second[iCnt];
}

int CTexture::GetFrameCnt(wstring StateKey)
{
	auto iter = m_mapFrameCnt.find(StateKey);
	if(iter == m_mapFrameCnt.end())
		return 0;
	return iter->second;
}
