#include <fstream>
#include <iostream>
#include <string>
#include <map>


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
    
    input.close();
    
    return 0;
}
