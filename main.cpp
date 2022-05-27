#include <iostream>
#include "ConverterJSON.h"
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"
#include "gtest/gtest.h"
#include "InvertedIndex.h"

using namespace std;
void TestInvertedIndexFunctionality(
        const vector<string>& docs,
        const vector<string>& requests,
        const std::vector<vector<Entry>>& expected
        ) {
    std::vector<std::vector<Entry>> result;
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    for(auto& request : requests) {
        std::vector<Entry> word_count = idx.GetWordCount(request);
        result.push_back(word_count);
    }
    ASSERT_EQ(result, expected);
}
TEST(TestCaseInvertedIndex, TestBasic) {
    const vector<string> docs = {
            "london is the capital of great britain",
            "big ben is the nickname for the Great bell of the striking clock"
    };
    const vector<string> requests = {"london", "the"};
    const vector<vector<Entry>> expected = {
            {
                {0, 1}
                }, {
                {0, 1}, {1, 3}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
    TEST(TestCaseInvertedIndex, TestBasic2) {
        const vector<string> docs = {
                "milk milk milk milk water water water",
                "milk water water",
                "milk milk milk milk milk water water water water water",
                "Americano Cappuccino"
        };
        const vector<string> requests = {"milk", "water", "Cappuccino"};
        const vector<vector<Entry>> expected = {
                {
                    {0, 4}, {1, 1}, {2, 5}
                    }, {
                    {0, 3}, {1, 2}, {2, 5}
                    }, {
                    {3, 1}
                }
        };
        TestInvertedIndexFunctionality(docs, requests, expected);
    }
    TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
        const vector<string> docs = {
                "a b c d e f g h i j k l",
                "statement"
        };
        const vector<string> requests = {"m", "statement"};
        const vector<vector<Entry>> expected = {
                {
                    {}
                    }, {
                    {1, 1}
                }
        };
        TestInvertedIndexFunctionality(docs, requests, expected);
    }
/*int main() {


    /*std::vector<std::vector<std::pair<int, float>>> answers = {
            {
                {2, 1},
                {0, 0.70f},
                {1, 0.30f}
            },
            {
                {}
            }
    };

    json.putAnswers(answers);*/
   /* std::vector<std::string> inputDocs;
    InvertedIndex invIndex;

    inputDocs.emplace_back("milk sugar salt");
    inputDocs.emplace_back("milk a milk b milk c milk d e milk");
    inputDocs.emplace_back("milk a milk b a str str a str");
    inputDocs.emplace_back("salt c milk d salt str r str");
    inputDocs.emplace_back("any a peace string bad f dog milk");
    inputDocs.emplace_back("cat  dad mother sister brother cat milk");
    inputDocs.emplace_back("dog killer sun string some big boss milk");

    invIndex.UpdateDocumentBase(inputDocs);

    for(auto it : invIndex.freq_dictionary)
    {
        std::cout << it.first << " : ";
        for(auto vecEl : it.second)
        {
            std::cout << "{" << vecEl.doc_id << "," << vecEl.count << "} ";
        }
        std::cout << std::endl;
    }
    return 0;
}*/
