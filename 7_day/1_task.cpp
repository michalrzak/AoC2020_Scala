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

std::set<std::string> count(std::map<std::string, std::vector<std::string>>& elems, std::string color){
    std::set<std::string> outp;

    if (elems.find(color) == elems.end())
        return outp;

    outp.insert(elems.at(color).begin(), elems.at(color).end());
    
    for (auto ele : elems.at(color)){
        std::set<std::string> temp {count(elems, ele)};
        outp.insert(temp.begin(), temp.end());
    }

    for (auto ele : outp) std::cout << ele << '\n';

    return outp;

}


int main(){
 
    std::fstream f;
    f.open("input.txt");

    std::map<std::string, std::vector<std::string>> vals;

    std::string line;
    while(std::getline(f, line)){
        std::string container {line.substr(0, line.find(" contain ")-1)};
        //std::cout << container << '\n';

        line = line.erase(0, line.find(" contain ") + 9);
        //std::cout << line << '\n';

        
        
        size_t pos;
        while((pos = line.find(", ")) != std::string::npos){
            std::string elem {line.substr(2, pos-2)};
            if (elem.back() == 's')
                elem.pop_back();

            if (vals.find(elem) == vals.end())
                vals.insert({elem, std::vector<std::string>()});
            
            vals.at(elem).push_back(container);
            std::cout << elem;

            line.erase(0, pos+2);
        }
        line.erase(0, 2);
        if (line.back() == '.')
            line.pop_back();
        if (line.back() == 's')
            line.pop_back();

        if (vals.find(line) == vals.end())
            vals.insert({line, std::vector<std::string>()});
            
        vals.at(line).push_back(container);
            
    }

    for (auto ele : vals.at("shiny gold bag")) std::cout << ele << '\n';

    std::cout << count(vals, "shiny gold bag").size() << '\n';

    return 0;
}