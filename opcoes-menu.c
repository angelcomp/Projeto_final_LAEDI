// Bibliotecas
#include "header.h"

// Definição de Opções do Menu
void menu_mostrar_opcoes(const int opcoes_exigidas[NUM_OPCOES][NUM_OPCOES], const int opcoes_escolhidas[NUM_OPCOES]) {
	const char *opcoes_texto[] = {
		"Cadastrar Ruas",
		"Cadastrar Numero de Vagas",
		"Cadastrar Valor",
		"Estacionar um carro",
		"Liberar vaga",
		"Emitir Relatórios"
	};

	azul_enunciado();
	printf("\n  Menu principal\n\n");
	reset_cores();

	branco_opcoes();
	// Para cada opção.
	for (int i = 0; i < NUM_OPCOES; i++) {
		
		// Mostrar o número da opção
		azul_enunciado();
		printf("  %d) ", i+1);
		reset_cores();
		branco_opcoes();
		
		// Escrever o texto
		printf("%s", opcoes_texto[i]);

		// Contando quantas exigências esta opção possui
		int num_exigencias = 0;
		int exigencias_opcao[NUM_OPCOES];
		for (int j = 0; j < NUM_OPCOES; j++) {
			// Definindo essa opção como não necessária inicialmente
			exigencias_opcao[j] = 0;

			// Mas se esta opção não tiver sido escolhida antes
			if(opcoes_escolhidas[j] == 0)
				// Definí-la em seu estado padrão
				exigencias_opcao[j] = opcoes_exigidas[i][j];

			num_exigencias += exigencias_opcao[j];
		}

		// Se tiver alguma exigência, mostrar qual/quais são
		int num_exigencias_iteradas = 0;
		if(num_exigencias > 0) {
			for (int j = 0; j < NUM_OPCOES; j++) {
				// Se for a primeira opção exigida
				if(j == 0) {
					vermelho_resposta();
					printf(" (requer opção ");
				}
				
				// Se a opção j é exigida, mostrar seu número e incrementar quantas
				// foram iteradas
				if(exigencias_opcao[j]) {
					printf("%d", j+1);
					num_exigencias_iteradas++;
				}

				// Se for a última iteração de j
				if(j == NUM_OPCOES - 1)
					printf(")");
				// Se esta for uma opção exigida e não for a última
				else if(exigencias_opcao[j] && 
						num_exigencias_iteradas < num_exigencias)
						printf(", ");
			}
		}
		reset_cores();
		printf("\n");
	}
	// Mostrar também, sempre por último, a opção para sair do programa
	azul_enunciado();
	printf("  %d) ", OPCAO_SAIR);
	vermelho_resposta(); 
	printf("Sair\n");
	reset_cores();
}

// Menu cadastrar ruas
int menu_cadastrar_ruas(rua ruas_cadastrar[MAX_RUAS]) {
	int num_ruas = 0;
	int i = 0;

	// Obter quantas ruas serão lidas
	int num_ruas_valido;
	do {
		amarelo_enunciado();
		printf("\n  Digite quantas ruas deseja cadastrar (min %d, máx %d).\n", MIN_RUAS, MAX_RUAS);
		printf("  >> ");
		reset_cores();

		scanf("%d", &num_ruas);
		getchar();

		num_ruas_valido = num_ruas >= MIN_RUAS && num_ruas <= MAX_RUAS;
		if(!num_ruas_valido) {
			vermelho_resposta();
			printf("\n  *Erro: número de ruas deve ser entre %d e %d!*\n", MIN_RUAS, MAX_RUAS);
			reset_cores();
		}
	} while(!num_ruas_valido);


	// Entrada de dados
	// Laço de repetição para nomear cada rua
	printf("\n");
	do {
		amarelo_enunciado();
		// Obtendo o nome da rua
		printf("  Digite o nome da %dª rua.\n",i+1);
		printf("  >> ");
		reset_cores();

		int nome_vazio;
		do {
			fgets(ruas_cadastrar[i].nome, 50, stdin);
			trim(ruas_cadastrar[i].nome);

			nome_vazio = strlen(ruas_cadastrar[i].nome) == 0;
		} while(nome_vazio);
		i++;
	} while(i < num_ruas);
	
	verde_resposta();
	printf("\n  Cadastro de ruas realizado com sucesso!\n");
	reset_cores();

	return num_ruas;
}





// Menu cadastrar vagas
void menu_cadastrar_vagas(rua ruas[MAX_RUAS], const int num_ruas) {
	
	int num_vagas_valido;

	for (int i = 0; i < num_ruas; i++) {
		do {
			azul_enunciado();
			printf("\n  Digite quantas vagas disponíveis a Rua '%s' possui (min %d, máx %d).\n", 
				ruas[i].nome, MIN_VAGAS, MAX_VAGAS);
			printf("  >> ");
			reset_cores();

			scanf("%d", &ruas[i].num_vagas);
			getchar();

			// Número de vagas válido = [5~20]
			num_vagas_valido = ( (ruas[i].num_vagas >= MIN_VAGAS) && (ruas[i].num_vagas <= MAX_VAGAS) );

			// Mensagem de número de vagas inválido
			if (!num_vagas_valido) {
				vermelho_resposta();
				printf("\n  *Erro: número de vagas deve ser entre %d e %d!*\n", MIN_VAGAS, MAX_VAGAS);
				reset_cores();
			}

		} while(!num_vagas_valido);

		// Atribuindo status de todas as vagas como vazio
		for (int j = 0; j < ruas[i].num_vagas; j++) {
			ruas[i].status_vagas[j] = 0;
		}
	}
	verde_resposta();
	printf("\n  Cadastro de vagas realizado com sucesso!\n");
	reset_cores();
}





void menu_cadastrar_valor(rua ruas_cadastrar_valor[MAX_RUAS], const int num_ruas) {
	int valor_valido;

	azul_enunciado();
	printf("\n  Informe o Valor a ser cobrado para cada rua (deverá ser entre R$ %.2f e R$ %.2f)\n", MIN_VALOR, MAX_VALOR);
	reset_cores();

	// Para cada rua cadastrada
	for (int i = 0; i < num_ruas; i++) {

		// Ler e verificar o valor lido
		do {
			amarelo_enunciado();
			printf("  - %dª rua: %s\n", i+1, ruas_cadastrar_valor[i].nome);
			printf("    >> R$: ");
			reset_cores();

			scanf("%f", &ruas_cadastrar_valor[i].valor_por_vaga);
			getchar();

			valor_valido = (ruas_cadastrar_valor[i].valor_por_vaga >= MIN_VALOR) && (ruas_cadastrar_valor[i].valor_por_vaga <= MAX_VALOR);

			if (!valor_valido) {
				vermelho_resposta();
				printf("\n  *Valor não está dentro dos limites de R$ %.2f e R$ %.2f*\n\n", MIN_VALOR, MAX_VALOR);
				reset_cores();
			}

		} while (!valor_valido); 
				
	}
	verde_resposta();
	printf("\n  Cadastro realizado com sucesso!\n");
	reset_cores();
}



void menu_estacionar_carro(rua ruas[MAX_RUAS], const int num_ruas, int *acumulador_clientes, float *acumulador_precos) {
	int rua_a_estacionar;

	azul_enunciado();
	printf("\n  As ruas disponíveis são:\n");
	reset_cores();
	
	for (int i = 0; i < num_ruas; i++) {
		verde_resposta();
		printf("  - %dª rua: %s\n", i+1, ruas[i].nome);
		reset_cores();
	}

	// Lendo o número da rua a estacionar
	int num_rua_valida;
	do {
		amarelo_enunciado();
		printf("\n  Digite o nº da rua que deseja acessar.\n");
		printf("  >> ");
		reset_cores();

		scanf("%d", &rua_a_estacionar);
		getchar();
		num_rua_valida = rua_a_estacionar >= 1 && rua_a_estacionar <= num_ruas;

		if(!num_rua_valida) {
			vermelho_resposta();
			printf("\n    Digite um valor válido.\n");
			reset_cores();
		}
	} while(!num_rua_valida);
	int idx = rua_a_estacionar-1;

	// Listando as vagas disponíveis
	int num_vagas_disponiveis = 0;
	azul_enunciado();
	printf("\n  Na rua %s as vagas disponíveis são: ", ruas[idx].nome);
	
	for (int i = 0; i < ruas[idx].num_vagas; i++) {
		// Se a vaga estiver disponível
		if(ruas[idx].status_vagas[i] == 0) {
			printf("%d", i+1);

			// Se não for a última iteração do vetor
			if(i < ruas[idx].num_vagas - 1)
				printf(", ");

			num_vagas_disponiveis++;
		}
	}
	reset_cores();

	if(num_vagas_disponiveis == 0) {
		vermelho_resposta();
		printf("\nNenhuma vaga está disponível!\n");
		reset_cores();
	} else {
		azul_enunciado();
		printf(".\n"); // Colocando um ponto final na listagem das vagas vagas

		// Lendo a vaga a estacionar
		int vaga_valida;
		int vaga_escolhida;
		int idx_vaga;
		do {
			amarelo_enunciado();
			printf("\n  Qual vaga deseja acessar?\n");
			printf("  >> ");
			reset_cores();

			scanf("%d", &vaga_escolhida);
			getchar();
			vaga_valida = vaga_escolhida >= 1 && vaga_escolhida <= ruas[idx].num_vagas;
			if(!vaga_valida) {
				vermelho_resposta();
				printf("\n  Vaga inválida.\n");
				reset_cores();
				continue;
			}
			idx_vaga = vaga_escolhida - 1;

			if(ruas[idx].status_vagas[idx_vaga] != 0) {
				vaga_valida = 0;
				vermelho_resposta();
				printf("\n  Esta vaga está ocupada.\n");
				reset_cores();
				continue;
			}
		} while(!vaga_valida);

		char placa[TAM_BUFFER_PLACA];
		amarelo_enunciado();
		printf("\n  Digite a placa do carro: ");
		reset_cores();
		fgets(placa, TAM_BUFFER_PLACA, stdin);
		trim(placa);
		
		int tempo_minutos;
		int tempo_valido;
		do {
			amarelo_enunciado();
			printf("\n  Digite o tempo (minutos) entre %dmin e %dmin: ", TEMPO_MINIMO, TEMPO_MAXIMO);
			reset_cores();
			scanf("%d", &tempo_minutos);
			getchar();
			tempo_valido = tempo_minutos >= TEMPO_MINIMO && tempo_minutos <= TEMPO_MAXIMO;

			if(!tempo_valido) {
				vermelho_resposta();
				printf("\n  Tempo inválido!\n");
				reset_cores();
			}
		} while(!tempo_valido);

		float valor_total = ruas[idx].valor_por_vaga * (((float) tempo_minutos)/30);
		char str_tempo[TAMANHO_TEMPO_STR];
		time_t tempo_raw = obter_tempo_agora(str_tempo);

		// Escrevendo os detalhes da operação
		rosa_titulo();
		printf("\n\n\t  Detalhes da operação:\n\n");
		reset_cores();
		azul_enunciado();
		printf("   Rua: %s\n", ruas[idx].nome);
		printf("   Vaga: %d\n", vaga_escolhida);
		printf("   Placa: %s\n", placa);
		printf("   Tempo: %d min\n", tempo_minutos);
		printf("\n");
		printf("   Hora: %s\n", str_tempo);
		printf("\n");
		printf("   Valor total: R$%.2f\n", valor_total);
		reset_cores();
		
		char op;
		int op_valida;
		int continuar_operacao;
		do {
			amarelo_enunciado();
			printf("\n  Deseja finalizar a alocação? (Y/n): ");
			reset_cores();
			op = tolower(leitura_especial_char());
			op_valida = op == '\n' || op == 'y' || op == 'n';
			if(!op_valida) {
				vermelho_resposta();
				printf("\n  Opção inválida!\n");
				reset_cores();
			}
		} while(!op_valida);
		continuar_operacao = op == 'y' || op == '\n';
		
		if(continuar_operacao) {
			// Mudando o estado da vaga para ocupado
			ruas[idx].status_vagas[idx_vaga] = 1;
	
			// Mudando outros atributos na rua especificada
			strcpy(ruas[idx].dados[idx_vaga].placa, placa);
			ruas[idx].dados[idx_vaga].tempo_estadia = tempo_minutos;
			ruas[idx].dados[idx_vaga].tempo_inicio = tempo_raw;

			// Aumentando os acumuladores para estatísticas
			*acumulador_clientes += 1;
			*acumulador_precos += valor_total;

			verde_resposta();
			printf("\n  Vaga alocada com sucesso!\n");
			reset_cores();
		} else {
			vermelho_resposta();
			printf("\n  Operação cancelada.\n");
			reset_cores();
		}
	}
}



void menu_liberar_vaga(rua ruas[MAX_RUAS], const int num_ruas) {
	int rua_a_liberar_vaga;

	azul_enunciado();
	printf("\n  As ruas disponíveis são:\n\n");
	reset_cores();
	
	for (int i = 0; i < num_ruas; i++) {
		verde_resposta();
		printf("   - %dª rua: %s\n", i+1, ruas[i].nome);
		reset_cores();
	}

	// Lendo o número da rua a liberar a vaga
	int num_rua_valida;
	do {
		amarelo_enunciado();
		printf("\n  Digite o nº da rua que deseja acessar.\n");
		printf("  >> ");
		reset_cores();

		scanf("%d", &rua_a_liberar_vaga);
		getchar();
		num_rua_valida = rua_a_liberar_vaga >= 1 && rua_a_liberar_vaga <= num_ruas;

		if(!num_rua_valida) {
			vermelho_resposta();
			printf("\n  Digite um valor válido.\n");
			reset_cores();
		}
	} while(!num_rua_valida);
	int idx = rua_a_liberar_vaga-1;

	// Listando as vagas ocupadas
	int num_vagas_ocupadas = 0;
	azul_enunciado();
	printf("\n  Na rua %s as vagas ocupadas são: ", ruas[idx].nome);
	for (int i = 0; i < ruas[idx].num_vagas; i++) {
		// Se a vaga estiver ocupada
		if(ruas[idx].status_vagas[i] != 0) {
			// Se não for a primeira iteração do vetor
			// e a posição anterior estiver ocupada
			if(i > 0 && ruas[idx].status_vagas[i-1] != 0)
				printf(", ");
				
			printf("%d", i+1);
			num_vagas_ocupadas++;
		}
	}
	reset_cores();

	if(num_vagas_ocupadas == 0) {
		vermelho_resposta();
		printf("\n  Todas as vagas estão disponíveis!\n");
	} else {
		azul_enunciado();
		printf(".\n"); // Colocando um ponto final na listagem das vagas vagas
		reset_cores();

		// Lendo a vaga a estacionar
		int vaga_valida;
		int vaga_escolhida;
		int idx_vaga;
		do {
			amarelo_enunciado();
			printf("\n  Qual vaga deseja liberar?\n");
			printf("  >> ");
			reset_cores();

			scanf("%d", &vaga_escolhida);
			getchar();
			vaga_valida = vaga_escolhida >= 1 && vaga_escolhida <= ruas[idx].num_vagas;
			if(!vaga_valida) {
				vermelho_resposta();
				printf("\n  Vaga inválida.\n");
				reset_cores();
				continue;
			}
			idx_vaga = vaga_escolhida - 1;

			if(ruas[idx].status_vagas[idx_vaga] == 0) {
				vaga_valida = 0;
				vermelho_resposta();
				printf("\n  Esta vaga está vazia!\n");
				reset_cores();
				continue;
			}
		} while(!vaga_valida);

		char op;
		int op_valida;
		int continuar_operacao;
		do {
			amarelo_enunciado();
			printf("\n  Deseja finalizar a liberação? (Y/n): ");
			reset_cores();
			op = tolower(leitura_especial_char());
			op_valida = op == '\n' || op == 'y' || op == 'n';
			if(!op_valida) {
				vermelho_resposta();
				printf("\n  Opção inválida!\n");
				reset_cores();
			}
		} while(!op_valida);
		continuar_operacao = op == 'y' || op == '\n';
		
		if(continuar_operacao) {
			// Mudando o estado da vaga para liberado
			ruas[idx].status_vagas[idx_vaga] = 0;

			// Os atributos não precisam ser mudados pois a vaga está vazia

			verde_resposta();
			printf("\n  Vaga liberada com sucesso!\n");
			reset_cores();
		} else {
			vermelho_resposta();
			printf("\n  Operação cancelada.\n");
			reset_cores();
		}

	}
}




// Opção do menu para mostrar relatorios
void menu_mostrar_relatorios(const rua ruas_mostrar[MAX_RUAS], const int num_ruas, const int opcoes_escolhidas[NUM_OPCOES], int acumulador_clientes, float acumulador_precos) {
	char opcao_escolhida;
	int opcao_char_valida;
	const char *opcoes_texto[] = {
		"Ruas Cadastradas",
		"Total de Vagas Disponíveis por Rua",
		"Carros estacionados (todos)",
		"Carros estacionados separados por rua",
		"Custo médio por rua",
		"Lucro total do estacionamento nesta sessão",
		"Quantidade total de clientes nesta sessão"
	};
	const int opcoes_exigidas_op6[NUM_OPCOES_OP_6][NUM_OPCOES] = {
		{1, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0}
	};

	// Variável utilizada para a opção c
	int total_vagas_ocupadas = 0;

	do {
		rosa_titulo();
		printf("\n Escolha uma das opções para emitir um relatório.\n\n");
		reset_cores();

		branco_opcoes();
		// Para cada opção. ..
		for (int i = 0; i < NUM_OPCOES_OP_6; i++) {

			// Mostrar o número da opção
			azul_enunciado();
			printf("  %c) ", i+'a');
			reset_cores();
			
			// Escrever o texto
			branco_opcoes();
			printf("%s", opcoes_texto[i]);
			reset_cores();

			// Contando quantas exigências esta opção possui
			int num_exigencias = 0;
			int exigencias_opcao[NUM_OPCOES];
			for (int j = 0; j < NUM_OPCOES; j++) {
				// Definindo essa opção como não necessária inicialmente
				exigencias_opcao[j] = 0;

				// Mas se esta opção não tiver sido escolhida antes
				if(opcoes_escolhidas[j] == 0)
					// Definí-la em seu estado padrão
					exigencias_opcao[j] = opcoes_exigidas_op6[i][j];

				num_exigencias += exigencias_opcao[j];
			}

			// Se tiver alguma exigência, mostrar qual/quais são
			int num_exigencias_iteradas = 0;
			if(num_exigencias > 0) {
				for (int j = 0; j < NUM_OPCOES; j++) {
					// Se for a primeira opção exigida
					if(j == 0) {
						vermelho_resposta();
						printf(" (requer opção ");
					}
					
					// Se a opção j é exigida, mostrar seu número e incrementar quantas
					// foram iteradas
					if(exigencias_opcao[j]) {
						printf("%d", j+1);
						num_exigencias_iteradas++;
					}

					// Se for a última iteração de j
					if(j == NUM_OPCOES - 1)
						printf(")");
					// Se esta for uma opção exigida e não for a última
					else if(exigencias_opcao[j] && 
							num_exigencias_iteradas < num_exigencias)
							printf(", ");
				}
			}
			printf("\n");
		}
		reset_cores();

		// Mostrar também, sempre por último, a opção para sair do menu
		azul_enunciado();
		printf("  %c) ", OPCAO_SAIR_CHAR);
		reset_cores();

		vermelho_resposta();
		printf("Voltar\n");
		reset_cores();

		// Laço de leitura da opção do usuário
		do {
			amarelo_enunciado();
			printf("\n  Digite a opção desejada:\n");
			printf("  >> ");
			reset_cores();

			// Entrada de dados
			do {
				opcao_escolhida = tolower(getchar());
			} while(opcao_escolhida == '\n'); // Impedindo que o usuário digite enter sem querer
			getchar(); // Consumindo o último \n no buffer

			// A opção deve ser entre 'a' e 'g', ou igual a '0'
			opcao_char_valida = (opcao_escolhida >= 'a' && opcao_escolhida <= 'a' + NUM_OPCOES_OP_6 - 1) || opcao_escolhida == OPCAO_SAIR_CHAR;

			if(!opcao_char_valida) {
				vermelho_resposta();
				printf("\n  *Opção inválida!*\n");
				reset_cores();
			}
		} while(!opcao_char_valida);

		// Variável que representa a primeira opção (de 1 a 6) que falta, se for 0 então nenhuma falta
		int opcao_faltante = 0;

		if(opcao_escolhida != OPCAO_SAIR_CHAR) {
			// Para cada uma das opções
			for (int i = 0; i < NUM_OPCOES; i++) {
				// Se esta opção for exigida pela que o usuário escolheu, mas não tiver sido escolhida
				if(opcoes_exigidas_op6[opcao_escolhida - 'a'][i] && !opcoes_escolhidas[i]) {
					opcao_faltante = i+1; // Marque-a como a faltante
					break;
				}
			}
		}
		// Se alguma opção faltar
		if(opcao_faltante != 0) {
			vermelho_resposta();
			printf("\n  *Esta opção requer que a opção %d seja acessada primeiro!*\n", opcao_faltante);
			reset_cores();
		
		} else {
			switch(opcao_escolhida) {
				case 'a':
					azul_enunciado();
					printf("\n  As ruas cadastradas foram:\n");
					reset_cores();
					
					for (int i = 0; i < num_ruas; i++) { 
						verde_resposta();
						printf("  - %dª rua: %s\n", i+1, ruas_mostrar[i].nome);
						reset_cores();
					}
					break;
				// Retorna relatório de vagas
				case 'b':
					azul_enunciado();
					printf("\n  O total de vagas disponíveis por rua é:\n");
					reset_cores();
										
					for (int i = 0; i < num_ruas; i++) {
						// Se o status for '0', status = livre
						int vagas_ocupadas = 0;
						for (int j = 0; j < ruas_mostrar[i].num_vagas; j++) {
							vagas_ocupadas += ruas_mostrar[i].status_vagas[j];
						}
						int vagas_livres = ruas_mostrar[i].num_vagas - vagas_ocupadas;

						verde_resposta();
						printf("  - Rua '%s': %d vagas - %d livres.\n", ruas_mostrar[i].nome, ruas_mostrar[i].num_vagas, vagas_livres);
						reset_cores();
					}
					break;

				case 'c':
					azul_enunciado();
					printf("\n  Os carros estacionados são:\n");
					reset_cores();

					// Para cada rua
					for (int i = 0; i < num_ruas; i++) {
						// Para cada vaga da rua
						for (int j = 0; j < ruas_mostrar[i].num_vagas; j++) {
							// Se esta vaga estiver ocupada
							if(ruas_mostrar[i].status_vagas[j]) {
								float valor_total = (ruas_mostrar[i].valor_por_vaga * ((float) ruas_mostrar[i].dados[j].tempo_estadia))/30;
								char tempo_str[TAMANHO_TEMPO_STR];
								obter_string_tempo(tempo_str, ruas_mostrar[i].dados[j].tempo_inicio);

								total_vagas_ocupadas++;
								verde_resposta();
								printf("\n  - Veículo %s:\n", ruas_mostrar[i].dados[j].placa);
								printf("  - Rua %s\n", ruas_mostrar[i].nome);
								printf("  - Vaga nº%d.\n", j+1);
								printf("  - Tempo de início: %s\n", tempo_str);
								printf("  - Tempo de estadia: %d minutos\n", ruas_mostrar[i].dados[j].tempo_estadia);
								printf("  - Valor da estadia: %.2f\n", valor_total);
								reset_cores();
							}
						}
					}
					if(total_vagas_ocupadas == 0) {
						vermelho_resposta();
						printf("\n  O estacionamento está vazio.\n");
						reset_cores();
					}
					break;

				case 'd':

					rosa_titulo();
					printf("\n  Os carros estacionados por rua são:\n");
					reset_cores();
					// Para cada rua
					for (int i = 0; i < num_ruas; i++) {

						printf("\n");
						azul_enunciado();
						printf("  Rua %d: Rua %s\n", i+1, ruas_mostrar[i].nome);
						reset_cores();

						// Para cada vaga
						int vagas_ocupadas_rua = 0;
						for (int j = 0; j < ruas_mostrar[i].num_vagas; j++) {
							if(ruas_mostrar[i].status_vagas[j]) {
								vagas_ocupadas_rua++;
								verde_resposta();
								printf("  - Vaga %d: Veículo %s.\n", j+1, ruas_mostrar[i].dados[j].placa);
								reset_cores();
							}
						}
						if(vagas_ocupadas_rua == 0) {
							vermelho_resposta();
							printf("  - Nenhum carro estacionado.\n");
							reset_cores();
						}
					}
					break;
				
				case 'e':
					// Para cada rua
					for (int i = 0; i < num_ruas; i++) {
						float soma_valor_rua_vagas = 0;
						float media_final;

						printf("\n");
						azul_enunciado();
						printf("  Rua %d: Rua %s\n", i+1, ruas_mostrar[i].nome);
						reset_cores();

						// Para cada vaga
						int vagas_ocupadas_rua = 0;
						for (int j = 0; j < ruas_mostrar[i].num_vagas; j++) {
							// Se a vaga estiver ocupada
							if(ruas_mostrar[i].status_vagas[j]) {
								vagas_ocupadas_rua++;

								// Calcular o valor dessa estadia e somar à variável acumuladora
								float valor_total = ruas_mostrar[i].valor_por_vaga * (((float) ruas_mostrar[i].dados[j].tempo_estadia)/30);
								soma_valor_rua_vagas += valor_total;
							}
						}
						// Se alguma vaga estiver ocupada, mostrar a média
						if(vagas_ocupadas_rua > 0) {
							media_final = soma_valor_rua_vagas/vagas_ocupadas_rua;
							verde_resposta();
							printf("  - Média de R$%.2f investidos por clientes.\n", media_final);
							reset_cores();
						} else {
							vermelho_resposta();
							printf("  Nenhum carro estacionado.\n");
							reset_cores();
						}
					}
					break;
				
				case 'f':
					verde_resposta();
					printf("\n  O EstacionaMentos até agora lucrou R$%.2f!\n", acumulador_precos);
					reset_cores();

					break;
			
				case 'g':
					verde_resposta();
					printf("\n  O EstacionaMentos recebeu %d clientes!\n", acumulador_clientes);
					reset_cores();

					break;

				case OPCAO_SAIR_CHAR:
					amarelo_enunciado();
					printf("\n  Voltando ao menu anterior!\n\n");
					reset_cores();
					break;

				// Erro improvável, pois todas as exceções já foram tratadas
				default:
					vermelho_resposta();
					printf("\n  *Erro desconhecido!*\n");
					reset_cores();
			}
		}

		if(opcao_escolhida != OPCAO_SAIR_CHAR) {
			printf("\n\t<Digite ENTER para continuar>");
			obter_enter(); // Aguardando pelo ENTER do usuário
			printf("\n");
		}
	} while(opcao_escolhida != OPCAO_SAIR_CHAR);
}