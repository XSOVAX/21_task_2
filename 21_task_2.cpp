#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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

vector<string> splitString(string const& str, char const& separator)
{
    vector<string> words;
    string word;
    stringstream ss(str);
    while (getline(ss, word, separator))
    {
        if (word.length() != 0) {
            words.push_back(word);
        }
    }
    return words;
}


string getUserString(const string& text)
{
    printf("%s", text.c_str());
    string user_input;
    getline(cin, user_input);
    return splitString(user_input, ' ')[0];
}



int main()
{

	return 0;
}