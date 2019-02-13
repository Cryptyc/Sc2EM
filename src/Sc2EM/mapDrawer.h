//////////////////////////////////////////////////////////////////////////
//
// This file is part of the BWEM Library.
// BWEM is free software, licensed under the MIT/X11 License. 
// A copy of the license is provided with the library in the LICENSE file.
// Copyright (c) 2015, 2017, Igor Dimitrijevic
//
//////////////////////////////////////////////////////////////////////////


#ifndef BWEM_MAP_DRAWER_H
#define BWEM_MAP_DRAWER_H

#include "../Sc2Bindings/Sc2Bindings.h"
#include <memory>
#include "utils.h"
#include "defs.h"


class BMP;
namespace SC2EM {
class Map;
namespace utils {



//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                  class MapDrawer
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////
//


class MapDrawer
{
public:

	static bool ProcessCommand(const std::string & command);

	static bool		showSeas;
	static bool		showLakes;
	static bool		showUnbuildable;
	static bool		showGroundHeight;
	static bool		showMinerals;
	static bool		showGeysers;
	static bool		showStaticBuildings;
	static bool		showBases;
	static bool		showAssignedRessources;
	static bool		showFrontier;
	static bool		showCP;

	struct Color
	{
		static const Sc2Bindings::Color	sea;
		static const Sc2Bindings::Color	lakes;
		static const Sc2Bindings::Color	unbuildable;
		static const Sc2Bindings::Color	highGround;
		static const Sc2Bindings::Color	veryHighGround;
		static const Sc2Bindings::Color	minerals;
		static const Sc2Bindings::Color	geysers;
		static const Sc2Bindings::Color	staticBuildings;
		static const Sc2Bindings::Color	bases;
		static const Sc2Bindings::Color	assignedRessources;
		static const Sc2Bindings::Color	frontier;
		static const Sc2Bindings::Color	cp;
	};

private:
	static bool ProcessCommandVariants(const std::string & command, const std::string & attributName, bool & attribut);
};


}} // namespace SC2EM::detail::detail


#endif

