#ifndef MXVIDEOPARAMFLAGS_H
#define MXVIDEOPARAMFLAGS_H

class MxVideoParamFlags {
public:
	MxVideoParamFlags();

	void SetF1bit3(MxBool p_e) { m_flags1.m_bit3 = p_e; }

	// inlined in ISLE
	void SetWideViewAngle(MxBool p_e) { m_flags1.m_bit6 = p_e; }

	// inlined in ISLE
	void SetF1bit7(MxBool p_e) { m_flags1.m_bit7 = p_e; }

	void SetF2bit0(MxBool p_e) { m_flags2.m_bit0 = p_e; }

	// inlined in ISLE
	void SetF2bit1(MxBool p_e) { m_flags2.m_bit1 = p_e; }

	MxBool GetF1bit3() { return m_flags1.m_bit3; }

	MxBool Get16Bit() { return m_flags1.m_bit5; }

	MxBool GetWideViewAngle() { return m_flags1.m_bit6; }

	MxBool GetF2bit0() { return m_flags2.m_bit0; }

	MxBool GetF2bit1() { return m_flags2.m_bit1; }

private:
	FlagBitfield m_flags1;
	FlagBitfield m_flags2;
};

#endif // MXVIDEOPARAMFLAGS_H
