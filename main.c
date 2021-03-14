/**
 * Descrição:
 * 				Projeto de controle referente à vagas de um estacionamento
 * 				estruturado a partir do desenvolvimento metodológico em 
 * 				Linguagem C.
 * 				
 * 
 * Autoria: 	
 * 				Angelica dos Santos 		- santosangelicassp@gmail.com
 * 				Lucas Omar Andrade Leal 	- lucasomarandradeleal@gmail.com
 * 				Rhian Luis Garcia Moraes 	- rhian.garcia@sga.pucminas.br
 * 
 * Data inicial: 22/05/2020
 * 
 * Compilado da seguinte forma:
 * 		$ gcc -Wall main.c menu-principal.c opcoes-menu.c funcoes-utilitarias.c cores.c arquivos.c -o estacionamentos
 * 		$ ./estacionamentos
 **/

// Inclusão de bibliotecas
#include "header.h"

int main(void) {
	setlocale(LC_ALL, "Portuguese");

    rosa_titulo();
	printf("\n\t**************************************************       _.-.___\\__");
	printf("\n\t  ****    Bem-vindo ao EstacionaMentos™!    ******>-----|  _      _`-.");
	printf("\n\t    **********************************************     ='-(_)----(_)--`\n\n");
    reset_cores();

	menu_principal();

	return 0;
}