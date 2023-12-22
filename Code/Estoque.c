#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX_EPIs 100

void Menu(){
	printf("\n====Estoque de EPI====\n");
	printf("1. Adicionar EPI\n");
	printf("2. Exibir EPI\n");
	printf("3. Atualizar EPI\n");
	printf("4. Excluir EPI\n");
	printf("0. Fechar programa\n");
	printf("======================\n");
	printf("Escolha uma opção: ");
}
typedef struct{
	char NOME[100];
	int CA;
	int QUANTIDADE;
	char VALIDADE[11];
}EPI;

void salvarDadosBinario(EPI listaEPIs[], int quantidadeEPIs) {
    FILE *file = fopen("estoque_epi.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }
    fwrite(&quantidadeEPIs, sizeof(int), 1, file);  
    fwrite(listaEPIs, sizeof(EPI), quantidadeEPIs, file); 
    fclose(file);
}
void carregarDadosBinario(EPI listaEPIs[], int *quantidadeEPIs) {
    FILE *file = fopen("estoque_epi.bin", "rb");
    if (file == NULL) {
        printf("Arquivo não encontrado. Iniciando com um estoque vazio.\n");
        return;
    }
    fread(quantidadeEPIs, sizeof(int), 1, file);  
    fread(listaEPIs, sizeof(EPI), *quantidadeEPIs, file);  
    fclose(file);
}


int main(){
	EPI epi;
	int OPCAO;
setlocale(LC_ALL,"Portuguese");
EPI listaEPIs[MAX_EPIs];
int quantidadeEPIs=0;
carregarDadosBinario(listaEPIs, &quantidadeEPIs);
do{
	Menu();
	scanf("%d",&OPCAO);
	system("cls");
switch(OPCAO){
	case 1:
		if(quantidadeEPIs<MAX_EPIs){
			printf("Inicie nomeando o EPI.[EX: Luva_de_proteção_química]\n");
			scanf("%99s",epi.NOME);
			printf("Agora informe o CA do EPI.\n");
			scanf("%d",&epi.CA);
			printf("Quantos desse EPI tem disponível?\n");
			scanf("%d",&epi.QUANTIDADE);
			printf("Qual a data de validade do EPI?[Considerar a mais proxíma]\n");
			scanf("%10s",&epi.VALIDADE);
			listaEPIs[quantidadeEPIs] = epi;
            quantidadeEPIs++;
		}
		else{
			printf("Capacidade máxima atingida. Exclua algum EPI ou contate o\n desenvolvedor");
		}
		salvarDadosBinario(listaEPIs, quantidadeEPIs);
	break;
    case 2: {
    int subOpcao;
    printf("1. Exibir todos os EPIs\n");
    printf("2. Buscar EPI pelo CA\n");
    printf("Escolha uma opção: ");
    scanf("%d", &subOpcao);

    if (subOpcao == 1) {
    	int i;
        for (i= 0; i < quantidadeEPIs; i++) {
            printf("EPI: %s, CA: %d, Quantidade: %d, Validade: %s\n", listaEPIs[i].NOME, listaEPIs[i].CA, listaEPIs[i].QUANTIDADE, listaEPIs[i].VALIDADE);
        }
    } else if (subOpcao == 2) {
        int i;
        int caBusca;
        printf("Informe o CA do EPI que deseja buscar: ");
        scanf("%d", &caBusca);
        int encontrado = 0;
        for (i=0; i < quantidadeEPIs; i++) {
            if (listaEPIs[i].CA == caBusca) {
                printf("EPI: %s, CA: %d, Quantidade: %d, Validade: %s\n", listaEPIs[i].NOME, listaEPIs[i].CA, listaEPIs[i].QUANTIDADE, listaEPIs[i].VALIDADE);
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("EPI com CA %d não encontrado.\n", caBusca);
        }
    } else {
        printf("Opção inválida.\n");
    }
    break;
}
    case 3: {
    int caBusca;
    printf("Informe o CA do EPI que deseja atualizar: ");
    scanf("%d", &caBusca);

    int encontrado = 0;
    int i;
    for (i=0; i < quantidadeEPIs; i++) {
        if (listaEPIs[i].CA == caBusca) {
            encontrado = 1;
            
            printf("Novo nome do EPI: ");
            scanf("%99s", listaEPIs[i].NOME);
            printf("Nova quantidade do EPI: ");
            scanf("%d", &listaEPIs[i].QUANTIDADE);
            printf("Nova validade do EPI: ");
            scanf("%10s", listaEPIs[i].VALIDADE);

            printf("EPI atualizado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("EPI com CA %d não encontrado.\n", caBusca);
    }
    salvarDadosBinario(listaEPIs, quantidadeEPIs);
    break;
}
    case 4: {
    int caBusca;
    printf("Informe o CA do EPI que deseja excluir: ");
    scanf("%d", &caBusca);

    int encontrado = 0;
    int i;
    for (i = 0; i < quantidadeEPIs; i++) {
        if (listaEPIs[i].CA == caBusca) {
            encontrado = 1;
            int j;
            for (j = i; j < quantidadeEPIs - 1; j++) {
                listaEPIs[j] = listaEPIs[j + 1];
            }
            quantidadeEPIs--; 
            printf("EPI com CA %d excluído com sucesso.\n", caBusca);
            break;
        }
    }
    if (!encontrado) {
        printf("EPI com CA %d não encontrado.\n", caBusca);
    }
    salvarDadosBinario(listaEPIs, quantidadeEPIs);
    break;
}
	case 0:
		printf("Saindo do programa. Até logo!\n");
		break;
default:
	printf("Opção inválida. Tente novamente.\n");
}
} while(OPCAO!=0);
system("pause");
return 0;
}