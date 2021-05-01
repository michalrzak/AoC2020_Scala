#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <map>

std::list<size_t>::iterator increment(std::list<size_t>::iterator it, int by, std::list<size_t>& l){
    for (int i {0}; i < by; ++i){
        ++it;
        if (it == l.end())
            it = l.begin();
    }
    return it;
}


int main(){

    std::string input {"653427918"};
    
    std::list<size_t> cups;
    std::map<size_t, std::list<size_t>::iterator> cupsmap;
    size_t max {1000000ul};
    size_t min {1};
    auto inserter {cups.begin()};
    for (char c : input){
        cups.push_back(c-'0');
        if (inserter == cups.end())
            inserter = cups.begin();
        else
            ++inserter;
        
        cupsmap[c-'0'] = inserter;
    }
    
    for (size_t i {input.size()+1}; i <= 1000000ul; ++i){
        cups.push_back(i);
        cupsmap[i] = ++inserter;
    }
    
    
    
    //for (auto ele : cupsmap)
        //std::cout << ele.first << ' ' << *(ele.second) << '\n';
    
    //std::cout << "\n Printing cups\n";
    //for (auto ele : cups)
      //  std::cout << ele << ' ';
   // std::cout << '\n';
    
    //game start
    auto ccup {cups.begin()};
    //std::cout << *ccup << '\n';
    for (size_t i {0}; i < 10000000ul; ++i){
        if(i % 1000 == 0)
            std::cout << i << '\n';
        
        //std::cout << *ccup << '\n';
        auto it1 {increment(ccup, 1, cups)};
        auto it2 {increment(ccup, 2, cups)};
        auto it3 {increment(ccup, 3, cups)};
        
        size_t ele1 {*it1};
        size_t ele2 {*it2};
        size_t ele3 {*it3};
        
        cups.erase(it1);
        cups.erase(it2);
        cups.erase(it3);
        
        
        size_t find {(*ccup)-1};
        if (!find)
            find=max;
        //std::cout << find << '\n';
        std::list<size_t>::iterator empl;
        
        
        
        while ((find == ele1 || find == ele2 || find == ele3)) --find?find:(find=max);
        //std::cout << "Find after: "<<find<<'\n';
        
        empl = cupsmap[find];
        //std::cout << "Find:" << find << '\n';
        //std::cout << *empl << '\n';
        
        //while ((empl = std::find(cups.begin(), cups.end(), --find?find:(find=max))) == cups.end() && (*empl != ele1 || *empl != ele2 || *empl != ele3));
        

        
        if (find != *empl){
                    std::cout << "Find:" << find << '\n';
        std::cout << "Destination: " <<  *empl << '\n';
            std::cin >> find;
        }
            
        
            
        
        //std::cout << *ccup << '\n';
        ++empl;
        empl = cups.insert(empl, ele3);
        cupsmap[ele3] = empl;
        empl = cups.insert(empl, ele2);
        cupsmap[ele2] = empl;
        empl = cups.insert(empl, ele1);
        cupsmap[ele1] = empl;
    
        ccup = increment(ccup, 1, cups);
        
        /*for (auto ele : cups)
            std::cout << ele << ' ';
        std::cout << '\n';
        
        for (auto ele : cupsmap)
            std::cout << ele.first << ' ' << *(ele.second) << '\n';*/
        
    }
    
    std::cout << "I finnshed\n";
    
    for (auto ele : cupsmap){
        if (ele.first != *ele.second)
            std::cout << ele.first << ' ' << *ele.second << "dont match\n";
    }
    
    std:: cout << *cupsmap[1] << ' ' << *increment(cupsmap[1], 1, cups) << ' ' << *(increment(cupsmap[1], 2, cups)) << '\n';
    
    auto one {std::find(cups.begin(), cups.end(), 1)};
    for (size_t i {0}; i < 8; ++i)
        std::cout << *(one=increment(one, 1, cups));
        
    std::cout << '\n';    
    
    return 0;
}
