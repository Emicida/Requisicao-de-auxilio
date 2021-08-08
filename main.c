#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>


//variavel global de numero de alunos registrados
int num_alunos = 0;
//variavel global de pesquisa por CPF de aluno
char cpf_pesquisa[13];

//numero de vagas pré-estipulado
int n_vagas = 15;

//menor indicie socioeconomico
float menor_ind = 0.0;

struct auxilio{
	//dados pessoais
	char nome_completo[60][99];
	char cpf[13][99];
	char idade[10][99];
	char curso[55][99];
	int fase[99];
	char numero_individuos[3][99];//numero de individuos do grupo familiar
	
	//dados economicos
	float ise[99]; //índice socioeconhomico
	float rf[99];//renda familiar bruta mensal
	float me[99];//moradia do estudante
	float ddc[99];//desoesas com tratamento de doença cronica no nucleo familiar
	float dtc[99];//despesa com transporte coletivo
	float vaas[99];//valor de abatimento para agravantes sociais

} aux;

int registrar(){
	system("color 1F");
	printf("\t\n================================================================================\n");
	if(n_vagas > 0){
		
		printf("\n\t\tRegistro de Aluno\n");
		
		printf("\n\t\tINFORMACOES PESSOAIS\n\n");
		
		FILE *pont_arquivo;
		pont_arquivo = fopen("Dados dos Alunos.txt", "a");
		
		printf("Nome completo: \n");
		scanf("%s", &aux.nome_completo[num_alunos]);
		fflush(stdin);
		fprintf( pont_arquivo, "\n\n Nome completo: "); // mensagem manual
		fputs(aux.nome_completo[num_alunos], pont_arquivo); // colocar string
		
		printf("CPF: \n");
		scanf("%s", &aux.cpf[num_alunos]);
		fflush(stdin);
		fprintf( pont_arquivo, "\n CPF: ");
		fputs(aux.cpf[num_alunos], pont_arquivo);
		
		printf("Data de nascimento: \n");
		scanf("%s", &aux.idade[num_alunos]);
		fflush(stdin);
		fprintf( pont_arquivo, "\n Idade: "); 
		fputs(aux.idade[num_alunos], pont_arquivo);
		
		printf("Curso: \n");
		scanf("%s", &aux.curso[num_alunos]);
		fflush(stdin);
		fprintf( pont_arquivo, "\n Curso: ");
		fputs(aux.curso[num_alunos], pont_arquivo);
		
		printf("Fase: \n");
		scanf("%s", &aux.fase[num_alunos]);
		fflush(stdin); 
		fprintf( pont_arquivo, "\n Fase: ");
		fputc(aux.fase[num_alunos], pont_arquivo);
		
		printf("Número de indivíduos do grupo familiar: \n");
		scanf("%s", &aux.numero_individuos[num_alunos]);
		fflush(stdin);
		fprintf( pont_arquivo, "\n Numero de individuos do grupo familiar: "); 
		fputs(aux.numero_individuos[num_alunos], pont_arquivo);
	
		printf("Renda Familiar Bruta Mensal: \n");
		scanf("%f", &aux.rf[num_alunos]);
		fprintf(pont_arquivo, "\n RF: ");
		fprintf(pont_arquivo,"%f",aux.rf);
	
		printf("Moradia do Estudante:\n \tAlugada= 0,8\n \tFinanciada= 0,9\n \tPrópria quitada\n ou \tCedida= 1\n");
		scanf("%f", &aux.me[num_alunos]);
		fprintf(pont_arquivo, "\n ME: ");
		fprintf(pont_arquivo,"%f",aux.me);
		
		printf(" Despesa com tratamento de Doença Crônica no núcleo familiar: \n \tSim = 0,9\n \tNão = 1\n");
		scanf("%f",&aux.ddc[num_alunos]);
		fprintf(pont_arquivo, "\n DDC: ");
		fprintf(pont_arquivo,"%f",aux.ddc);
	
		printf("Despesas com transporte coletivo: \n");
		scanf("%f", &aux.dtc[num_alunos]);
		fprintf(pont_arquivo, "\n DTC: ");
		fprintf(pont_arquivo,"%f",aux.dtc);
		
		printf("Valor de abatimento para agravantes sociais:\t \n Definidas em 0,7 (Leve) até 1(Grave) \n");
		scanf("%f", &aux.vaas[num_alunos]);
		fprintf(pont_arquivo, "\n VAAS: ");
		fprintf(pont_arquivo,"%f",aux.vaas);
	
		fclose(pont_arquivo); //fechar arquivo
		
		//sistema para verificar se o aluno da udesc pode ter acesso a auxílios e bolsas
		aux.ise[num_alunos] = (aux.rf[num_alunos] * aux.me[num_alunos] * aux.ddc[num_alunos] * aux.dtc[num_alunos] * aux.vaas[num_alunos]) / ((strtol(aux.numero_individuos[num_alunos],NULL,10)) * 100);	
		printf("%f",aux.ise);
		/*
		O menor indicie é registrado na id num_alunos, o primeiro registro é obrigatoriamente o menor
		mas se os proximos forem menores que o útlimo a ser registrado, ele passa a ser o menor indicie atual
	*/
	
	//se for o 1°
	if(num_alunos==0){
		menor_ind = aux.ise[num_alunos];	
	}
	
	else{
		//se for o segundo, terceiro e assim por diante
		for(num_alunos=!0;num_alunos++;n_vagas--){
			//ex: se aux.ise[1] < aux.ise[0] então...
			if(aux.ise[num_alunos]<menor_ind){
				menor_ind = aux.ise[num_alunos];
			}
			else{
				printf("Não há mais vagas");
			}		
		}
	}
	num_alunos++;
printf("\t\n================================================================================\n");	
	}
}
int visualizaDetalhado(){
	printf("\t\n================================================================================\n");
	int i = 0, achou = 0;
	printf("CPF do aluno a ser encontrado: ");
	scanf("%s", &cpf_pesquisa);
	if(num_alunos>0){
			do{	
				if(strcmp(aux.cpf[i],cpf_pesquisa) == 0){
					printf("\tNome Completo: %s", aux.nome_completo[i]);
					printf("\t\tDADOS PESSOAIS\n");
					printf("\t\tCPF: %s\n", aux.cpf[i]);
					printf("\t\tData de nascimento: %s anos\n", aux.idade[i]);
					printf("\t\tCurso: %s,  %dº fase \n", aux.curso[i], aux.fase[i]);
					printf("\t\tNúmero de individuos do grupo familiar: %s\n", aux.numero_individuos[i]);
					achou ++;
					i = num_alunos;
				}
				else{
					i++;	
				}
			}while(i<num_alunos);
	if(achou == 0){
			printf("Aluno não encontrado \n", i);
		}
	}
	else{
		printf("Nao há alunos registrados ainda.\n");
	}
	printf("\t\n================================================================================\n");
}

//gera uma lista de todos os alunos registrados
int visualizaTodos(){
	int i;
	printf("\t\n================================================================================\n");
	if(num_alunos>0){
		for(i=0; i<num_alunos; i++){
			printf("ID: %d\n", i);
			printf("Nome: %s\n",  aux.nome_completo[i]);
		}
	}
	else{
		printf("Não há alunos registrados ainda");
	}
	printf("\t\n================================================================================\n");
}

//lista os nomes dos alunos que têm auxílio
int verificaAuxilio(){
	printf("\t\n================================================================================\n");
	if(num_alunos>0){
		
	}else{
		printf("Não há alunos registrados ainda\n");
	}
	printf("\t\n===============================================================================\n");
}

int main(int argc, char *argv[]){
	system("color 1F");
	setlocale(LC_ALL,"Portuguese");
	FILE *file;
	file = fopen("Dados dos Alunos.txt", "w");
	fprintf( file, "Alunos requerentes");
	fclose(file); //fechar arquivo
	
	int escolha, verif=1;
	system("color 1F");
	do{
		//menu de opções
		printf("\t\tSistema de Auxílio/Bolsas da UDESC\n");
		printf("\n\t\t0 - Registrar um aluno novo\n");
		printf("\t\t1 - Visualizar que alunos recebem auxilio\n");
		printf("\t\t2 - Visualizar todos os alunos\n");
		printf("\t\t3 - Visualizar dados de aluno específio\n");
		printf("\t\t4 - Limpar a tela\n");
		printf("\t\t5 - Finalizar o programa\n");
		printf("\n\t\tEscolha... ");
		scanf("%d", &escolha);
		switch(escolha){
			//registro de alunos
			case 0:
				registrar();
				verif = 1;		
			break;
			
			//Visualização de quem recebe auxilio/bolsas
			case 1:
				verificaAuxilio();
				verif = 1;
			break;
			
			//Visualização de todos os alunos registrados
			case 2:
				visualizaTodos();
				verif = 1;
			break;
			
			//visualização de dados de aluno especifico
			case 3:
				visualizaDetalhado();
				verif = 1;
			break;
			//encerrar o programa
			case 4:
				system("cls");
			break;
			
			case 5:
				verif = 0;
				system("cls");
			break;
			
			default:
				verif = 1;
				system("cls");
			break;
		}
	}while(verif == 1);
	system("pause");
	return 0;
}
