#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

int main(){

    std::fstream input;
    input.open("input.txt");

    std::string line;

    unsigned long zero_mask {0};
    unsigned long one_mask {0};
    std::vector<unsigned long> x_mask;

    std::map<unsigned long, unsigned long> mem;

    //getline(input, line);
    while (getline(input, line)){
        size_t pos = line.find(" = ");
        
        if (line.substr(0, pos) == "mask"){
            
            zero_mask = (1ul<<36)-1;
            one_mask = 0ul;
            x_mask.clear();
            x_mask.push_back(0);

            std::string mask {line.substr(pos+3, std::string::npos)};
            //std::cout << mask << '\n';
            for (size_t i {0}; i < mask.size(); ++i){
                if (mask.at(i) == 'X')
                    zero_mask = zero_mask ^ (1ul << (mask.size()-i-1));

                if (mask.at(i) == '1')
                    one_mask = one_mask ^ (1ul << (mask.size()-i-1));

                if (mask.at(i) == 'X'){
                    unsigned long curr {1ul << (mask.size()-i-1)};
                    size_t max {x_mask.size()};
                    for (size_t j {0}; j < max; ++j){
                        x_mask.push_back(x_mask.at(j) ^ curr);
                        std::cout << "Pushing: " << x_mask.at(j) << ' ' << curr << ' ' << (x_mask.at(j) ^ curr) << '\n';
                    }

                }
            }


        } else {
            unsigned long value {std::stoul(line.substr(pos+3, std::string::npos))};
            
            size_t first {line.substr(0, pos).find('[')};

            unsigned long key {(std::stoul(line.substr(first+1, pos-5)) & zero_mask) | one_mask};

            std::cout << key << '\n';
            

            for (auto mask : x_mask){
                std::cout << "Mask: " <<  mask << ' ' << (key ^ mask) << '\n';
                if (mem.find(key ^ mask) == mem.end())
                    mem.insert({key ^ mask, 0});

                mem.at(key ^ mask) = value;
            }
            
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