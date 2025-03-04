#ifndef BUILDINGS_H
#define BUILDINGS_H

#include "buildingentity.h"

class LegoEventNotificationParam;

class InfoCenterEntity : public BuildingEntity {
public:
	const char* ClassName() const override { return "InfoCenterEntity"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, InfoCenterEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// InfoCenterEntity::`scalar deleting destructor'
};

class GasStationEntity : public BuildingEntity {
public:
	const char* ClassName() const override { return "GasStationEntity"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, GasStationEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// GasStationEntity::`scalar deleting destructor'
};

class HospitalEntity : public BuildingEntity {
public:
	const char* ClassName() const override { return "HospitalEntity"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, HospitalEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// HospitalEntity::`scalar deleting destructor'
};

class PoliceEntity : public BuildingEntity {
public:
	const char* ClassName() const override { return "PoliceEntity"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, PoliceEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// PoliceEntity::`scalar deleting destructor'
};

class BeachHouseEntity : public BuildingEntity {
public:
	const char* ClassName() const override { return "BeachHouseEntity"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, BeachHouseEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// BeachHouseEntity::`scalar deleting destructor'
};

class RaceStandsEntity : public BuildingEntity {

	const char* ClassName() const override {
		// at LEGO1 0x100f0300, needs no annotation
		return "RaceStandsEntity";
	}

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, RaceStandsEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// RaceStandsEntity::`scalar deleting destructor'
};

class JailEntity : public BuildingEntity {

	const char* ClassName() const override {
		// at LEGO1 0x100f0300, needs no annotation
		return "RaceStandsEntity";
	}

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, JailEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// JailEntity::`scalar deleting destructor'
};

class CaveEntity : public BuildingEntity {

	const char* ClassName() const override {
		// at LEGO1 0x100f0300, needs no annotation
		return "RaceStandsEntity";
	}

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, CaveEntity::ClassName()) ||
			   BuildingEntity::IsA(p_name);
	}

	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// CaveEntity::`scalar deleting destructor'
};

#endif // BUILDINGS_H
