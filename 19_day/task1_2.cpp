#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <regex>


/*bool match(std::string& input, std::map<int, Node>& rules, int matching){

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
}*/

std::vector<std::string> split(std::string inp, std::string c){
    std::vector<std::string> outp;
    
    size_t pos {0};
    while ((pos = inp.find(c)) != std::string::npos){
        outp.push_back(inp.substr(0, pos));
        inp = inp.substr(pos+c.length(), std::string::npos);
    }
    outp.push_back(inp);
    return outp;
}



std::string to_regex(std::string inp, const std::map<int, std::string>& rules){
    std::string outp;
    auto v {split (inp, " ")};

    if (rules.at(8) == inp)
        return "(" + to_regex(rules.at(42), rules) + ")+";
    if (rules.at(11) == inp){
        std::string temp1 {to_regex(rules.at(42), rules)};
        std::string temp2 {to_regex(rules.at(31), rules)};

        for(size_t i {0}; i < 8; ++i){
            if (i != 0)
                outp += "|";

            for (size_t j {0}; j <= i;++j)
                outp += temp1;

            for (size_t j {0}; j <= i;++j)
                outp += temp2;

        }
        return "(" + outp + ")";
    }

    for (auto item : v){
        //std::cout << item << "\n";
        if (item.at(0) == '"')
            outp += item.at(1);
        else if (item.at(0) == '|')
            outp += "|";
        else
            outp += to_regex(rules.at(std::stoi(item)), rules);
    }
    //std::cout << outp << '\n';

    if (v.at(0).at(0) == '"' && v.size() == 1)  
        return outp;
    return "(" + outp + ")";

}


int main(){

    std::fstream input;
    input.open("input.txt");

    std::map<int, std::string> rules;

    std::string line {"start the while :)"};
    while(getline(input, line) && line != ""){

        int index {std::stoi(line.substr(0, line.find(' ')-1))};

        rules.insert({index, ""});

        line = line.substr(line.find(' ')+1, std::string::npos);
        rules.at(index) = line;
    }

    std::regex re {to_regex(rules.at(0), rules)};

    for (auto& rule : rules){
        std::string regex (to_regex(rule.second, rules));
        std::cout << regex << '\n';
    }


    size_t count {0};
    while(getline(input, line)){
        std::cout << line << '\n';
        std::smatch m;
        if (std::regex_match(line, re))
            ++count;
        
    }

    std::cout << count << '\n';


    input.close();
    return 0;
}//((a)(((a)(a))|((b)(b))((a)(b))|((b)(a)))|(((a)(b))|((b)(a))((a)(a))|((b)(b)))(b))