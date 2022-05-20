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
/**
   * Метод считывает поле max_responses для определения предельного
   * количества ответов на один запрос
   * @return
   */
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
/**
   * Метод получения запросов из файла requests.json
   * @return возвращает список запросов из файла requests.json
   */
std::vector<std::string> ConverterJSON::GetRequests()
{
    std::ifstream requestsFile("../requests.json");
    std::string tmpString;
    if(!requestsFile.is_open()) throw std::invalid_argument("requests file is missing!");
    std::vector<std::string> result;
    nlohmann::json requestsJson;
    requestsFile >> requestsJson;
    requestsFile.close();
    if(requestsJson["requests"].empty()) throw std::invalid_argument("requests file is empty!");
    for(auto it = requestsJson["requests"].begin(); it != requestsJson["requests"].end(); ++it)
    {
        tmpString = it.value();
        result.emplace_back(tmpString);
    }
    return result;
}

/**
   * Положить в файл answers.json результаты поисковых запросов
   */
void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{
    if(answers.empty()) return;
    int num = 1;
    std::string requestNum;
    std::ofstream answersFile;
    answersFile.open("../answers.json",std::ios::out);
    nlohmann::json answersJson;
    if(answersFile.is_open())
    {

        for(auto &req : answers)
        {
            requestNum = "request" + std::to_string(num++);

            if(req.size() == 1)
            {
                if(req.at(0).first == 0 && req.at(0).second == 0)
                {
                    answersJson["answers"][requestNum].emplace("result", "false");
                }
                else
                {
                    answersJson["answers"][requestNum].emplace("result", "true");
                    nlohmann::json tempJson ;
                    tempJson.push_back({{"docid", req.at(0).first}, {"rank", req.at(0).second}});
                    answersJson["answers"][requestNum].emplace("relevance", tempJson);
                }
            }
            else
            {
                answersJson["answers"][requestNum].emplace("result", "true");
                nlohmann::json tempJson ;
                for(auto vec : req)
                {
                    tempJson.push_back({{"docid",vec.first},{"rank",vec.second}});
                }
                answersJson["answers"][requestNum].emplace("relevance",tempJson);
            }
        }
    }
    answersFile << answersJson;
    answersFile.close();
}