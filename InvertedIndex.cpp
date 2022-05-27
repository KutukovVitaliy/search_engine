//
// Created by kvitadmin on 23.05.2022.
//

#include "InvertedIndex.h"
/*** Метод определяет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
*/
std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
    std::vector<Entry> entry;
    size_t docNum = 0;
    for(auto &doc : docs)
    {
        size_t count = 0, pos = 0;
        while(pos != std::string::npos)
            {
                pos = doc.find(word, pos);
                if(pos != std::string::npos)
                {
                    count++;
                    pos++;
                }

            }
        if(count > 0)
            {
                entry.emplace_back(Entry{docNum, count});
            }
        docNum++;
    }
    return entry;
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
    std::vector<std::thread> threads;
    std::mutex mFreq;
    docs = input_docs;
    size_t docNum = 0;
    for(auto str : docs)
    {

        threads.push_back(std::thread( [str, docNum, this, &mFreq](){
            std::stringstream sStr;
            std::string  tempStr;
            std::vector<std::string> vecStr;
            std::vector<Entry> entry;
            sStr << str;
            while (sStr >> tempStr) vecStr.emplace_back(tempStr);
            std::vector<std::string>::iterator beginIt, currentIt;
            beginIt = vecStr.begin();
            while(beginIt != vecStr.end())
            {
                size_t count = 1;
                for(currentIt = beginIt + 1; currentIt != vecStr.end(); currentIt++)
                {
                    if(*beginIt == *currentIt)
                    {
                        vecStr.erase(currentIt);
                        currentIt--;
                        count++;
                    }
                }
                entry.emplace_back(Entry{docNum, count});
                mFreq.lock();
                auto it = freq_dictionary.find(*beginIt);
                if( it == freq_dictionary.end())
                {
                    freq_dictionary.emplace(std::make_pair(*beginIt, entry));
                }
                else
                {
                    for(auto &en : entry)
                        it->second.emplace_back(en);
                }
                mFreq.unlock();
                entry.clear();
                beginIt++;
            }

        }));
        docNum++;
    }
    for(auto &thr : threads) thr.join();
}