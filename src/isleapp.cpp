#include "isleapp.h"

// #include "3d_manager.h"
#include "animation_manager.h"
#include "building_manager.h"
#include "debugcpp.h"
#include "gamestate.h"
#include "input_manager.h"
#include "legomain.h"
#include "misc.h"
#include "model_presenter.h"
#include "mx_background_audio_manager.h"
#include "part_presenter.h"
#include "types.h"
#include "utils.h"
#include "video_manager.h"
#include "world_presenter.h"
// #include "mx_background_audio_manager.h"
#include "legofs.h"
#include "mx_ds_action.h"
#include "mx_misc.h"
#include "mx_omni_create_flags.h"
#include "mx_omni_create_param.h"
#include "mx_streamer.h"
#include "mx_tickle_manager.h"
#include "mx_timer.h"
#include "mx_transition_manager.h"
#include "mx_variable_table.h"
#include "mxdirect3d.h"
#include "resource.h"
#include "roi.h"
#include "timer.h"

IsleApp* g_isle = NULL;

unsigned char g_mousedown = 0;

unsigned char g_mousemoved = 0;

IsleApp::IsleApp()
	: m_unk0x24(0), m_use3dSound(TRUE), m_useMusic(TRUE), m_useJoystick(TRUE),
	  m_joystickIndex(0), m_wideViewAngle(TRUE), m_islandQuality(1),
	  m_islandTexture(1), m_gameStarted(FALSE), m_frameDelta(10),
	  m_cursorArrow(NULL), m_cursorBusy(NULL), m_cursorNo(NULL),
	  m_cursorCurrent(NULL) {

	MxRect32 r(0, 0, 639, 479);
	MxVideoParamFlags flags;
	m_videoParam = MxVideoParam(r, NULL, 1, flags);

	LegoOmni::CreateInstance();
}

IsleApp::~IsleApp() {
	if (LegoOmni::GetInstance()) {
		Close();
		MxOmni::DestroyInstance();
	}
}

void IsleApp::Close() {
	MxDSAction ds;
	ds.SetUnknown24(-2);

	if (Lego()) {
		GameState()->Save(0);
		exit(0);
		if (InputManager()) {
			InputManager()->QueueEvent(c_notificationKeyPress, 0, 0, 0, 0);
		}

		VideoManager()
			->Get3DManager()
			->GetLego3DView()
			->GetViewManager()
			->RemoveAll(NULL);

		Lego()->RemoveWorld(ds.GetAtomId(), ds.GetObjectId());
		Lego()->DeleteObject(ds);
		TransitionManager()->SetWaitIndicator(NULL);
		Lego()->Resume();

		while (Streamer()->Close(NULL) == SUCCESS) {
		}

		while (Lego() && !Lego()->DoesEntityExist(ds)) {
			Timer()->GetRealTime();
			TickleManager()->Tickle();
		}
	}
}

void IsleApp::SetupVideoFlags(BOOL param_6, BOOL param_7, BOOL wideViewAngle) {
	m_videoParam.Flags().SetF2bit0(!param_6);
	m_videoParam.Flags().SetF1bit7(param_7);
	m_videoParam.Flags().SetWideViewAngle(wideViewAngle);
	m_videoParam.Flags().SetF2bit1(1);
}

BOOL IsleApp::SetupLegoOmni() {
	BOOL result = FALSE;

	BOOL failure = 0;
	MxOmniCreateParam param(m_videoParam, MxOmniCreateFlags());
	failure = Lego()->Create(param) == FAILURE;

	if (!failure) {
		VariableTable()->SetVariable("ACTOR_01", "");
		TickleManager()->SetClientTickleInterval((MxCore*) VideoManager(), 10);
		result = TRUE;
	}
	return result;
}

BOOL IsleApp::Setup() {
	legofs_init();

	SetupVideoFlags(m_unk0x24, FALSE, m_wideViewAngle);

	MxOmni::SetSound3D(m_use3dSound);

	if (!SetupLegoOmni()) {
		log_error("Failed to setup omni\n");
		return FAILURE;
	}

	GameState()->SetSavePath(m_savePath);
	GameState()->SerializePlayersInfo(LegoStorage::c_read);
	GameState()->SerializeScoreHistory(LegoStorage::c_read);

	int iVar10 = 0;
	switch (m_islandQuality) {
	case 0:
		iVar10 = 1;
		break;
	case 1:
		iVar10 = 2;
		break;
	default:
		iVar10 = 100;
	}

	int uVar1 = (m_islandTexture == 0);
	LegoModelPresenter::configureLegoModelPresenter(uVar1);
	LegoPartPresenter::configureLegoPartPresenter(uVar1, iVar10);
	LegoWorldPresenter::configureLegoWorldPresenter(m_islandQuality);
	LegoBuildingManager::configureLegoBuildingManager(m_islandQuality);
	LegoROI::configureLegoROI(iVar10);
	LegoAnimationManager::configureLegoAnimationManager(m_islandQuality);
	if (LegoOmni::GetInstance()) {
		if (LegoOmni::GetInstance()->GetInputManager()) {
			LegoOmni::GetInstance()->GetInputManager()->SetUseJoystick(
				m_useJoystick
			);
			LegoOmni::GetInstance()->GetInputManager()->SetJoystickIndex(
				m_joystickIndex
			);
		}
	}
	return SUCCESS;
}

void handle_input() {
	controller_scan();
	controller_data keys = get_keys_pressed();

	if (keys.c[0].A) {
		g_mousedown = true;
	}
	if (keys.c[0].x) {
		g_mousemoved = true;
	}
}

void game_loop() {
	while (!Lego()->is_closed) {
		handle_input();

		if (g_mousemoved) {
			g_mousemoved = false;
		}

		if (g_mousedown && g_mousemoved) {
			g_isle->Tick(0);
		}

		display_show(display_get());
		g_isle->Tick(1);
	}
}

int main() {
	debug_init_isviewer();
	debug_init_usblog();
	joypad_init();
	timer_init();
	display_init(
		RESOLUTION_512x240,
		DEPTH_16_BPP,
		3,
		GAMMA_NONE,
		FILTERS_RESAMPLE
	);

	audio_init(48000, 4);
	mixer_init(16);

	rdpq_init();
	srand(timer_ticks());

	g_isle = new IsleApp();
	if (g_isle->Setup() != SUCCESS) {
		log_error("Failed to setup Isle App");
		return FAILURE;
	}

	game_loop();

	return SUCCESS;
}

inline void IsleApp::Tick(BOOL sleepIfNotNextFrame) {
	static MxLong g_lastFrameTime = 0;

	static int g_startupDelay = 200;

	if (!Lego()) {
		return;
	}
	if (!TickleManager()) {
		return;
	}
	if (!Timer()) {
		return;
	}

	MxLong currentTime = Timer()->GetRealTime();
	if (currentTime < g_lastFrameTime) {
		g_lastFrameTime = -m_frameDelta;
	}

	if (m_frameDelta + g_lastFrameTime < currentTime) {
		if (!Lego()->IsPaused()) {
			TickleManager()->Tickle();
		}
		g_lastFrameTime = currentTime;

		if (g_startupDelay == 0) {
			return;
		}

		g_startupDelay--;
		if (g_startupDelay != 0) {
			return;
		}

		LegoOmni::GetInstance()->CreateBackgroundAudio();
		BackgroundAudioManager()->Enable(this->m_useMusic);

		MxStreamController* stream = Streamer()->Open(
			"rom:/scripts/isle/isle",
			MxStreamer::e_diskStream
		);
		MxDSAction ds;

		ds.SetAtomId(stream->GetAtom());
		ds.SetUnknown24(-1);
		ds.SetObjectId(0);
		if (Start(&ds) != SUCCESS) {
			return;
		}
		m_gameStarted = TRUE;
	} else if (sleepIfNotNextFrame != 0) {
		// Sleep(0);
	}
}

void IsleApp::SetupCursor(WPARAM wParam) {
	switch (wParam) {
	case e_cursorArrow:
		m_cursorCurrent = m_cursorArrow;
		break;
	case e_cursorBusy:
		m_cursorCurrent = m_cursorBusy;
		break;
	case e_cursorNo:
		m_cursorCurrent = m_cursorNo;
		break;
	case e_cursorNone:
		m_cursorCurrent = NULL;
	case e_cursorUnused3:
	case e_cursorUnused4:
	case e_cursorUnused5:
	case e_cursorUnused6:
	case e_cursorUnused7:
	case e_cursorUnused8:
	case e_cursorUnused9:
	case e_cursorUnused10:
		break;
	}

	// SetCursor(m_cursorCurrent);
}
