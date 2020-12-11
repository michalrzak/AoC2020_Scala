#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <set>

struct node {
    std::vector<std::string> nodes;
    std::string value;
};

unsigned long count(std::map<std::string, std::vector<std::pair<int, std::string>>>& elems, std::string color){

    if (!elems.at(color).size())
        return 1;
    
    unsigned long outp {1};
    for (auto ele : elems.at(color)){
        std::cout << ele.second << '\n';
        outp += static_cast<unsigned long>(ele.first) * count(elems, ele.second);
    }

    return outp;

}




int main(){
 
    std::fstream f;
    f.open("input.txt");

    std::map<std::string, std::vector<std::pair<int, std::string>>> vals;

    std::string line;
    while(std::getline(f, line)){
        std::string container {line.substr(0, line.find(" contain ")-1)};
        //std::cout << container << '\n';

        line = line.erase(0, line.find(" contain ") + 9);
        //std::cout << line << '\n';

        vals.insert({container, std::vector<std::pair<int, std::string>>()});
        
        size_t pos;
        while((pos = line.find(", ")) != std::string::npos){
            std::cout << line.substr(0,1) << '\n';
            int count {stoi(line.substr(0,1))};

            std::string elem {line.substr(2, pos-2)};
            if (elem.back() == 's')
                elem.pop_back();
            
            vals.at(container).push_back({count, elem});
            line.erase(0, pos+2);
        }
        if (line != "no other bags."){
            int count {stoi(line.substr(0,1))};

            line.erase(0, 2);
            if (line.back() == '.')
                line.pop_back();
            if (line.back() == 's')
                line.pop_back();
            vals.at(container).push_back({count, line});
        }
    }

    std::cout << count(vals, "shiny gold bag") << '\n';

    return 0;
}