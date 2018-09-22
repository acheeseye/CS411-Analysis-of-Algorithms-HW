#include <vector>

using Bridge = std::vector<int>;
using myBridge = std::vector<int>;

std::vector<int> getBuildableBridges(std::vector<myBridge> &bridges);
std::vector<Bridge> getState(std::vector<myBridge> &bridges);
void setAdjacencyList(std::vector<myBridge> &bridges, std::vector<std::vector<int>> &adjacencyList, std::vector<int> &listStarter);
int getMaxTollPrice(std::vector<std::vector<int>> adjacencyList, const std::vector<Bridge> &bridges);
std::vector<myBridge> translateToMyBridgeType(const std::vector<Bridge> &bridges);
int build(int w, int e, const std::vector<Bridge> &bridges);