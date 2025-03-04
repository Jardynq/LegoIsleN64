#ifndef MXOMNICREATEFLAGS_H
#define MXOMNICREATEFLAGS_H

// SIZE 0x02
class MxOmniCreateFlags {
public:
	MxOmniCreateFlags();

	// FUNCTION: BETA10 0x10092b50
	void CreateObjectFactory(MxBool p_enable) { m_flags1.m_bit0 = p_enable; }

	// FUNCTION: BETA10 0x10092b90
	void CreateTickleManager(MxBool p_enable) { m_flags1.m_bit2 = p_enable; }

	// FUNCTION: BETA10 0x10092bd0
	void CreateVideoManager(MxBool p_enable) { m_flags1.m_bit4 = p_enable; }

	// FUNCTION: BETA10 0x10092c10
	void CreateSoundManager(MxBool p_enable) { m_flags1.m_bit5 = p_enable; }

	// FUNCTION: BETA10 0x10130cd0
	MxBool CreateObjectFactory() const { return m_flags1.m_bit0; }

	// FUNCTION: BETA10 0x10130cf0
	MxBool CreateVariableTable() const { return m_flags1.m_bit1; }

	// FUNCTION: BETA10 0x10130d10
	MxBool CreateTickleManager() const { return m_flags1.m_bit2; }

	// FUNCTION: BETA10 0x10130d30
	MxBool CreateNotificationManager() const { return m_flags1.m_bit3; }

	// FUNCTION: BETA10 0x10130d50
	MxBool CreateVideoManager() const { return m_flags1.m_bit4; }

	// FUNCTION: BETA10 0x10130d70
	MxBool CreateSoundManager() const { return m_flags1.m_bit5; }

	// FUNCTION: BETA10 0x10130d90
	MxBool CreateMusicManager() const { return m_flags1.m_bit6; }

	// FUNCTION: BETA10 0x10130db0
	MxBool CreateEventManager() const { return m_flags1.m_bit7; }

	// FUNCTION: BETA10 0x10130dd0
	MxBool CreateTimer() const { return m_flags2.m_bit1; }

	// FUNCTION: BETA10 0x10130e00
	MxBool CreateStreamer() const { return m_flags2.m_bit2; }

private:
	FlagBitfield m_flags1;
	FlagBitfield m_flags2;
};

#endif // MXOMNICREATEFLAGS_H
