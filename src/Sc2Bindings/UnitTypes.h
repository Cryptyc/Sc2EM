#pragma once
#include <sc2api/sc2_api.h>
#include "Sc2Bindings.h"
using namespace sc2;
using namespace Sc2Bindings;

class Sc2UnitTypes
{
public:
	static Sc2UnitTypes& getInstance()
	{
		static Sc2UnitTypes   instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}

	bool RefreshUnitTypeData(const ObservationInterface* obs, bool ShouldRefresh);
	const UnitTypeData GetUnitTypeData(UnitTypeID Unit);

	const float GetUnitRadius(UnitTypeID typeId);

	const TilePosition GetTileSize(UnitTypeID UnitType);

private:

	Sc2UnitTypes()
		: UnitTypesCached(false)
	{
		SetupUnitRadius();
	}
	Sc2UnitTypes(Sc2UnitTypes const&);
	void operator=(Sc2UnitTypes const&);

	void SetupUnitRadius();
	UnitTypes UnitTypeMap;
	std::map <UnitTypeID, float> UnitSizes;
	bool UnitTypesCached;

};