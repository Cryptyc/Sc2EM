//////////////////////////////////////////////////////////////////////////
//
// This file is part of the BWEM Library.
// BWEM is free software, licensed under the MIT/X11 License. 
// A copy of the license is provided with the library in the LICENSE file.
// Copyright (c) 2015, 2017, Igor Dimitrijevic
//
//////////////////////////////////////////////////////////////////////////


#include "mapDrawer.h"
#include "map.h"
#include "Sc2Bindings.h"

using namespace Sc2Bindings;

using namespace std;


namespace SC2EM {

using namespace sc2_ext;

namespace utils {


//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//                                  class MapDrawer
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

bool MapDrawer::showSeas						= true;
bool MapDrawer::showLakes						= true;
bool MapDrawer::showUnbuildable					= true;
bool MapDrawer::showGroundHeight				= true;
bool MapDrawer::showMinerals					= true;
bool MapDrawer::showGeysers						= true;
bool MapDrawer::showStaticBuildings				= true;
bool MapDrawer::showBases						= true;
bool MapDrawer::showAssignedRessources			= true;
bool MapDrawer::showFrontier					= true;
bool MapDrawer::showCP							= true;

const Sc2Bindings::Color MapDrawer::Color::sea					= Sc2Bindings::Colors::Blue;
const Sc2Bindings::Color MapDrawer::Color::lakes					= Sc2Bindings::Colors::Blue;
const Sc2Bindings::Color MapDrawer::Color::unbuildable			= Sc2Bindings::Colors::Brown;
const Sc2Bindings::Color MapDrawer::Color::highGround			= Sc2Bindings::Colors::Brown;
const Sc2Bindings::Color MapDrawer::Color::veryHighGround		= Sc2Bindings::Colors::Red;
const Sc2Bindings::Color MapDrawer::Color::minerals				= Sc2Bindings::Colors::Cyan;
const Sc2Bindings::Color MapDrawer::Color::geysers				= Sc2Bindings::Colors::Green;
const Sc2Bindings::Color MapDrawer::Color::staticBuildings		= Sc2Bindings::Colors::Purple;
const Sc2Bindings::Color MapDrawer::Color::bases					= Sc2Bindings::Colors::Blue;
const Sc2Bindings::Color MapDrawer::Color::assignedRessources	= Sc2Bindings::Colors::Blue;
const Sc2Bindings::Color MapDrawer::Color::frontier				= Sc2Bindings::Colors::Grey;
const Sc2Bindings::Color MapDrawer::Color::cp					= Sc2Bindings::Colors::White;


bool MapDrawer::ProcessCommandVariants(const string & command, const string & attributName, bool & attribut)
{
	if (command == "show " + attributName) { attribut = true; return true; }
	if (command == "hide " + attributName) { attribut = false; return true; }
	if (command == attributName)		   { attribut = !attribut; return true; }
	return false;
}


bool MapDrawer::ProcessCommand(const string & command)
{
	if (ProcessCommandVariants(command, "seas", showSeas))								return true;
	if (ProcessCommandVariants(command, "lakes", showLakes))							return true;
	if (ProcessCommandVariants(command, "unbuildable", showUnbuildable))				return true;
	if (ProcessCommandVariants(command, "gh", showGroundHeight))						return true;
	if (ProcessCommandVariants(command, "minerals", showMinerals))						return true;
	if (ProcessCommandVariants(command, "geysers", showGeysers))						return true;
	if (ProcessCommandVariants(command, "static buildings", showStaticBuildings))		return true;
	if (ProcessCommandVariants(command, "bases", showBases))							return true;
	if (ProcessCommandVariants(command, "assigned ressources", showAssignedRessources))	return true;
	if (ProcessCommandVariants(command, "frontier", showFrontier))						return true;
	if (ProcessCommandVariants(command, "cp", showCP))									return true;
	
	if (ProcessCommandVariants(command, "all", showSeas))
	if (ProcessCommandVariants(command, "all", showLakes))
	if (ProcessCommandVariants(command, "all", showUnbuildable))
	if (ProcessCommandVariants(command, "all", showGroundHeight))
	if (ProcessCommandVariants(command, "all", showMinerals))
	if (ProcessCommandVariants(command, "all", showGeysers))
	if (ProcessCommandVariants(command, "all", showStaticBuildings))
	if (ProcessCommandVariants(command, "all", showBases))
	if (ProcessCommandVariants(command, "all", showAssignedRessources))
	if (ProcessCommandVariants(command, "all", showFrontier))
	if (ProcessCommandVariants(command, "all", showCP))
		return true;

	return false;
}

}} // namespace SC2EM::utils



