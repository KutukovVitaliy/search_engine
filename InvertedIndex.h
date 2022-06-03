//
// Created by kvitadmin on 23.05.2022.
//

#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <thread>
#include <mutex>

struct Entry {
    size_t docId, count;
    // Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const {
        return (docId == other.docId &&
        count == other.count);
    }
};
class InvertedIndex {
public:
    InvertedIndex() = default;
    /**
    * Обновить или заполнить базу документов, по которой будем совершать
    поиск
    * @param inputDocs содержимое документов
    */
    void UpdateDocumentBase(std::vector<std::string> inputDocs);

    /*** Метод определяет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
*/
    std::vector<Entry> GetWordCount(const std::string& word);

//private:
    std::vector<std::string> docs; // список содержимого документов
    std::map<std::string, std::vector<Entry>> freqDictionary; // частотный словарь
};

#endif //SEARCH_ENGINE_INVERTEDINDEX_H
