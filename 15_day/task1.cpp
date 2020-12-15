#include <map>
#include <string>
#include <iostream>

int main() {

    std::string input = "18,8,0,5,4,1,20";

    std::map<int, int> vals;

    int turn {1};

    size_t pos {0};
    while ((pos = input.find(',')) != std::string::npos){
        vals[std::stoi(input.substr(0, pos))] = turn++;
        input = input.substr(pos+1, std::string::npos);
    }

    int curr {vals[std::stoi(input)]};
    vals[std::stoi(input)] = turn++;

    for (; turn <= 2020; ++turn){
        
        std::cout << curr << '\n';

        int temp {curr};

        if (vals[curr] == 0)
            curr = 0;
        else
            curr = turn - vals[curr];  

        vals[temp] = turn;

    }  

    return 0;
}