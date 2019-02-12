//////////////////////////////////////////////////////////////////////////
//
// This file is part of the BWEM Library.
// BWEM is free software, licensed under the MIT/X11 License. 
// A copy of the license is provided with the library in the LICENSE file.
// Copyright (c) 2015, 2017, Igor Dimitrijevic
//
//////////////////////////////////////////////////////////////////////////


#ifndef BWEM_BWAPI_EXT_H
#define BWEM_BWAPI_EXT_H

#include "Sc2Bindings.h"
#include "utils.h"
#include "defs.h"
#include <vector>

namespace BWEM {


namespace sc2_ext {


template<typename T, int Scale = 1>
inline std::ostream & operator<<(std::ostream & out, Sc2Bindings::Point<T, Scale> A)		{ out << "(" << A.x << ", " << A.y << ")"; return out; }


template<typename T, int Scale = 1>
inline Sc2Bindings::Position center(Sc2Bindings::Point<T, Scale> A)	{ return Sc2Bindings::Position(A) + Sc2Bindings::Position(Scale/2, Scale/2); }


template<typename T, int Scale = 1>
inline Sc2Bindings::Point<T, Scale> operator+(Sc2Bindings::Point<T, Scale> A, int b)	{ return A + Sc2Bindings::Point<T, Scale>(b, b); }

template<typename T, int Scale = 1>
inline Sc2Bindings::Point<T, Scale> operator+(int a, Sc2Bindings::Point<T, Scale> B)	{ return B + a; }

template<typename T, int Scale = 1>
inline Sc2Bindings::Point<T, Scale> operator-(Sc2Bindings::Point<T, Scale> A, int b)		{ return A + (-b); }

template<typename T, int Scale = 1>
inline Sc2Bindings::Point<T, Scale> operator-(int a, Sc2Bindings::Point<T, Scale> B)		{ return a + (B*-1); }


// Enlarges the bounding box [TopLeft, BottomRight] so that it includes A.
template<typename T, int Scale = 1>
inline void makeBoundingBoxIncludePoint(Sc2Bindings::Point<T, Scale> & TopLeft, Sc2Bindings::Point<T, Scale> & BottomRight, const Sc2Bindings::Point<T, Scale> & A)
{
	if (A.x < TopLeft.x)		TopLeft.x = A.x;
	if (A.x > BottomRight.x)	BottomRight.x = A.x;

	if (A.y < TopLeft.y)		TopLeft.y = A.y;
	if (A.y > BottomRight.y)	BottomRight.y = A.y;
}


// Makes the smallest change to A so that it is included in the bounding box [TopLeft, BottomRight].
template<typename T, int Scale = 1>
inline void makePointFitToBoundingBox(Sc2Bindings::Point<T, Scale> & A, const Sc2Bindings::Point<T, Scale> & TopLeft, const Sc2Bindings::Point<T, Scale> & BottomRight)
{
	if		(A.x < TopLeft.x)		A.x = TopLeft.x;
	else if (A.x > BottomRight.x)	A.x = BottomRight.x;
	
	if		(A.y < TopLeft.y)		A.y = TopLeft.y;
	else if (A.y > BottomRight.y)	A.y = BottomRight.y;
}


template<typename T, int Scale = 1>
bool inBoundingBox(const Sc2Bindings::Point<T, Scale> & A, const Sc2Bindings::Point<T, Scale> & topLeft, const Sc2Bindings::Point<T, Scale> & bottomRight)
{
	return  (A.x >= topLeft.x) && (A.x <= bottomRight.x) &&
			(A.y >= topLeft.y) && (A.y <= bottomRight.y);
}


template<typename T, int Scale = 1>
inline int queenWiseDist(Sc2Bindings::Point<T, Scale> A, Sc2Bindings::Point<T, Scale> B){ A -= B; return utils::queenWiseNorm(A.x, A.y); }

template<typename T, int Scale = 1>
inline int squaredDist(Sc2Bindings::Point<T, Scale> A, Sc2Bindings::Point<T, Scale> B)	{ A -= B; return squaredNorm(A.x, A.y); }

template<typename T, int Scale = 1>
inline double dist(Sc2Bindings::Point<T, Scale> A, Sc2Bindings::Point<T, Scale> B)		{ A -= B; return utils::norm(A.x, A.y); }

template<typename T, int Scale = 1>
inline int roundedDist(Sc2Bindings::Point<T, Scale> A, Sc2Bindings::Point<T, Scale> B)	{ return int(0.5 + dist(A, B)); }


inline int distToRectangle(const Sc2Bindings::Position & a, const Sc2Bindings::TilePosition & TopLeft, const Sc2Bindings::TilePosition & Size)
{
	auto topLeft = Sc2Bindings::Position(TopLeft);
	auto bottomRight = Sc2Bindings::Position(TopLeft + Size) - 1;

	if (a.x >= topLeft.x)
		if (a.x <= bottomRight.x)
			if (a.y > bottomRight.y)	return a.y - bottomRight.y;											// S
			else if (a.y < topLeft.y)	return topLeft.y - a.y;												// N
			else						return 0;															// inside
		else
			if (a.y > bottomRight.y)	return roundedDist(a, bottomRight);									// SE
			else if (a.y < topLeft.y)	return roundedDist(a, Sc2Bindings::Position(bottomRight.x, topLeft.y));	// NE
			else						return a.x - bottomRight.x;											// E
	else
		if (a.y > bottomRight.y)		return roundedDist(a, Sc2Bindings::Position(topLeft.x, bottomRight.y));	// SW
		else if (a.y < topLeft.y)		return roundedDist(a, topLeft);										// NW
		else							return topLeft.x - a.x;												// W
}


template<typename T, int Scale = 1>
inline std::vector<Sc2Bindings::Point<T, Scale>> innerBorder(Sc2Bindings::Point<T, Scale> TopLeft, Sc2Bindings::Point<T, Scale> Size, bool noCorner = false)
{
	std::vector<Sc2Bindings::Point<T, Scale>> Border;
	for (int dy = 0 ; dy < Size.y ; ++dy)
	for (int dx = 0 ; dx < Size.x ; ++dx)
		if ((dy == 0) || (dy == Size.y-1) ||
			(dx == 0) || (dx == Size.x-1))
			if (!noCorner ||
				!(((dx == 0) && (dy == 0)) || ((dx == Size.x-1) && (dy == Size.y-1)) ||
				  ((dx == 0) && (dy == Size.y-1)) || ((dx == Size.x-1) && (dy == 0))))
			Border.push_back(TopLeft + Sc2Bindings::Point<T, Scale>(dx, dy));

	return Border;
}

template<typename T, int Scale = 1>
inline std::vector<Sc2Bindings::Point<T, Scale>> outerBorder(Sc2Bindings::Point<T, Scale> TopLeft, Sc2Bindings::Point<T, Scale> Size, bool noCorner = false)
{
	return innerBorder(TopLeft - 1, Size + 2, noCorner);
}


inline std::vector<Sc2Bindings::WalkPosition> outerMiniTileBorder(Sc2Bindings::TilePosition TopLeft, Sc2Bindings::TilePosition Size, bool noCorner = false)
{
	return outerBorder(Sc2Bindings::WalkPosition(TopLeft), Sc2Bindings::WalkPosition(Size), noCorner);
}


inline std::vector<Sc2Bindings::WalkPosition> innerMiniTileBorder(Sc2Bindings::TilePosition TopLeft, Sc2Bindings::TilePosition Size, bool noCorner = false)
{
	return innerBorder(Sc2Bindings::WalkPosition(TopLeft), Sc2Bindings::WalkPosition(Size), noCorner);
}


void drawDiagonalCrossMap(Sc2Bindings::Position topLeft, Sc2Bindings::Position bottomRight, Sc2Bindings::Color col, DebugInterface *Debug);


template<typename T, int Scale = 1>
inline bool overlap(const Sc2Bindings::Point<T, Scale> & TopLeft1, const Sc2Bindings::Point<T, Scale> & Size1, const Sc2Bindings::Point<T, Scale> & TopLeft2, const Sc2Bindings::Point<T, Scale> & Size2)
{
	if (TopLeft2.x >= TopLeft1.x + Size1.x) return false;
	if (TopLeft2.y >= TopLeft1.y + Size1.y) return false;
	if (TopLeft1.x >= TopLeft2.x + Size2.x) return false;
	if (TopLeft1.y >= TopLeft2.y + Size2.y) return false;
	return true;
}

template<typename T, int Scale = 1>
inline bool disjoint(const Sc2Bindings::Point<T, Scale> & TopLeft1, const Sc2Bindings::Point<T, Scale> & Size1, const Sc2Bindings::Point<T, Scale> & TopLeft2, const Sc2Bindings::Point<T, Scale> & Size2)
{
	if (TopLeft2.x > TopLeft1.x + Size1.x) return true;
	if (TopLeft2.y > TopLeft1.y + Size1.y) return true;
	if (TopLeft1.x > TopLeft2.x + Size2.x) return true;
	if (TopLeft1.y > TopLeft2.y + Size2.y) return true;
	return false;
}




}} // namespace BWEM::sc2_ext




#endif

