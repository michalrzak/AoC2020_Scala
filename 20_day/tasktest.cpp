#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>


std::string getColumn(const std::vector<std::string>& tiles, size_t index){
    std::string outp;
    for (std::string row : tiles)
        outp += row.at(index);
    return outp;
}

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
    input.open("input.txt");


    std::map<int, std::vector<std::string>> tiles;

    int currentTile {-1};

    std::string line;
    while (getline(input, line)){
        if (currentTile == -1){
            line = line.substr(line.find(' ')+1, std::string::npos);
            currentTile = std::stoi(line);
            tiles.insert({currentTile, {}});
        }
        else  if (line == "")
            currentTile = -1;
        else
            tiles.at(currentTile).push_back(line);
    }
    input.close();

    std::string line {".#..#..###"};

    for (auto tile : tiles){
        for (int i {0}; i < 8)
    }

    return 0;
}