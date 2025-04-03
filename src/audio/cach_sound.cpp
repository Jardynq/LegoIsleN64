#include "cach_sound.h"

#include "sound_manager.h"
#include "misc.h"
#include "mixer.h"
#include "wav64.h"

#include <assert.h>
#include <cstddef>

LegoCacheSound::LegoCacheSound() {
	Init();
}

LegoCacheSound::~LegoCacheSound() {
	Destroy();
}

void LegoCacheSound::Init() {
	m_wav = wav64_t();
	m_is_playing = FALSE;
	m_looping = TRUE;
	m_volume = 69;
	m_unk0x70 = FALSE;
	m_muted = FALSE;
}

MxResult LegoCacheSound::Create(
	MxString p_mediaSrcPath,
	MxS32 p_volume,
	wav64_t *p_wav
) {
	m_volume = p_volume;
	if (p_wav != nullptr) {
		wav64_close(&m_wav);
		m_wav = *p_wav;
	}

	m_filename = GetBaseFilename(p_mediaSrcPath);
	return SUCCESS;
}

void LegoCacheSound::Destroy() {
	wav64_close(&m_wav);
	Init();
}

LegoCacheSound* LegoCacheSound::Clone() {
	LegoCacheSound* pnew = new LegoCacheSound();
	assert(pnew);

	MxResult result =
		pnew->Create(m_filename, m_volume, &m_wav);
	if (result == SUCCESS) {
		return pnew;
	} else {
		delete pnew;
		return nullptr;
	}
}

MxResult LegoCacheSound::Play(const char* p_name, MxBool p_looping) {
	if (p_name != NULL) {
		m_filename = p_name;
	}

	if (p_looping) {
		wav64_set_loop(&m_wav, true);
	} else {
		wav64_set_loop(&m_wav, false);
	}
	
	float volume = (float)m_volume * (float)SoundManager()->GetVolume() / 100'00;
	mixer_ch_set_vol(0, volume, volume);
	wav64_play(&m_wav, 0);

	m_looping = p_looping;

	m_is_playing = TRUE;
	m_unk0x70 = TRUE;
	return SUCCESS;
}

void LegoCacheSound::Stop() {
	wav64_close(&m_wav);

	m_is_playing = FALSE;

	if (m_filename.GetLength() != 0) {
		m_filename = "";
	}
}

MxResult LegoCacheSound::Tickle() {
	bool hasFinished = false;

	if (!m_looping) {
		if (m_unk0x70) {
			if (!hasFinished) {
				return SUCCESS;
			}
			m_unk0x70 = FALSE;
		}

		if (hasFinished) {
			if (m_filename.GetLength() != 0) {
				m_filename = "";
			}

			m_is_playing = FALSE;
			return SUCCESS;
		}
	}

	if (m_filename.GetLength() == 0) {
		return SUCCESS;
	}

	if (!m_muted) {
		Play(m_filename.GetData(), m_looping);
	}

	return SUCCESS;
}

void LegoCacheSound::SetDistance(MxS32 p_min, MxS32 p_max) {
	//m_sound.SetDistance(p_min, p_max);
}

void LegoCacheSound::MuteSilence(MxBool p_muted) {
	if (m_muted != p_muted) {
		m_muted = p_muted;

		if (m_muted) {
			mixer_ch_set_vol(0, 0, 0);
		} else {
			float volume = (float)m_volume * (float)SoundManager()->GetVolume() / 100'00;
			mixer_ch_set_vol(0, volume, volume);
		}
	}
}

void LegoCacheSound::MuteStop(MxBool p_muted) {
	if (m_muted != p_muted) {
		m_muted = p_muted;

		if (m_muted) {
			wav64_close(&m_wav);
		} else {
			Play(m_filename.GetData(), m_looping);
		}
	}
}

MxString LegoCacheSound::GetBaseFilename(MxString& p_path) {
	// Get the base filename from the given path
	// e.g. "Z:\Lego\Audio\test.wav" --> "test"
	char* str = p_path.GetData();

	// Start at the end of the string and work backwards.
	char* p = str + strlen(str);
	char* end = p;

	while (str != p--) {
		// If the file has an extension, we want to exclude it from the output.
		// Set this as our new end position.
		if (*p == '.') {
			end = p;
		}

		// Stop if we hit a directory or drive letter.
		if (*p == '\\') {
			break;
		}
	}

	MxString output;
	// Increment by one to shift p to the start of the filename.
	char* x = ++p;
	// If end points to the dot in filename, change it to a null terminator.
	x[end - p] = '\0';
	return output = x;
}
