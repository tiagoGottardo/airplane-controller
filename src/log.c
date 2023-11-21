//para ler e adicionar coisas num arquivo
#include<stdio.h>
#include<stdlib.h>

void le_arquivo (FILE **arquivo)
{
    FILE *farq=*arquivo;
  char texto[1000], nomeDoArquivo[1000];
  printf("Qual é o nome do seu arquivo?");
  scanf("%s",nomeDoArquivo);
    getchar();  

  
  farq = fopen (nomeDoArquivo, "w+");
  

  if (farq == NULL)
    {
      printf ("\nProblemas em escrever no arquivo!");
    }

  printf ("\nDigite o que voce quer digitar no arquivo: ");
  fgets (texto,1000, stdin );
    
  fprintf (farq, "%s", texto);

  fclose (farq);

}
/* EXEMPLO DE COMO ELE FICA COM A MAIN:
#include<stdio.h>
#include<stdlib.h>

void le_arquivo (FILE **arquivo)
{
    FILE *farq=*arquivo;
  char texto[1000], nomeDoArquivo[1000];
  printf("Qual é o nome do seu arquivo?");
  scanf("%s",nomeDoArquivo);
    getchar();  

  
  farq = fopen (nomeDoArquivo, "w+");
  

  if (farq == NULL)
    {
      printf ("\nProblemas em escrever no arquivo!");
    }

  printf ("\nDigite o que voce quer digitar no arquivo: ");
  fgets (texto,1000, stdin );
    
  fprintf (farq, "%s", texto);

  fclose (farq);

}

int
main ()
{
    FILE *farq;
    le_arquivo ( &farq);
    
return 0;
}*/