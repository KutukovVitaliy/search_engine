//
// Created by kvitadmin on 06.05.2022.
//

#include "ConverterJSON.h"
#include <fstream>
#include <exception>
#include "nlohmann/json.hpp"

/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
*
в config.json
*/
std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::ifstream configFile("../config.json"), tmpFile;
    std::string tmpString;
    if(!configFile.is_open()) throw std::invalid_argument("Config file is missing!");
    std::vector<std::string> result;
    nlohmann::json configJson;
    configFile >> configJson;
    configFile.close();
    if(configJson["config"].empty()) throw std::invalid_argument("Config file is empty!");
    for(auto it = configJson["files"].begin(); it != configJson["files"].end(); ++it)
    {
        tmpFile.open(it.value());
        if(tmpFile.is_open())
        {
            tmpFile >> tmpString;
            result.emplace_back(tmpString);
            tmpString.erase();
            tmpFile.close();
        }
    }
    return result;
}

int ConverterJSON::GetResponsesLimit()
{
    std::ifstream configFile("../config.json"), tmpFile;
    std::string tmpString;
    if(!configFile.is_open()) throw std::invalid_argument("Config file is missing!");
    std::vector<std::string> result;
    nlohmann::json configJson;
    configFile >> configJson;
    configFile.close();
    if(configJson["config"].empty()) throw std::invalid_argument("Config file is empty!");
    return configJson["config"].value("max_responses", 0);
}