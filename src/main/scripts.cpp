#include "scripts.h"

#include "mx_atom.h"

MxAtomId* g_copterScript = NULL;

MxAtomId* g_dunecarScript = NULL;

MxAtomId* g_jetskiScript = NULL;

MxAtomId* g_racecarScript = NULL;

MxAtomId* g_carraceScript = NULL;

MxAtomId* g_carracerScript = NULL;

MxAtomId* g_jetraceScript = NULL;

MxAtomId* g_jetracerScript = NULL;

MxAtomId* g_isleScript = NULL;

MxAtomId* g_elevbottScript = NULL;

MxAtomId* g_infodoorScript = NULL;

MxAtomId* g_infomainScript = NULL;

MxAtomId* g_infoscorScript = NULL;

MxAtomId* g_regbookScript = NULL;

MxAtomId* g_histbookScript = NULL;

MxAtomId* g_hospitalScript = NULL;

MxAtomId* g_policeScript = NULL;

MxAtomId* g_garageScript = NULL;

MxAtomId* g_act2mainScript = NULL;

MxAtomId* g_act3Script = NULL;

MxAtomId* g_jukeboxScript = NULL;

MxAtomId* g_pz5Script = NULL;

MxAtomId* g_introScript = NULL;

MxAtomId* g_testScript = NULL;

MxAtomId* g_jukeboxwScript = NULL;

MxAtomId* g_sndAnimScript = NULL;

MxAtomId* g_creditsScript = NULL;

MxAtomId* g_nocdSourceName = NULL;

void CreateScripts() {
	g_copterScript =
		new MxAtomId("\\lego\\scripts\\build\\copter", e_lowerCase2);
	g_dunecarScript =
		new MxAtomId("\\lego\\scripts\\build\\dunecar", e_lowerCase2);
	g_jetskiScript =
		new MxAtomId("\\lego\\scripts\\build\\jetski", e_lowerCase2);
	g_racecarScript =
		new MxAtomId("\\lego\\scripts\\build\\racecar", e_lowerCase2);
	g_carraceScript =
		new MxAtomId("\\lego\\scripts\\race\\carrace", e_lowerCase2);
	g_carracerScript =
		new MxAtomId("\\lego\\scripts\\race\\carracer", e_lowerCase2);
	g_jetraceScript =
		new MxAtomId("\\lego\\scripts\\race\\jetrace", e_lowerCase2);
	g_jetracerScript =
		new MxAtomId("\\lego\\scripts\\race\\jetracer", e_lowerCase2);
	g_isleScript = new MxAtomId("\\lego\\scripts\\isle\\isle", e_lowerCase2);
	g_elevbottScript =
		new MxAtomId("\\lego\\scripts\\infocntr\\elevbott", e_lowerCase2);
	g_infodoorScript =
		new MxAtomId("\\lego\\scripts\\infocntr\\infodoor", e_lowerCase2);
	g_infomainScript =
		new MxAtomId("\\lego\\scripts\\infocntr\\infomain", e_lowerCase2);
	g_infoscorScript =
		new MxAtomId("\\lego\\scripts\\infocntr\\infoscor", e_lowerCase2);
	g_regbookScript =
		new MxAtomId("\\lego\\scripts\\infocntr\\regbook", e_lowerCase2);
	g_histbookScript =
		new MxAtomId("\\lego\\scripts\\infocntr\\histbook", e_lowerCase2);
	g_hospitalScript =
		new MxAtomId("\\lego\\scripts\\hospital\\hospital", e_lowerCase2);
	g_policeScript =
		new MxAtomId("\\lego\\scripts\\police\\police", e_lowerCase2);
	g_garageScript =
		new MxAtomId("\\lego\\scripts\\garage\\garage", e_lowerCase2);
	g_act2mainScript =
		new MxAtomId("\\lego\\scripts\\act2\\act2main", e_lowerCase2);
	g_act3Script = new MxAtomId("\\lego\\scripts\\act3\\act3", e_lowerCase2);
	g_jukeboxScript =
		new MxAtomId("\\lego\\scripts\\isle\\jukebox", e_lowerCase2);
	g_pz5Script = new MxAtomId("\\lego\\scripts\\isle\\pz5", e_lowerCase2);
	g_introScript = new MxAtomId("\\lego\\scripts\\intro", e_lowerCase2);
	g_testScript = new MxAtomId("\\lego\\scripts\\test\\test", e_lowerCase2);
	g_jukeboxwScript =
		new MxAtomId("\\lego\\scripts\\isle\\jukeboxw", e_lowerCase2);
	g_sndAnimScript = new MxAtomId("\\lego\\scripts\\sndanim", e_lowerCase2);
	g_creditsScript = new MxAtomId("\\lego\\scripts\\credits", e_lowerCase2);
	g_nocdSourceName = new MxAtomId("\\lego\\scripts\\nocd", e_lowerCase2);
}

void DestroyScripts() {
	delete g_copterScript;
	delete g_dunecarScript;
	delete g_jetskiScript;
	delete g_racecarScript;
	delete g_carraceScript;
	delete g_carracerScript;
	delete g_jetraceScript;
	delete g_jetracerScript;
	delete g_isleScript;
	delete g_elevbottScript;
	delete g_infodoorScript;
	delete g_infomainScript;
	delete g_infoscorScript;
	delete g_regbookScript;
	delete g_histbookScript;
	delete g_hospitalScript;
	delete g_policeScript;
	delete g_garageScript;
	delete g_act2mainScript;
	delete g_act3Script;
	delete g_jukeboxScript;
	delete g_pz5Script;
	delete g_introScript;
	delete g_testScript;
	delete g_jukeboxwScript;
	delete g_sndAnimScript;
	delete g_creditsScript;
	delete g_nocdSourceName;

	g_copterScript = NULL;
	g_dunecarScript = NULL;
	g_jetskiScript = NULL;
	g_racecarScript = NULL;
	g_carraceScript = NULL;
	g_carracerScript = NULL;
	g_jetraceScript = NULL;
	g_jetracerScript = NULL;
	g_isleScript = NULL;
	g_elevbottScript = NULL;
	g_infodoorScript = NULL;
	g_infomainScript = NULL;
	g_infoscorScript = NULL;
	g_regbookScript = NULL;
	g_histbookScript = NULL;
	g_hospitalScript = NULL;
	g_policeScript = NULL;
	g_garageScript = NULL;
	g_act2mainScript = NULL;
	g_act3Script = NULL;
	g_jukeboxScript = NULL;
	g_pz5Script = NULL;
	g_introScript = NULL;
	g_testScript = NULL;
	g_testScript = NULL;
	g_jukeboxwScript = NULL;
	g_sndAnimScript = NULL;
	g_creditsScript = NULL;
	g_nocdSourceName = NULL;
}

const char* GetNoCD_SourceName() {
	return g_nocdSourceName->GetInternal();
}
