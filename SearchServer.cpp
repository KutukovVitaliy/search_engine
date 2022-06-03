//
// Created by kvitadmin on 30.05.2022.
//

#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queriesInput)
{
    std::vector<std::set<std::string>> vecStrSet;
    std::set<std::string> tmpSet;
    std::vector<std::multimap<int, std::string>> vecQueryMap;
    std::multimap<int, std::string> queryMap;
    std::stringstream sStr;
    std::string  tempStr;
    //Формируем список уникальных слов для каждого запроса
    for( auto &el : queriesInput)
    {
        sStr << el;
        while (sStr >> tempStr) tmpSet.emplace(tempStr);
        vecStrSet.emplace_back(tmpSet);
        tmpSet.clear();
        sStr.clear();
    }

    //Сортируем слова в порядке частоты встречаемости в словаре freqDictionary
    for(auto &vecEl : vecStrSet)
    {
        for(auto el : vecEl)
        {
            auto found = std::find_if(index.freqDictionary.begin(), index.freqDictionary.end(), [el](std::pair<std::string,std::vector<Entry>> it){
                return el == it.first;
            });
            if(found != index.freqDictionary.end())
            {
                int sumCount = 0;
                for(auto &vecEl : found->second)
                {
                    sumCount += vecEl.count;
                }
                queryMap.emplace(std::make_pair(sumCount, el));
            }
            else
            {
                queryMap.emplace(std::make_pair(0, el));
            }
        }
        vecQueryMap.emplace_back(queryMap);
        queryMap.clear();
    }
    //Для каждого запроса по первому слову из списка формируем список документов
    std::vector<std::vector<int>> vecDocsList;//Вектор списков номеров документов для каждого запроса по первым словам запроса
    std::vector<int> docsList;//
    for(auto &vecMapEl : vecQueryMap)
    {

        auto searchStr = vecMapEl.begin()->second;//первое слово из списка
        auto found = std::find_if(index.freqDictionary.begin(), index.freqDictionary.end(), [searchStr](std::pair<std::string,std::vector<Entry>> it){
            return searchStr == it.first;
        });
        if(found != index.freqDictionary.end())
        {
            for(auto &el : found->second)
            {
                docsList.emplace_back(el.docId);
            }
            vecDocsList.emplace_back(docsList);
            docsList.clear();
        }
        else
        {
            docsList.emplace_back(DOC_NOT_FOUND);
            vecDocsList.emplace_back(docsList);
            docsList.clear();
        }

    }
    //Ищем соответствия следующего слова и этого списка документов


}