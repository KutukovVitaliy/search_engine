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
    std::ifstream configFile("../config.json");
    if(!configFile.is_open()) throw std::invalid_argument("Config file is missing!");
    std::vector<std::string> result;
    nlohmann::json configJson;
    configFile >> configJson;
}