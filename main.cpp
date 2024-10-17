#include <iostream>
#include <vector>
#include <map>

using namespace std;

// estrutura para representar transicoes
struct transition{
    char symbol;             
    int next_state;         
};

// estrutura para representar estados
struct state{
    int id;                   
    bool is_accepting;  
};

vector<char> symbols;          // lista de simbolos terminais                 
vector<string> input_strings;  // lista de cadeias de entrada
map<int, vector<transition>> transition_table; // grafo por lista de adjacencia, ligando o estado às transicoes 

// declaracao das funcoes
bool process_string(vector<state> states, string input, string currtn, int id_state, int indx_i);
vector<pair<int,bool> > find_paths(char letter, int index);
bool is_terminal_symbol(char last_symbol);

int main(){
    // leitura dos inputs que definem a automato

    // primeira linha: numero de estados
    int n_states;
    cin >> n_states;
    vector<state> states(n_states);

    for(int i = 0; i<n_states; i++){
        states[i].id = i;
        states[i].is_accepting = false;
    }

    // segunda linha: simbolos terminais
    int n_symbols;
    cin >> n_symbols;

    for(int i = 0; i < n_symbols; i++){
        char buffer_char;
        cin >> buffer_char;
        symbols.push_back(buffer_char);
    }
   
    // terceira linha: numero de estados iniciais
    int n_initial_states;
    cin >> n_initial_states;

    // quarta linha: estados de aceitacao
    int n_acceptance_states;
    cin >> n_acceptance_states;

    for(int i = 0; i < n_acceptance_states; i++){
        int buffer_int;
        cin >> buffer_int;
        states[buffer_int].is_accepting = true;
    }

    // quinta linha: numero de transicoes
    int n_transitions;
    cin >> n_transitions;

    // proximas N transicoes linhas: leitura das transicoes
    for(int i = 0; i < n_transitions; i++){
        int from_state, to_state;
        char symbol;

        cin>> from_state >> symbol >> to_state;
        transition_table[from_state].push_back({symbol, to_state}); // definicao das transicoes
    }

    // numero de cadeias de entrada
    int n_input_strings;
    cin >> n_input_strings;

    // leitura das cadeias de entrada
    vector<string> input_strings;
    for(int i = 0; i < n_input_strings; i++){
        string buffer_str;
        cin >> buffer_str;
        input_strings.push_back(buffer_str);
    }

    // tenta processar todas as cadeias, iniciando em todos estados iniciais 
    int accept;
    for(auto input: input_strings){
        accept = 0;
        for(int i = 0; i < n_initial_states; i++){
            if(process_string(states, input, "-", i, 0)){ // se retornar 'true' o automato aceita
                cout << "aceita" << endl;
                accept = 1;
                break;
            }
        }

        if(accept == 0){
            cout << "rejeita" << endl;
        }
    }

    return 0;
}


// funcao que percorre o grafo de estados e por backtracking verifica se a cadeia eh aceita
bool process_string(vector<state> states, string input, string currtn, int id_state, int indx_i) {

    // condicao de aceitacao da busca recursiva, para o caso onde a cadeia eh aceita
    if(states[id_state].is_accepting && currtn == input && is_terminal_symbol(currtn.back())){
        return true;
    }else{
        if(currtn == "-") currtn.clear(); // limpa a entrada na primeira interacao

        // encontra os caminhos possiveis a partir do estado 'id_state'
        vector<pair<int, bool>> paths = find_paths(input[indx_i], id_state);

        for(auto path : paths){ // percorre reccursivamente os caminhos possiveis
            if(path.second && process_string(states, input, currtn + input[indx_i], path.first, indx_i + 1))
                return true;
            
            if(!path.second && process_string(states, input, currtn, path.first, indx_i)) // caso em que ha transicao lambda
                return true;
        }
    }

    return false;
}

// funcao que encontra os caminhos possiveis para um simbolo a partir de um estado
vector<pair<int,bool>> find_paths(char sym, int index){

    // sera retornado um vetor de pares com o 'id' do estado e um bool que eh falso para transicoes lambda
    vector<pair<int, bool>> paths;

    for(auto transition : transition_table[index]){
        if(sym == transition.symbol)
            paths.push_back({transition.next_state, true});
        
        if(transition.symbol == '-') // transicao lambda
            paths.push_back({transition.next_state, false});

    }

    return paths;
}

// funcao que verifica se um simbolo faz parte da lista de simbolos terminais
bool is_terminal_symbol(char last_symbol){
    
    for(auto sym: symbols){
        if(sym == last_symbol || last_symbol == '-')
            return true;
    }

    return false;
}