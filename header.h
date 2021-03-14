#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Definição de constantes
#define OPCAO_SAIR 0
#define OPCAO_SAIR_CHAR '0'
#define NUM_OPCOES 6
#define NUM_OPCOES_OP_6 7
#define MIN_RUAS 3
#define MAX_RUAS 20
#define MAX_CHAR_NOME 50
#define MIN_VAGAS 5
#define MAX_VAGAS 20
#define MIN_VALOR 1.0
#define MAX_VALOR 2.0
#define TAM_BUFFER_PLACA 30
#define TEMPO_MINIMO 30
#define TEMPO_MAXIMO 120
#define NOME_ARQUIVO_RUAS "ruas.dat"
#define TAMANHO_TEMPO_STR 32

// Definição de estruturas
typedef struct {
	char placa[TAM_BUFFER_PLACA];
	int tempo_estadia;
	time_t tempo_inicio;
} dados_vaga;

typedef struct {
	char nome[MAX_CHAR_NOME];
	int num_vagas;

	// Disponibilidade de cada vaga a um dado momento
	// pode estar livre (0) ou ocupada (!= 0)
	int status_vagas[MAX_VAGAS];
	dados_vaga dados[MAX_VAGAS];

	float valor_por_vaga;
} rua;

// Declaração de funções

// Funções do menu
void menu_principal();
void menu_mostrar_opcoes(const int [][NUM_OPCOES], const int []);
int menu_cadastrar_ruas(rua []);
void menu_cadastrar_vagas(rua [], const int);
void menu_cadastrar_valor(rua [], const int);
void menu_estacionar_carro(rua [], const int, int *, float *);
void menu_liberar_vaga(rua [], const int);
void menu_mostrar_relatorios(const rua [], const int, const int [], int, float);

// Funções utilitárias
void trim(char *str);
time_t obter_tempo_agora(char []);
void obter_string_tempo(char [], const time_t);
char leitura_especial_char();
void obter_enter();

// Funções de cores
void rosa_titulo(void);
void amarelo_enunciado(void);
void azul_enunciado(void);
void verde_resposta(void);
void vermelho_resposta(void);
void branco_opcoes(void);
void reset_cores(void);

// Funções para escrever em arquivos
int ler_ruas_de_arquivo(const char [], rua [], int *);
int escrever_ruas_em_arquivo(const char [], const rua [], int);
