#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Room
{
public:
    enum RoomType
    {
        bedroom,
        kitchen,
        bathroom,
        restroom,
        playroom,
        living,
        main,
        undefined
    };
    vector<string> roomNames = {"bedroom", "kitchen", "bathroom", "restroom", "playroom", "living", "main", "undefined"};
    RoomType type = RoomType::undefined;
    int length{2000};
    int width{2000};
};

struct Floor
{
public:
    enum FloorType
    {
        first,
        second,
        third,
        undefined
    };
    vector<string> floorNames = {"first", "second", "third", "undefined"};
    FloorType type = FloorType::undefined;
    int height{2600};
    int maxRoomCount{4};
    vector<Room> rooms;
};
struct Building
{
public:
    enum class BuildingType
    {
        house,
        garage,
        shed,
        bathHouse,
        undefined
    };
    vector<string> buildingNames = {"house", "garage", "shed", "bathHouse", "undefined"};
    BuildingType type = BuildingType::undefined;
    bool isStove{false};
    int maxFloorInHouse{3};
    vector<Floor> floors;
    int square { 0 };
};
struct Area
{
public:
    int square{0};
    vector<Building> buildings;
};

struct Vilage
{
public:
    vector<Area> areas;
};

vector<string> splitString(string const &str, char const &separator)
{
    vector<string> words;
    string word;
    stringstream ss(str);
    while (getline(ss, word, separator))
    {
        if (word.length() != 0)
        {
            words.push_back(word);
        }
    }
    return words;
}

string getUserString(const string &text)
{
    printf("%s", text.c_str());
    string user_input;
    getline(cin, user_input);
    return splitString(user_input, ' ')[0];
}

bool isNumeric(string &number)
{
    if (number.begin() == number.end())
        return false;
    auto it = find_if(number.begin(), number.end(), [](char const &c)
                      { return !isdigit(c); });
    return it == number.end();
}

int getNumber(string text)
{
    string user_input;
    while (true)
    {
        user_input = getUserString(text);
        if (isNumeric(user_input))
            break;
        cout << "Это должно быть число!\n";
    }
    return stoi(user_input);
}

void buildingHaveStove(Building &build)
{
    cout << "Есть ли печь с трубой в здании?\n";
    bool result{false};
    string answer = getUserString("Введите (y) если есть : ");
    result = (answer == "y" or answer == "у" or answer == "Y" or answer == "У");
    build.isStove = result;
}

int getNumberRange(string text, int from, int to)
{
    int number;
    do
    {
        cout << "Введите число в диапозоне от " << from << " до " << to << endl;
        number = getNumber(text);
    } while (number < from or number > to);
    return number;
}

void whatIsArea(Building &build)
{
    int square{ 0 };
    do {
    cout << "Введите размеры.";
    int width = getNumber("Введите ширину : ");
    int length = getNumber("Введите длину : ");
    square = width * length;
    } while(square <= 0);
    cout << "Площадь равна : " << square;
    build.square = square;
}

Building fillBuildingInfo()
{
    Building newBuilding;
    cout << "Какого типа ваше строение:\n";
    for (int i = 0; i < newBuilding.buildingNames.size(); ++i)
    {
        cout << i + 1 << ". " << newBuilding.buildingNames[i] << endl;
    }
    int typeBuilding = getNumberRange("Введите номер подходящего типа :", 1, newBuilding.buildingNames.size());
    switch (typeBuilding)
    {
    case 1:
    {
        newBuilding.type = Building::BuildingType::house;
        buildingHaveStove(newBuilding);
    }
    case 2:
    {
        newBuilding.type = Building::BuildingType::garage;
        whatIsArea(newBuilding);
    }
    case 3:
    {
        newBuilding.type = Building::BuildingType::shed;
        whatIsArea(newBuilding);
    }
    case 4:
    {
        newBuilding.type = Building::BuildingType::bathHouse;
        buildingHaveStove(newBuilding);
        whatIsArea(newBuilding);
    }
    default:
        newBuilding.type = Building::BuildingType::undefined;
    }
    return newBuilding;
}

void fillingArea(Area &area)
{
    string message;
    if (area.buildings.empty())
    {
        message = "Введите количество зданий на участке : ";
    }
    else
    {
        message = "На участке уже зарегистрированно " + to_string(area.buildings.size()) + "домов\n. Общей площадью = " + to_string(area.square) + "\nСколько домов вы хотите добавить : ";
    }
    int countBildingsInArea = getNumber(message);

    for (int i = 0; i < countBildingsInArea; ++i)
    {
        area.buildings.push_back(fillBuildingInfo());
    }
}
void createMyVillage()
{
    Vilage myVilage;
    int countAreas = getNumber("Введите количество участков в поселке : ");
    myVilage.areas.resize(countAreas);
    bool wantFillingInData{true};
    int countFillingAreas{0};
    while (wantFillingInData and countFillingAreas < countAreas)
    {
        int countArea = getNumber("Введите номер участка для заполнения : ");
        fillingArea(myVilage.areas[countArea]);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    createMyVillage();
    return 0;
}