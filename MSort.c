#include <stdio.h>
#include <stdlib.h>
#define TAMANHO 4096
typedef struct _Endereco Endereco;
struct _Endereco
{
 char logradouro[72];
 char bairro[72];
 char cidade[72];
 char uf[72];
 char sigla[2];
 char cep[8];
 char lixo[2];
};

int main(int argc, char**argv)
{ 
 if (argc != 4)
 {
  fprintf(stderr, "Erro na chamada do comando.\n");
  fprintf(stderr, "Uso para o programa %s: [ARQUIVO1] [ARQUIVO2] [ARQUIVO ORDENADO].\n", argv[0]);
  return 1;
 }

 //preferi colocar a partir daqui pra nao instanciar nada caso os srgumentos de linha não estejam preenhidos
 FILE *arq, *saida, *saida2, *ordenado;
 Endereco e;
 Endereco e1;
 Endereco e2;
 int qt;
 int qtdArq1, qtdArq2;
 int c;
 int d;
 long posicao, primeiro, ultimo, meio;
 
 //arquivo de cep ordenado
 arq = fopen("cep_ordenado.dat", "r"); ////era f
 if (!arq)
 {
  //fprintf(stderr, "Arquivo %s não pode ser aberto para leitura\n", argv[1]);
  fprintf(stderr, "Erro na abertura do arquivo cep_ordenado.dat. O programa será abortado!");
  return 1;
 }
 saida = fopen(argv[1], "w"); 
 if (!saida)
 {
  fclose(arq);
  fprintf(stderr, "Arquivo %s não pode ser aberto para escrita\n", argv[1]);
  return 1;
 }
 saida2 = fopen(argv[2], "w");
 if (!saida2)
 {
  fclose(arq);
  fprintf(stderr, "Arquivo %s não pode ser aberto para escrita\n", argv[2]);
  return 1;
 }
    
 ordenado = fopen(argv[2], "w");
 if (!ordenado)
 {
  fclose(ordenado);
  fprintf(stderr, "Arquivo %s não pode ser aberto para escrita\n", argv[3]);
  return 1;
 }
 //se chegou aqui todos os arquivos passam bem =D
 qt = fread(&e, sizeof(Endereco), 1, arq);
 
 printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));

 while (qt > 0)
 {  
   srand(time(NULL));  
  int numero = rand();  
  
 /* printf("numero: %ld\n\n", numero);
  printf("aleatório: %ld\n\n", numero % 2);*/

  if (numero % 2 == 0) {// se o número aleatório for par eu mando pro arquivo par (saida2) do contrário vai para o impar   
   fwrite(&e, sizeof(Endereco), 1, saida2);   
   //printf("Escrevendo o %d no arquivo 2",e.cep);
   c++;
  }
  else {
   fwrite(&e, sizeof(Endereco), 1, saida);
   //printf("Escrevendo o %d no arquivo 2",e.cep);
   d++;
  }
  qt = fread(&e, sizeof(Endereco), 1, arq);
 }
 //aqui os arquivos ja estão prontinhos pra uso
 printf("Total de CEPs no arquivo 1: %d\n", d);
 
 printf("Total de CEPs no arquivo 2: %d\n", c);
 
 // pra garantir que está no inicio do arquivo
/*rewind(qtdArq1);
 rewind(qtdArq2);*/
 //printf("...............................");
 qtdArq1 = fread(&e1, sizeof(Endereco), 1, saida); 
 qtdArq2 = fread(&e2, sizeof(Endereco), 1, saida2);
// printf("...............................");
 while (qtdArq1 > 0 && qtdArq1 > 0)  {
  if (e1.cep < e2.cep) {
  // printf("Arquivo1 é maior que o arquivo 2");
   fwrite(&e1, sizeof(Endereco), 1, ordenado);
   qtdArq1 = fread(&e1, sizeof(Endereco), 1, saida);
  }
  else {
    //printf("Arquivo2 é maior que o arquivo 1");
   fwrite(&e2, sizeof(Endereco), 1, ordenado);
   qtdArq2 = fread(&e2, sizeof(Endereco), 1, saida2);
  }
 }

 printf("Pegando os remanescentes dos arquivos");

 while (qtdArq1 > 0) {
  fwrite(&e1, sizeof(Endereco), 1, ordenado);
  qtdArq1 = fread(&e1, sizeof(Endereco), 1, saida);
 }
 while (qtdArq2 > 0) {
  fwrite(&e2, sizeof(Endereco), 1, ordenado);
  qtdArq2 = fread(&e2, sizeof(Endereco), 1, saida2);
 }
    
 fclose(arq);
 fclose(saida);
 fclose(saida2);
 fclose(ordenado);
 printf("Processo finalizado!");
 return 0;
}

