#pragma once

#define PUSHKEY(nKey) ((*CKeyMgr::GetInst())->GetKeyBoardState(nKey) & 0x80)
#define UPKEY(nKey) !((*CKeyMgr::GetInst())->GetKeyBoardState(nKey) & 0x80)
#define MOUSESTATE ((*CKeyMgr::GetInst())->GetMouseState())

#define DeltaTime ((*CTimeMgr::GetInst())->GetTime())
#define SINGLE(type) (*type::GetInst())

#define SINGLETON(type) public:\
	static type** GetInst()\
	{\
		static type* pInst = 0;\
		if(pInst == 0)\
			pInst = new type;\
		return &pInst;\
	}\
	static void Destroy()\
	{\
		type** ppInst = GetInst();\
		if(*ppInst != 0)\
		{\
			delete *ppInst;\
			*ppInst = 0;\
		}\
	}