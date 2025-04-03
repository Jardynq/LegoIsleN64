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

	// MxVariableTable::`scalar deleting destructor'
};

// class MxCollection<MxVariable *>

// class MxHashTable<MxVariable *>

// class MxHashTableCursor<MxVariable *>

// MxCollection<MxVariable *>::Compare

// MxCollection<MxVariable *>::~MxCollection<MxVariable *>

// MxCollection<MxVariable *>::Destroy

// MxCollection<MxVariable *>::`scalar deleting destructor'

// MxHashTable<MxVariable *>::Hash

// MxHashTable<MxVariable *>::~MxHashTable<MxVariable *>

// MxHashTable<MxVariable *>::`scalar deleting destructor'

// MxHashTableCursor<MxVariable *>::~MxHashTableCursor<MxVariable *>

// MxHashTableCursor<MxVariable *>::`scalar deleting destructor'

// MxHashTable<MxVariable *>::Resize

// MxHashTable<MxVariable *>::NodeInsert

// MxHashTableCursor<MxVariable *>::MxHashTableCursor<MxVariable *>

// MxHashTable<MxVariable *>::Add

// MxHashTableCursor<MxVariable *>::Current

// MxHashTableCursor<MxVariable *>::DeleteMatch

// MxHashTableCursor<MxVariable *>::Find

// MxHashTableNode<MxVariable *>::MxHashTableNode<MxVariable *>

// MxHashTable<MxVariable *>::MxHashTable<MxVariable *>

// MxCollection<MxVariable *>::SetDestroy

// MxVariableTable::~MxVariableTable

// MxCollection<MxVariable *>::MxCollection<MxVariable *>

// MxHashTable<MxVariable *>::DeleteAll

