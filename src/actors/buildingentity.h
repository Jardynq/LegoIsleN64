#ifndef BUILDINGENTITY_H
#define BUILDINGENTITY_H

#include "legoentity.h"

class LegoEventNotificationParam;

class BuildingEntity : public LegoEntity {
public:
	BuildingEntity();
	~BuildingEntity() override;

	MxLong Notify(MxParam& p_param) override;

	static const char* ClassName() { return "BuildingEntity"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, BuildingEntity::ClassName()) ||
			   LegoEntity::IsA(p_name);
	}

	virtual MxLong HandleClick(LegoEventNotificationParam& p_param) = 0;

	// BuildingEntity::`scalar deleting destructor'
};

#endif // BUILDINGENTITY_H
