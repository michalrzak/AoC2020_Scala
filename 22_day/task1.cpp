#include <iostream>
#include <fstream>
#include <queue>
#include <string>


int main(){
    
    std::queue<int> p1;
    std::queue<int> p2;
    
    std::fstream input;
    input.open("input.txt");
    
    std::string line;
    getline(input, line); //skip "Player 1"
    
    while (getline(input, line) && line != "")
        p1.push(stoi(line));
    
    getline(input, line); //skip "Player 2"
    while (getline(input, line) && line != "")
        p2.push(stoi(line));
    
    
    while (p1.size() && p2.size()){
        int p1card {p1.front()};
        int p2card {p2.front()};
        p1.pop();
        p2.pop();
        
        if (p1card > p2card){
            p1.push(p1card);
            p1.push(p2card);
        }
        else{
            p2.push(p2card);
            p2.push(p1card);
        }
        
    }
    
    std::queue<int>* winner;
    
    if (p1.size())
        winner = &p1;
    else
        winner = &p2;
    
    size_t res {0};
    size_t mult {winner->size()};
    
    while((mult=winner->size())){
        res+=winner->front()*mult;
        winner->pop();
    }
    
    std::cout << res << '\n';
        
    
    return 0;
}
