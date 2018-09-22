#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::min;

#include "build.hpp"

using Bridge = vector<int>;
using myBridge = vector<int>;

enum
{
    west = 0,
    east = 1,
    toll = 2,
    status = 3
    // buildable = 3,
    // built = 4
};

enum Status : int
{
    Buildable = 0,
    Built = 1,
    CannotBuild = 2
};

void printAllNodes(vector<myBridge> &allnodes)
{
    for (auto n : allnodes)
    {
        for (auto m : n)
        {
            cout << m << " ";
        }
        cout << endl;
    }
}

void printList(vector<vector<int>> &allnodes)
{
    for (auto n : allnodes)
    {
        cout << "{";
        for (auto m : n)
        {
            cout << " " << m << " ";
        }
        cout << "}" << endl;
    }
}

vector<int> getBuildableBridges(vector<myBridge> &bridges)
{
    vector<int> CannotBuildCollection;
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
                        CannotBuildCollection.push_back(BridgeToBuildIndex);
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
    for (auto n : CannotBuildCollection)
    {
        bridges[n][status] = Status::CannotBuild;
    }
    return CanBuildCollection;
}

vector<Bridge> getState(vector<myBridge> &bridges)
{
    vector<Bridge> copy = bridges;
    return copy;
}

void setAdjacencyList(vector<myBridge> &bridges, vector<vector<int>> &adjacencyList, vector<int> &listStarter)
{
    auto canBuild = getBuildableBridges(bridges);

    if (canBuild.size() == 0)
    {
        adjacencyList.push_back(listStarter);
        //printList(adjacencyList);
        listStarter.pop_back();
        return;
    }

    auto currentBridgeState = getState(bridges);
    //printAllNodes(bridges);
    for (int i = 0; i < canBuild.size(); ++i)
    {
        bridges = currentBridgeState;
        bridges[canBuild[i]][status] = Status::Built;
        listStarter.push_back(canBuild[i]);
        //printAllNodes(bridges);
        setAdjacencyList(bridges, adjacencyList, listStarter);
    }
    listStarter.pop_back();
    return;
}

int getMaxTollPrice(vector<vector<int>> adjacencyList, const vector<Bridge> &bridges)
{

    int maxToll = 0;
    for (auto &allBuiltBridges : adjacencyList)
    {
        int totalToll = 0;
        for (auto &singleBuiltBridgeIndex : allBuiltBridges)
        {
            //cout << singleBuiltBridgeIndex << " ";
            totalToll += bridges[singleBuiltBridgeIndex][toll];
        }
        //cout << endl;
        if (totalToll > maxToll)
        {
            maxToll = totalToll;
        }
    }
    return maxToll;
}

vector<myBridge> translateToMyBridgeType(const vector<Bridge> &bridges)
{
    auto copy = bridges;
    for (auto &n : copy)
    {
        n.push_back(0);
    }
    return copy;
}

int build(int w, int e, const vector<Bridge> &bridges)
{
    int maxBridgeCount = min(w, e);
    vector<myBridge>
        myBridges = translateToMyBridgeType(bridges);
    //printAllNodes(myBridges);
    vector<vector<int>> adjacencyList{};
    vector<int> listStarter{};
    setAdjacencyList(myBridges, adjacencyList, listStarter);
    //printList(adjacencyList);
    return getMaxTollPrice(adjacencyList, bridges);
}

// int main()
// {
//     int w = 3;
//     int e = 3;
//     const vector<Bridge> allNodes{
//         Bridge{0, 1, 3},  //0
//         Bridge{1, 1, 5},  //1
//         Bridge{1, 2, 4},  //2
//         Bridge{2, 0, 8},  //3
//         Bridge{2, 2, 6},  //4
//         Bridge{0, 0, 1}}; //5

//     int result = build(w, e, allNodes);
//     cout << result << endl;
//     return 0;
// }