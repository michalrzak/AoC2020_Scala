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


    int topRight {-1};
    int topLeft {-2};
    int botRight {-3};
    int botLeft {-4};

    for (auto tileSet : tiles){

        for (int i {0}; i < 8; ++i){
            std::vector<std::string> altTile;
            switch(i){
                case 0:
                    altTile = tileSet.second;
                    break;
                case 1:
                    altTile = rotate(tileSet.second, 2);
                    break;
                case 2:
                    altTile = flip(tileSet.second);
                    break;
                case 3:
                    altTile = flip(rotate(tileSet.second, 2));
                    break;
                case 4:
                    altTile = rotate(tileSet.second, 1);
                    break;
                case 5:
                    altTile = flip(rotate(tileSet.second, 1));
                    break;
                case 6:
                    altTile = rotate(rotate(tileSet.second, 2), 1);
                    break;
                case 7:
                    altTile = flip(rotate(rotate(tileSet.second, 2), 1));
                    break;
            }

            //topLeft
            bool found {true};
            if (topLeft == -2){
                for (auto tS : tiles){
                    for (int j {0}; j < 8; ++j){
                        std::vector<std::string> altTS;
                        switch(j){
                            case 0:
                                altTS = tS.second;
                                break;
                            case 1:
                                altTS = rotate(tS.second, 2);
                                break;
                            case 2:
                                altTS = flip(tS.second);
                                break;
                            case 3:
                                altTS = flip(rotate(tS.second, 2));
                                break;
                            case 4:
                                altTS = rotate(tS.second, 1);
                                break;
                            case 5:
                                altTS = flip(rotate(tS.second, 1));
                                break;
                            case 6:
                                altTS = rotate(rotate(tS.second, 2), 1);
                                break;
                            case 7:
                                altTS = flip(rotate(rotate(tS.second, 2), 1));
                                break;
                        }


                        if (tS.first == tileSet.first)
                            continue;

                        if (altTS.at(0) == altTile.at(altTile.size()-1)){
                            std::cout << altTS.at(0) << '\n';
                            found = false;
                            break;
                        }

                        if (getColumn(altTile, 0) == getColumn(altTS, altTile.size()-1)){
                            std::cout << altTile.at(0) << '\n';
                            found = false;
                            break;
                        }
                    }
                    if (!found)
                        break;
                }
                if (found && tileSet.first != topRight && tileSet.first != botLeft && tileSet.first != botRight)
                    topLeft = tileSet.first;
            }
            
            //topRight
            found = true;
            if (topRight == -1){
                for (auto tS : tiles){
                    for (int j {0}; j < 8; ++j){
                        std::vector<std::string> altTS;
                        switch(j){
                            case 0:
                                altTS = tS.second;
                                break;
                            case 1:
                                altTS = rotate(tS.second, 2);
                                break;
                            case 2:
                                altTS = flip(tS.second);
                                break;
                            case 3:
                                altTS = flip(rotate(tS.second, 2));
                                break;
                            case 4:
                                altTS = rotate(tS.second, 1);
                                break;
                            case 5:
                                altTS = flip(rotate(tS.second, 1));
                                break;
                            case 6:
                                altTS = rotate(rotate(tS.second, 1), 2);
                                break;
                            case 7:
                                altTS = flip(rotate(rotate(tS.second, 1), 2));
                                break;
                        }


                        if (tS.first == tileSet.first)
                            continue;

                        if (altTS.at(0) == altTile.at(altTile.size()-1)){
                            found = false;
                            break;
                        }

                        if (getColumn(altTile, altTile.size()-1) == getColumn(altTS, 0)){
                            found = false;
                            break;
                        }
                    }
                    if (!found)
                        break;
                }
                if (found && tileSet.first != topLeft && tileSet.first != botLeft && tileSet.first != botRight)
                    topRight = tileSet.first;
            }

            //botLeft
            found = true;
            if (botLeft == -4){
                for (auto tS : tiles){
                    for (int j {0}; j < 8; ++j){
                        std::vector<std::string> altTS;
                        switch(j){
                            case 0:
                                altTS = tS.second;
                                break;
                            case 1:
                                altTS = rotate(tS.second, 2);
                                break;
                            case 2:
                                altTS = flip(tS.second);
                                break;
                            case 3:
                                altTS = flip(rotate(tS.second, 2));
                                break;
                            case 4:
                                altTS = rotate(tS.second, 1);
                                break;
                            case 5:
                                altTS = flip(rotate(tS.second, 1));
                                break;
                            case 6:
                                altTS = rotate(rotate(tS.second, 1), 2);
                                break;
                            case 7:
                                altTS = flip(rotate(rotate(tS.second, 1), 2));
                                break;
                        }


                        if (tS.first == tileSet.first)
                            continue;

                        if (altTS.at(altTS.at(0).size()-1) == altTile.at(altTile.at(0).size()-1)){
                            found = false;
                            break;
                        }

                        if (getColumn(altTile, 0) == getColumn(altTS, 0)){
                            found = false;
                            break;
                        }
                    }
                }
                if (found && tileSet.first != topLeft && tileSet.first != topRight && tileSet.first != botRight)
                    botLeft = tileSet.first;
            }
            
            //botRight
            found = true;
            if (botRight == -3){
                for (auto tS : tiles){
                    for (int j {0}; j < 8; ++j){
                        std::vector<std::string> altTS;
                        switch(j){
                            case 0:
                                altTS = tS.second;
                                break;
                            case 1:
                                altTS = rotate(tS.second, 2);
                                break;
                            case 2:
                                altTS = flip(tS.second);
                                break;
                            case 3:
                                altTS = flip(rotate(tS.second, 2));
                                break;
                            case 4:
                                altTS = rotate(tS.second, 1);
                                break;
                            case 5:
                                altTS = flip(rotate(tS.second, 1));
                                break;
                            case 6:
                                altTS = rotate(rotate(tS.second, 1), 2);
                                break;
                            case 7:
                                altTS = flip(rotate(rotate(tS.second, 1), 2));
                                break;
                        }


                        if (tS.first == tileSet.first)
                            continue;

                        if (altTS.at(altTS.at(0).size()-1) == altTile.at(altTile.at(0).size()-1)){
                            found = false;
                            break;
                        }

                        if (getColumn(altTile, altTile.size()-1) == getColumn(altTS, altTS.size()-1)){
                            found = false;
                            break;
                        }
                    }
                    if (found == false)
                        break;
                }
                //std::cout << tileSet.first << ' ' << found << '\n';
                if (found && tileSet.first != topLeft && tileSet.first != topRight && tileSet.first != botLeft)
                    botRight = tileSet.first;
            }
        
        }
        
    }

    //auto test {rotate(flip(tiles.at(2971)))};
    //for (auto row : test)
    //   /  std::cout << row << '\n';

    //std::cout << getColumn(rotate(flip(tiles.at(2971))), tiles.at(2971).size()-1) << '\n';
   // std::cout << rotate(flip(tiles.at(2971))).at(tiles.at(2971).at(0).size()-1) << '\n';


    std::cout << static_cast<size_t>(topLeft) * topRight * botLeft * botRight << '\n';
    std::cout << topLeft << ' ' << topRight << ' ' << botLeft << ' ' << botRight << '\n';

    return 0;
}