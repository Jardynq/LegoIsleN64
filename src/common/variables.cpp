#include "variables.h"

#include "3d_manager.h"
#include "gamestate.h"
#include "nav_controller.h"
#include "video_manager.h"
#include "misc.h"
#include "roi.h"

const char* g_varJETSPEED = "jetSPEED";

const char* g_varJETFUEL = "jetFUEL";

const char* g_varDUNESPEED = "duneSPEED";

const char* g_varDUNEFUEL = "duneFUEL";

const char* g_varMOTOSPEED = "motoSPEED";

const char* g_varMOTOFUEL = "motoFUEL";

const char* g_varAMBULSPEED = "ambulSPEED";

const char* g_varAMBULFUEL = "ambulFUEL";

const char* g_varTOWSPEED = "towSPEED";

const char* g_varTOWFUEL = "towFUEL";

// the STRING is already declared for GLOBAL 0x101020cc

const char* g_varVISIBILITY = "VISIBILITY";

const char* g_varCAMERALOCATION = "CAMERA_LOCATION";

const char* g_varCURSOR = "CURSOR";

const char* g_varWHOAMI = "WHO_AM_I";

// the STRING is already declared at LEGO1 0x100f3fb0

const char* g_delimiter2 = " \t";

const char* g_varHIDE = "HIDE";

const char* g_varSHOW = "SHOW";

const char* g_papa = "Papa";

const char* g_mama = "Mama";

const char* g_pepper = "Pepper";

const char* g_nick = "Nick";

const char* g_laura = "Laura";

void VisibilityVariable::SetValue(const char* p_value) {
	MxVariable::SetValue(p_value);

	if (p_value) {
		char* instruction = strtok(m_value.GetData(), g_delimiter2);
		char* name = strtok(NULL, g_delimiter2);
		MxBool show;

		if (!strcmpi(instruction, g_varHIDE)) {
			show = FALSE;
		} else if (!strcmpi(instruction, g_varSHOW)) {
			show = TRUE;
		} else {
			return;
		}

		LegoROI* roi = FindROI(name);
		if (roi) {
			roi->SetVisibility(show);
		}
	}
}

void CameraLocationVariable::SetValue(const char* p_value) {
	char buffer[256];
	MxVariable::SetValue(p_value);

	strcpy(buffer, p_value);

	char* location = strtok(buffer, ",");
	NavController()->UpdateLocation(location);

	location = strtok(NULL, ",");
	if (location) {
		MxFloat pov = (MxFloat) atof(location);
		VideoManager()->Get3DManager()->SetFrustrum(pov, 0.1f, 250.0f);
	}
}

void CursorVariable::SetValue(const char* p_value) {
}

void WhoAmIVariable::SetValue(const char* p_value) {
	MxVariable::SetValue(p_value);

	if (!strcmpi(p_value, g_papa)) {
		GameState()->SetActorId(3);
	} else if (!strcmpi(p_value, g_mama)) {
		GameState()->SetActorId(2);
	} else if (!strcmpi(p_value, g_pepper)) {
		GameState()->SetActorId(1);
	} else if (!strcmpi(p_value, g_nick)) {
		GameState()->SetActorId(4);
	} else if (!strcmpi(p_value, g_laura)) {
		GameState()->SetActorId(5);
	}
}
