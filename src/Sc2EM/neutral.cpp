//////////////////////////////////////////////////////////////////////////
//
// This file is part of the BWEM Library.
// BWEM is free software, licensed under the MIT/X11 License. 
// A copy of the license is provided with the library in the LICENSE file.
// Copyright (c) 2015, 2017, Igor Dimitrijevic
//
//////////////////////////////////////////////////////////////////////////


#include "neutral.h"
#include "mapImpl.h"

using namespace Sc2Bindings;
using namespace sc2;

using namespace std;


namespace BWEM {

using namespace detail;
using namespace sc2_ext;

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                  class Neutral
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

Neutral::Neutral(sc2::Unit u, Map * pMap)
	: m_bwapiUnit(u)
	, m_pMap(pMap)
	, m_pos(Sc2Bindings::PositionFromPoint3D(u.pos))
	, m_topLeft(Sc2Bindings::GetInitialTilePosition(u))
	, m_size(Sc2Bindings::GetSizeFromRadius(u.radius))
{

	PutOnTiles();
}


Neutral::~Neutral()
{
	try
	{
		RemoveFromTiles();
	
		if (Blocking())
			MapImpl::Get(GetMap())->OnBlockingNeutralDestroyed(this);
	}
	catch(...)
	{
		bwem_assert(false);
	}
}


TilePosition Neutral::BottomRight() const
{
	return m_topLeft + m_size - 1;
}


void Neutral::PutOnTiles()
{
	bwem_assert(!m_pNextStacked);

	for (int dy = 0 ; dy < Size().y ; ++dy)
	for (int dx = 0 ; dx < Size().x ; ++dx)
	{
		auto & tile = MapImpl::Get(GetMap())->GetTile_(TopLeft() + TilePosition(dx, dy));
		if (!tile.GetNeutral()) tile.AddNeutral(this);
		else
		{
			Neutral * pTop = tile.GetNeutral()->LastStacked();
			bwem_assert(this != tile.GetNeutral());
			bwem_assert(this != pTop);
			bwem_assert(!pTop->IsGeyser());
			bwem_assert_plus(pTop->Type().unit_type_id == Type().unit_type_id, "stacked neutrals have different types: " + pTop->Type().getName() + " / " + Type().getName());
			bwem_assert_plus(pTop->TopLeft() == TopLeft(), "stacked neutrals not aligned: " + my_to_string(pTop->TopLeft()) + " / " + my_to_string(TopLeft()));
			bwem_assert((dx == 0) && (dy == 0));

			pTop->m_pNextStacked = this;
			return;
		}
	}
}


void Neutral::RemoveFromTiles()
{
	for (int dy = 0 ; dy < Size().y ; ++dy)
	for (int dx = 0 ; dx < Size().x ; ++dx)
	{
		auto & tile = MapImpl::Get(GetMap())->GetTile_(TopLeft() + TilePosition(dx, dy));
		bwem_assert(tile.GetNeutral());

		if (tile.GetNeutral() == this)
		{
			tile.RemoveNeutral(this);
			if (m_pNextStacked) tile.AddNeutral(m_pNextStacked);
		}
		else
		{
			Neutral * pPrevStacked = tile.GetNeutral();
			while (pPrevStacked->NextStacked() != this) pPrevStacked = pPrevStacked->NextStacked();
			bwem_assert(pPrevStacked->Type().unit_type_id == Type().unit_type_id);
			bwem_assert(pPrevStacked->TopLeft() == TopLeft());
			bwem_assert((dx == 0) && (dy == 0));

			pPrevStacked->m_pNextStacked = m_pNextStacked;
			m_pNextStacked = nullptr;
			return;
		}
	}

	m_pNextStacked = nullptr;
}


vector<const Area *> Neutral::BlockedAreas() const
{
	vector<const Area *> Result;
	for (WalkPosition w : m_blockedAreas)
		Result.push_back(GetMap()->GetArea(w));

	return Result;
}


void Neutral::SetBlocking(const vector<WalkPosition> & blockedAreas)
{
	bwem_assert(m_blockedAreas.empty() && !blockedAreas.empty());

	m_blockedAreas = blockedAreas;
}
	


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                  class Ressource
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////


Ressource::Ressource(sc2::Unit u, Map * pMap)
	: Neutral(u, pMap),
	m_initialAmount(u.mineral_contents)
{
	bwem_assert(Sc2Bindings::IsMineralField(u.unit_type) || Sc2Bindings::IsVespeneGeyser(u.unit_type));
}
	


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                  class Mineral
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////


Mineral::Mineral(sc2::Unit u, Map * pMap)
	: Ressource(u, pMap)
{
	bwem_assert(Sc2Bindings::IsMineralField(u.unit_type));
}


Mineral::~Mineral()
{
	MapImpl::Get(GetMap())->OnMineralDestroyed(this);
}

	


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                  class Geyser
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////


Geyser::Geyser(sc2::Unit u, Map * pMap)
	: Ressource(u, pMap)
{
	bwem_assert(Sc2Bindings::IsVespeneGeyser(u.unit_type));
}


Geyser::~Geyser()
{
}

	


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                  class StaticBuilding
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////


StaticBuilding::StaticBuilding(sc2::Unit u, Map * pMap) : Neutral(u, pMap)
{
	bwem_assert(Sc2Bindings::IsStaticNeutral(u.unit_type));
}



	
} // namespace BWEM



