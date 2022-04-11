#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<locale.h>
#include<string.h>

struct data{//struct para as datas
	int dia;
	int mes;
	int ano;
};

struct contato{//struct para os contatos
	char nome[30];
	char telefone[15];
	char email[20];
	data aniv;
};

struct eventos{//struct para os eventos
	char nome[30];
	data evento;
};

void cabecalho(); 
void input(); 
void listar();
void pesquisar();
void anivMes();
void editar_contacto();
void remover_contato();
void remover_evento();
void adicionar_evento();
void listar_evento();
void alterar_senha();
int senha_final = 123456;


int main(){
	setlocale(LC_ALL,"Portuguese");//Permite adicionar caracteres especiais
	int senha;
	
	int opc;
	cabecalho();
	printf("     Tela de Login\n\n");
	
	printf("Digite a senha: ");
	scanf("%i",&senha);
	if(senha!=senha_final){
		do{
			printf("Senha invalida!\n");
			printf("Digite a senha novamente: ");
			scanf("%i",&senha);
		}while(senha!=senha_final);
		printf("Acesso Liberado!");
		getch();
	}else{
		printf("Acesso Liberado!");
		getch();
	}
	do{//mostra o menu de op��es
		cabecalho();
		printf("Contato\n\n");
		printf("1- Inserir novo contato\n");
		printf("2- Listar contatos\n");
		printf("3- Pesquisar contato\n");
		printf("4- Remover Contato\n\n");
		printf("=============================\n\n");
		printf("Anivers�rio\n\n");
		printf("5- Aniversariante do mes\n\n");
		printf("=============================\n\n");
		printf("Evento\n\n");
		printf("6- Inserir novo evento\n");
		printf("7- Listar evento\n");
		printf("8- Remover evento\n\n");
		printf("9- Sair\n\n");
		printf("Escolha uma op��o: ");
		scanf("%d",&opc);
		
		//switch que leva para a op��o desejada
		switch(opc){
			case 1:
				input();//chama a fun��o de adicionar usu�rios
			break;
			
			case 2:
				listar();//chama a fun��o para listar os contatos
			break;
			
			case 3:
				pesquisar();//chama a fun��o para a pesquisa de contato
			break;
			
			case 4:
				remover_contato();//chama a fun��o de excluir o contato selecionado
			break;
			
			case 5:
				anivMes();//chama a fun��o para mostrar os anivers�riantes do m�s selecionado
			break;
			
			case 6:
				adicionar_evento();//chama a fun��o de adicionar um evento
			break;
			
			case 7:
				listar_evento();//chama a fun�a� de listar os eventos
			break;
			
			case 8:
				remover_evento();//chama a fun��o para remover o evento
			break;
			
			
			case 9:
				printf("Saindo....");//op��o para sa�r do programa
			break;
			
			default:
				printf("Op��o invalida!");
				getch();
			break;
		}	
	}while(opc != 9);	
}

void cabecalho(){//fun��o para adicionar o cabe�alho 
	system("cls");//comando para limpar a tela
	printf("--------------------------\n");
	printf("\tAGENDA");
	printf("\n--------------------------\n\n");
}

void input(){//fun��o para adicionar um novo contato
	
	FILE* arquivo;//ponteiro que aponta para o arquivo
	contato ctt;//variavel temporaria
	arquivo = fopen("agenda.txt","ab");//abre o arquivo em binario(por quest�o de seguran�a), se o arquivo existir, 
									     //grava as informa��es no final do arquivo, e se o arquivo n�o existir, criar um arquivo com o nome agenda.txt
	
	if(arquivo ==  NULL){
		printf("Erro ao abrir o arquivo!");//caso aconte�a erros ao abrir o arquivo, retorna a mensagem de erro
	}else{
		do{
			cabecalho();//chama a fun��o de cabe�alho
			printf("     Adicionar Novo Contato\n\n");
			fflush(stdin);//comando para limpas o buffer do teclado
			printf("Digite o nome: ");
			gets(ctt.nome);//captura o nome do contato
			
			printf("Digite o n�mero: ");
			gets(ctt.telefone);//captura o telefone do contato
			
			printf("Digite o email: ");
			gets(ctt.email);//captura o email do contato
			
			printf("Digite a data de anivers�rio: ");
			scanf("%d %d %d",&ctt.aniv.dia,&ctt.aniv.mes,&ctt.aniv.ano);//captura a data de anivers�rio
			
			fwrite(&ctt, sizeof(contato),1,arquivo);//grava as informa��es na variavel arquivo, sizeof serve para pegar o tamanho exato do contato
			
			printf("Deseja adicionar mais contatos(s/n): ");
			 	
		}while(getche() == 's');//while para cadastrar mais um contato caso seja digitado "s"
		fclose(arquivo);//fecha o arquivo pora evitar perca de dados
	}
}

void adicionar_evento(){//fun��o para adicionar um evento, muito parecida com a fun��o de adicionar um contato, 
						//por�m grava os dados em um arquivo separado e tem menos dados de entrada
	
	FILE* arquivo_eventos; // criando a vari�vel ponteiro para o arquivo
	eventos evt;
	arquivo_eventos = fopen("agenda_evento.txt","ab"); //abre o arquivo em binario(por quest�o de seguran�a), se o arquivo existir, 
									     				//grava as informa��es no final do arquivo, e se o arquivo n�o existir, criar um arquivo com o nome agenda_envento.txt
	
	if(arquivo_eventos ==  NULL){ //erro em abrir o arquivo
		printf("Erro ao abrir o arquivo!");
	}else{
		do{
			cabecalho();
			printf("     Adicionar novo evento\n\n");
			fflush(stdin); //limpar o buffer do teclado
			printf("Digite o nome do evento: ");
			gets(evt.nome);
			
			printf("Digite a data: ");
			scanf("%d %d %d",&evt.evento.dia,&evt.evento.mes,&evt.evento.ano);
			
			fwrite(&evt, sizeof(eventos),1,arquivo_eventos); //escreve o conte�do da string para o stream de arquivo apontado
			
			printf("Deseja adicionar mais eventos(s/n): ");
			
		}while(getche() == 's');   
		fclose(arquivo_eventos);  //fecha o arquivo pora evitar perca de dados
	}
}

void listar(){//fun��o que mostra na tela todos os contatos
	
	FILE* arquivo; // criando a vari�vel ponteiro para o arquivo
	contato ctt;
	
	arquivo = fopen("agenda.txt","rb");//abre o arquivo binario em modo de leitura
	cabecalho();
	printf("     Seu Contatos\n\n");
	
	if(arquivo ==  NULL){  //erro em abrir o arquivo
		printf("Erro ao abrir o arquivo!");//retorna mensagem de erro se tiver erro ao abrir o arquivo
	}else{
			while(fread(&ctt,sizeof(contato),1,arquivo)==1){//while para rodar enquanto estiver retornando uma linha
				//mostra as informa��es contidas no arquivo
				printf("Nome: %s\n",ctt.nome);
				printf("Fone: %s\n",ctt.telefone);
				printf("Email: %s\n",ctt.email);
				printf("Anivers�rio: %d/ %d/ %d\n",ctt.aniv.dia, ctt.aniv.mes,ctt.aniv.ano);
				printf("------------------------\n");
			}
		fclose(arquivo);//fecha o arquivo pora evitar perca de dados
		getch();//apenas para fazer o programa esperar at� que o usu�rio digite alguma tecla
	}
}

void listar_evento(){//fun��o para listar um evento, muito parecida com a fun��o de listar um contato, por�m l� os dados em um arquivo separado
	FILE* arquivo_eventos; // criando a vari�vel ponteiro para o arquivo
	eventos evt;
	
	arquivo_eventos = fopen("agenda_evento.txt","rb"); //abre o arquivo binario em modo de leitura
	cabecalho();
	printf("     Seu Eventos\n\n");
	
	if(arquivo_eventos ==  NULL){
		printf("Erro ao abrir o arquivo");
	}else{
			while(fread(&evt,sizeof(eventos),1,arquivo_eventos)==1){
				printf("Nome: %s\n",evt.nome);
				printf("Data: %d/ %d/ %d\n",evt.evento.dia,evt.evento.mes,evt.evento.ano);
				printf("------------------------\n");
			}
		fclose(arquivo_eventos); //fecha o arquivo pora evitar perca de dados
		getch();
	}
}

void pesquisar(){//fun��o para pesquisar um contato em espec�fico

	FILE* arquivo;// criando a vari�vel ponteiro para o arquivo
	contato ctt;
	char nome[30];//string para receber o nome a ser pesquisado
	
	arquivo = fopen("agenda.txt","rb"); //abre o arquivo binario em modo de leitura
	cabecalho();
	printf("     Buscar Contato Pelo Nome\n\n");
	
	if(arquivo ==  NULL){ //erro em abrir o arquivo
		printf("Erro ao abrir o arquivo!");
	}else{
		fflush(stdin);//limpa o buffer do teclado
		printf("Digite o nome para a busca: ");
		gets(nome);	
		//o trecho abaixo vai fazer a leitura de linha por linha e comparar pelo nome
		while(fread(&ctt,sizeof(contato),1,arquivo)==1){
			if(strcmp(nome,ctt.nome)==0){
				printf("\n------------------------\n");
				printf("Nome: %s\n",ctt.nome);
				printf("Fone: %s\n",ctt.telefone);
				printf("Email: %s\n",ctt.email);
				printf("Anivers�rio: %d/ %d/ %d\n",ctt.aniv.dia, ctt.aniv.mes,ctt.aniv.ano);
				printf("------------------------\n");
			}else{
				getch();
			}
		}
		fclose(arquivo);
		getch();
	}
}
void anivMes(){//fun��o para mostrar os aniversariantes do m�s selecionado(funciona de forma parecida com a fun��o de busca)
	FILE* arquivo;// criando a vari�vel ponteiro para o arquivo
	contato ctt;
	
	arquivo = fopen("agenda.txt","rb");//abre o arquivo binario em modo de leitura
	cabecalho();
	printf("     Aniversariantes!\n\n");
	
	if(arquivo ==  NULL){ //erro em abrir o arquivo
		printf("Erro ao abrir o arquivo");
	}else{
		int mes;
		
		printf("Digite o m�s: ");
		scanf("%d",&mes);
		//o trecho abaixo vai fazer a leitura de linha por linha e comparar pelo nome
		while(fread(&ctt,sizeof(contato),1,arquivo)==1){
			if(mes==ctt.aniv.mes){
			
				printf("\n------------------------\n");
					printf("Nome: %s\n",ctt.nome);
					printf("Fone: %s\n",ctt.telefone);
					printf("Email: %s\n",ctt.email);
					printf("Anivers�rio: %d/ %d/ %d\n",ctt.aniv.dia, ctt.aniv.mes,ctt.aniv.ano);
					printf("------------------------\n");
			}
		}
	}
	fclose(arquivo);
	getch();
}

void remover_contato(){//fun��o para excluir contatos
	
	 FILE* arquivo;// criando a vari�vel ponteiro para o arquivo
	 FILE* temp;// criando a vari�vel ponteiro para o arquivo temporario
	 contato ctt;
	 char nome[30];
	 
	 arquivo = fopen("agenda.txt","rb");//abrir em modo rb leitura binaria
	 temp = fopen("tmp.txt","wb"); //abrir em modo wb ele limpa e grava binario
	 
	 if(arquivo==NULL&&temp==NULL){
		printf("Problemas na abertura do arquivo!\n");
		getch();
	 }else{
		cabecalho();
		printf("     Excluir Contatos\n\n");
		fflush(stdin);
		printf("Digite o nome a deletar: ");
		gets(nome);
		while(fread(&ctt,sizeof(contato),1,arquivo)==1){
			if(strcmp(nome,ctt.nome)==0){
				printf("Nome: %s\n",ctt.nome);
			    printf("Fone: %s\n",ctt.telefone);
				printf("Email: %s\n",ctt.email);
			    printf("Anivers�rio: %d/%d/%d\n",ctt.aniv.dia,ctt.aniv.mes,ctt.aniv.ano);
			    printf("-------------------------------------------------\n");
	        }else{
		    	fwrite(&ctt,sizeof(contato),1,temp);//gravando os dados no arquivo temp
	  	    }	
	    } 
	    fclose(arquivo);//fechar o arq
	    fclose(temp);//fechar o temp
	    fflush(stdin);
	    
		   printf("Deseja deletar (s/n)? ");
		   if(getche()=='s'){
		   //ser� removido o arquivo "agenda.txt" e renomeado o arquivo "tmp.txt" para "agenda.txt"
		      if(remove("agenda.txt")==0&&rename("tmp.txt","agenda.txt")==0){//verifica se as operacoes foram 
			  																		//realizadas com sucesso!
		    	printf("\nOperacao realizada com sucesso!");
		      }else{
		        remove("tmp.txt");//remover o arquivo tmp se acondicao foi "n" na hora de deletar
		      }
		    }
		  fclose(temp);
		  fclose(arquivo);
		  getch();
		 
	}
}

void remover_evento(){//Fun��o para remover os eventos, muito parecida com a fun��o de excluir um contato, por�m l� e edita os dados em um arquivo separado
	
	 FILE* arquivo_eventos;
	 FILE* temp2;
	 eventos evt;
	 char nome[30];
	 
	 arquivo_eventos = fopen("agenda_evento.txt","rb");//abrir em modo rb leitura binaria
	 temp2 = fopen("tmp2.txt","wb"); //abrir em modo wb ele limpa e grava binario
	 
	 if(arquivo_eventos==NULL&&temp2==NULL){
		printf("Problemas na abertura do arquivo!\n");
		getch();
	 }else{
		cabecalho();
		printf("     Excluir Eventos\n\n");
		fflush(stdin);
		printf("Digite o nome do evento que deseja deletar: ");
		gets(nome);
		while(fread(&evt,sizeof(eventos),1,arquivo_eventos)==1){
			if(strcmp(nome,evt.nome)==0){
				printf("Nome: %s\n",evt.nome);
				printf("Data: %d/%d/%d\n",evt.evento.dia,evt.evento.mes,evt.evento.ano);
				printf("-------------------------------------------------\n");
	        }else{
	   			fwrite(&evt,sizeof(eventos),1,temp2);
	       }
	    }
		  fclose(arquivo_eventos);//fechar o arq
		  fclose(temp2);//fechar o temp
		  fflush(stdin);
		  printf("Deseja deletar (s/n)? ");
		  if(getche()=='s'){
		   	if(remove("agenda_evento.txt")==0&&rename("tmp2.txt","agenda_evento.txt")==0){//verifica se as operacoes foram realizadas com sucesso!
		    	printf("\nOperacao realizada com sucesso!");
		    }else{
		    remove("tmp2.txt");
		    }
		  }
		  fclose(temp2);
		  fclose(arquivo_eventos);
		  getch();	 
	}
}
