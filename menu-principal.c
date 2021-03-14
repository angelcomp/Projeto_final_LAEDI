#include "header.h"

// Menu principal
void menu_principal() {
	// Declaração de variáveis	
	rua ruas[MAX_RUAS];
	int num_ruas;

	// Marca com 1 as opções que são exigidas para uma opção
	// poder ser ativada: opcoes_exigidas[2] é {1, 1, 0, 0, 0, 0},
	// ou seja, a opção 3 exige que as opções 1 e 2 já tenham sido
	// selecionadas antes
	const int opcoes_exigidas[NUM_OPCOES][NUM_OPCOES] = {
		{0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0},
		{1, 1, 1, 0, 0, 0},
		{1, 1, 1, 1, 0, 0},
		{1, 0, 0, 0, 0, 0}
	};
	
	// Variável que indica quantas vezes uma opção pode ser acessada, 0 significa infinito
	const int limite_acessos_opcao[NUM_OPCOES] = {1, 1, 1, 0, 0, 0};

	int opcao;
	int opcoes_escolhidas[NUM_OPCOES] = {0,0,0,0,0};

	int acumulador_clientes = 0;
	float acumulador_precos = 0;

	// Tentando ler do arquivo e armazenando em uma variável
	rua ruas_arq[MAX_RUAS];
	int num_ruas_arq;

	// Variáveis utilizadas para perguntas de Y/n neste escopo
	// Também são utilizadas no switch mais pra frente
	char op;
	int op_valida;
	int continuar_operacao;

	if(ler_ruas_de_arquivo(NOME_ARQUIVO_RUAS, ruas_arq, &num_ruas_arq) == 0) {

		// Perguntar para o usuário se ele quer obter esses dados
		branco_opcoes();
		printf("\n\tFoi detectado um arquivo contendo dados sobre o estacionamento.\n");
		reset_cores();		
		do {
			amarelo_enunciado();
			printf("\n  Deseja abrir? (Y/n): ");
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
			// Copiando as ruas lidas do arquivo para o arquivo principal
			num_ruas = num_ruas_arq;
			for (size_t i = 0; i < num_ruas; i++) {
				ruas[i] = ruas_arq[i];
			}

			// Definir as opções 1, 2 e 3 como já escolhidas
			opcoes_escolhidas[0] = 1;
			opcoes_escolhidas[1] = 1;
			opcoes_escolhidas[2] = 1;
		}
	}
	
	// Iniciar menu
	do {
		menu_mostrar_opcoes(opcoes_exigidas, opcoes_escolhidas);

		// Ler e validar a opção
		int opcao_valida;
		do {
			amarelo_enunciado();
			printf("\n  Digite uma opção.\n");
			printf("  >> ");
			reset_cores();
			scanf("%d", &opcao);
			getchar();

			opcao_valida = (opcao >= 1 && opcao <= NUM_OPCOES) || opcao == OPCAO_SAIR;
			if(!opcao_valida) {
				vermelho_resposta();
				printf("\n  *Erro: opção inválida!*\n");
				reset_cores();
			}
		} while (!opcao_valida);

		// Não pedir para digitar enter se estiver saindo
		int pedir_confirmacao_enter = opcao != OPCAO_SAIR;
		// Por padrão, contar quantas vezes o usuário selecionou a opção
		int incrementar_opcao_escolhida = 1;

		// Variável que representa a primeira opção (de 1 a 6) que falta, se for 0 então nenhuma falta
		int opcao_faltante = 0;

		if(opcao != OPCAO_SAIR) {
			// Para cada uma das opções
			for (int i = 0; i < NUM_OPCOES; i++) {
				// Se esta opção for exigida pela que o usuário escolheu, mas não tiver sido escolhida
				if(opcoes_exigidas[opcao - 1][i] && !opcoes_escolhidas[i]) {
					opcao_faltante = i+1; // Marque-a como a faltante
					break;
				}
			}
		}
		// Se alguma opção faltar
		if(opcao_faltante != 0) {
			// Não incremente-a e mostre um aviso ao usuário
			incrementar_opcao_escolhida = 0;

			vermelho_resposta();
			printf("\n  *Esta opção requer que a opção %d seja acessada primeiro!*\n", opcao_faltante);
			reset_cores();
		
		// Se essa opção for escolhida em seu limite
		} else if(opcoes_escolhidas[opcao - 1] >= limite_acessos_opcao[opcao - 1] && limite_acessos_opcao[opcao - 1] != 0) {
			// Não incremente-a e mostre um aviso ao usuário
			incrementar_opcao_escolhida = 0;

			vermelho_resposta();
			printf("\n  *Esta opção já foi escolhida vezes o suficiente!*\n");
			reset_cores();

		} else { // Caso esteja tudo certo
			switch(opcao) {
				case 1:
					num_ruas = menu_cadastrar_ruas(ruas);
					break;
				case 2:
					menu_cadastrar_vagas(ruas, num_ruas);
					break;
				case 3:
					menu_cadastrar_valor(ruas, num_ruas);
					break;
				case 4:
					menu_estacionar_carro(ruas, num_ruas, &acumulador_clientes, &acumulador_precos);
					break;
				case 5:
					menu_liberar_vaga(ruas, num_ruas);
					break;
				case 6:
					menu_mostrar_relatorios(ruas, num_ruas, opcoes_escolhidas, acumulador_clientes, acumulador_precos);
					pedir_confirmacao_enter = 0;
					break;

				case OPCAO_SAIR:
					// Se o usuário tiver escolhido as 3 primeiras opções, ele pode salvar
					// os dados do arquivo em um arquivo se desejar
					if(opcoes_escolhidas[0] && opcoes_escolhidas[1] && opcoes_escolhidas[2]) {
						branco_opcoes();
						printf("\n\tOs dados das ruas desta sessão podem ser salvos em um arquivo.\n");
						reset_cores();
						do {
							amarelo_enunciado();
							printf("\n  Deseja salvá-los? (Y/n): ");
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
							switch (escrever_ruas_em_arquivo(NOME_ARQUIVO_RUAS, ruas, num_ruas)) {
								case 0:
									verde_resposta();
									printf("\n  Dados gravados com sucesso!\n");
									reset_cores();
									break;
								case 1:
									vermelho_resposta();
									printf("\n  Erro ao abrir o arquivo!\n");
									reset_cores();
									break;
								case 2:
									vermelho_resposta();
									printf("\n  Erro ao gravar no arquivo!\n");
									reset_cores();
									break;	

								default:
									break;
							}
						}
					}

					azul_enunciado();
					printf("\n\t*********************************************            _.-.___\\__");
					printf("\n\t  *******          Bye-bye!!!         *******>----------|  _      _`-.");
					printf("\n\t*********************************************          ='-(_)----(_)--`\n\n");
					reset_cores();
					break;

				default:
					vermelho_resposta();
					printf("\n  *Opção inválida, erro desconhecido!*\n");
					incrementar_opcao_escolhida = 0;
					reset_cores();
			}
		}

		if(pedir_confirmacao_enter) {
			printf("\n\t<Digite ENTER para continuar>");
			obter_enter(); // Aguardando pelo ENTER do usuário
			printf("\n");
		}
		if(opcao != OPCAO_SAIR && incrementar_opcao_escolhida) {
			opcoes_escolhidas[opcao - 1]++;
		}
		
	} while(opcao != OPCAO_SAIR);
}