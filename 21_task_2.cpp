#include <iostream>
#include <vector>

using namespace std;

struct Room
{
public:
    enum RoomType { bedroom, kitchen, bathroom, restroom, playroom, living, main, undefined };
    vector<string>roomNames = { "bedroom", "kitchen", "bathroom", "restroom", "playroom", "living", "main", "undefined" };
    RoomType type = RoomType::undefined;
    int length{ 2000 };
    int width{ 2000 };
};

struct Floor
{
public:
    enum FloorType { first, second, third, undefined };
    vector<string> floorNames = { "first", "second", "third", "undefined" };
    FloorType type = FloorType::undefined;
    int height{ 2600 };
    int maxRoomCount{ 4 };
    vector<Room>rooms;
};
struct Building {
public:
    enum class BuildingType { house, garage, shed, bathHouse, undefined };
    vector<string> buildingNames = { "house", "garage", "shed", "bathHouse", "undefined" };
    BuildingType type = BuildingType::undefined;
    bool isStove{ false };
    int maxFloorInHouse{ 3 };
    vector<Floor>floors;
};
struct Area
{
public:
    int square{ 0 };
    vector<Building>buildings;
};

struct Vilage
{
public:
    vector<Area>areas;
};

int main()
{

	return 0;
}