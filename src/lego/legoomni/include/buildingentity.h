#ifndef BUILDINGENTITY_H
#define BUILDINGENTITY_H

#include "legoentity.h"

class LegoEventNotificationParam;

class BuildingEntity : public LegoEntity {
public:
	BuildingEntity();
	~BuildingEntity() override;

	MxLong Notify(MxParam& p_param) override;

	const char* ClassName() const override { return "BuildingEntity"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, BuildingEntity::ClassName()) ||
			   LegoEntity::IsA(p_name);
	}

	virtual MxLong HandleClick(LegoEventNotificationParam& p_param) = 0;

	// BuildingEntity::`scalar deleting destructor'
};

#endif // BUILDINGENTITY_H
