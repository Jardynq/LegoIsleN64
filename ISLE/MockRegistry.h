#ifndef MOCK_REG_H
#define MOCK_REG_H

enum RegType {
	RegString,
	RegInt,
	RegBool
};
void RegReset();
int RegReadKey(const char* key, enum RegType type, void* output, int max_len);
int RegWriteKey(const char* key, enum RegType type, const void* input);

#endif // MOCK_REG_H
