#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct transition{
    char symbol;             
    int next_state;         
};
 
struct state{
    int id;                   
    bool is_accepting;  
};

vector<char> symbols;                    
vector<string> input_strings;
unordered_map<int, vector<transition>> transition_table; 

bool process_string(vector<state> states, string input, string currtn, int indx_s, int indx_i);
vector<pair<int,bool> > find_paths(char letter, int index);
bool is_terminal_symbol(string word);

int main(){

    // First Line: number of states
    int n_states;
    cin >> n_states;
    vector<state> states(n_states);

    for(int i = 0; i<n_states; i++){
        states[i].id = i;
        states[i].is_accepting = false;
    }

    // Second Line: terminal symbols 
    int n_symbols;
    cin >> n_symbols;

    for(int i = 0; i < n_symbols; i++){
        char buffer_char;
        cin >> buffer_char;
        symbols.push_back(buffer_char);
    }
   
    // Third Line: initial states
    int n_initial_states;
    cin >> n_initial_states;

    // Fourth Line: acceptance states
    int n_acceptance_states;
    cin >> n_acceptance_states;

    for(int i = 0; i < n_acceptance_states; i++){
        int buffer_int;
        cin >> buffer_int;
        states[buffer_int].is_accepting = true;
    }

    // Fifth Line: number of transitions
    int n_transitions;
    cin >> n_transitions;

    // Nexts N Lines: read the transitions
    for(int i = 0; i < n_transitions; i++){
        int from_state, to_state;
        char symbol;

        cin>> from_state >> symbol >> to_state;
        transition_table[from_state].push_back({symbol, to_state});
    }

    // Inputs
    int n_input_strings;
    cin >> n_input_strings;

    vector<string> input_strings;
    for(int i = 0; i < n_input_strings; i++){
        string buffer_str;
        cin >> buffer_str;
        input_strings.push_back(buffer_str);
    }
        
    for(auto input: input_strings){
        for(int i = 0; i<n_initial_states; i++)
            (process_string(states, input, "-", i, 0))? cout << "aceita\n" : cout << "rejeita\n";
    }

    return 0;
}


// backtracking
bool process_string(vector<state> states, string input, string currtn, int indx_s, int indx_i) {
    if(states[indx_s].is_accepting && currtn == input && is_terminal_symbol(currtn)){
        return true;
    }else{
        if(currtn == "-") currtn.clear();

        vector<pair<int, bool>> paths = find_paths(input[indx_i], indx_s);

        for(auto path : paths){
            if(path.second && process_string(states, input, currtn + input[indx_i], path.first, indx_i + 1))
                return true;
            
            if(!path.second && process_string(states, input, currtn, path.first, indx_i)) // AFN-Lambda
                return true;
        }
    }

    return false;
}

vector<pair<int,bool>> find_paths(char letter, int index){
    vector<pair<int, bool>> paths;

    for(auto transition : transition_table[index]){
        if(letter == transition.symbol)
            paths.push_back({transition.next_state, true});
        
        if(transition.symbol == '-') // AFN-Lambda
            paths.push_back({transition.next_state, false});

    }

    return paths;
}

bool is_terminal_symbol(string word){
    char last_symbol = word.back();
    
    for(auto sym: symbols){
        if(sym == last_symbol || last_symbol == '-')
            return true;
    }

    return false;
}