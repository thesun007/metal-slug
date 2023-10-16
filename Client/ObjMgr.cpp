#include "StdAfx.h"
#include "ObjMgr.h"


CObjMgr::CObjMgr(void)
{}

CObjMgr::~CObjMgr(void)
{
	OnRelease();
}

HRESULT CObjMgr::PushObject(wstring TagKey, CObj* pObj)
{
	if(pObj == NULL)
		return E_FAIL;
	if(FAILED(pObj->OnInit()))
		return E_FAIL;
	auto iter = m_mapObject.find(TagKey);
	if(iter == m_mapObject.end())
	{
		list<CObj*> _list;
		_list.push_back(pObj);
		m_mapObject.insert(make_pair(TagKey, _list));
	}
	else
		iter->second.push_back(pObj);
	return S_OK;
}

int CObjMgr::OnUpdate()
{
	auto iter = m_mapObject.begin();
	for(; iter != m_mapObject.end() ; ++iter)
	{
		for(auto iter2 = iter->second.begin();
			iter2 != iter->second.end();)
		{
			switch((*iter2)->OnUpdate())
			{
			case RESULT_OBJECT_DELETE:
				delete *iter2;
				*iter2 = NULL;
				iter2 = iter->second.erase(iter2);
				break;
			default:
				m_mapRender[(*iter2)->GetLayer()].insert(
					make_pair((*iter2)->GetInfo().vPos.y, (*iter2)));
				++iter2;
			}
		}
	}
	return RESULT_NONE;
}

void CObjMgr::OnRender()
{
	for(int i = 0; i < LAYER_END; ++i)
	{
		for(auto iter = m_mapRender[i].begin();
			iter != m_mapRender[i].end(); ++iter)
		{
			iter->second->OnRender();
		}
		m_mapRender[i].clear();
	}
}

void CObjMgr::OnRelease()
{
	for(int i = 0; i < LAYER_END; ++i)
	{
		m_mapRender[i].clear();
	}
	auto iter = m_mapObject.begin();
	for(; iter != m_mapObject.end() ; ++iter)
	{
		for(auto iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2)
		{
			delete *iter2;
		}
		iter->second.clear();
	}
	m_mapObject.clear();
}

list<CObj*>* CObjMgr::GetObjectList(wstring TagKey)
{
	auto iter = m_mapObject.find(TagKey);
	if (iter == m_mapObject.end())
		return NULL;
	else
		return &iter->second;
}
