#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

#define TAMANHO 100

typedef struct
{
  char nome[TAMANHO];
  int telefone;
  char email[TAMANHO];
} Pessoa;

typedef struct
{
  int matricula;
  float salario;
  Pessoa pessoa;
} Funcionario;



int buscaBinaria(int posicaoInicial, int posicaoFinal, int vetorInteiro[], int valorProcurado){
  int posicaoMeio = (posicaoInicial + posicaoFinal)/2;
  if(posicaoFinal < posicaoInicial){
    return -1;
  }
  if(valorProcurado == vetorInteiro[posicaoMeio]){
    return posicaoMeio;
  }
  if(vetorInteiro[posicaoMeio] > valorProcurado){
    return buscaBinaria(posicaoInicial, (posicaoMeio-1), vetorInteiro, valorProcurado);
  }
  return buscaBinaria((posicaoMeio+1), posicaoFinal, vetorInteiro, valorProcurado);
}



int pesquisar(Funcionario funcionario[], int num, int *contador)
{
  int i;
  if (*contador < 0)
    return -1;
  for (i = 0; i < *contador; i++)
  {
    if (funcionario[i].matricula == num)
    {
      return i;
    }
  }
  return -1;
}
int validarMatricula()
{
  int num;
  do
  {
    printf("Coloque o número da matricula: ");
    scanf("%d", &num);
  } while (num < 1);
  return num;
}

int menu()
{
  int op;
  // system("@cls||clear"); // LIMPA A TELA
  printf("\n\nSISTEMA FOLHA DE PAGAMENTO\n\n");
  printf("1 - Inserir\n");
  printf("2 - Pesquisar por matricula\n");
  printf("3 - Pesquisar por nome\n");
  printf("4 - Aumentar\n");
  printf("5 - Diminuir\n");
  printf("6 - Excluir\n");
  printf("7 - Listar\n");
  printf("0 - Sair\n");
  do
  {
    printf("Escolha sua opção: ");
    scanf(" %d", &op);
  } while (op < 0 || op > 7);
  return op;
}

void inserirFuncionario(Funcionario vetorFuncionario[], int *contadorVetorFuncionario)
{
  Funcionario funcionario;
  printf("\nInserir o matricula: ");
  scanf("%d", &funcionario.matricula);
  int encontrar = pesquisar(vetorFuncionario, funcionario.matricula, contadorVetorFuncionario);
  if (encontrar == -1)
  {
    printf("Inserir o nome: ");
    scanf(" %100[^\n]s", funcionario.pessoa.nome);
    printf("Inserir o telefone: ");
    scanf("%d", &funcionario.pessoa.telefone);
    printf("Inserir o email: ");
    scanf(" %100[^\n]s", funcionario.pessoa.email);
    printf("Inserir o salario: ");
    scanf("%f", &funcionario.salario);
    vetorFuncionario[*contadorVetorFuncionario] = funcionario;
    *contadorVetorFuncionario = *contadorVetorFuncionario + 1;
  }
  else
  {
    printf("\n Essa matrícula já esta cadastrada! \n");
  }
}

void pesquisarMatricula(Funcionario funcionario[], int *contadorVetorFuncionario)
{
  int pesq, num;
  num = validarMatricula();
  pesq = pesquisar(funcionario, num, contadorVetorFuncionario);
  if (pesq != -1)
  {
    printf("%s\n", funcionario[pesq].pessoa.nome);
    printf("%d\n", funcionario[pesq].pessoa.telefone);
    printf("%s\n", funcionario[pesq].pessoa.email);
    printf("%.2f\n", funcionario[pesq].salario);
    printf("%d\n", funcionario[pesq].matricula);
  }
  else
  {
    printf("Não existe uma usuario com essa matricula");
  }
}

int pesquisarNome(Funcionario funcionario[], int *contadorVetorFuncionario)
{
  char nome[TAMANHO];
  printf("Digite o nome para pesquisar: ");
  scanf(" %100[^\n]s\n", nome);
  for (int i = 0; i <= *contadorVetorFuncionario; i++)
  {
    if (strcmp(funcionario[i].pessoa.nome, nome) == 0 && funcionario[i].matricula != 0)
    {
      printf("%s\n", funcionario[i].pessoa.nome);
      printf("%d\n", funcionario[i].pessoa.telefone);
      printf("%s\n", funcionario[i].pessoa.email);
      printf("%.2f\n", funcionario[i].salario);
      printf("%d\n", funcionario[i].matricula);
      return 0;
      break;
    }
  }
  printf("Não encontrado.\n");
  return 0;
}

void aumentarSalario(Funcionario funcionario[], int *contadorVetorFuncionario)
{
  int num, pesq;
  float valor;
  num = validarMatricula();
  pesq = pesquisar(funcionario, num, contadorVetorFuncionario);
  if (pesq != -1)
  {
    do
    {
      printf("Digite a porcentagem do aumento. ");
      scanf("%f", &valor);
      if (valor <= 0)
      {
        printf("\nInsira um valor maior que 0 \n");
      }
    } while (valor <= 0);
    funcionario[pesq].salario = funcionario[pesq].salario * valor / 100 + funcionario[pesq].salario;
    printf("Você aumentou o salário em R$ %.2f, no usuario: %d\n", valor, num);
  }
  else
  {
    printf("matricula não encontrada.");
  }
}
void diminuir(Funcionario funcionario[], int *contador)
{
  int i, num, tamanho = 0, pesq;
  float valor;
  num = validarMatricula();
  pesq = pesquisar(funcionario, num, contador);
  if (pesq != -1)
  {
    printf("Digite o valor que deseja diminuir: ");
    scanf("%f", &valor);
    if (funcionario[tamanho].salario >= valor)
    {
      funcionario[tamanho].salario -= valor;
      printf("Foi diminuirdo R$ %.2f, da matricula: %d\n", valor, num);
    }
    else
    {
      printf("não é possivel diminuir essa quantidade do salario .\n");
    }
  }
  else
  {
    printf("Matricula não encontrada.\n");
  }
}

void demitir(Funcionario funcionario[], int *contador)
{
  int num, pesq;
  float valor;
  num = validarMatricula();
  pesq = pesquisar(funcionario, num, contador);
  if (pesq != -1)
  {
    for (int i = 0; i < *contador; i++)
    {
      funcionario[i] = funcionario[i + 1];
    }
    *contador = *contador - 1;
    printf("Voce demitiu o funcionario com sucesso.\n");
  }
  else
  {
    printf("Funcionario não encontrado.\n");
  }
}

void listar(Funcionario funcionario[], int *contador)
{
  int i;
  if (*contador > -1)
  {
    for (i = 0; i < *contador; i++)
    {
      if (funcionario[i].matricula != 0)
      {
        printf("Número da matricula: %d\t", funcionario[i].matricula);
        printf("Salário: %.2f\n", funcionario[i].salario);
      }
    }
  }
  else
  {
    printf("Não existe nenhum funcionario.");
  }
}

void lerArquivo(Funcionario *vetorFuncionario, int *tamanho)
{
  FILE *arq;
  arq = fopen("folha_de_pagamento.bin", "rb");
  if (arq)
  {
    fread(&*tamanho, sizeof(int), 1, arq);
    fread(vetorFuncionario, sizeof(Funcionario), *tamanho, arq);
    fclose(arq);
  }
}

void gravarArquivo(Funcionario *vetorFuncionario, int tamanho)
{
  FILE *arq;
  arq = fopen("folha_de_pagamento.bin", "wb");
  fwrite(&tamanho, sizeof(int), 1, arq);
  fwrite(vetorFuncionario, sizeof(Funcionario), tamanho, arq);
  fclose(arq);
}

int main()
{
  setlocale(LC_ALL, "Portuguese");
  int vetor[11] = {0,1,2,3,4,5,6,8,9,10,11};
  int resultado =0;
  resultado = buscaBinaria(0, 10, vetor, 2);
  printf("---- %d -----", resultado);
  Funcionario vetorFuncionario[TAMANHO];
  int contadorVetorFuncionario = 0;
  int op = 30;
  lerArquivo(vetorFuncionario, &contadorVetorFuncionario);
  do
  {
    op = menu();
    switch (op)
    {
    case 0:
      gravarArquivo(vetorFuncionario, contadorVetorFuncionario);
      break;
    case 1:
      inserirFuncionario(vetorFuncionario, &contadorVetorFuncionario);
      break;
    case 2:
      pesquisarMatricula(vetorFuncionario, &contadorVetorFuncionario);
      break;
    case 3:
      pesquisarNome(vetorFuncionario, &contadorVetorFuncionario);
      break;
    case 4:
      aumentarSalario(vetorFuncionario, &contadorVetorFuncionario);
      break;
    case 5:
      diminuir(vetorFuncionario, &contadorVetorFuncionario);
      break;
    case 6:
      demitir(vetorFuncionario, &contadorVetorFuncionario);
      break;
    case 7:
      listar(vetorFuncionario, &contadorVetorFuncionario);
      break;
    default:
      printf("\n\nOpção inválida!\n\n");
    }
  } while (op != 0);
  return 0;
}