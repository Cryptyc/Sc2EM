#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"

#include "sc2utils/sc2_manage_process.h"
#include "bwem.h"

#include <iostream>

namespace { auto & theMap = SC2EM::Map::Instance(); }

class FooBot : public sc2::Agent {
public:
    uint32_t restarts_;

    FooBot() :
        restarts_(0) {
    }
	bool bInitialized{ false };

    virtual void OnGameStart() final {
        std::cout << "Starting a new game (" << restarts_ << " restarts)" << std::endl;
    };

	void InitializeMap(const ObservationInterface* obs)
	{
		theMap.Initialize(obs);
		theMap.EnableAutomaticPathAnalysis();
		bool startingLocationsOK = theMap.FindBasesForStartingLocations();
		assert(startingLocationsOK);

		SC2EM::utils::MapPrinter::Initialize(&theMap);
		SC2EM::utils::printMap(theMap);      // will print the map into the file <StarCraftFolder>bwapi-data/map.bmp
		SC2EM::utils::pathExample(theMap);   // add to the printed map a path between two starting locations
	}

    virtual void OnStep() final 
	{
		if (!bInitialized)
		{
			InitializeMap(Observation());
			bInitialized = true;
		}
        uint32_t game_loop = Observation()->GetGameLoop();

        if (game_loop % 100 == 0) {
            sc2::Units units = Observation()->GetUnits(sc2::Unit::Alliance::Self);
            for (auto& it_unit : units) {
                sc2::Point2D target = sc2::FindRandomLocation(Observation()->GetGameInfo());
                Actions()->UnitCommand(it_unit, sc2::ABILITY_ID::SMART, target);
            }
        }
    };

    virtual void OnGameEnd() final {
        ++restarts_;
        std::cout << "Game ended after: " << Observation()->GetGameLoop() << " loops " << std::endl;
    };

private:
};

//*************************************************************************************************
int main(int argc, char* argv[]) {
    sc2::Coordinator coordinator;
    if (!coordinator.LoadSettings(argc, argv)) {
        return 1;
    }

    // Add the custom bot, it will control the players.
    FooBot bot;

    coordinator.SetParticipants({
        CreateParticipant(sc2::Race::Terran, &bot),
        CreateComputer(sc2::Race::Terran)
    });

    // Start the game.
    coordinator.LaunchStarcraft();

    // Step forward the game simulation.
    bool do_break = false;
    while (!do_break) {
        coordinator.StartGame(sc2::kMapBelShirVestigeLE);
        while (coordinator.Update() && !do_break) {
            if (sc2::PollKeyPress()) {
                do_break = true;
            }
        }
    }

    return 0;
}
