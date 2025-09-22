#ifndef LISTA_H
    #define LISTA_H

    typedef struct no_ NO;
    typedef struct lista_ LISTA;

    //funçoes da relação de pacientes: LISTA
    LISTA *criar_lista(); //lista sempre ordenada, lembrar de arrumar na struct tbm
    void apagar_lista(LISTA **lista); //necessaria ao salvar os dados no disco
    bool inserir_paciente_lista(LISTA *lista, PACIENTE *paciente); //feita, sempre adiciona no final
    bool apagar_paciente_lista(LISTA *lista, int ID); //depois ver se remover retorna bool ou PACIENTE*      
    PACIENTE *buscar_paciente(LISTA* lista, int ID);
    void listar_pacientes(LISTA* lista);
    bool lista_vazia(LISTA *lista); //necessaria para verificaçao na função apagar_lista

    //bool save_lista();
    //bool load_lista();

#endif