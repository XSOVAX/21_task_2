#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

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
        undefined
    };
    vector<string> roomNames = {"спальня", "кухня", "ванна", "туалет", "игровая комната", "гостиная", "другой тип"};
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
    vector<string> floorNames = {"первый", "второй", "третий", "чердак"};
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
    vector<string> buildingNames = { "undefined","дом", "гараж", "сарай", "баня" };
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
    cout << "Введите размеры.\n";
    int width = getNumber("Введите ширину(м) : ");
    int length = getNumber("Введите длину(м) : ");
    square = width * length;
    } while(square <= 0);
    cout << "Площадь равна(м^2) : " << square << endl;
    build.square = square;
}

Room newRoom(Building& build)
{
    Room thisRoom;
    cout << "Какого типа эта комната ?\n";
    for (int i = 0; i < thisRoom.roomNames.size(); ++i)
    {
        cout << i + 1 << ". " << thisRoom.roomNames[i] << endl;
    }
    int numberRoomType = getNumberRange("Введите номер подходящего типа комнаты : ", 1, thisRoom.roomNames.size()) - 1;
    thisRoom.type = (Room::RoomType)numberRoomType;
    do { thisRoom.length = getNumber("Введите длинну комнаты(м) : "); } while (thisRoom.length <= 0);
    do { thisRoom.width = getNumber("Введите ширину комнаты(м) : "); } while (thisRoom.width <= 0);
    build.square += thisRoom.length * thisRoom.width;
    return thisRoom;
}

void whatKindOfHouse(Building& build)
{
    buildingHaveStove(build);
    int count_floor = getNumberRange("Сколько этажей в ваше доме? ", 1, build.maxFloorInHouse);
    build.floors.resize(count_floor);
    int type_floor = 0;
    for (auto floor : build.floors)
    {
        floor.type = (Floor::FloorType)type_floor;
        cout << "Этаж " << floor.floorNames[type_floor] << endl;
        floor.height = getNumberRange("Какая высота потолка на этаже?(см) ", 200, 1000);
        int count_rooms = getNumberRange("Сколько комнат на этаже? ", 1, floor.maxRoomCount);
        for (int i = 0; i < count_rooms; ++i)
        {
            floor.rooms.push_back(newRoom(build));
        }
        type_floor++;
    }
}

Building fillBuildingInfo(Area &area)
{
    Building newBuilding;
    cout << "Какого типа ваше строение:\n";
    for (int i = 1; i < newBuilding.buildingNames.size(); ++i)
    {
        cout << i << ". " << newBuilding.buildingNames[i] << endl;
    }
    int typeBuilding = getNumberRange("Введите номер подходящего типа : ", 1, newBuilding.buildingNames.size() - 1);
    newBuilding.type = (Building::BuildingType)typeBuilding;
    if (typeBuilding == 1) 
    {
        whatKindOfHouse(newBuilding);
    }
    else 
    {
        if (typeBuilding == 4)
        {
            buildingHaveStove(newBuilding);
            whatIsArea(newBuilding);
        }
        else 
        {
            whatIsArea(newBuilding);
        }
    }
    area.square += newBuilding.square;
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
        message = "На участке уже зарегистрированно зданий : " 
            + to_string(area.buildings.size()) 
            + ".\nОбщей площадью = " 
            + to_string(area.square) 
            + "\nСколько домов вы хотите добавить : ";
    }
    int countBildingsInArea = getNumber(message);

    for (int i = 0; i < countBildingsInArea; ++i)
    {
        cout << "Здание # " << i + 1 << endl;
        area.buildings.push_back(fillBuildingInfo(area));
    }
}

void showRoom(Room const& room) {
    cout << "            Тип ------------ : " << room.roomNames[(int)room.type] << endl;
    cout << "            Ширина --------- : " << room.width << endl;
    cout << "            Длина ---------- : " << room.length << endl;
    cout << "            Площадь (м2) --- : " << fixed << setprecision(2) << room.width * room.length << endl;
    cout << endl;
}

void showFloor(Floor const& floor) {
    cout << "        Тип ---------------- : " << floor.floorNames[(int)floor.type] << endl;
    cout << "        Высота ------------- : " << floor.height << endl;
    cout << "        Количество комнат -- : " << floor.rooms.size() << endl;
    cout << endl;

    if (!floor.rooms.empty()) {
        for (auto const& room : floor.rooms) {
            showRoom(room);
            cout << "-----------------------------" << endl;
        }
    }
}

void showBuilding(Building const& building) {
    cout << "    Тип -------------------- : " << building.buildingNames[(int)building.type] << endl;
    cout << "    Наличие печи ----------- : " << (building.isStove ? "Есть" : "Нет") << endl;
    cout << "    Количество этажей ------ : " << building.floors.size() << endl;
    cout << "    Площадь дома (м2) ------ : " << fixed << setprecision(2) << building.square << endl;
    cout << endl;

    if (!building.floors.empty()) {
        for (auto const& floor : building.floors) {
            showFloor(floor);
            cout << "-----------------------------" << endl;
        }
    }
}

void showSector(Area const& sector) {
    cout << "Количество зданий ---------- :" << sector.buildings.size() << endl;
    cout << endl;

    if (!sector.buildings.empty()) {
        for (auto const& building : sector.buildings) {
            showBuilding(building);
            cout << "-----------------------------" << endl;
        }
    }
}

void showExistingSectors(vector<Area> const& area) {
    if (!area.empty()) {
        for (auto const& sector : area) showSector(sector);
    }
}

void createMyVillage()
{
    Vilage myVilage;
    bool wantFillingInData{ true };
    do {
        cout << "Хотите заполнить поселок данными или просмотреть ?\n";
        cout << 0 << ". Выйти. \n";
        cout << 1 << ". Просмотреть. \n";
        cout << 2 << ". Заполнить. \n";
        int action = getNumberRange("Выберите действие : ", 0, 2);
        switch (action) 
        {
        case 0:
            wantFillingInData = false;
        case 1:
            showExistingSectors(myVilage.areas);
            continue;
        case 2:
        {
            int countAreas = getNumber("Введите количество участков в поселке : ");
            myVilage.areas.resize(countAreas);
            int countFillingAreas{ 0 };
            while (wantFillingInData and countFillingAreas < countAreas)
            {
                int countArea = getNumberRange("Введите номер участка для заполнения : ", 1, myVilage.areas.size());
                fillingArea(myVilage.areas[countArea - 1]);
                countFillingAreas++;
            }
        }
        }
    } while (wantFillingInData);
}


int main()
{
    setlocale(LC_ALL, "Russian");
    createMyVillage();
    return 0;
}