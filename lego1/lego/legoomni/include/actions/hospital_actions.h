// This file was automatically generated by the actionheadergen tool.
// Please do not manually edit this file.
#ifndef HOSPITAL_ACTIONS_H
#define HOSPITAL_ACTIONS_H

namespace HospitalScript {
#if __cplusplus >= 201103L
	enum Script : int {
#else
	enum Script {
#endif
		c_noneHospital = -1,

		c__StartUp = 0,
		c_Doc_Entity = 1,
		c_Doc_Model = 2,
		c_Info_Ctl = 3,
		c_Door_Ctl = 4,
		c_Background_Bitmap = 5,
		c_PizzaLed_Bitmap = 6,
		c_CopLed_Bitmap = 7,
		c_Info_Up_Bitmap = 8,
		c_Info_Down_Bitmap = 9,
		c_Door_Mask_Bitmap = 10,
		c_ConfigAnimation = 11,
		c_hho002cl_Wav_500 = 12,
		c_hho002cl_Pho_500 = 13,
		c_hho002cl_0_sfx = 14,
		c_hho002cl_1_sfx = 15,
		c_hho002cl_Anim = 16,
		c_HHO003CL_Wav_501 = 17,
		c_HHO003CL_Pho_501 = 18,
		c_hho003cl_0_sfx = 19,
		c_hho003cl_1_sfx = 20,
		c_hho003cl_2_sfx = 21,
		c_hho003cl_3_sfx = 22,
		c_hho003cl_4_sfx = 23,
		c_hho003cl_Anim = 24,
		c_hho004jk_Wav_502 = 25,
		c_hho004jk_Pho_502 = 26,
		c_hho004jk_0_sfx = 27,
		c_hho004jk_1_sfx = 28,
		c_hho004jk_2_sfx = 29,
		c_hho004jk_3_sfx = 30,
		c_hho004jk_4_sfx = 31,
		c_hho004jk_5_sfx = 32,
		c_hho004jk_Anim = 33,
		c_hho016cl_Wav_503 = 34,
		c_hho016cl_Pho_503 = 35,
		c_hho016cl_0_sfx = 36,
		c_hho016cl_1_sfx = 37,
		c_hho016cl_Anim = 38,
		c_hho017cl_Wav_504 = 39,
		c_hho017cl_Pho_504 = 40,
		c_hho017cl_0_sfx = 41,
		c_hho017cl_1_sfx = 42,
		c_hho017cl_Anim = 43,
		c_hho018cl_Wav_505 = 44,
		c_hho018cl_Pho_505 = 45,
		c_hho018cl_0_sfx = 46,
		c_hho018cl_1_sfx = 47,
		c_hho018cl_2_sfx = 48,
		c_hho018cl_3_sfx = 49,
		c_hho018cl_Anim = 50,
		c_hho019cl_Wav_506 = 51,
		c_hho019cl_Pho_506 = 52,
		c_hho019cl_0_sfx = 53,
		c_hho019cl_1_sfx = 54,
		c_hho019cl_2_sfx = 55,
		c_hho019cl_Anim = 56,
		c_hho020cl_Wav_507 = 57,
		c_hho020cl_Pho_507 = 58,
		c_hho020cl_0_sfx = 59,
		c_hho020cl_1_sfx = 60,
		c_hho020cl_Anim = 61,
		c_hho021cl_Wav_508 = 62,
		c_hho021cl_Pho_508 = 63,
		c_hho021cl_0_sfx = 64,
		c_hho021cl_1_sfx = 65,
		c_hho021cl_2_sfx = 66,
		c_hho021cl_Anim = 67,
		c_hho023cl_Wav_509 = 68,
		c_hho023cl_Pho_509 = 69,
		c_hho023cl_0_sfx = 70,
		c_hho023cl_1_sfx = 71,
		c_hho023cl_2_sfx = 72,
		c_hho023cl_Anim = 73,
		c_hho024cl_Wav_510 = 74,
		c_hho024cl_Pho_510 = 75,
		c_hho024cl_0_sfx = 76,
		c_hho024cl_1_sfx = 77,
		c_hho024cl_2_sfx = 78,
		c_hho024cl_3_sfx = 79,
		c_hho024cl_Anim = 80,
		c_hho025cl_Wav_511 = 81,
		c_hho025cl_Pho_511 = 82,
		c_hho025cl_0_sfx = 83,
		c_hho025cl_1_sfx = 84,
		c_hho025cl_2_sfx = 85,
		c_hho025cl_Anim = 86,
		c_hho026cl_Wav_512 = 87,
		c_hho026cl_Pho_512 = 88,
		c_hho026cl_0_sfx = 89,
		c_hho026cl_1_sfx = 90,
		c_hho026cl_Anim = 91,
		c_hhoa22cl_Wav_513 = 92,
		c_hhoa22cl_Pho_513 = 93,
		c_hhoa22cl_0_sfx = 94,
		c_hhoa22cl_1_sfx = 95,
		c_hhoa22cl_2_sfx = 96,
		c_hhoa22cl_3_sfx = 97,
		c_hhoa22cl_Anim = 98,
		c_hho008p1_Wav_514 = 99,
		c_hho007p1_Wav_514 = 100,
		c_hho007p1_0_sfx = 101,
		c_hho007p1_1_sfx = 102,
		c_hho007p1_2_sfx = 103,
		c_hho007p1_3_sfx = 104,
		c_hho007p1_Anim = 105,
		c_hho006cl_Wav_515 = 106,
		c_hho006cl_Pho_515 = 107,
		c_hho015cl_Wav_515 = 108,
		c_hho015cl_Pho_515 = 109,
		c_hho009en_Wav_515 = 110,
		c_hho009en_Pho_515 = 111,
		c_hho010re_Wav_515 = 112,
		c_hho010re_Pho_515 = 113,
		c_hho014en_Wav_515 = 114,
		c_hho014en_Pho_515 = 115,
		c_hho013re_Wav_515 = 116,
		c_hho013re_Pho_515 = 117,
		c_hho012en_Wav_515 = 118,
		c_hho012en_Pho_515 = 119,
		c_hho011en_Wav_515 = 120,
		c_hho011en_Pho_515 = 121,
		c_hho011re_Wav_515 = 122,
		c_hho011re_Pho_515 = 123,
		c_hho008cl_Wav_515 = 124,
		c_hho008cl_Pho_515 = 125,
		c_hho006cl_0_sfx = 126,
		c_hho006cl_1_sfx = 127,
		c_hho006cl_2_sfx = 128,
		c_hho006cl_3_sfx = 129,
		c_hho006cl_4_sfx = 130,
		c_hho006cl_5_sfx = 131,
		c_hho006cl_6_sfx = 132,
		c_hho006cl_7_sfx = 133,
		c_hho006cl_8_sfx = 134,
		c_hho006cl_9_sfx = 135,
		c_hho006cl_10_sfx = 136,
		c_hho006cl_11_sfx = 137,
		c_hho006cl_12_sfx = 138,
		c_hho006cl_Anim = 139,

		c_hho002cl_RunAnim = 500,
		c_hho003cl_RunAnim = 501,
		c_hho004jk_RunAnim = 502,
		c_hho016cl_RunAnim = 503,
		c_hho017cl_RunAnim = 504,
		c_hho018cl_RunAnim = 505,
		c_hho019cl_RunAnim = 506,
		c_hho020cl_RunAnim = 507,
		c_hho021cl_RunAnim = 508,
		c_hho023cl_RunAnim = 509,
		c_hho024cl_RunAnim = 510,
		c_hho025cl_RunAnim = 511,
		c_hho026cl_RunAnim = 512,
		c_hhoa22cl_RunAnim = 513,
		c_hho007p1_RunAnim = 514,
		c_hho006cl_RunAnim = 515
	};
	} // namespace HospitalScript

#endif // HOSPITAL_ACTIONS_H
