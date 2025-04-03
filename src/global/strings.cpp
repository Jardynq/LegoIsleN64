#include "types.h"

#include <ctype.h>

int strcmpi(const char* s1, const char* s2) {
	if (!s1 || !s2) {
		return (s1 == s2) ? 0 : (s1 ? 1 : -1);
	}

	while (*s1 && *s2) {
		char c1 = tolower((u8) *s1);
		char c2 = tolower((u8) *s2);

		if (c1 != c2) {
			return c1 - c2;
		}

		s1++;
		s2++;
	}

	return (u8) *s1 - (u8) *s2;
}

int strncmpi(const char* s1, const char* s2, int n) {
	if (!s1 || !s2) {
		return (s1 == s2) ? 0 : (s1 ? 1 : -1);
	}

	while (*s1 && *s2 && n > 0) {
		char c1 = tolower((u8) *s1);
		char c2 = tolower((u8) *s2);

		if (c1 != c2) {
			return c1 - c2;
		}

		s1++;
		s2++;
		n--;
	}

	return n <= 0 ? 0 : (u8) *s1 - (u8) *s2;
}
