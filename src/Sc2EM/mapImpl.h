//////////////////////////////////////////////////////////////////////////
//
// This file is part of the BWEM Library.
// BWEM is free software, licensed under the MIT/X11 License. 
// A copy of the license is provided with the library in the LICENSE file.
// Copyright (c) 2015, 2017, Igor Dimitrijevic
//
//////////////////////////////////////////////////////////////////////////


#ifndef BWEM_MAP_IMPL_H
#define BWEM_MAP_IMPL_H


#include "graph.h"
#include "map.h"
#include "tiles.h"
#include <queue>
#include <memory>
#include "utils.h"
#include "defs.h"


namespace SC2EM {

	class Neutral;
	class Mineral;
	class Geyser;
	class StaticBuilding;
	class ChokePoint;

	namespace detail {

		using namespace std;
		using namespace utils;
		using namespace sc2_ext;



		class TempAreaInfo;
		//////////////////////////////////////////////////////////////////////////////////////////////
		//                                                                                          //
		//                                  class MapImpl
		//                                                                                          //
		//////////////////////////////////////////////////////////////////////////////////////////////
		//

		class MapImpl : public Map
		{
		public:
			// Downcast helpers
			static MapImpl *			Get(Map * pMap) { return static_cast<MapImpl *>(pMap); }
			static const MapImpl *		Get(const Map * pMap) { return static_cast<const MapImpl *>(pMap); }

			using Map::GetTile_;
			using Map::GetMiniTile_;

			MapImpl();
			~MapImpl();

			void						Initialize(const ObservationInterface *obs) override;

			bool						AutomaticPathUpdate() const override { return m_automaticPathUpdate; }
			void						EnableAutomaticPathAnalysis() const override { m_automaticPathUpdate = true; }

			bool						FindBasesForStartingLocations() override;

			altitude_t					MaxAltitude() const override { return m_maxAltitude; }

			int							BaseCount() const override { return GetGraph().BaseCount(); }
			int							ChokePointCount() const override { return static_cast<int>(GetGraph().ChokePoints().size()); }

			const vector<Sc2Bindings::TilePosition> &			StartingLocations() const override { return m_StartingLocations; }

			const vector<unique_ptr<Geyser>> &			Geysers() const override { return m_Geysers; }
			const vector<unique_ptr<Mineral>> &			Minerals() const override { return m_Minerals; }
			const vector<unique_ptr<StaticBuilding>> &	StaticBuildings() const override { return m_StaticBuildings; }

			Mineral *					GetMineral(sc2::Unit u) const override;
			Geyser *					GetGeyser(sc2::Unit u) const override;

			void						OnMineralDestroyed(sc2::Unit u) override;
			void						OnStaticBuildingDestroyed(sc2::Unit u) override;

			const vector<Area> &		Areas() const override { return GetGraph().Areas(); }

			// Returns an Area given its id. Range = 1..Size()
			const Area *				GetArea(Area::id id) const override { return m_Graph.GetArea(id); }
			Area *						GetArea(Area::id id) { return m_Graph.GetArea(id); }

			const Area *				GetArea(Sc2Bindings::WalkPosition w) const override { return m_Graph.GetArea(w); }
			const Area *				GetArea(Sc2Bindings::TilePosition t) const override { return m_Graph.GetArea(t); }

			Area *						GetArea(Sc2Bindings::WalkPosition w) { return m_Graph.GetArea(w); }
			Area *						GetArea(Sc2Bindings::TilePosition t) { return m_Graph.GetArea(t); }

			const Area *				GetNearestArea(Sc2Bindings::WalkPosition w) const override { return m_Graph.GetNearestArea(w); }
			const Area *				GetNearestArea(Sc2Bindings::TilePosition t) const override { return m_Graph.GetNearestArea(t); }

			Area *						GetNearestArea(Sc2Bindings::WalkPosition w) { return m_Graph.GetNearestArea(w); }
			Area *						GetNearestArea(Sc2Bindings::TilePosition t) { return m_Graph.GetNearestArea(t); }


			const CPPath &				GetPath(const Sc2Bindings::Position & a, const Sc2Bindings::Position & b, int * pLength = nullptr) const override { return m_Graph.GetPath(a, b, pLength); }

			const class Graph &			GetGraph() const { return m_Graph; }
			class Graph &				GetGraph() { return m_Graph; }


			const vector<pair<pair<Area::id, Area::id>, Sc2Bindings::WalkPosition>> &		RawFrontier() const override { return m_RawFrontier; }



			void						OnMineralDestroyed(const Mineral * pMineral);
			void						OnBlockingNeutralDestroyed(const Neutral * pBlocking);

		private:
			void						ReplaceAreaIds(Sc2Bindings::WalkPosition p, Area::id newAreaId);

			void						InitializeNeutrals(const ObservationInterface *obs);
			void						LoadData(const ObservationInterface *obs);
			void						DecideSeasOrLakes();
			void						ComputeAltitude();
			void						ProcessBlockingNeutrals();
			void						ComputeAreas();
			vector<pair<Sc2Bindings::WalkPosition, MiniTile *>>
				SortMiniTiles();
			vector<TempAreaInfo>		ComputeTempAreas(const vector<pair<Sc2Bindings::WalkPosition, MiniTile *>> & MiniTilesByDescendingAltitude);
			void						CreateAreas(const vector<TempAreaInfo> & TempAreaList);
			void						SetAreaIdInTiles();
			void						SetAreaIdInTile(Sc2Bindings::TilePosition t);
			void						SetAltitudeInTile(Sc2Bindings::TilePosition t);


			altitude_t							m_maxAltitude;

			mutable bool						m_automaticPathUpdate = false;

			class Graph							m_Graph;
			vector<unique_ptr<Mineral>>			m_Minerals;
			vector<unique_ptr<Geyser>>			m_Geysers;
			vector<unique_ptr<StaticBuilding>>	m_StaticBuildings;
			vector<Sc2Bindings::TilePosition>			m_StartingLocations;

			vector<pair<pair<Area::id, Area::id>, Sc2Bindings::WalkPosition>>	m_RawFrontier;
		};





	}
} // namespace SC2EM::detail


#endif

