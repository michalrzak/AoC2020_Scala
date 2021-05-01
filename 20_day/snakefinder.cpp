#include <string>
#include <vector>
#include <fstream>
#include <iostream>


std::vector<std::string> rotate(const std::vector<std::string>& tiles, int times){
    std::vector<std::string> outp;

    switch (times){
        case 1:
            for (size_t i {0}; i < tiles.size(); ++i){
                outp.push_back("");
                for (size_t j {0}; j < tiles.size(); ++j){
                    outp.back()+=tiles.at(j).at(i);
                }
            }
            break;
        
        case 2:
            for(size_t i{tiles.size()}; i > 0; --i)
                outp.push_back(tiles.at(i-1));
            break;
    }

    
    return outp;
}

std::vector<std::string> flip(const std::vector<std::string>& tiles){
    std::vector<std::string> outp;

    for(std::string line : tiles){  
        outp.push_back("");
        std::copy(line.crbegin(), line.crend(), std::back_inserter(outp.back()));
    }
    return outp;
}

std::vector<std::string> rot(const std::vector<std::string>& tS, int j){
    std::vector<std::string> altTS;
    switch(j){
        case 0:
            altTS = tS;
            break;
        case 1:
            altTS = rotate(tS, 2);
            break;
        case 2:
            altTS = flip(tS);
            break;
        case 3:
            altTS = flip(rotate(tS, 2));
            break;
        case 4:
            altTS = rotate(tS, 1);
            break;
        case 5:
            altTS = flip(rotate(tS, 1));
            break;
        case 6:
            altTS = rotate(rotate(tS, 1), 2);
            break;
        case 7:
            altTS = flip(rotate(rotate(tS, 1), 2));
            break;
    }
    return altTS;
}



int main(){

    std::fstream input;
    input.open("field.txt");


    std::vector<std::string> field;
    
    std::string line;
    while(getline(input, line)){
        field.push_back(line);
    }


    std::vector<std::string> temp {rot(field, 1)};
    for (auto ele : temp)
        std::cout << ele << '\n';

    std::vector<std::pair<int, int>> snake = {{-1, -19}, {0, -18}, {0, -15}, {-1, -14}, {-1, -13}, {0, -12}, {0, -9}, {-1, -8}, {-1, -7}, {0, -6}, {0, -3}, {-1, -2}, {-1, -1}, {-2, -1}, {-1, 0}};

    size_t count {0};
    for (int i {0}; i < 8; ++i){
        count = 0;
        std::vector<std::string> f {rot(field, i)};
        for (size_t y {2}; y < 96; ++y){
            for (size_t x{19}; x < 96; ++x){
                bool found {true};
                for (auto ele : snake){
                    if (f.at(y+ele.first).at(x+ele.second) != '#'){
                        found = false;
                        break;
                    }
                }
                if (found)
                    ++count;
            }
        }
        std::cout << count << '\n';
        if (count != 0)
            break;
    }

    size_t all {0};
    for (auto ele : field)
        for (char c : ele)
            if (c == '#')
                ++all;

    std::cout << all - count*snake.size() << '\n';
    std::cout << all << '\n';

    return 0;
}