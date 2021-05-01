#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>


std::map<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>> rules;

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


bool match2 (std::string& line, std::vector<std::string>& r){
    for (auto rule : r){
        if (rule.at(0) >= 'a' && rule.at(0) <= 'z' && line.at(0) == rule.at(0))
            line=line.substr(1, std::string::npos);
        else if (rule.at(0) >= 'a' && rule.at(0) <= 'z' && line.at(0) != rule.at(0))
            return false;
        else{
            std::string cp {line};
            if (!match2(line, rules.at(rule).first))
                line = cp;
            else if (!match2(line, rules.at(rule).second))
                return false;
        }
    }
    return true;
}


bool match(std::string& line, std::map<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>& rules){

    for (auto ele : rules){
        if (ele.first.at(0) <= '9' && ele.first.at(0) >= '0')
            match(line, rules);
    }

    return false;

}


int main() {

    std::fstream input;
    input.open("input.txt");


    

    std::string line {"fadf"};
    while(getline(input, line) && line != ""){
        std::vector<std::string> v {split(line, ": ")};
        std::string index = v.at(0);
        rules.insert({index,{}});

        if (line.find(" | ") != std::string::npos){
            v = split(v.at(1), " | ");
            rules.at(index) = {split(v.at(0), " "), split(v.at(1), " ")};
        } else 
            rules.at(index) = {split(v.at(0), " "), {}};
    }


    size_t count {0};
    while (getline(input, line)){
        if (match2(line, rules.at("0").first) || match2(line, rules.at("0").second))
            ++count;
    }

    std::cout << count << '\n';

    return 0;
}