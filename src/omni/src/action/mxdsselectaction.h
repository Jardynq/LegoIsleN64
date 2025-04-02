#ifndef MXDSSELECTACTION_H
#define MXDSSELECTACTION_H

#include "mxdsparallelaction.h"
#include "mxstringlist.h"

class MxDSSelectAction : public MxDSParallelAction {
public:
	MxDSSelectAction();
	~MxDSSelectAction() override;

	void CopyFrom(MxDSSelectAction& p_dsSelectAction);
	MxDSSelectAction& operator=(MxDSSelectAction& p_dsSelectAction);

	static const char* ClassName() { return "MxDSSelectAction"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSSelectAction::ClassName()) ||
			   MxDSParallelAction::IsA(p_name);
	}

	MxU32 GetSizeOnDisk() override;
	void Deserialize(MxU8*& p_source, MxS16 p_unk0x24) override;
	MxDSAction* Clone() override;

	// MxDSSelectAction::`scalar deleting destructor'

private:
	MxString m_unk0x9c;
	MxStringList* m_unk0xac;
};

// MxStringListCursor::`scalar deleting destructor'

// MxListCursor<MxString>::~MxListCursor<MxString>

// MxListCursor<MxString>::`scalar deleting destructor'

// MxStringListCursor::~MxStringListCursor

#endif // MXDSSELECTACTION_H
