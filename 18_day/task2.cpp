#include <string>
#include <fstream>
#include <iostream>


size_t solve(std::string& equation){ //destroys the string; not creating copy for efficiency
    size_t res {0};
    short operation{0}; //0 - plus; 1 - mult 
    
    while(equation.size()!=0 && equation.at(0)!=')'){
        
        if(equation.at(0) == '('){
            equation = equation.substr(1, std::string::npos);
            switch (operation){
                case 0:
                    res += solve(equation);
                    break;
                case 1:
                    res *= solve(equation);
                    break;
            }
        }
        else if (equation.at(0) == '+'){
            operation = 0;
        }
        else if (equation.at(0) == '*'){
            operation = 1;
            equation = equation.substr(1, std::string::npos);
            res*=solve(equation);
            break;
        }
        else if (equation.at(0) >= '0' && equation.at(0) <= '9'){
            switch (operation){
                case 0:
                    res += (equation.at(0)-'0');
                    break;
                case 1:
                    res *= (equation.at(0)-'0');
                    break;
            }
        }

        equation = equation.substr(1, std::string::npos);
    }

    return res;
}

int main () {

    std::fstream input;
    input.open("input.txt");

    std::string line;

    size_t res {0};
    while(getline(input, line)){
        res += solve(line);
    }

    std::cout << res << '\n';

    return 0;
}
