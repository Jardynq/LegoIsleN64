// This file was automatically generated by the actionheadergen tool.
// Please do not manually edit this file.
#ifndef JETSKI_ACTIONS_H
#define JETSKI_ACTIONS_H

namespace JetskiScript {
#if __cplusplus >= 201103L
	enum Script : int {
#else
	enum Script {
#endif
		c_noneJetski = -1,

		c__StartUp = 0,

		c_Jetski_Actor = 3,

		c_Info_Ctl = 5,
		c_Exit_Ctl = 6,
		c_ShelfUp_Ctl = 7,
		c_Platform_Ctl = 8,

		c_Background = 64,
		c_ColorBook_Bitmap = 65,
		c_ShelfUp_Up_Bitmap = 66,
		c_ShelfUp_Down_Bitmap = 67,
		c_PlatformUp_Bitmap = 68,
		c_PlatformLeft = 69,
		c_Rotate_Sound = 70,
		c_PlatformLeft_Bitmap = 71,
		c_Yellow_Ctl = 72,
		c_Yellow_Up_Bitmap = 73,
		c_Yellow_Down_Bitmap = 74,
		c_Red_Ctl = 75,
		c_Red_Up_Bitmap = 76,
		c_Red_Down_Bitmap = 77,
		c_Blue_Ctl = 78,
		c_Blue_Up_Bitmap = 79,
		c_Blue_Down_Bitmap = 80,
		c_Green_Ctl = 81,
		c_Green_Up_Bitmap = 82,
		c_Green_Down_Bitmap = 83,
		c_Gray_Ctl = 84,
		c_Gray_Up_Bitmap = 85,
		c_Gray_Down_Bitmap = 86,
		c_Black_Ctl = 87,
		c_Black_Up_Bitmap = 88,
		c_Black_Down_Bitmap = 89,
		c_Info_Up_Bitmap = 90,
		c_Info_Down_Bitmap = 91,
		c_Exit_Up_Bitmap = 92,
		c_Exit_Down_Bitmap = 93,
		c_Decal_Bitmap = 94,
		c_Decals_Ctl = 95,
		c_JSFRNT_T1_Up = 96,
		c_JSFRNT_T1_Up_Bitmap = 97,
		c_JSFRNT_T1_Dn = 98,
		c_JSFRNT_T1_Dn_Bitmap = 99,
		c_JSFRNT_Texture_1 = 100,
		c_Decals_Ctl1 = 101,
		c_JSFRNT_T2_Up = 102,
		c_JSFRNT_T2_Up_Bitmap = 103,
		c_JSFRNT_T2_Dn = 104,
		c_JSFRNT_T2_Dn_Bitmap = 105,
		c_JSFRNT_Texture_2 = 106,
		c_Decals_Ctl2 = 107,
		c_JSFRNT_B1_Up = 108,
		c_JSFRNT_B1_Up_Bitmap = 109,
		c_JSFRNT_B1_Dn = 110,
		c_JSFRNT_B1_Dn_Bitmap = 111,
		c_JSFRNT_Texture_3 = 112,
		c_Decals_Ctl3 = 113,
		c_JSFRNT_B2_Up = 114,
		c_JSFRNT_B2_Up_Bitmap = 115,
		c_JSFRNT_B2_Dn = 116,
		c_JSFRNT_B2_Dn_Bitmap = 117,
		c_JSFRNT_Texture_4 = 118,
		c_Decals_Ctl4 = 119,
		c_JSWNSH_T1_Up = 120,
		c_JSWNSH_T1_Up_Bitmap = 121,
		c_JSWNSH_T1_Dn = 122,
		c_JSWNSH_T1_Dn_Bitmap = 123,
		c_JSWNSH_Texture_1 = 124,
		c_Decals_Ctl5 = 125,
		c_JSWNSH_T2_Up = 126,
		c_JSWNSH_T2_Up_Bitmap = 127,
		c_JSWNSH_T2_Dn = 128,
		c_JSWNSH_T2_Dn_Bitmap = 129,
		c_JSWNSH_Texture_2 = 130,
		c_Decals_Ctl6 = 131,
		c_JSWNSH_B1_Up = 132,
		c_JSWNSH_B1_Up_Bitmap = 133,
		c_JSWNSH_B1_Dn = 134,
		c_JSWNSH_B1_Dn_Bitmap = 135,
		c_JSWNSH_Texture_3 = 136,
		c_Decals_Ctl7 = 137,
		c_JSWNSH_B2_Up = 138,
		c_JSWNSH_B2_Up_Bitmap = 139,
		c_JSWNSH_B2_Dn = 140,
		c_JSWNSH_B2_Dn_Bitmap = 141,
		c_JSWNSH_Texture_4 = 142,
		c_Shelf_Sound = 143,
		c_PlaceBrick_Sound = 144,
		c_GetBrick_Sound = 145,
		c_Paint_Sound = 146,
		c_Decal_Sound = 147,
		c_Build_Animation = 148,
		c_Build_Anim0 = 149,
		c_Build_Anim1 = 150,
		c_Build_Anim2 = 151,
		c_Jsuser_Model = 152,
		c_IJS001D4_Wav_500 = 153,
		c_IJS001D4_Pho_500 = 154,
		c_IJS002D4_Wav_500 = 155,
		c_IJS002D4_Pho_500 = 156,
		c_ijs001d4_0_sfx = 157,
		c_ijs001d4_1_sfx = 158,
		c_ijs001d4_2_sfx = 159,
		c_ijs001d4_3_sfx = 160,
		c_ijs001d4_4_sfx = 161,
		c_ijs001d4_5_sfx = 162,
		c_ijs001d4_6_sfx = 163,
		c_ijs001d4_7_sfx = 164,
		c_ijs001d4_8_sfx = 165,
		c_ijs001d4_9_sfx = 166,
		c_ijs001d4_10_sfx = 167,
		c_ijs001d4_11_sfx = 168,
		c_ijs001d4_12_sfx = 169,
		c_ijs001d4_13_sfx = 170,
		c_ijs001d4_14_sfx = 171,
		c_ijs001d4_15_sfx = 172,
		c_ijs001d4_Anim = 173,
		c_IJSxx2D4_Wav_501 = 174,
		c_IJSxx2D4_Pho_501 = 175,
		c_ijsxx2d4_0_sfx = 176,
		c_ijsxx2d4_1_sfx = 177,
		c_ijsxx2d4_2_sfx = 178,
		c_ijsxx2d4_3_sfx = 179,
		c_ijsxx2d4_4_sfx = 180,
		c_ijsxx2d4_5_sfx = 181,
		c_ijsxx2d4_6_sfx = 182,
		c_ijsxx2d4_Anim = 183,
		c_IJS003D4_Wav_502 = 184,
		c_IJS003D4_Pho_502 = 185,
		c_ijs003d4_0_sfx = 186,
		c_ijs003d4_1_sfx = 187,
		c_ijs003d4_Anim = 188,
		c_IJS004D4_Wav_503 = 189,
		c_IJS004D4_Pho_503 = 190,
		c_ijs004d4_0_sfx = 191,
		c_ijs004d4_1_sfx = 192,
		c_ijs004d4_2_sfx = 193,
		c_ijs004d4_3_sfx = 194,
		c_ijs004d4_4_sfx = 195,
		c_ijs004d4_5_sfx = 196,
		c_ijs004d4_Anim = 197,
		c_IJS005D4_Wav_504 = 198,
		c_IJS005D4_Pho_504 = 199,
		c_ijs005d4_0_sfx = 200,
		c_ijs005d4_1_sfx = 201,
		c_ijs005d4_2_sfx = 202,
		c_ijs005d4_3_sfx = 203,
		c_ijs005d4_4_sfx = 204,
		c_ijs005d4_5_sfx = 205,
		c_ijs005d4_6_sfx = 206,
		c_ijs005d4_7_sfx = 207,
		c_ijs005d4_8_sfx = 208,
		c_ijs005d4_9_sfx = 209,
		c_ijs005d4_10_sfx = 210,
		c_ijs005d4_11_sfx = 211,
		c_ijs005d4_12_sfx = 212,
		c_ijs005d4_Anim = 213,
		c_IJS006D4_Wav_505 = 214,
		c_IJS006D4_Pho_505 = 215,
		c_ijs006d4_0_sfx = 216,
		c_ijs006d4_1_sfx = 217,
		c_ijs006d4_2_sfx = 218,
		c_ijs006d4_3_sfx = 219,
		c_ijs006d4_4_sfx = 220,
		c_ijs006d4_5_sfx = 221,
		c_ijs006d4_6_sfx = 222,
		c_ijs006d4_7_sfx = 223,
		c_ijs006d4_8_sfx = 224,
		c_ijs006d4_9_sfx = 225,
		c_ijs006d4_10_sfx = 226,
		c_ijs006d4_11_sfx = 227,
		c_ijs006d4_12_sfx = 228,
		c_ijs006d4_13_sfx = 229,
		c_ijs006d4_14_sfx = 230,
		c_ijs006d4_15_sfx = 231,
		c_ijs006d4_16_sfx = 232,
		c_ijs006d4_Anim = 233,
		c_IJS007D4_Wav_506 = 234,
		c_IJS007D4_Pho_506 = 235,
		c_ijs007d4_0_sfx = 236,
		c_ijs007d4_1_sfx = 237,
		c_ijs007d4_2_sfx = 238,
		c_ijs007d4_3_sfx = 239,
		c_ijs007d4_4_sfx = 240,
		c_ijs007d4_5_sfx = 241,
		c_ijs007d4_6_sfx = 242,
		c_ijs007d4_7_sfx = 243,
		c_ijs007d4_8_sfx = 244,
		c_ijs007d4_Anim = 245,

		c_ijs001d4_RunAnim = 500,
		c_ijsxx2d4_RunAnim = 501,
		c_ijs003d4_RunAnim = 502,
		c_ijs004d4_RunAnim = 503,
		c_ijs005d4_RunAnim = 504,
		c_ijs006d4_RunAnim = 505,
		c_ijs007d4_RunAnim = 506
	};
	} // namespace JetskiScript

#endif // JETSKI_ACTIONS_H
