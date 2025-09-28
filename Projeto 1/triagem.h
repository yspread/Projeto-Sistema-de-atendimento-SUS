#ifndef TRIAGEM_H
    #define TRIAGEM_H

    typedef struct fila_ FILA;
    typedef struct no_ NO;

    //funçoes relativas a FILA para triagem na sala de emergência
    FILA *criar_fila(void);
    void apagar_fila(FILA **fila); 
    bool inserir_paciente_triagem(FILA *fila, PACIENTE *paciente);
    PACIENTE* chamar_para_atendimento(FILA *fila);
    int fila_get_tamanho(FILA *fila);
    bool fila_cheia(FILA *fila);
    bool fila_vazia(FILA *fila);
    void fila_listar(FILA *fila);
    //bool save_fila();
    //bool load_fila();
#endif