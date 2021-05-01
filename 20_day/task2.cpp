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
    std::cout << tiles.size() << '\n';

    std::vector<std::vector<int>> map(12);
    std::vector<std::vector<int>> mapr(12);


    for (auto& v : map)
        for (size_t i {0}; i < 12; ++i)
            v.push_back(0);
    

    for (auto& v : mapr)
        for (size_t i {0}; i < 12; ++i)
            v.push_back(0);
    
    map.at(0).at(0) = 1699;
    mapr.at(0).at(0) = 3;


    std::map<int, bool> placed;
    placed[1699] = true;

    //while(placed < 144){
        for (size_t y {0}; y < 12; ++y){
            std::cout << "helo?\n";
            for (size_t x {0}; x < 12; ++x){
                if (x == 0 && y == 0)
                    continue;

            

                bool found {false};
                for (auto tile : tiles){
                    std::cout << tile.first << '\n';
                    std::cout << placed[tile.first] << '\n';
                    if (placed[tile.first])
                        continue;
                    for (size_t i {0}; i < 8; ++i){
                        std::vector<std::string> ct {rot(tile.second, i)};
                        //for (auto ele : ct)
                        //    std::cout << ele << '\n';
                        if (x!=0){
                            //std::cout << y << ' ' << x << '\n';
                            std::cout << map.at(y).at(x-1) << '\n';
                            std::cout << getColumn(ct, 0) << '\n';
                            std::cout << getColumn(rot(tiles.at(map.at(y).at(x-1)), mapr.at(y).at(x-1)), 9) << '\n';
                            if(getColumn(rot(tiles.at(map.at(y).at(x-1)), mapr.at(y).at(x-1)), 9) == getColumn(ct, 0)){
                                map.at(y).at(x) = tile.first;
                                mapr.at(y).at(x) = i;
                                placed[tile.first] = true;
                                found = true;
                                std::cout << tile.first << '\n';
                                std::cout << i << '\n';
                                std::cout << y << ' ' << x<< '\n';
                                //std::cin >> currentTile;
                                break;
                            }

                        }else
                            if (rot(tiles.at(map.at(y-1).at(x)), mapr.at(y-1).at(x)).at(9) == ct.at(0)){
                                map.at(y).at(x) = tile.first;
                                mapr.at(y).at(x) = i;
                                placed[tile.first] = true;
                                found = true;
                                std::cout << y << ' ' << x<< '\n';
                                break;
                            }
                    }
                    if (found)
                        break;
                }
            }
        }
        //std::cout << placed << '\n';
        
    //}


 for (size_t y {0}; y < 12; ++y){
        for (size_t i {1}; i < 9; ++i){
            for(size_t x {0}; x < 12; ++x){
                
                //std::cout << rot(tiles.at(map.at(y).at(x)), mapr.at(y).at(x)).at(i);
                    std::cout << rot(tiles.at(map.at(y).at(x)), mapr.at(y).at(x)).at(i).substr(1, 8);
                                
            }
            std::cout << '\n';
        }
    }


/*
    for (size_t y {0}; y < 12; ++y){
        for (size_t i {0}; i < 10; ++i){
            for(size_t x {0}; x < 12; ++x){
                std::cout << rot(tiles.at(map.at(y).at(x)), mapr.at(y).at(x)).at(i);
            }
            std::cout << '\n';
        }
    }
*/

    return 0;
}