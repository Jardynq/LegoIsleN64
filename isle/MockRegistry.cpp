#include "MockRegistry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <unistd.h>

const int LINE_LEN = 1024;
const char* REGISTRY_FILE = "registry.txt";

void RegReset() {
	FILE* file = fopen(REGISTRY_FILE, "w");
	fclose(file);
}

int RegReadKey(const char* key, enum RegType type, void* output, int size) {
	FILE* file = fopen(REGISTRY_FILE, "r");
	if (file == NULL) {
		printf("Failed to open registry for reading:\n%s\n", strerror(errno));
		return -1;
	}

	int key_len = strlen(key);
	int max_len = size > LINE_LEN ? LINE_LEN : size;
	char line[LINE_LEN] = { 0 };
	while (fgets(line, LINE_LEN, file) > 0) {
		for (int i = 0; i < LINE_LEN; i++) {
			if (line[i] == '\n') line[i] = 0;
		}

		if (strncmp(line, key, key_len - 1) == 0) {
			switch (type) {
			case RegString:
				strncpy((char*)output, line + key_len + 1, max_len);
				break;
			case RegInt:
			case RegBool:
				*(int*)output = atoi(line + key_len + 1);
				break;
			}
			fclose(file);
			return 0;
		}
		memset(line, 0, LINE_LEN);
	}
	fclose(file);
	return -1;
}

int RegWriteKey(const char* key, enum RegType type, const void* input) {
	FILE* file = fopen(REGISTRY_FILE, "a");
	if (file == NULL) {
		printf("Failed to open registry for writing:\n%s\n", strerror(errno));
		return -1;
	}

	switch (type) {
	case RegString:
		fprintf(file, "%s;%s\n", key, input);
		break;
	case RegInt:
	case RegBool:
		fprintf(file, "%s;%d\n", key, *(int*)input);
		break;
	}
	fclose(file);
	return 0;
}