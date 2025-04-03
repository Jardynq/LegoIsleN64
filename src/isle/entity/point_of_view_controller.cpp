#include "3d_view.h"
#include "entity.h"
#include "legomain.h"
#include "nav_controller.h"
#include "point_of_view_controller.h"
#include "sound_manager.h"
#include "misc.h"
#include "mx_misc.h"
#include "mx_tickle_manager.h"
#include "mx_timer.h"
#include "realtime.h"
#include "roi.h"

MxBool g_unk0x100f75ac = FALSE;

//////////////////////////////////////////////////////////////////////

LegoMouseController::LegoMouseController() {
	m_isButtonDown = FALSE;
}

LegoMouseController::~LegoMouseController() {
}

void LegoMouseController::LeftDown(int p_x, int p_y) {
	m_isButtonDown = TRUE;
	m_buttonX = p_x;
	m_buttonY = p_y;
}

void LegoMouseController::LeftUp(int p_x, int p_y) {
	m_isButtonDown = FALSE;
	m_buttonX = p_x;
	m_buttonY = p_y;
}

void LegoMouseController::LeftDrag(int p_x, int p_y) {
	m_buttonX = p_x;
	m_buttonY = p_y;
}

void LegoMouseController::RightDown(int p_x, int p_y) {
	m_isButtonDown = TRUE;
	m_buttonX = p_x;
	m_buttonY = p_y;
}

void LegoMouseController::RightUp(int p_x, int p_y) {
	m_isButtonDown = FALSE;
	m_buttonX = p_x;
	m_buttonY = p_y;
}

void LegoMouseController::RightDrag(int p_x, int p_y) {
	m_buttonX = p_x;
	m_buttonY = p_y;
}

//////////////////////////////////////////////////////////////////////

LegoPointOfViewController::LegoPointOfViewController() {
	m_lego3DView = NULL;
	m_entity = NULL;
	m_nav = NULL;
	// m_entityOffsetUp is a temporary kludge.  It should be replaced
	// by 3D camera offset and position stored in the entity since each
	// entity may have a different best viewpoint.
	m_entityOffsetUp = 0.0;
}

LegoPointOfViewController::~LegoPointOfViewController() {
	TickleManager()->UnregisterClient(this);
	if (m_nav) {
		delete m_nav;
		m_nav = NULL;
	}
}

MxResult LegoPointOfViewController::Create(Lego3DView* p_lego3DView) {
	m_lego3DView = p_lego3DView;
	m_nav = new LegoNavController();
	LegoOmni::GetInstance()->SetNavController(m_nav);
	m_nav->SetTrackDefault(TRUE);
	TickleManager()->RegisterClient(this, 10);
	return SUCCESS;
}

void LegoPointOfViewController::OnViewSize(int p_width, int p_height) {
	m_nav->SetControlMax(p_width, p_height);
}

void LegoPointOfViewController::LeftDown(int p_x, int p_y) {
	LegoMouseController::LeftDown(p_x, p_y);
	AffectPointOfView();
}

void LegoPointOfViewController::LeftDrag(int p_x, int p_y) {
	LegoMouseController::LeftDrag(p_x, p_y);
	AffectPointOfView();
}

void LegoPointOfViewController::AffectPointOfView() {
	m_nav->SetTargets(GetButtonX(), GetButtonY(), GetIsButtonDown());
}

MxResult LegoPointOfViewController::Tickle() {
	ViewROI* pov = m_lego3DView->GetPointOfView();

	if (pov != NULL && m_nav != NULL && m_entity == NULL) {
		Mx3DPointFloat newDir, newPos;

		Vector3 pos(pov->GetWorldPosition());
		Vector3 dir(pov->GetWorldDirection());

		if (m_nav->CalculateNewPosDir(pos, dir, newPos, newDir, NULL)) {
			MxMatrix mat;

			CalcLocalTransform(newPos, newDir, pov->GetWorldUp(), mat);
			((TimeROI*) pov)->FUN_100a9b40(mat, Timer()->GetTime());
			pov->WrappedSetLocalTransform(mat);
			m_lego3DView->Moved(*pov);

			SoundManager()->UpdateListener(
				pov->GetWorldPosition(),
				pov->GetWorldDirection(),
				pov->GetWorldUp(),
				pov->GetWorldVelocity()
			);

			g_unk0x100f75ac = FALSE;
		} else {
			if (g_unk0x100f75ac == FALSE) {
				Mx3DPointFloat vel;

				vel.Clear();
				pov->FUN_100a5a30(vel);

				SoundManager()->UpdateListener(
					pov->GetWorldPosition(),
					pov->GetWorldDirection(),
					pov->GetWorldUp(),
					pov->GetWorldVelocity()
				);

				g_unk0x100f75ac = TRUE;
			}
		}
	}

	return SUCCESS;
}

void LegoPointOfViewController::SetEntity(LegoEntity* p_entity) {
	TickleManager()->UnregisterClient(this);
	m_entity = p_entity;

	ViewROI* pov = m_lego3DView->GetPointOfView();

	if (m_entity != NULL && pov != NULL) {
		MxMatrix mat;

		CalcLocalTransform(
			Mx3DPointFloat(
				m_entity->GetWorldPosition()[0],
				m_entity->GetWorldPosition()[1] + m_entityOffsetUp,
				m_entity->GetWorldPosition()[2]
			),
			m_entity->GetWorldDirection(),
			m_entity->GetWorldUp(),
			mat
		);

		pov->WrappedSetLocalTransform(mat);
	} else {
		TickleManager()->RegisterClient(this, 10);
	}
}
