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
	g_copterScript = new MxAtomId("rom:/scripts/build/copter", e_lowerCase2);
	g_dunecarScript =
		new MxAtomId("rom:/lego/scripts/build/dunecar", e_lowerCase2);
	g_jetskiScript = new MxAtomId("rom:/scripts/build/jetski", e_lowerCase2);
	g_racecarScript = new MxAtomId("rom:/scripts/build/racecar", e_lowerCase2);
	g_carraceScript = new MxAtomId("rom:/scripts/race/carrace", e_lowerCase2);
	g_carracerScript = new MxAtomId("rom:/scripts/race/carracer", e_lowerCase2);
	g_jetraceScript = new MxAtomId("rom:/scripts/race/jetrace", e_lowerCase2);
	g_jetracerScript = new MxAtomId("rom:/scripts/race/jetracer", e_lowerCase2);
	g_isleScript = new MxAtomId("rom:/scripts/isle/isle", e_lowerCase2);
	g_elevbottScript =
		new MxAtomId("rom:/scripts/infocntr/elevbott", e_lowerCase2);
	g_infodoorScript =
		new MxAtomId("rom:/scripts/infocntr/infodoor", e_lowerCase2);
	g_infomainScript =
		new MxAtomId("rom:/scripts/infocntr/infomain", e_lowerCase2);
	g_infoscorScript =
		new MxAtomId("rom:/scripts/infocntr/infoscor", e_lowerCase2);
	g_regbookScript =
		new MxAtomId("rom:/scripts/infocntr/regbook", e_lowerCase2);
	g_histbookScript =
		new MxAtomId("rom:/scripts/infocntr/histbook", e_lowerCase2);
	g_hospitalScript =
		new MxAtomId("rom:/scripts/hospital/hospital", e_lowerCase2);
	g_policeScript = new MxAtomId("rom:/scripts/police/police", e_lowerCase2);
	g_garageScript = new MxAtomId("rom:/scripts/garage/garage", e_lowerCase2);
	g_act2mainScript = new MxAtomId("rom:/scripts/act2/act2main", e_lowerCase2);
	g_act3Script = new MxAtomId("rom:/scripts/act3/act3", e_lowerCase2);
	g_jukeboxScript = new MxAtomId("rom:/scripts/isle/jukebox", e_lowerCase2);
	g_pz5Script = new MxAtomId("rom:/scripts/isle/pz5", e_lowerCase2);
	g_introScript = new MxAtomId("rom:/scripts/intro", e_lowerCase2);
	g_testScript = new MxAtomId("rom:/scripts/test/test", e_lowerCase2);
	g_jukeboxwScript = new MxAtomId("rom:/scripts/isle/jukeboxw", e_lowerCase2);
	g_sndAnimScript = new MxAtomId("rom:/scripts/sndanim", e_lowerCase2);
	g_creditsScript = new MxAtomId("rom:/scripts/credits", e_lowerCase2);
	g_nocdSourceName = new MxAtomId("rom:/scripts/nocd", e_lowerCase2);
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
