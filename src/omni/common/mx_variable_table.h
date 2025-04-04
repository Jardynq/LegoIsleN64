#pragma once

#include "mx_hashtable.h"
#include "mx_variable.h"

class MxVariableTable : public MxHashTable<MxVariable*> {
public:
	MxVariableTable() { SetDestroy(Destroy); }
	void SetVariable(const char* p_key, const char* p_value);
	void SetVariable(MxVariable* p_var);
	const char* GetVariable(const char* p_key);

	static void Destroy(MxVariable* p_obj) { p_obj->Destroy(); }

	MxS8 Compare(MxVariable*, MxVariable*) override;
	MxU32 Hash(MxVariable*) override;
};
