#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>

int main(){

    std::fstream input;
    input.open("input.txt");

    std::string line;

    unsigned long long zero_mask {0};
    unsigned long long one_mask {0};

    std::map<std::string, unsigned long> mem;

    //getline(input, line);
    while (getline(input, line)){
        size_t pos = line.find(" = ");
        if (line.substr(0, pos) == "mask"){
            zero_mask = (1ul<<36)-1;
            one_mask = 0ul;
            std::string mask {line.substr(pos+3, std::string::npos)};
            std::cout << mask << '\n';
            for (size_t i {0}; i < mask.size(); ++i){
                if (mask.at(i) == '0')
                    zero_mask = zero_mask ^ (1ul << (mask.size()-i-1));

                if (mask.at(i) == '1')
                    one_mask = one_mask ^ (1ul << (mask.size()-i-1));
            }


        } else {
            unsigned long value {std::stoul(line.substr(pos+3, std::string::npos))};
            
            size_t first {line.substr(0, pos).find('[')};

            std::string key {line.substr(first+1, pos-5)};
            
            unsigned long insert {(value & zero_mask) | one_mask};
            if (mem.find(key) == mem.end())
                mem.insert({key, 0});

            mem.at(key) = insert;
        }
    }

    unsigned long res {0};
    for (auto ele : mem) {
        std::cout << ele.first << ' ' << ele.second << '\n';
        res+=ele.second;
    }

    std::cout << res << '\n';

    return 0;
}