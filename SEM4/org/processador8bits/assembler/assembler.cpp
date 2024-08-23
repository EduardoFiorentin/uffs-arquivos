#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <bitset>

using namespace std;

string gerenate_bitset(int value) {
    return bitset<6>{value}.to_string();
}


vector<string> substitute(vector<string> instructions) {

    vector<string> new_instructions; 

    // regras:
    vector<pair<regex, string>> rules = {
        
        // remover espaços 
        pair<regex, string> { regex{ "[ \t]" }, "" }, 

        // trocar identificadores
        pair<regex, string> { regex{ "ldmr" }, "000" }, 
        pair<regex, string> { regex{ "ldrm" }, "001" }, 
        pair<regex, string> { regex{ "add" }, "010" },
        pair<regex, string> { regex{ "sub" }, "011" },
        pair<regex, string> { regex{ "mul" }, "100" },
        pair<regex, string> { regex{ "div" }, "101" },
        pair<regex, string> { regex{ "lct" }, "110" }
    }; 

    for (int i = 0; i < rules.size(); i++) {
        for (int j = 0; j < instructions.size(); j++) {

            instructions[j] = regex_replace(instructions[j], rules[i].first, rules[i].second); 
        }
    }



    return instructions; 
}

int main() {

    string a = "lct r0, 50;";
    string b = "lct r1, 10;";
    string c = "add r2, r0, r1;";
    string d = "add r2, r0, r1;";
    string e = "ldrm r2, m0;";
    string f = "ldmr r3, m0; ";
    string g = "sub r4, r3, r1; ";
    string h = "ldrm r4, m1;";

    
    vector<string> instructions = {a, b, c, d, e, f, g, h}; 
    vector<string> new_instructions; 


    new_instructions = substitute(instructions); 

     
    // matches words beginning by "Geek"

    // string s = "Ttste am teste";

    
     
    // // regex_replace() for replacing the match with 'geek' 
    // cout << std::regex_replace(s, regex {"am"}, "geek");
     
    // string result;
     
    // // regex_replace( ) for replacing the match with 'geek'
    // // regex_replace(back_inserter(result), s.begin(), s.end(), r,  "geek");
 
    // cout << result; 

    int i = 1;
    for (string instruction: new_instructions) {
        cout << i << " : " << instruction << endl; 
        i++; 
    }

    return 0; 
}