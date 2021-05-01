#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <map>


bool queue_equals(std::queue<int> lop, std::queue<int> rop){
    
    if (lop.size() != rop.size())
        return false;
    
    while (lop.size()){
        if (lop.front() != rop.front())
            return false;
        lop.pop();
        rop.pop();
    }
    return true;
}

void queue_print(std::queue<int> op){
    while (op.size()){
        std::cout << op.front() << ' ';
        op.pop();
    }
    std::cout << '\n';
}


bool recursive_combat(std::queue<int> p1, std::queue<int> p2){ //True = Player 1 won

    std::map<std::pair<std::queue<int>, std::queue<int>>, bool> past_state;

    while (p1.size() && p2.size()){
        bool ret {false};
        
        if (past_state[{p1, p2}])
            return true;
            
        past_state[{p1, p2}] = true;
            
        
        
        int c1 {p1.front()};
        int c2 {p2.front()};
        p1.pop();
        p2.pop();

        if (c1 < p1.size()+1 && c2 < p2.size()+1){
            //create new queue of right size
            std::queue <int> newp1;
            std::queue <int> newp2;
            std::queue <int> cp1 {p1};
            std::queue <int> cp2 {p2};
            for (size_t i {0}; i < c1; ++i){
                newp1.push(cp1.front());
                cp1.pop();
            }
            for (size_t i {0}; i < c2; ++i){
                newp2.push(cp2.front());
                cp2.pop();
            }
            
            
            if (recursive_combat(newp1, newp2)){
                p1.push(c1);
                p1.push(c2);
                //std::cout << "p1 " << c1 << ' ' << c2 << "\n";
            }
            else {
                p2.push(c2);
                p2.push(c1);
                //std::cout << "p2 " << c1 << ' ' << c2 << "\n";
            }
        }
        else{
            if (c1 > c2){
                p1.push(c1);
                p1.push(c2);
                //std::cout << "p1 " << c1 << ' ' << c2 << "\n";
            }
            else{
                p2.push(c2);
                p2.push(c1);
                //std::cout << "p2 " << c1 << ' ' << c2 << "\n";
            }
        }
    }
    
    //std::cout << "returning\n";
    std::queue<int>* winner;
    bool ret {false};
    if (p1.size()){
        winner = &p1;
        ret = true;
    }
    else
        winner = &p2;
        
    size_t res {0};
    size_t mult {winner->size()};
    std::cout << mult << '\n';
    queue_print(*winner);
    while((mult=winner->size())){
        res+=winner->front()*mult;
        winner->pop();
    }
    std::cout << res << '\n';
    return ret;
}



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
    

    recursive_combat(p1, p2);
}
