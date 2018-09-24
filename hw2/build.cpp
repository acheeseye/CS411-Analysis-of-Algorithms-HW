// build.cpp
// Jason Hsi
// Analysis of Algorithms Fall 2018
// Due: Sept 24, 2018
// Purpose: create a solution to maximize bridge toll

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <cmath>
using std::pow;
#include <algorithm>
using std::find;

#include "build.hpp"

using myBridge = vector<int>;
using Bridge = vector<int>;

enum
{
    west = 0,
    east = 1,
    toll = 2,
    status = 3
};

enum Status : int
{
    Buildable = 0,
    Built = 1,
    CannotBuild = 2
};

// getAllDistinctSubsets
vector<vector<int>> getAllDistinctSubsets(const vector<Bridge> &bridges)
{
    int totalScenarioCount = pow(2, bridges.size());
    vector<vector<int>> returnvec;
    vector<int> subset;

    for (auto decimalValue = 0; decimalValue < totalScenarioCount; ++decimalValue)
    {
        int decimalBuffer = decimalValue;
        subset.clear();
        while (decimalBuffer > 0)
        {
            int binaryBit = decimalBuffer % 2;
            subset.push_back(binaryBit);
            decimalBuffer /= 2;
        }
        returnvec.push_back(subset);
    }
    return returnvec;
}

// getBuildableBridgesAndUpdate
// determines plausibilty of bridges to be built and updates vector<myBridge> according to building status
vector<int> getBuildableBridgesAndUpdate(vector<myBridge> &bridges)
{
    vector<int> CanBuildCollection;
    for (int BridgeToBuildIndex = 0; BridgeToBuildIndex < bridges.size(); ++BridgeToBuildIndex)
    {
        if (bridges[BridgeToBuildIndex][status] == Status::Buildable)
        {
            bool buildableFlag = true;
            for (int BuiltBridgeIndex = 0; BuiltBridgeIndex < bridges.size(); ++BuiltBridgeIndex)
            {
                if (bridges[BuiltBridgeIndex][status] == Status::Built)
                {
                    int BuiltCityWest = bridges[BuiltBridgeIndex][west];
                    int BuiltCityEast = bridges[BuiltBridgeIndex][east];

                    int ToBuildWest = bridges[BridgeToBuildIndex][west];
                    int ToBuildEast = bridges[BridgeToBuildIndex][east];

                    if ((BuiltCityWest < ToBuildWest && BuiltCityEast > ToBuildEast) ||
                        (BuiltCityWest > ToBuildWest && BuiltCityEast < ToBuildEast) ||
                        (BuiltCityWest == ToBuildWest || BuiltCityEast == ToBuildEast))
                    {
                        bridges[BridgeToBuildIndex][status] = Status::CannotBuild;
                        buildableFlag = false;
                        break;
                    }
                }
            }
            if (buildableFlag)
            {
                CanBuildCollection.push_back(BridgeToBuildIndex);
            }
        }
    }
    return CanBuildCollection;
}

// translateToMyBridgeType
// returns a vector<myBridge> object, where myBridge has an extra value for [status]
vector<myBridge> translateToMyBridgeType(const vector<Bridge> &bridges)
{
    auto copy = bridges;
    for (auto &n : copy)
    {
        n.push_back(Status::Buildable);
    }
    return copy;
}

// resetToAllBuildable
// resets bridges to analyze new building scenario
void resetToAllBuildable(vector<myBridge> &bridges)
{
    for (auto &n : bridges)
    {
        n[status] = Status::Buildable;
    }
}

// getPlausibleBuilds
// returns all distinct subset of bridges that can be built together -- including subsets of the subsets
vector<vector<int>> getPlausibleBuilds(vector<vector<int>> &distinctSubsets, vector<myBridge> &myBridges)
{
    vector<vector<int>> plausibleScenarios;
    for (int subsetID = 0; subsetID < distinctSubsets.size(); ++subsetID)
    {
        resetToAllBuildable(myBridges);
        for (int bridgeIndex = 0; bridgeIndex < distinctSubsets[subsetID].size(); ++bridgeIndex)
        {
            auto canBuild = getBuildableBridgesAndUpdate(myBridges);
            if (distinctSubsets[subsetID][bridgeIndex] == 1)
            {
                if (find(canBuild.begin(), canBuild.end(), bridgeIndex) != canBuild.end())
                {
                    myBridges[bridgeIndex][status] = Status::Built;

                    if (distinctSubsets[subsetID].size() - 1 == bridgeIndex)
                    {
                        plausibleScenarios.push_back(distinctSubsets[subsetID]);
                        continue;
                    }
                    myBridges[bridgeIndex][status] == Status::CannotBuild;
                }
                else
                {
                    break;
                }
            }
        }
    }
    return plausibleScenarios;
}

// getMaxToll
int getMaxToll(vector<vector<int>> &plausibleScenarios, vector<myBridge> &myBridges)
{
    int maxToll = 0;
    for (int plausibleScenarioID = 0; plausibleScenarioID < plausibleScenarios.size(); ++plausibleScenarioID)
    {
        int tollTotal = 0;
        for (int bridgeID = 0; bridgeID < plausibleScenarios[plausibleScenarioID].size(); ++bridgeID)
        {
            if (plausibleScenarios[plausibleScenarioID][bridgeID] == 1)
            {
                tollTotal += myBridges[bridgeID][toll];
            }
        }
        if (tollTotal > maxToll)
        {
            maxToll = tollTotal;
        }
    }
    return maxToll;
}

// build
// overarching solution to call required functions
int build(int w, int e, const vector<Bridge> &bridges)
{
    auto distinctSubsets = getAllDistinctSubsets(bridges);
    auto myBridges = translateToMyBridgeType(bridges);
    auto plausibleScenarios = getPlausibleBuilds(distinctSubsets, myBridges);
    auto maxToll = getMaxToll(plausibleScenarios, myBridges);
    return maxToll;
}