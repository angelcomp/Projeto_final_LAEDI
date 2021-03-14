#include "header.h"

int ler_ruas_de_arquivo(const char nome_arq[], rua ruas[], int *num_ruas) {
	FILE *fileptr;
	// Se não puder abrir o arquivo
	if(NULL == (fileptr = fopen(nome_arq, "r"))) {
		return 1;
	}

	rua rua_placeholder;
	int count = 0;

	// Se houver falha na leitura do arquivo
	if(!fread(&rua_placeholder, sizeof(rua), 1, fileptr)) {
		// E essa falha não for de fim de arquivo
		if(!feof(fileptr)) {
			// Fechar, pois é um erro de leitura.
			fclose(fileptr);
			return 2;
		}
	} else {
		// Substitua a rua no vetor
		ruas[count] = rua_placeholder;
		count++;
	}
	
	// Enquanto não for o fim do arquivo
	while(!feof(fileptr)) {
		// Se não conseguir ler o arquivo
		if(!fread(&rua_placeholder, sizeof(rua), 1, fileptr)) {

			// E ainda não for seu fim
			if(!feof(fileptr)) {
				// Erro de leitura
				fclose(fileptr);
				return 2;
			}	
		} else {
			// Substituir a rua no vetor
			ruas[count] = rua_placeholder;
			count++;
		}
	}
	
	// O número de ruas recebe a contagem de ruas lidas do arquivo
	*num_ruas = count;

	fclose(fileptr);

	// Sucesso na leitura
	return 0;
}

int escrever_ruas_em_arquivo(const char nome_arq[], const rua ruas[], int num_ruas) {
	FILE *fileptr;
	
	// Abrindo o arquivo no modo escrita para limpar seus conteúdos
	if(NULL == (fileptr = fopen(nome_arq, "wb"))) {
		// Erro ao abrir o arquivo
		return 1;
	}
	fclose(fileptr);

	// Reabrindo o arquivo no modo de anexação para adicionar novos conteúdos
	if(!(fileptr = fopen(nome_arq, "ab"))) {
		// Erro ao abrir o arquivo
		return 1;
	}

	// Para cada rua...
	for (int i = 0; i < num_ruas; i++) {

		// Fazendo uma cópia da rua e liberando todas as vagas propositalmente
		rua rua_cpy = ruas[i];
		for (int j = 0; j < rua_cpy.num_vagas; j++) {
			rua_cpy.status_vagas[j] = 0;
			
		}
		
		// Caso tenha algum erro na hora de escrever os conteúdos
		if(!fwrite(&rua_cpy, sizeof(rua), 1, fileptr)) {
			// Fechar o arquivo
			fclose(fileptr);
			return 2;
		}
	}
	
	// Fechar o arquivo pois deu tudo certo
	fclose(fileptr);

	return 0;
}