//////////////////////////////////////////////////////////////////////////
//
// This file is part of the BWEM Library.
// BWEM is free software, licensed under the MIT/X11 License. 
// A copy of the license is provided with the library in the LICENSE file.
// Copyright (c) 2015, 2017, Igor Dimitrijevic
//
//////////////////////////////////////////////////////////////////////////


#include "map.h"
#include "mapImpl.h"
#include "bwapiExt.h"

using namespace Sc2Bindings;

using namespace std;


namespace SC2EM {

using namespace detail;
using namespace sc2_ext;

namespace utils {

bool seaSide(WalkPosition p, const Map * pMap)
{
	if (!pMap->GetMiniTile(p).Sea()) return false;

	for (WalkPosition delta : {WalkPosition(0, -1), WalkPosition(-1, 0), WalkPosition(+1, 0), WalkPosition(0, +1)})
	{
		if (pMap->Valid(p + delta))
		{
			if (!pMap->GetMiniTile(p + delta, check_t::no_check).Sea())
			{
				return true;
			}
		}
	}

	return false;
}

} // namespace utils


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                  class Map
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

unique_ptr<Map> Map::m_gInstance = nullptr;


Map & Map::Instance()
{
	if (!m_gInstance)
	{
		m_gInstance = make_unique<MapImpl>();
	}

	return *m_gInstance.get();
}


Position Map::RandomPosition() const
{
	const auto PixelSize = Position(Size());
	return Position(rand() % static_cast<int>(PixelSize.x), rand() % static_cast<int>(PixelSize.y));
}


template<class TPosition>
TPosition crop(const TPosition & p, float siseX, float sizeY)
{
	TPosition res = p;

	if (res.x < 0)
	{
		res.x = 0;
	}
	else if (res.x >= siseX)
	{
		res.x = siseX - 1;
	}

	if (res.y < 0)
	{
		res.y = 0;
	}
	else if (res.y >= sizeY)
	{
		res.y = sizeY - 1;
	}

	return res;
}

const Tile &Map::GetTile(const Sc2Bindings::TilePosition & p, utils::check_t checkMode) const
{

	bwem_assert((checkMode == utils::check_t::no_check) || Valid(p));
	utils::unused(checkMode); 
	return m_Tiles[Size().x * p.y + p.x]; 
}

const MiniTile &Map::GetMiniTile(const Sc2Bindings::WalkPosition & p, utils::check_t checkMode) const
{ 
	bwem_assert((checkMode == utils::check_t::no_check) || Valid(p)); 
	utils::unused(checkMode); 
	return m_MiniTiles[WalkSize().x * p.y + p.x]; 
}

TilePosition Map::Crop(const TilePosition & p) const
{
	return crop(p, Size().x, Size().y);
}


WalkPosition Map::Crop(const WalkPosition & p) const
{
	return crop(p, WalkSize().x, WalkSize().y);
}


Position Map::Crop(const Position & p) const
{
	return crop(p, 32*Size().x, 32*Size().y);
}


} // namespace SC2EM



