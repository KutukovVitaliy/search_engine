#include <iostream>
#include "ConverterJSON.h"
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"
/*#include "gtest/gtest.h"
TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}*/
int main() {
    ConverterJSON json;
    /*std::vector<std::string> res = json.GetTextDocuments();
    std::cout << "ResponsesLimit = " << json.GetResponsesLimit() << std::endl;
    for(auto el : res)
        std::cout << el << std::endl;
    res = json.GetRequests();
    for(auto el : res)
        std::cout << el << std::endl;*/
    std::vector<std::vector<std::pair<int, float>>> answers = {
            {
                {2, 1},
                {0, 0.70f},
                {1, 0.30f}
            },
            {
                {}
            }
    };

    json.putAnswers(answers);

    return 0;
}
