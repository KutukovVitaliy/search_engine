#include <iostream>
#include "ConverterJSON.h"
#include <vector>
int main() {
    ConverterJSON json;
    std::vector<std::string> res = json.GetTextDocuments();
    std::cout << "ResponsesLimit = " << json.GetResponsesLimit() << std::endl;
    for(auto el : res)
        std::cout << el << std::endl;

    return 0;
}
