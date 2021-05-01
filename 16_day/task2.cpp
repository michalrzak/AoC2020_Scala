#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


bool in_range(const std::vector<std::vector<std::pair<int, int>>>& rules, int val){
    for (auto rule : rules)
        for (auto range : rule)
            if (range.first <= val && range.second >= val)
                return true;

    return false;

}

bool check_constraint(std::vector<std::pair<int, int>>& constraint, int val){
    for (auto range : constraint)
        if (val >= range.first && val <= range.second)
            return true;

    return false;
}

void remove(std::vector<std::vector<int>>& map, int inp){
    for (auto i {map.begin()}; i != map.end(); ++i){
        for (auto it{i->begin()}; it != i->end();){
            if(*it == inp)
                it = i->erase(it);
            else
                ++it;
        }
    }
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

    //your ticket
    getline(input, line);
    getline(input, line);
    std::vector<int> your_ticket;
    {
        size_t pos {0};
        while((pos = line.find(',')) != std::string::npos){
            int current {std::stoi(line.substr(0, pos))};

            your_ticket.push_back(current);
            line = line.substr(pos+1, std::string::npos);
        }
        std::cout << line << '\n';
        your_ticket.push_back(std::stoi(line));
    }
    getline(input, line);


    //ignore nearby ticket header
    getline(input, line);

    std::vector<std::vector<int>> tickets;
    while(getline(input, line)){

        size_t pos {0};

        bool valid {true};

        std::vector<int> ticket;
        while((pos = line.find(',')) != std::string::npos){
            int current {std::stoi(line.substr(0, pos))};

            if(!in_range(rules, current)){
                valid = false;
                break;
            }

            ticket.push_back(current);
            line = line.substr(pos+1, std::string::npos);
        }

        if (!valid)
            continue;

        int current {std::stoi(line)};

        if(!in_range(rules, current))
            continue;

        
        ticket.push_back(current);
        tickets.push_back(ticket);
    }

    //map values
    std::vector<std::vector<int>> map;

    for (size_t i {0}; i < tickets.at(0).size(); ++i){
        map.push_back({});
        for (size_t j {0}; j < rules.size(); ++j){
            bool valid {true};
            for (auto ticket : tickets){
                if (!check_constraint(rules.at(j), ticket.at(i))){
                    valid = false;
                    break;
                }
            }

            if (valid){
                std::cout << "==================\n";
                for (auto ele : tickets)
                    std::cout << ele.at(i) << ' ';
                std::cout << "\n==================\n";
                map.back().push_back(j);
            }
        }
    }

    for (auto ele : map){
        for (auto elee : ele)
            std::cout << elee << ' ';
        std::cout << '\n';
    }

    std::vector<int> final(map.size());

    bool cont {true};
    while (cont) {
        //auto found = std::find(map.begin(), map.end(), [](auto v){return !v.size();});
        cont=false;

        for (size_t i {0}; i < map.size(); ++i){
            if (map.at(i).size() == 1){
                final.at(i) = map.at(i).at(0);
                cont = true;
                remove(map, map.at(i).at(0));
            }
        }
    }

    std::cout << '\n';

    for (auto ele : final)
        std::cout << ele << '\n';


    std::cout << '\n';
    size_t res {1};
    for(size_t i {0}; i < final.size(); ++i){
        if (final.at(i) < 6)
            res*=your_ticket.at(i);
    }
    std::cout << res << '\n';

    return 0;
}