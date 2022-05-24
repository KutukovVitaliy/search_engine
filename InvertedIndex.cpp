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