#include <iostream>
#include <string>
#include <list>
#include <algorithm>

std::list<int>::iterator increment(std::list<int>::iterator it, int by, std::list<int>& l){
    for (int i {0}; i < by; ++i){
        ++it;
        if (it == l.end())
            it = l.begin();
    }
    return it;
}


int main(){

    std::string input {"653427918"};
    
    std::list<int> cups;
    int max {0};
    int min {10};
    for (char c : input){
        cups.push_back(c-'0');
        if (c-'0' > max)
            max = c-'0';
        if (c-'0' < min)
            min = c-'0';
    }
    
    
    
    for (auto ele : cups)
            std::cout << ele << ' ';
        std::cout << '\n';
    
    //game start
    auto ccup {cups.begin()};
    for (size_t i {0}; i < 100; ++i){
        
        auto it1 {increment(ccup, 1, cups)};
        auto it2 {increment(ccup, 2, cups)};
        auto it3 {increment(ccup, 3, cups)};
        
        int ele1 {*it1};
        int ele2 {*it2};
        int ele3 {*it3};
        
        cups.erase(it1);
        cups.erase(it2);
        cups.erase(it3);
        
        
        int find {*ccup};
        std::cout << find << '\n';
        std::list<int>::iterator empl;
        while ((empl = std::find(cups.begin(), cups.end(), --find?find:(find=max))) == cups.end() && (*empl != ele1 || *empl != ele2 || *empl != ele3));
        
        ++empl;
        empl = cups.insert(empl, ele3);
        empl = cups.insert(empl, ele2);
        empl = cups.insert(empl, ele1);
    
        ccup = increment(ccup, 1, cups);
        
        for (auto ele : cups)
            std::cout << ele << ' ';
        std::cout << '\n';
    }
    
    auto one {std::find(cups.begin(), cups.end(), 1)};
    for (size_t i {0}; i < 8; ++i)
        std::cout << *(one=increment(one, 1, cups));
        
    std::cout << '\n';    
    
    return 0;
}
