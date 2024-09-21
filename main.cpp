#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct transition{
    char symbol;             
    int next_state;         
};

struct state{
    int id;                   
    bool is_accepting;  
};

class Automaton {
    public:
        vector<state> states;                    
        unordered_map<int, vector<transition>> transition_table; 

        void add_state(int id, bool is_accepting) {
            states.push_back({id, is_accepting});
        }

        void add_transition(int from_state, char symbol, int to_state) {
            transition_table[from_state].push_back({symbol, to_state});
        }

        bool process_string(string input) {
           // Backtracking ....
        }
};

// Function to tranform qi --> i
int string_to_number(string str) {
    if(str.empty() || str[0] != 'q')
        throw invalid_argument("Invalid");
    
    return stoi(str.substr(1));
}

int main(){
    Automaton automaton_x;

    // First Line: number of states
    int n_states;
    cin >> n_states;

    // Second Line: terminal symbols 
    int n_symbols;
    cin >> n_symbols;

    vector<char> symbols(n_symbols);
    for(int i = 0; i < n_symbols; i++)
        cin >> symbols[i];

    // Third Line: initial states
    int n_initial_states;
    cin >> n_initial_states;

    vector<int> initial_states(n_initial_states);
    for(int i = 0; i < n_initial_states; i++)
        cin >> initial_states[i];

    // Fourth Line: acceptance states
    int n_acceptance_states;
    cin >> n_acceptance_states;

    vector<int> acceptance_states(n_acceptance_states);
    for(int i = 0; i < n_acceptance_states; i++)
        cin >> acceptance_states[i];

    // Fifth Line: number of transitions
    int n_transitions;
    cin >> n_transitions;

    // Sixth Line: the transitions
    for(int i = 0; i < n_transitions; i++){
        string q_initial, q_final, x;

        cin >> q_initial >> x >> q_final;
    }

    // Inputs
    int n_input_strings;
    cin >> n_input_strings;

    vector<string> input_strings(n_input_strings);
    for(int i = 0; i < n_input_strings; i++)
        cin >> input_strings[i];

    return 0;
}