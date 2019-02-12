#include <sc2api/sc2_api.h>
#include "Sc2Bindings.h"

#include <cmath>

namespace Sc2Bindings
{
	WalkPosition WalkPositionFromPoint3D(sc2::Point3D Position)
	{
		WalkPosition NewWalkPosition;
		NewWalkPosition.x = static_cast<int>(round(Position.x));
		NewWalkPosition.y = static_cast<int>(round(Position.y));
		return NewWalkPosition;
	}

	TilePosition TilePositionFromPoint3D(sc2::Point3D Position)
	{
		TilePosition NewTilePosition;
		NewTilePosition.x = static_cast<int>(round(Position.x));
		NewTilePosition.y = static_cast<int>(round(Position.y));
		return NewTilePosition;
	}

	Position PositionFromPoint3D(sc2::Point3D Position)
	{
		Sc2Bindings::Position NewPosition;
		NewPosition.x = static_cast<int>(round(Position.x));
		NewPosition.y = static_cast<int>(round(Position.y));
		return NewPosition;
	}
	
	TilePosition TilePositionFromPoint2D(sc2::Point2D Position)
	{
		Sc2Bindings::TilePosition NewPosition;
		NewPosition.x = static_cast<int>(round(Position.x));
		NewPosition.y = static_cast<int>(round(Position.y));
		return NewPosition;
	}

	TilePosition GetInitialTilePosition(sc2::Unit u)
	{
		TilePosition ReturnPos;
		ReturnPos.x = static_cast<int>(round(u.pos.x - u.radius));
		ReturnPos.y = static_cast<int>(round(u.pos.y - u.radius));
		return ReturnPos;
	}

	TilePosition GetSizeFromRadius(float radius)
	{
		TilePosition ReturnPos;
		ReturnPos.x = static_cast<int>(round(radius));
		ReturnPos.y = static_cast<int>(round(radius));
		return ReturnPos;
	}

	bool IsVespeneGeyser(sc2::UnitTypeID UnitType)
	{

		switch (UnitType.ToType()) {

		case UNIT_TYPEID::NEUTRAL_VESPENEGEYSER: return true;
		case UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER: return true;
		case UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER: return true;
		case UNIT_TYPEID::NEUTRAL_PURIFIERVESPENEGEYSER: return true;
		case UNIT_TYPEID::NEUTRAL_RICHVESPENEGEYSER: return true;
		case UNIT_TYPEID::NEUTRAL_SHAKURASVESPENEGEYSER: return true;
		default: return false;

		}
	}

	bool IsMineralField(sc2::UnitTypeID UnitType)
	{

		switch (UnitType.ToType()) {
		case sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD: return true;
		case sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD750: return true;
		case sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD: return true;
		case sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD750: return true;
		case sc2::UNIT_TYPEID::NEUTRAL_PURIFIERMINERALFIELD: return true;
		case sc2::UNIT_TYPEID::NEUTRAL_PURIFIERMINERALFIELD750: return true;
		case sc2::UNIT_TYPEID::NEUTRAL_PURIFIERRICHMINERALFIELD: return true;
		case sc2::UNIT_TYPEID::NEUTRAL_PURIFIERRICHMINERALFIELD750: return true;
		case sc2::UNIT_TYPEID::NEUTRAL_LABMINERALFIELD: return true;
		case sc2::UNIT_TYPEID::NEUTRAL_LABMINERALFIELD750: return true;
		case sc2::UNIT_TYPEID::NEUTRAL_BATTLESTATIONMINERALFIELD: return true;
		case sc2::UNIT_TYPEID::NEUTRAL_BATTLESTATIONMINERALFIELD750: return true;
		default: return false;
		}
	}

	bool IsStaticNeutral(sc2::UnitTypeID UnitType)
	{

		switch (UnitType.ToType())
		{
			// Neutral
			case sc2::UNIT_TYPEID::NEUTRAL_BATTLESTATIONMINERALFIELD: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_BATTLESTATIONMINERALFIELD750: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_COLLAPSIBLEROCKTOWERDEBRIS: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_COLLAPSIBLEROCKTOWERDIAGONAL: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_COLLAPSIBLEROCKTOWERPUSHUNIT: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERDEBRIS: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERDIAGONAL: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERPUSHUNIT: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERPUSHUNITRAMPLEFT: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERPUSHUNITRAMPRIGHT: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERRAMPLEFT: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_COLLAPSIBLETERRANTOWERRAMPRIGHT: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_DEBRISRAMPLEFT: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_DEBRISRAMPRIGHT: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_DESTRUCTIBLEDEBRIS6X6: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_DESTRUCTIBLEDEBRISRAMPDIAGONALHUGEBLUR: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_DESTRUCTIBLEDEBRISRAMPDIAGONALHUGEULBR: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_DESTRUCTIBLEROCK6X6: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_DESTRUCTIBLEROCKEX1DIAGONALHUGEBLUR: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_FORCEFIELD: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_KARAKFEMALE: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_UNBUILDABLEBRICKSDESTRUCTIBLE: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_UNBUILDABLEPLATESDESTRUCTIBLE: return true;
			case sc2::UNIT_TYPEID::NEUTRAL_XELNAGATOWER: return true;
			default: return false;
		}
	}

	sc2::Point2DI ToPoint2DI(sc2::Point2D point)
	{
		return sc2::Point2DI{ static_cast<int>(point.x),
							 static_cast<int>(point.y)
		};
	}

	bool Pathable(const sc2::GameInfo & info, const sc2::Point2D & point)
	{
		const sc2::Point2DI point_i = ToPoint2DI(point);
		if (point_i.x < 0 || point_i.x >= info.width || point_i.y < 0 || point_i.y >= info.width)
			return false;

		assert(info.pathing_grid.data.size() == info.width * info.height);
		const unsigned char encoded_placement = info.pathing_grid.data[point_i.x + ((info.height - 1) - point_i.y) * info.width];
		const bool decoded_placement = encoded_placement == 255 ? false : true;
		return decoded_placement;
	}

	bool Placement(const sc2::GameInfo & info, const sc2::Point2D & point)
	{
		const sc2::Point2DI point_i(static_cast<int>(point.x), static_cast<int>(point.y));
		if (point_i.x < 0 || point_i.x >= info.width || point_i.y < 0 || point_i.y >= info.width)
		{
			return false;
		}

		assert(info.placement_grid.data.size() == info.width * info.height);
		const unsigned char encoded_placement = info.placement_grid.data[point_i.x + ((info.height - 1) - point_i.y) * info.width];
		const bool decoded_placement = encoded_placement == 255 ? true : false;
		return decoded_placement;
	}

}
