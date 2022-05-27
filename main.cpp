#include <iostream>
#include "ConverterJSON.h"
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"
//#include "gtest/gtest.h"
#include "InvertedIndex.h"

/*TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}*/

int main() {


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
    std::vector<std::string> inputDocs;
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
}
