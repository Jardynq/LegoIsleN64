#include "mxvariabletable.h"

MxS8 MxVariableTable::Compare(MxVariable* p_var0, MxVariable* p_var1) {
	return p_var0->GetKey()->Compare(*p_var1->GetKey());
}

MxU32 MxVariableTable::Hash(MxVariable* p_var) {
	const char* str = p_var->GetKey()->GetData();
	MxU32 value = 0;

	for (MxS32 i = 0; str[i]; i++) {
		value += str[i];
	}

	return value;
}

void MxVariableTable::SetVariable(const char* p_key, const char* p_value) {
	MxHashTableCursor<MxVariable*> cursor(this);
	MxVariable* var = new MxVariable(p_key, p_value);

	if (cursor.Find(var)) {
		delete var;
		cursor.Current(var);
		var->SetValue(p_value);
	} else {
		MxHashTable<MxVariable*>::Add(var);
	}
}

void MxVariableTable::SetVariable(MxVariable* p_var) {
	MxHashTableCursor<MxVariable*> cursor(this);

	if (cursor.Find(p_var)) {
		cursor.DeleteMatch();
	}

	MxHashTable<MxVariable*>::Add(p_var);
}

const char* MxVariableTable::GetVariable(const char* p_key) {

	const char* value = "";
	MxHashTableCursor<MxVariable*> cursor(this);
	MxVariable* var = new MxVariable(p_key);

	MxBool found = cursor.Find(var);
	delete var;

	if (found) {
		cursor.Current(var);
		value = var->GetValue()->GetData();
	}

	return value;
}
