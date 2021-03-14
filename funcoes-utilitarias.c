#include <string.h>
#include <stdio.h>
#include <time.h>

void trim(char *str) {
	// Especifica quais caracteres devem ser removidos das pontas
	// É utilizado uma string para permitir a utilização de strchr()
	const char remover_das_pontas[] = "\n \t";

	int i;


	// Removendo do final da string
	i = strlen(str) - 1;	
	// Enquanto a string possuir no final dela um caractere que deve ser removido
	while(i >= 0 && strchr(remover_das_pontas, str[i]) != NULL) {
		i--;
	}
	str[i+1] = '\0'; // Delimitando a string no final


	// Enquanto o começo da string possuir esses caracteres inválidos
	i = 0;
	while(str[i] != '\0' && strchr(remover_das_pontas, str[i]) != NULL) {
		i++;
	}
	// Delimitar o começo da string no índice do primeiro caractere válido
	strcpy(str, &str[i]);
	
}

// Obter um tempo formatado, recebe uma string e um time_t
void obter_string_tempo(char tempo_formatado[], const time_t tempo_raw) {
	// Obtendo informações sobre o tempo
	struct tm *info_tempo;
	info_tempo = localtime(&tempo_raw);

	// Escrevendo as informações do tempo em um formato específico para a string desejada
	sprintf(tempo_formatado, "Dia %02d/%02d/%04d, às %02d:%02d", 
		info_tempo->tm_mday, info_tempo->tm_mon+1, info_tempo->tm_year + 1900, info_tempo->tm_hour, info_tempo->tm_min);
}

// Obtém o tempo no momento da chamada da função, o escreve
// em uma string e retorna o time_t
time_t obter_tempo_agora(char tempo_formatado[]) {
	time_t tempo_agora = time(0);
	obter_string_tempo(tempo_formatado, tempo_agora);
	return tempo_agora;
}

char leitura_especial_char() {
	char c;

	// Lendo uma string e a formatando bonitinhamente
	char str[32];
	fgets(str, 32, stdin);
	trim(str);

	c = str[0];
	// Se for uma string vazia após o trim() que remove os \n,
	// Isso significa que o usuário só digitou ENTER
	if(c == '\0') {
		return '\n';
	}	
	return c;
}

void obter_enter() {
	char c;
	while( (c = getchar()) != '\n' && c != EOF) {}
}