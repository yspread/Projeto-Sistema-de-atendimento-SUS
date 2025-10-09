# Projeto-Sistema-de-atendimento-SUS

Trabalho para a disciplina de Algoritmos e Estruturas de dados ICMC - USP
Rafael Pavon Diesner: 16898096
Enzo Ferreira de Castro Lima: 16863736
Eric Costa Lopes: 17070779

## Visão Geral

Nesse Sistema de Atendimento do SUS, nós precisamos organizar dados sobre os pacientes, os procedimentos que os envolvem, etc. Cada sessão desse sistema (paciente, fila/triagem, lista, historico, procedimento, procedimento de salvamento) compõe um TAD. Guardamos as informações de cada paciente na struct PACIENTE, o que inclui seu nome, ID, tamanho do nome e um ponteiro para seu histórico. Isso facilita o acesso aos dados de cada paciente, que serão usados aos longo do trabalho inteiro.
O projeto simula um serviço de atendimento médico de pacientes em um ambiente de Pronto Socorro (PS), por meio de Tipos Abstratos de Dados (TADs) como listas, filas e pilhas. Escolhemos fazer implementar todas as estruturas de dados de modo simplesmente encadeado a fim de padronizar toda a implementação do sistema e ter um gerenciamento de memória mais eficiente.

## Lista de Pacientes

Para manter o registro de todos os pacientes atendidos no PS, foi utilizada uma lista simplesmente encadeada. Esta escolha se justifica pela necessidade de armazenar um número indefinido de pacientes, limitado apenas pela memória do sistema. A lista armazena informações sobre o paciente e seu histórico de tratamento. As principais funcionalidades implementadas para a lista de pacientes são:
- Inserir paciente: adiciona um novo paciente no final da lista. Complexidade constante.
- Apagar paciente: remove um paciente da lista, utilizado para registrar o óbito. Complexidade linear em função da posição do paciente na lista.
- Buscar paciente: procura por um paciente na lista a partir de seu ID. Complexidade linear em função da posição do paciente na lista.
- Listar todos os pacientes: Exibe todos os pacientes registrados no sistema. Complexidade linear em função do tamnho da lista.
A utilização de uma lista encadeada facilita a inserção e remoção de pacientes sem a necessidade de realocar grandes blocos de memória, tornando as operações mais eficientes

## Fila de Triagem

Para a triagem dos pacientes, foi implementada uma fila simplesmente encadeada. Esta estrutura de dados segue o princípio "primeiro a chegar, primeiro a ser atendido", que é o critério de atendimento definido para a emergência. A fila tem um tamanho finito, representando a capacidade limitada de atendimento do hospital. Ao invés de armazenar pacientes na fila, escolhemos armazenar apenas os IDs dos pacientes, buscando evitar salvamentos duplos de pacientes e gasto desnecessário de memória. Nas operações relativas a fila em que é necessário retornar o paciente, usamos o ID para buscar as outras informações na lista e assim retornar as informações desejadas. As principais funcionalidades implementadas para a fila de triagem são:
- Inserir paciente na triagem: adiciona um paciente no final da fila de espera. Complexidade constante.
- Chamar para atendimento: remove o paciente do início da fila para ser atendido. Complexidade constante.
- Verificar se a fila está cheia: checa se a capacidade máxima de atendimento foi atingida. Complexidade constate.
- Verificar se a fila está vazia: Checa se não há pacientes na fila de espera. Complexidade constante.
- Mostrar fila de espera: Exibe a lista de pacientes aguardando atendimento. Complexidade linear em função do tamanho da fila.
A utilização de uma fila encadeada permite inserção e remoção em complexidades constante.

## TAD Histórico de Procedimentos Médicos

O histórico de tratamento de cada paciente é gerenciado por uma pilha simplesmente encadeada. A escolha desta estrutura se deve ao fato de que o último procedimento médico adicionado é o primeiro a ser desfeito. Cada paciente pode ter no máximo 10 procedimentos em seu histórico. As funcionalidades do histórico médico incluem:
- Inserir procedimento: adiciona um novo procedimento no topo da pilha do histórico do paciente. Complexidade constante.
- Retirar procedimento: remove o procedimento mais recatendimento aos pacientes.ente do histórico. Complexidade constante
- Consultar histórico: exibe todos os procedimentos no histórico de um paciente. Complexidade linear em função do tamanho do histórico.
- Verificar se o histórico está cheio ou vazio: controla o número de procedimentos registrados. Complexidade constante.
Para esse TAD, criamos um TAD procedimento, para mais fácil organização das operações diretas sobre os procedimentos.
A utilização de uma pilha encadeada evita que seja alocado mais memória que será usada.

## Permanência dos Dados

Todas as informações registradas são salvas em disco. Isso garante que os dados dos pacientes e da fila de espera não sejam perdidos ao finalizar o programa. Para isso, foram implementadas as funções save() e load(), que salvam as informae carregam os dados de arquivos binários, respectivamente. Na função save, é necessário salvar além das informações de cada paciente na lista, o tamanho das strings que serão salvas, para que se possa usar a função fread para ler elas adequadamente na função load. Na fila, como dito anteriormente, salvamos apenas os IDs do paciente, já que as outras informações dos pacientes podem ser acessadas pela lista. Quando o sistema é executado, todas as informações salvas são carregadas pro sistema.

## Interface do Sistema

O sistema possui uma interface de menu de texto que permite ao usuário interagir com as funcionalidades do pronto socorro. Todas as operações estão centralizadas na interface, o que facilita o uso do sistema. As opções do menu incluem:
    1. Registrar: Com um id e nome criamos um paciente e inserimos na lista e na fila. Se ele ja estiver na lista, é apenas adicionado na fila e se já estiver na fila também a criação falha
    2. Registrar óbito de paciente: remove um paciente da lista, apagando seus dados do sistema. Um paciente que está na fila não pode ter seu óbito registrado
    3. Adicionar procedimento ao histórico médico: adiciona um procedimento ao histórico de um paciente.Recebe um ID para buscar o paciente
    4. Desfazer procedimento do histórico médico: retira o procedimento mais recente do histórico de um paciente
    5. Chamar paciente para atendimento: retira o primeiro da fila, que será atendido agora
    6. Mostrar fila de espera: lista toda a fila de espera, com ID e nome dos pacientes
    7. Mostrar histórico do paciente : se lê o ID de um paciente, busca ele na lista e imprime seu histórico de procedimentos
    8. Sair: Desliga o sistema e automáticamente salva os dados da lista e da fila em um arquivo binário

