#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>


std::vector<std::string> split(std::string inp, std::string c){
    std::vector<std::string> outp;
    
    size_t pos {0};
    while ((pos = inp.find(c)) != std::string::npos){
        outp.push_back(inp.substr(0, pos));
        inp = inp.substr(pos+c.length(), std::string::npos);
    }
    outp.push_back(inp);
    return outp;
}


int main() {

    std::fstream input;
    input.open("input.txt");


    std::map<std::string, std::vector<std::string>> alerg;
    std::map<std::string, size_t> count;
    std::map<std::string, size_t> candidate;

    std::string line;
    while (getline(input, line)){
        std::vector<std::string> elems {split(line, " ")};

        std::vector<std::string> al;

        size_t range {0};
        for (auto it {elems.rbegin()}; it != elems.rend(); ++it){
            ++range;
            if (it->at(0) == '(')
                break;
            al.push_back(it->substr(0, it->size()-1));
        }

        elems.erase(elems.begin()+(elems.size()-range), elems.end());

        for (auto it {al.rbegin()}; it != al.rend(); ++it){
            if (it->at(0) == '(')
                break;

            alerg[*it].insert(alerg[*it].end(), elems.begin(), elems.end());
            ++count[*it];
        }

        for (auto ele : elems)
            ++candidate[ele];
    }

    input.close();

    for (auto ele : alerg){
        std::cout << ele.first << '[' << count.at(ele.first) << ']';
        for (auto e : ele.second)
            std::cout << ' ' << e;
        std::cout << '\n';
    }


    for (auto al : alerg){
        for (auto ing : al.second)
            if (candidate.at(ing) && std::count(al.second.begin(), al.second.end(), ing) == count.at(al.first))
                candidate.at(ing) = 0;
    }


    size_t res {0};
    for (auto ele : candidate)
        res+=ele.second;

    std::cout << res << '\n';


    return 0;
}