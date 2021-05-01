#include <vector>
#include <iostream>
#include <fstream>
#include <string>


bool in_range(const std::vector<std::vector<std::pair<int, int>>>& rules, int val){
    for (auto rule : rules)
        for (auto range : rule)
            if (range.first <= val && range.second >= val)
                return true;

    return false;

}


int main(){

    std::fstream input;
    input.open("input.txt");


    std::vector<std::vector<std::pair<int, int>>> rules;

    std::string line;
    
    getline(input, line);
    while (line != ""){

        //splitaway name
        line = line.substr(line.find(": ")+ 2, std::string::npos);
        rules.push_back({});

        size_t pos {0};
        while ((pos = line.find(" or ")) != std::string::npos){
            size_t range_pos {0};
            range_pos = line.find('-');
            
            int first {std::stoi(line.substr(0, range_pos))};
            int second {std::stoi(line.substr(range_pos+1, pos))};

            rules.back().push_back({first, second});

            line = line.substr(pos+4, std::string::npos);
        }

        {
            size_t range_pos {0};
            range_pos = line.find('-');
            
            int first {std::stoi(line.substr(0, range_pos))};
            int second {std::stoi(line.substr(range_pos+1, pos))};

            rules.back().push_back({first, second});
        }

        getline(input, line);
    }

    for(auto ele : rules){
        for (auto rule : ele){
            std::cout<< rule.first << ' ' << rule.second << '\n';
        }
    }

    //ignore your ticket
    getline(input, line);
    getline(input, line);
    getline(input, line);


    //ignore nearby ticket header
    getline(input, line);

    size_t res {0};
    while(getline(input, line)){

        size_t pos {0};

        
        while((pos = line.find(',')) != std::string::npos){
            int current {std::stoi(line.substr(0, pos))};

            if(!in_range(rules, current))
                res += current;

            line = line.substr(pos+1, std::string::npos);
        }

        int current {std::stoi(line)};

        if(!in_range(rules, current))
            res += current;

    }

    std::cout << res << '\n';

    return 0;
}