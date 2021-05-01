#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>


std::map<std::pair<int, int>, bool> one_day(std::map<std::pair<int, int>, bool>& tiles){
    
    std::map<std::pair<int, int>, bool> next_day;
    
    std::vector<std::pair<int, int>> dirs {{-1, -1}, {0, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 0}};
    
    //create whitetiles everywhere arround black tiles
    for (auto ele: tiles){
        if (ele.second)
            for (auto dir : dirs){
                if (!tiles[{ele.first.first + dir.first, ele.first.second + dir.second}])
                    tiles[{ele.first.first + dir.first, ele.first.second + dir.second}] = 0;
            }
    }
    
    //actual logic
    for (auto tile : tiles){
        next_day[tile.first] = tile.second;
        size_t count {0};
        for (auto dir : dirs){
            std::pair<int, int> curr {tile.first.first + dir.first, tile.first.second + dir.second};
            if (tiles.find(curr) != tiles.end())
                if (tiles.at(curr))
                    ++count;
        }
        
        if(tile.second && (count == 0 || count > 2))
            next_day.at(tile.first) = 0;
        
        if (!tile.second && count == 2)
            next_day.at(tile.first) = 1;
    }
    
    return next_day;
    
}


int main(){

    std::fstream input;
    input.open("input.txt");
    
    std::map<std::pair<int, int>, bool> tiles;
    
    std::string line;
    while (getline(input, line)){
        std::pair<int, int> start {0, 0};
        char prev {'e'};
        
        for (char c : line){
            switch(c){
                case 'e':
                    if (prev == 'e' || prev == 'w'){
                        --start.first;
                        --start.second;
                    }
                    if (prev == 's')
                        --start.second;
                    if (prev == 'n')
                        --start.first;
                    break;
                case 'w':
                    if (prev == 'e' || prev == 'w'){
                        ++start.first;
                        ++start.second;
                    }
                    if (prev == 's')
                        ++start.first;
                    if (prev == 'n')
                        ++start.second;
                    break;
            }
            prev = c;
        }
        
        if(tiles[start])
            std::cout << "flipped back\n";
        
        //tiles[start] = !tiles[start];
        if (tiles[start])
            tiles[start] = false;
        else
            tiles[start] = true;
        
        
    }
    
    size_t count {0};
    for (auto ele : tiles)
        if (ele.second)
            ++count;
        
    std::cout << count << '\n';
    
    
    for (size_t i {0}; i < 100; ++i){
        tiles = one_day(tiles);
        size_t count {0};
        for (auto ele : tiles)
            if (ele.second)
                ++count;
            
        std::cout << count << '\n';
    }
    
    input.close();
    
    return 0;
}
