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

    InvertedIndex invIndex;
    std::string word = "milk";

    invIndex.docs.emplace_back("milk sugar salt");
    invIndex.docs.emplace_back("milk a milk b milk c milk d e milk");

    for(auto &el : invIndex.GetWordCount(word))
    {
        std::cout << el.doc_id << " : " << el.count << std::endl;
    }
    return 0;
}
