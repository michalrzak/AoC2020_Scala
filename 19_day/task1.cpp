#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>


struct Node {
    std::string val;
    Node* def {nullptr};
    Node* alt {nullptr};
};



bool match(std::string& input, std::map<int, Node>& rules, int matching){

    //std::cout << "em\n";

    Node* curr {&rules.at(matching)};
//std::cout << curr->def->val << '\n';

    while(curr->def != nullptr){
        std::cout << "entering: " << curr->def->val.at(0) << '\n';
        std::cout << "input: " << input << '\n';
        if (curr->def->val.at(0) > '9'){ //if is letter
            if(input.at(0) == curr->def->val.at(0)){
                input = input.substr(1, std::string::npos);
                curr = curr->def;
            }
            else if(curr->alt != nullptr && curr->alt->val.at(0) > '9' && input.at(0) == curr->alt->val.at(0)){
                input = input.substr(1, std::string::npos);
                curr = curr->alt;
            } else if (curr->alt != nullptr && curr->alt->val.at(0) <= '9' && match(input, rules, std::stoi(curr->alt->val))){
                curr = curr->alt;
            } else {
                return false;
            }
        } else if (curr->def->val.at(0) <= '9'){ //if is refernce
            std::cout << "This is it: " <<  curr->def->val << '\n';
            std::string copy {input};
            if(match(input, rules, std::stoi(curr->def->val)))
                curr = curr->def;
            else { std::cout << curr->alt->val << "fadfa\n"; input=copy; if(curr->alt != nullptr && curr->alt->val.size()!=0 && curr->alt->val.at(0) > '9' && input.at(0) == curr->alt->val.at(0)){
                input = input.substr(1, std::string::npos);
                curr = curr->alt;
            } else if (curr->alt != nullptr && curr->alt->val.size()!=0 && curr->alt->val.at(0) <= '9' && match(input, rules, std::stoi(curr->alt->val))){
                input = input.substr(1, std::string::npos);
                curr = curr->alt;
            } else {
                return false;
            }}
        }
        std::cout << curr->val << "FADFA" << '\n' << input << '\n';
    }

    return true;
}



int main(){

    std::fstream input;
    input.open("input.txt");

    std::map<int, Node> rules;

    std::string line {"start the while :)"};
    while(getline(input, line) && line != ""){

        int index {std::stoi(line.substr(0, line.find(' ')-1))};

        rules.insert({index, {""}});
        Node* curr {&rules.at(index)};

        line = line.substr(line.find(' ')+1, std::string::npos);

        size_t pos {0};
        while ((pos = line.find(' ')) != std::string::npos){
            std::cout << line << '\n';
            std::string val {line.substr(0, pos)};
            std::cout << val << '\n';

            if (val.at(0) == '\"'){
                curr->def = new Node;
                curr->def->val = val.at(1);
                curr = curr->def;
            }
            else if (val.at(0) == '|') {
                line = line.substr(1, std::string::npos);
                pos = line.find(' ');
                val = line.substr(0, pos);
                
                rules.at(index).alt = new Node;
                rules.at(index).alt->val = val;
                curr = rules.at(index).alt;
            }
            else{
                curr->def = new Node;
                curr->def->val = val;
                curr = curr->def;
            }
            line = line.substr(pos+1, std::string::npos);
        }
        curr->def = new Node;
        if (line.at(0) == '"')
            curr->def->val = line.at(1);
        else
            curr->def->val = line;


    }


    size_t count {0};
    while(getline(input, line)){
        std::string linecopy {line};
        std::cout << line << '\n';
        if (match(line, rules, 0) && line.size() == 0)
            ++count;
        std::cout << line << ' ' << linecopy << '\n';
    }

    std::cout << count << '\n';

    input.close();
    return 0;
}