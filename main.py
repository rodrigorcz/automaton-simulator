# estrutura para representar transicoes
class Transition:
    def __init__(self, symbol: str, next_state: int):
        self.symbol = symbol
        self.next_state = next_state
        
# estrutura para representar estados
class State:
    def __init__(self, state_id: int, accept: bool = False):
        self.id = state_id
        self.accept = accept

# variaveis globais
symbols: list[str] = []       # lista de simbolos terminais
input_strings: list[str] = [] # lista de cadeias de entrada
transition_table: dict[int, list[Transition]] = {} # tabela de transicao (grafo por lista de adjacencia)

# funcao que percorre o grafo de estados e por backtracking verifica se a cadeia eh aceita
def process_string(states: list[State], input: str, currtn: str, id_state: int, indx_i: int) -> bool:

    # condicao de aceitacao
    if states[id_state].accept and currtn == input and is_terminal_symbol(currtn[-1]):
        return True

    else:
        if currtn == "-": # limpa a primeira interacao
            currtn = ""

        # verifica se ainda há caracteres na cadeia de entrada para processar
        if indx_i < len(input):
            
            # encontra os caminhos possíveis a partir do estado 'id_state'
            paths = find_paths(input[indx_i], id_state)

            for path in paths:  # percorre recursivamente os caminhos possiveis
                if path[1] and process_string(states, input, currtn + input[indx_i], path[0], indx_i + 1):
                    return True

                if not path[1] and process_string(states, input, currtn, path[0], indx_i):  # transicao lambda
                    return True

    return False

# funcao que encontra os caminhos possiveis para um simbolo a partir de um estado
def find_paths(sym: str, index: int) -> list[tuple[int, bool]]:

    # retorna uma lista de pares com o 'id' do estado e um bool que e falso para transicoes lambda
    paths: list[tuple[int, bool]] = []

    for transition in transition_table.get(index, []):
        if sym == transition.symbol:
            paths.append((transition.next_state, True))

        if transition.symbol == '-':  # transicao lambda
            paths.append((transition.next_state, False))

    return paths

# verifica se um simbolo faz parte da lista de simbolos terminais
def is_terminal_symbol(last_symbol: str) -> bool:
    return last_symbol in symbols or last_symbol == '-'


# funcao principal
def main() -> None:
    # leitura dos inputs que definem o automato

    # primeira linha: numero de estados
    n_states = int(input().strip())
    states = [State(i) for i in range(n_states)]

    # segunda linha: numero de simbolos terminais seguido dos simbolos
    data_inpt = input().strip().split()
    n_symbols = int(data_inpt[0])
    for i in range(1, n_symbols + 1):
        symbols.append(data_inpt[i])

    # terceira linha: numero de estados iniciais
    n_initial_states = int(input().strip())

    # quarta linha: estados de aceitacao (primeiro numero indica quantos estados, depois vem os ids)
    data_inpt = input().strip().split()
    n_accept_states = int(data_inpt[0])
    for i in range(1, n_accept_states + 1):
        buffer_int = int(data_inpt[i])
        states[buffer_int].accept = True

    # quinta linha: numero de transicoes
    n_transitions = int(input().strip())

    # proximas N transicoes: leitura das transicoes
    for _ in range(n_transitions):
        from_state, symbol, to_state = input().strip().split()
        from_state = int(from_state)
        to_state = int(to_state)

        if from_state not in transition_table:
            transition_table[from_state] = []

        transition_table[from_state].append(Transition(symbol, to_state))

    # numero de cadeias de entrada
    n_input_strings = int(input().strip())

    # leitura das cadeias de entrada
    for _ in range(n_input_strings):
        buffer_str = input().strip()
        input_strings.append(buffer_str)

    # tenta processar todas as cadeias, iniciando em todos estados iniciais
    for input_str in input_strings:
        res = False
        for i in range(n_initial_states):
            if process_string(states, input_str, '-', i, 0):  # se retornar 'True', o automato aceita
                print("aceita")
                res = True
                break

        if not res:
            print("rejeita")
            
if __name__ == "__main__":
    main()