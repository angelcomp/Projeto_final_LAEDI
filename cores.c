#include <stdio.h>

// Funções abaixo são para trocar as cores
void rosa_titulo(void) {
    printf("\033[1;35m");
}

void amarelo_enunciado(void) {
    printf("\033[1;33m");
}

void azul_enunciado(void) {
    printf("\033[1;34m");
}

void verde_resposta(void) {
    printf("\033[1;32m");
}

void vermelho_resposta(void) {
    printf("\033[1;31m");
}

void branco_opcoes(void) {
    printf("\033[1;29m");
}

void reset_cores(void) {
    printf("\033[0m");
}