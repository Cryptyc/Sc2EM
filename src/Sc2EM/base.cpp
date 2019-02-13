//////////////////////////////////////////////////////////////////////////
//
// This file is part of the BWEM Library.
// BWEM is free software, licensed under the MIT/X11 License. 
// A copy of the license is provided with the library in the LICENSE file.
// Copyright (c) 2015, 2017, Igor Dimitrijevic
//
//////////////////////////////////////////////////////////////////////////


#include "../Sc2Bindings/Sc2Bindings.h"
#include "base.h"
#include "graph.h"
#include "mapImpl.h"
#include "neutral.h"
#include "bwapiExt.h"


using namespace Sc2Bindings;

using namespace std;


namespace SC2EM {

using namespace detail;
using namespace sc2_ext;


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                  class Base
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////


Base::Base(Area * pArea, const TilePosition & location, const vector<Ressource *> & AssignedRessources, const vector<Mineral *> & BlockingMinerals)
	: m_pArea(pArea),
	m_pMap(pArea->GetMap()),
	m_location(location),
	m_center(Position(location) + Position(Sc2Bindings::GetSizeFromRadius(Sc2UnitTypes::getInstance().GetUnitRadius(UNIT_TYPEID::TERRAN_COMMANDCENTER)))),
	m_BlockingMinerals(BlockingMinerals)
{
	bwem_assert(!AssignedRessources.empty());

	for (Ressource * r : AssignedRessources)
		if		(Mineral * m = r->IsMineral())	m_Minerals.push_back(m);
		else if (Geyser * g = r->IsGeyser())		m_Geysers.push_back(g);
}


Base::Base(const Base & Other)
	: m_pMap(Other.m_pMap), m_pArea(Other.m_pArea)
{
	bwem_assert(false);
}


void Base::SetStartingLocation(const TilePosition & actualLocation)
{
	m_starting = true;
	m_location = actualLocation;
	m_center = Position(actualLocation) + Position(Sc2Bindings::GetSizeFromRadius(Sc2UnitTypes::getInstance().GetUnitRadius(UNIT_TYPEID::TERRAN_COMMANDCENTER)));
}


void Base::OnMineralDestroyed(const Mineral * pMineral)
{
	bwem_assert(pMineral);

	auto iMineral = find(m_Minerals.begin(), m_Minerals.end(), pMineral);
	if (iMineral != m_Minerals.end())
		fast_erase(m_Minerals, distance(m_Minerals.begin(), iMineral));

	iMineral = find(m_BlockingMinerals.begin(), m_BlockingMinerals.end(), pMineral);
	if (iMineral != m_BlockingMinerals.end())
		fast_erase(m_BlockingMinerals, distance(m_BlockingMinerals.begin(), iMineral));
}

	
} // namespace SC2EM



