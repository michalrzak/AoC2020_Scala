#include <map>
#include <string>
#include <iostream>

int main() {

    std::string input = "18,8,0,5,4,1,20";

    std::map<size_t, size_t> vals;

    size_t turn {1};

    size_t pos {0};
    while ((pos = input.find(',')) != std::string::npos){
        vals[std::stoi(input.substr(0, pos))] = turn++;
        input = input.substr(pos+1, std::string::npos);
    }

    size_t curr {vals[std::stoul(input)]};
    vals[std::stoul(input)] = turn++;

    size_t outp;

    for (; turn <= 30000000ul; ++turn){
        
        outp = curr;

        //std::cout << curr << '\n';
        //std::cout << turn << '\n';

        size_t temp {curr};

        if (vals[curr] == 0)
            curr = 0;
        else
            curr = turn - vals[curr];  

        vals[temp] = turn;

    }  

    std::cout << outp << '\n';

    return 0;
}