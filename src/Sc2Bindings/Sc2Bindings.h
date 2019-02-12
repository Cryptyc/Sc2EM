#pragma once

#include <sc2api/sc2_api.h>
#include "SetContainer.h"
#include "Type.h"
#include "Color.h"
#include "Position.h"
#include "Type.h"
#include "UnitTypes.h"

#define DRAW_HIGHT 150

namespace Sc2Bindings
{


	WalkPosition WalkPositionFromPoint3D(sc2::Point3D Position);

	TilePosition TilePositionFromPoint3D(sc2::Point3D Position);

	Position PositionFromPoint3D(sc2::Point3D Position);

	TilePosition TilePositionFromPoint2D(sc2::Point2D Position);

	TilePosition GetInitialTilePosition(sc2::Unit u);
	
	TilePosition GetSizeFromRadius(float radius);

	bool  IsVespeneGeyser(sc2::UnitTypeID UnitType);

	bool IsMineralField(sc2::UnitTypeID UnitType);

	bool IsStaticNeutral(sc2::UnitTypeID UnitType);

	bool Placement(const sc2::GameInfo & info, const sc2::Point2D & point);

	bool Pathable(const sc2::GameInfo & info, const sc2::Point2D & point);

}

