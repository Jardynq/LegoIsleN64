#ifndef LEGOCHARACTERMANAGER_H
#define LEGOCHARACTERMANAGER_H

#include "mxvariable.h"
#include "roi/legoroi.h"

class LegoActor;
class LegoExtraActor;
class LegoStorage;
class LegoROI;

#pragma warning(disable : 4237)

struct LegoCharacterComparator {
	MxBool operator()(const char* const& p_a, const char* const& p_b) const {
		return strcmpi(p_a, p_b) < 0;
	}
};

struct LegoCharacter {
	LegoCharacter(LegoROI* p_roi) {
		m_roi = p_roi;
		m_refCount = 1;
	}
	~LegoCharacter() { delete m_roi; }

	void AddRef() { m_refCount++; }
	MxU32 RemoveRef() {
		if (m_refCount != 0) {
			m_refCount--;
		}

		return m_refCount;
	}

	LegoROI* m_roi;
	MxU32 m_refCount;
};

struct LegoActorInfo;

typedef map<char*, LegoCharacter*, LegoCharacterComparator> LegoCharacterMap;

class CustomizeAnimFileVariable : public MxVariable {
public:
	CustomizeAnimFileVariable(const char* p_key);

	void SetValue(const char* p_value) override;
};

class LegoCharacterManager {
public:
	LegoCharacterManager();
	~LegoCharacterManager();

	MxResult Write(LegoStorage* p_storage);
	MxResult Read(LegoStorage* p_storage);
	const char* GetActorName(MxS32 p_index);
	MxU32 GetNumActors();
	LegoROI* GetActorROI(const char* p_name, MxBool p_createEntity);

	void Init();
	static void SetCustomizeAnimFile(const char* p_value);
	static MxBool IsActor(const char* p_name);

	void ReleaseAllActors();
	MxBool Exists(const char* p_name);
	MxU32 GetRefCount(LegoROI* p_roi);
	void ReleaseActor(const char* p_name);
	void ReleaseActor(LegoROI* p_roi);
	void ReleaseAutoROI(LegoROI* p_roi);
	MxBool FUN_100849a0(LegoROI* p_roi, LegoTextureInfo* p_texture);
	LegoExtraActor* GetExtraActor(const char* p_name);
	LegoActorInfo* GetActorInfo(const char* p_name);
	LegoActorInfo* GetActorInfo(LegoROI* p_roi);
	MxBool SwitchColor(LegoROI* p_roi, LegoROI* p_targetROI);
	MxBool SwitchVariant(LegoROI* p_roi);
	MxBool SwitchSound(LegoROI* p_roi);
	MxBool SwitchMove(LegoROI* p_roi);
	MxBool SwitchMood(LegoROI* p_roi);
	MxU32 GetAnimationId(LegoROI* p_roi);
	MxU32 GetSoundId(LegoROI* p_roi, MxBool p_und);
	MxU8 GetMood(LegoROI* p_roi);
	LegoROI* CreateAutoROI(
		const char* p_name,
		const char* p_lodName,
		MxBool p_createEntity
	);
	MxResult FUN_10085870(LegoROI* p_roi);
	LegoROI* FUN_10085a80(
		const char* p_name,
		const char* p_lodName,
		MxBool p_createEntity
	);

	static const char* GetCustomizeAnimFile() { return g_customizeAnimFile; }

private:
	LegoROI* CreateActorROI(const char* p_key);
	void RemoveROI(LegoROI* p_roi);
	LegoROI* FindChildROI(LegoROI* p_roi, const char* p_name);

	static char* g_customizeAnimFile;
	static MxU32 g_maxMove;
	static MxU32 g_maxSound;

	LegoCharacterMap* m_characters;
	CustomizeAnimFileVariable* m_customizeAnimFile;
};

// clang-format off

// list<ROI *,allocator<ROI *> >::_Buynode


// ?_Construct@@YAXPAPAVROI@@ABQAV1@@Z


// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::~_Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >


// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::iterator::_Inc


// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::erase


// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::_Erase


// map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::~map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >


// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::iterator::_Dec


// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::_Insert


// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::insert


// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::_Buynode


// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::_Lrotate


// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::_Rrotate


// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::_Nil
// clang-format on

#endif // LEGOCHARACTERMANAGER_H
