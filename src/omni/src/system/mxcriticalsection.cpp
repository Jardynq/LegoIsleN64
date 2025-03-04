#include "mxcriticalsection.h"

#include <stdio.h>

BOOL g_useMutex = FALSE;

MxCriticalSection::MxCriticalSection() {
	HANDLE mutex;

	if (g_useMutex) {
		mutex = CreateMutexA(NULL, FALSE, NULL);
		m_mutex = mutex;
	} else {
		InitializeCriticalSection(&m_criticalSection);
		m_mutex = NULL;
	}
}

MxCriticalSection::~MxCriticalSection() {
	if (m_mutex != NULL) {
		CloseHandle(m_mutex);
	} else {
		DeleteCriticalSection(&m_criticalSection);
	}
}

void MxCriticalSection::Enter() {
	DWORD result;
	FILE* file;

	if (m_mutex != NULL) {
		result = WaitForSingleObject(m_mutex, 5000);
		if (result == WAIT_FAILED) {
			file = fopen("C:\\DEADLOCK.TXT", "a");
			if (file != NULL) {
				fprintf(file, "mutex timeout occurred!\n");
				fclose(file);
			}

			abort();
		}
	} else {
		EnterCriticalSection(&m_criticalSection);
	}
}

void MxCriticalSection::Leave() {
	if (m_mutex != NULL) {
		ReleaseMutex(m_mutex);
	} else {
		LeaveCriticalSection(&m_criticalSection);
	}
}

void MxCriticalSection::SetDoMutex() {
	g_useMutex = TRUE;
}
