#ifndef MXOMNICREATEFLAGS_H
#define MXOMNICREATEFLAGS_H

class MxOmniCreateFlags {
public:
	MxOmniCreateFlags();

	void CreateObjectFactory(MxBool p_enable) { m_flags1.m_bit0 = p_enable; }

	void CreateTickleManager(MxBool p_enable) { m_flags1.m_bit2 = p_enable; }

	void CreateVideoManager(MxBool p_enable) { m_flags1.m_bit4 = p_enable; }

	void CreateSoundManager(MxBool p_enable) { m_flags1.m_bit5 = p_enable; }

	MxBool CreateObjectFactory() const { return m_flags1.m_bit0; }

	MxBool CreateVariableTable() const { return m_flags1.m_bit1; }

	MxBool CreateTickleManager() const { return m_flags1.m_bit2; }

	MxBool CreateNotificationManager() const { return m_flags1.m_bit3; }

	MxBool CreateVideoManager() const { return m_flags1.m_bit4; }

	MxBool CreateSoundManager() const { return m_flags1.m_bit5; }

	MxBool CreateMusicManager() const { return m_flags1.m_bit6; }

	MxBool CreateEventManager() const { return m_flags1.m_bit7; }

	MxBool CreateTimer() const { return m_flags2.m_bit1; }

	MxBool CreateStreamer() const { return m_flags2.m_bit2; }

private:
	FlagBitfield m_flags1;
	FlagBitfield m_flags2;
};

#endif // MXOMNICREATEFLAGS_H
