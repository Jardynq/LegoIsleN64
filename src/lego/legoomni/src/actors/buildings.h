#ifndef BUILDINGS_H
#define BUILDINGS_H

#include "buildingentity.h"

class LegoEventNotificationParam;

class InfoCenterEntity : public BuildingEntity {
public:
	static const char* ClassName() { return "InfoCenterEntity"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, InfoCenterEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// InfoCenterEntity::`scalar deleting destructor'
};

class GasStationEntity : public BuildingEntity {
public:
	static const char* ClassName() { return "GasStationEntity"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, GasStationEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// GasStationEntity::`scalar deleting destructor'
};

class HospitalEntity : public BuildingEntity {
public:
	static const char* ClassName() { return "HospitalEntity"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, HospitalEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// HospitalEntity::`scalar deleting destructor'
};

class PoliceEntity : public BuildingEntity {
public:
	static const char* ClassName() { return "PoliceEntity"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, PoliceEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// PoliceEntity::`scalar deleting destructor'
};

class BeachHouseEntity : public BuildingEntity {
public:
	static const char* ClassName() { return "BeachHouseEntity"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, BeachHouseEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// BeachHouseEntity::`scalar deleting destructor'
};

class RaceStandsEntity : public BuildingEntity {

	static const char* ClassName() {
		// at LEGO1 0x100f0300, needs no annotation
		return "RaceStandsEntity";
	}

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, RaceStandsEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// RaceStandsEntity::`scalar deleting destructor'
};

class JailEntity : public BuildingEntity {

	static const char* ClassName() {
		// at LEGO1 0x100f0300, needs no annotation
		return "RaceStandsEntity";
	}

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, JailEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// JailEntity::`scalar deleting destructor'
};

class CaveEntity : public BuildingEntity {

	static const char* ClassName() {
		// at LEGO1 0x100f0300, needs no annotation
		return "RaceStandsEntity";
	}

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, CaveEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// CaveEntity::`scalar deleting destructor'
};

#endif // BUILDINGS_H
