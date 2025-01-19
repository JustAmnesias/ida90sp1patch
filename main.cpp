// ***********************************************************************************
// * ATTENTION: This code contains a lot of shit code.                              *
// * If you broke your eyes, sorry.                                                *
// * If you don't like the naming conventions, IDC :D                              *
// ***********************************************************************************

// By JustAmnesia with love for u :D

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <json/json.h>
#include <cstdlib>
#include <cstring>

//Like just got time rn
std::string NTime()
{
    std::time_t rn = std::time(nullptr);
    std::tm* lT = std::localtime(&rn);
    std::ostringstream oss;
    oss << std::put_time(lT, "%Y-%m-%d %H:%M:%S"); // Formating
    return oss.str();
}

//Like just time rn + 10 years
std::string FTime()
{
    std::time_t rn = std::time(nullptr);
    std::tm* fT = std::localtime(&rn);
    fT->tm_year += 10;
    std::mktime(fT);
    std::ostringstream oss;
    oss << std::put_time(fT, "%Y-%m-%d %H:%M:%S"); // Formating
    return oss.str();
}

Json::Value LicenseShit()
{
    std::string startDate = NTime();
    std::string endDate = FTime();

    Json::Value license;
    license["header"]["version"] = 1;

    Json::Value id;
    id["id"] = "48-2437-ACBD-29";
    id["license_type"] = "named";
    id["product"] = "IDA";
    id["product_id"] = "IDAPRO";
    id["edition_id"] = "ida-pro";
    id["seats"] = 1;
    id["start_date"] = startDate;
    id["end_date"] = endDate;
    id["issued_on"] = startDate;
    id["owner"] = "Amnesia"; // Change this 

    Json::Value addons(Json::arrayValue);
    std::vector<std::string> addonPlugins = {
        "HEXX86", "HEXX64", "HEXARM", "HEXARM64",
        "HEXMIPS", "HEXMIPS64", "HEXPPC", "HEXPPC64",
        "HEXRV64", "HEXARC",  "HEXARC64"
    };
    for (size_t i = 0; i < addonPlugins.size(); ++i)
    {
        Json::Value addon;
        addon["id"] = "48-1337-DEAD-" + std::to_string(i);
        addon["code"] = addonPlugins[i];
        addon["owner"] = id["id"];
        addon["start_date"] = startDate;
        addon["end_date"] = endDate;
        addons.append(addon);
    }

    id["add_ons"] = addons;
    id["features"] = Json::arrayValue;
    license["payload"]["name"] = "Amnesia"; // Change this 
    license["payload"]["email"] = "Amnesia@gmail.com"; // Change this 
    license["payload"]["licenses"] = Json::arrayValue;
    license["payload"]["licenses"].append(id);
    license["signature"] = "3238353E900849B6547801BBF8AF31E7822CB4B74A6F54DE03F5E9DFF96AC5DA981B50A62EAAF021F2052CC44498107B36C2D3B34C86B7B48084313189274A1D5D1F45C1F512820C508EA22ABA43EC584E6FEFF6BA9969DD428268F40859AFFE8A2E5BB66CA9C71E78FCAC14E3168D26D11952A71C0F330251D9D74FFC67BD24"; // Just work so using this :D

    return license;
}

void writeJS(const Json::Value& jsValue, const std::string& name)
{
    std::ofstream file(name, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file :( -> " << name << std::endl;
        return;
    }

    Json::StreamWriterBuilder wBuilder;
    wBuilder["indentation"] = "";
    std::string outString = Json::writeString(wBuilder, jsValue);

    file << outString;
    file.close();
}

int main()
{
    Json::Value license = LicenseShit(); // Just gen 
    writeJS(license, "idapro.hexlic");

    std::cout << "License file generated: idapro.hexlic :D\n";
    return 0;
}
