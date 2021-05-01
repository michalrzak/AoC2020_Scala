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
    std::map<std::string, std::string> map;

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

        for (auto ele : elems){
            ++candidate[ele];
            map[ele] = "";
        }
    }

    input.close();

    for (auto ele : alerg){
        std::cout << ele.first << '[' << count.at(ele.first) << ']';
        for (auto e : ele.second)
            std::cout << ' ' << e;
        std::cout << '\n';
    }

    bool changed {true};
    while (changed){
        changed = false;
        for (auto al : alerg){
            size_t found {0};
            std::string i;
            std::map<std::string, bool> cand;
            for (auto ing : al.second){
                if (!cand[ing] && map.at(ing) == "" && std::count(al.second.begin(), al.second.end(), ing) == count.at(al.first)){
                    cand[ing] = true;
                    if (!found)
                        i = ing;
                    ++found;
                }
            }
            if (found == 1){
                map[i] = al.first;
                changed = true;
            }
            //else if (found == 1 && map[i] != "")
                //map[i] = "";
        }
    }

    std::cout << "this is a test\n";

    std::string r;
    
    std::vector <std::string> dangerous;
    
    for (auto ele : map){
        if (ele.second != ""){
            std::cout << ele.first << ':' << ele.second << '\n';
            dangerous.push_back(ele.first);
        }
    }

    std::sort(dangerous.begin(), dangerous.end(), [&map](std::string s1, std::string s2){return map.at(s1) < map.at(s2);});

    bool first {true};
    for (auto ele : dangerous){
        if (first)
            first = false;
        else
            r += ',';
        r+=ele;
    }


    std::cout << r << '\n';

    return 0;
}