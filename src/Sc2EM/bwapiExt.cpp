//////////////////////////////////////////////////////////////////////////
//
// This file is part of the BWEM Library.
// BWEM is free software, licensed under the MIT/X11 License. 
// A copy of the license is provided with the library in the LICENSE file.
// Copyright (c) 2015, 2017, Igor Dimitrijevic
//
//////////////////////////////////////////////////////////////////////////


#include "bwapiExt.h"


using namespace Sc2Bindings;

using namespace std;

using namespace sc2;

namespace SC2EM {

using namespace utils;
using namespace detail;

namespace sc2_ext {


void drawDiagonalCrossMap(Sc2Bindings::Position topLeft, Sc2Bindings::Position bottomRight, Sc2Bindings::Color col,  DebugInterface *Debug)
{
	float m_maxZ = 50.0f;
	Point3D TopLeftSc2;
	Point3D BottomRightSc2;
	TopLeftSc2.x = static_cast<float>(topLeft.x);
	TopLeftSc2.y = static_cast<float>(topLeft.y);
	BottomRightSc2.x = static_cast<float>(bottomRight.x);
	BottomRightSc2.y = static_cast<float>(bottomRight.y);
	Debug->DebugLineOut(TopLeftSc2, BottomRightSc2, BWToSc2Color(col));
	Debug->DebugLineOut(Point3D(BottomRightSc2.x, TopLeftSc2.y, m_maxZ + 0.2f), Point3D(TopLeftSc2.x, BottomRightSc2.y, m_maxZ + 0.2f), BWToSc2Color(col));
}


}} // namespace SC2EM::sc2_ext



