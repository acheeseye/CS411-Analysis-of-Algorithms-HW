// build.hpp
// Jason Hsi
// Analysis of Algorithms Fall 2018
// Due: Sept 24, 2018
// Purpose: header file for build.cpp

#include <vector>

using Bridge = std::vector<int>;
using myBridge = std::vector<int>;

std::vector<std::vector<int>> allDistinctSubsetGenerator(const std::vector<Bridge> &bridges);
std::vector<int> getBuildableBridges(std::vector<myBridge> &bridges);
std::vector<myBridge> translateToMyBridgeType(const std::vector<Bridge> &bridges);
void resetToAllBuildable(std::vector<myBridge> &bridges);
std::vector<std::vector<int>> getPlausibleBuilds(std::vector<std::vector<int>> &distinctSubsets, std::vector<myBridge> &myBridges);
int getMaxToll(std::vector<std::vector<int>> &plausibleScenarios, std::vector<myBridge> &myBridges);
int build(int w, int e, const std::vector<Bridge> &bridges);