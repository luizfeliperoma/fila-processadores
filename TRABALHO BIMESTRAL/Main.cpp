#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include "TAD.h"

void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)
{
	int i;
	textcolor(CorT);
	textbackground(CorF);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CI,LF);
	printf("%c",200); 
	gotoxy(CF,LF);
	printf("%c",188);
	
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI);
		printf("%c",205);
		
		gotoxy(i,LF);
		printf("%c",205);
	}
	
	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i);
		printf("%c",186);
		
		gotoxy(CF,i);
		printf("%c",186);
	}
	textcolor(7);
	textbackground(0);
}

void MolduraProc(int quant, int ut)
{
	int LI=5,LF=7,linha=6,proc=1;
	gotoxy(48,5);printf("PRESSIONE A TECLA RESPECTIVA");
	gotoxy(51,6);printf("PARA DESATIVAR/ATIVAR");
	gotoxy(50,7);printf("O PROCESSADOR ESCOLHIDO");
	
	gotoxy(46,10);printf("['G'] - Gravacao em Disp. Interno");
	gotoxy(46,11);printf("['E'] - Gravacao em Disp. Externo");
	gotoxy(46,12);printf("['L'] - Leitura");
	gotoxy(46,13);printf("['I'] - Impressao");
	
	gotoxy(54,16);printf("UM NOVO PROCESSO");
	gotoxy(52,17);printf("CHEGA A CADA: %d Ut's", ut);
	
	gotoxy(53,20);printf("[Q] - ALTERAR Ut's");
	
	gotoxy(49,22);printf("[ESC] SAIR/EXIBIR RELATORIO");
	
	for(int i=0;i<quant;i++)
	{
		Moldura(8,LI,14,LF,2,0);
		LI+=4;
		LF+=4;
		textcolor(GREEN);
		gotoxy(4,linha); printf("[");
		textcolor(WHITE);
		gotoxy(5,linha); printf("%d",proc);
		textcolor(GREEN);
		gotoxy(6,linha); printf("]");
		textcolor(WHITE);
		linha+=4;
		proc++;
	}
	
	int aux = 5-quant;
	
	for(int i=0;i<aux;i++)
	{
		Moldura(8,LI,14,LF,4,0);
		LI+=4;
		LF+=4;
		textcolor(RED);
		gotoxy(4,linha); printf("[");
		textcolor(WHITE);
		gotoxy(5,linha); printf("%d",proc);
		textcolor(RED);
		gotoxy(6,linha); printf("]");
		textcolor(WHITE);
		linha+=4;
		proc++;
	}
	
	//Moldura(8,5,12,7,2,0);
	Moldura(15,5,21,7,7,0);
	Moldura(22,5,28,7,7,0);
	Moldura(29,5,35,7,7,0);
	Moldura(36,5,42,7,7,0);
	
	//Moldura(8,9,12,11,2,0);
	Moldura(15,9,21,11,7,0);
	Moldura(22,9,28,11,7,0);
	Moldura(29,9,35,11,7,0);
	Moldura(36,9,42,11,7,0);	
	
	//Moldura(8,13,12,15,2,0);
	Moldura(15,13,21,15,7,0);
	Moldura(22,13,28,15,7,0);
	Moldura(29,13,35,15,7,0);
	Moldura(36,13,42,15,7,0);
	
	//Moldura(8,17,12,19,2,0);
	Moldura(15,17,21,19,7,0);
	Moldura(22,17,28,19,7,0);
	Moldura(29,17,35,19,7,0);
	Moldura(36,17,42,19,7,0);
	
	//Moldura(8,21,12,23,2,0);
	Moldura(15,21,21,23,7,0);
	Moldura(22,21,28,23,7,0);
	Moldura(29,21,35,23,7,0);
	Moldura(36,21,42,23,7,0);
}

void LimparTela(void)
{
	int i;
	for(i=6;i<24;i++)
	{
		gotoxy(2,i);printf ("                                                                              ");
	}
}

void Limpar(int c,int l)
{
	gotoxy(c,l);printf("  ");
}

void LimparMenuSec()
{
	for(int i=1;i<=25;i++)
	{
		gotoxy(81,i);printf("                                        ");
	}
}

void InicializaFilas(TpFila F[5])
{
	for(int i=0;i<5;i++)
		Inicializar(F[i]);
}

void InicializaVetor(int vCont[5],float vMedia[4],int vQuantE[4], float vContProc[5])
{
	for(int i=0;i<5;i++)
	{
		vCont[i]=0;
		vContProc[i]=0;
	}
		
	for(int i=0;i<4;i++)
	{
		vMedia[i]=0;
		vQuantE[i]=0;
	}		
}

void AlterarUt(int &ut)
{
	Moldura(81,1,120,25,9,3);
	gotoxy(88,3); printf("* * * SIMULACAO PAUSADA! * * *");
	gotoxy(90,6); printf("Digite o intervalo (em UT)");
	gotoxy(92,7); printf("para que novas tarefas");
	gotoxy(94,8); printf("sejam solicitadas:");
	gotoxy(113,8);scanf("%d", &ut);
	
	while(ut<=0)
	{
		gotoxy(93,19);printf("Digite um intervalo");
		gotoxy(97,20);printf("maior que 0!");
		Limpar(113,8);
		gotoxy(113,8);scanf("%d", &ut);
	}
	gotoxy(52,17);printf("CHEGA A CADA: %d Ut's", ut);
	LimparMenuSec();
}

void InicioProc(int quantProc,int ut)
{	
	LimparTela();
	int tarefa, tempo=0, i, j, menorFim, procMenor, linha, inseriu=1, e,vetQuantE[4],vetCont[5], desativa=0, c=4, l=6, LI=5, LF=7;
	char op;
	float vetMedia[4], vetContProc[5];
	TpFila F[5];
	TpElem Elemento;
	
	InicializaFilas(F);
	InicializaVetor(vetCont,vetMedia,vetQuantE,vetContProc);

	MolduraProc(quantProc,ut);
	
	FILE *Ptr = fopen("Tarefas.txt", "r");
	
	for(int i=0;i<quantProc;i++)
		F[i].Status = 1;
	
	do
	{
		if(!kbhit())
		{

			j=9;
	
			if(tempo%ut == 0 && desativa == 0)
			{
				if(inseriu == 1)
				{
					fscanf(Ptr,"%d",&tarefa);
					inseriu=0;
				
					switch(tarefa)
					{
						case 1:
							Elemento.Nome = 'G';
							Elemento.Prioridade = 1;
							Elemento.Ut = 5;
							break;
							
						case 2:
							Elemento.Nome = 'E';
							Elemento.Prioridade = 2;
							Elemento.Ut = 8;
							break;
							
						case 3:
							Elemento.Nome = 'L';
							Elemento.Prioridade = 3;
							Elemento.Ut = 4;
							break;
							
						case 4:
							Elemento.Nome = 'I';
							Elemento.Prioridade = 4;
							Elemento.Ut = 3;
							break;
					}
				}
					
				menorFim = MAXFILA;
					
				for(int i=0;i<5;i++)
				{
					if(F[i].Fim<menorFim && F[i].Status==1)
					{
						menorFim = F[i].Fim;
						procMenor = i;
					}		
				}
				
				if(!FilaCheia(F[procMenor].Fim) && menorFim < MAXFILA)	
				{
					if(FilaVazia(F[procMenor].Fim))
					{
						Elemento.Status=1;
						Elemento.Entrou=tempo;
						Inserir(F[procMenor],Elemento);
					}
					else
					{
						Elemento.Status=0;
						Elemento.Entrou=tempo;
						Inserir(F[procMenor],Elemento);
					}
					inseriu=1;
				}
					
				switch(procMenor)
				{
					case 0:
						linha = 6;
						break;
						
					case 1:
						linha = 10;
						break;
						
					case 2:
						linha = 14;
						break;
						
					case 3:
						linha = 18;
						break;
						
					case 4:
						linha = 22;
						break;						
				}
					
				for(int a=0;a<=F[procMenor].Fim;a++)
				{
					gotoxy(j,linha);printf("'%c-%d'",F[procMenor].Fila[a].Nome,F[procMenor].Fila[a].Prioridade);
					j+=7;
				}
							
			}	
								
			tempo++;
			for(int i=0;i<5;i++)
			{
				int linhaUt = 8+(i*4);
				
				if(!FilaVazia(F[i].Fim))
					if(F[i].Status==1)
					{
						F[i].Fila[0].Ut--;
						
						if(F[i].Fila[0].Ut > 0)
				        {
				            gotoxy(11,linhaUt);printf("%d", F[i].Fila[0].Ut); 
				   	 	}
			            else
			            {
							gotoxy(10, linhaUt);printf("  ");
	                	
	                		switch(F[i].Fila[0].Nome)
	                		{
	                			case 'G':
	                				e=0;
	                				break;
	                			case 'E':
	                				e=1;
	                				break;
	                			case 'L':
	                				e=2;
	                				break;
	                			case 'I':
	                				e=3;
	                				break;
	                		}
	                		
	                		
	               			 vetMedia[e] += (tempo - F[i].Fila[0].Entrou);
							vetQuantE[e]++;
	
							F[i].Ut += (tempo - F[i].Fila[0].Entrou);
	               	 		
							Retirar(F[i]);
							
							vetCont[i]++;
														
							vetContProc[i]++;
							
							int col = 9;
							switch(i)
							{
								case 0:
									linha = 6;
									break;
									
								case 1:
									linha = 10;
									break;
									
								case 2:
									linha = 14;
									break;
									
								case 3:
									linha = 18;
									break;
									
								case 4:
									linha = 22;
									break;		
							}
							col = 9;
							for(int a=0;a<5;a++)
							{
								gotoxy(col,linha);printf("     ");
								col+=7;
								
							}
							
							col = 9;
							for(int a=0;a<=F[i].Fim;a++)
							{
								gotoxy(col,linha);printf("'%c-%d'",F[i].Fila[a].Nome,F[i].Fila[a].Prioridade);
								col+=7;
							}
						}
								
					}
			}
			
			gotoxy(73,24);printf("Ut: %d",tempo);
			
		}
		else
		{
			
			op = toupper(getch());
			
			switch(op)
			{
				case 'Q':
					AlterarUt(ut);
					break;
				
				case 27:					
					desativa = 1;
					for(int i=0;i<5;i++)
					{
						c=4;
						textcolor(RED);
						gotoxy(c,l); printf("[");
						c++;
						textcolor(WHITE);
						gotoxy(c,l); printf("%d",i+1);
						c++;
						textcolor(RED);
						gotoxy(c,l); printf("]");
						c++;
						textcolor(WHITE);
						Moldura(8,LI,14,LF,4,0);
						l+=4;
						LI+=4;
						LF+=4;
					}
					break;
					
				case '1':
					if(F[0].Status == 1)
					{
						F[0].Status = 0;
						textcolor(RED);
						gotoxy(4,6); printf("[");
						textcolor(WHITE);
						gotoxy(5,6); printf("1");
						textcolor(RED);
						gotoxy(6,6); printf("]");
						textcolor(WHITE);
						Moldura(8,5,14,7,4,0);
					}
					else
					{
						F[0].Status = 1;
						textcolor(GREEN);
						gotoxy(4,6); printf("[");
						textcolor(WHITE);
						gotoxy(5,6); printf("1");
						textcolor(GREEN);
						gotoxy(6,6); printf("]");
						textcolor(WHITE);
						Moldura(8,5,14,7,2,0);
					}
					break;
				case '2':												
					if(F[1].Status == 1)
					{
						F[1].Status = 0;
						textcolor(RED);
						gotoxy(4,10); printf("[");
						textcolor(WHITE);
						gotoxy(5,10); printf("2");
						textcolor(RED);
						gotoxy(6,10); printf("]");
						textcolor(WHITE);
						Moldura(8,9,14,11,4,0);
					}
					else
					{
						F[1].Status = 1;
						textcolor(GREEN);
						gotoxy(4,10); printf("[");
						textcolor(WHITE);
						gotoxy(5,10); printf("2");
						textcolor(GREEN);
						gotoxy(6,10); printf("]");
						textcolor(WHITE);
						Moldura(8,9,14,11,2,0);
					}
					break;
				case '3':
					if(F[2].Status == 1)
					{
						F[2].Status = 0;
						textcolor(RED);
						gotoxy(4,14); printf("[");
						textcolor(WHITE);
						gotoxy(5,14); printf("3");
						textcolor(RED);
						gotoxy(6,14); printf("]");
						textcolor(WHITE);
						Moldura(8,13,14,15,4,0);
					}
					else
					{
						F[2].Status = 1;
						textcolor(GREEN);
						gotoxy(4,14); printf("[");
						textcolor(WHITE);
						gotoxy(5,14); printf("3");
						textcolor(GREEN);
						gotoxy(6,14); printf("]");
						textcolor(WHITE);
						Moldura(8,13,14,15,2,0);
					}
					break;
				case '4':
					if(F[3].Status == 1)
					{
						F[3].Status = 0;
						textcolor(RED);
						gotoxy(4,18); printf("[");
						textcolor(WHITE);
						gotoxy(5,18); printf("4");
						textcolor(RED);
						gotoxy(6,18); printf("]");
						textcolor(WHITE);
						Moldura(8,17,14,19,4,0);
					}
					else
					{
						F[3].Status = 1;
						textcolor(GREEN);
						gotoxy(4,18); printf("[");
						textcolor(WHITE);
						gotoxy(5,18); printf("4");
						textcolor(GREEN);
						gotoxy(6,18); printf("]");
						textcolor(WHITE);
						Moldura(8,17,14,19,2,0);
					}
					break;
				case '5':
					if(F[4].Status == 1)
					{
						F[4].Status = 0;
						textcolor(RED);
						gotoxy(4,22); printf("[");
						textcolor(WHITE);
						gotoxy(5,22); printf("5");
						textcolor(RED);
						gotoxy(6,22); printf("]");
						textcolor(WHITE);
						Moldura(8,21,14,23,4,0);
					}
					else
					{
						F[4].Status = 1;
						textcolor(GREEN);
						gotoxy(4,22); printf("[");
						textcolor(WHITE);
						gotoxy(5,22); printf("5");
						textcolor(GREEN);
						gotoxy(6,22); printf("]");
						textcolor(WHITE);
						Moldura(8,21,14,23,2,0);
					}
					break;
			}
		}			
		
		Sleep(1000);
		
	}while(op != 27 || !VerificaTermino(F));
	
	for(int i=0;i<4;i++)
		if(vetQuantE[i] > 0)
			vetMedia[i]/=vetQuantE[i];
		
	system("cls");
	Moldura(1,1,80,25,9,3);
	gotoxy(33,4);printf("* * * RELATORIO * * *");
	
	gotoxy(4,9);printf("QUANTIDADE DE PROCESSOS");
	gotoxy(32,9);printf("TEMPO MEDIO PROCESSADOR");
	gotoxy(60,9);printf("TEMPO MEDIO TAREFA");
	
	int lR=11;
	for(int i=0;i<5;i++)
	{
		gotoxy(11,lR);printf("Proc. %d: %d",i+1,vetCont[i]);
		lR++;
	}
	
	for(int i=0;i<5;i++)
		if(vetContProc[i]>0)
			vetContProc[i] = F[i].Ut/vetContProc[i];
	
	lR=11;
	for(int i=0;i<5;i++)
	{
		gotoxy(37,lR);printf("Proc. %d: %.2f",i+1,vetContProc[i]);
		lR++;
	}

	gotoxy(61,11);printf("Grav. Int.: %.2f",vetMedia[0]);
	gotoxy(61,12);printf("Grav. Ext.: %.2f",vetMedia[1]);
	gotoxy(61,13);printf("Leitura: %.2f",vetMedia[2]);
	gotoxy(61,14);printf("Impressao: %.2f",vetMedia[3]);
	
	gotoxy(18,23);printf("PRESSIONE QUALQUER TECLA PARA ENCERRAR O PROGRAMA");
	
	getch();
	fclose(Ptr);
}

int main(void)
{
	int ut, sair=0, quantProc=0;
	char proc;
	
	Moldura(1,1,80,25,9,3);
	
	gotoxy(15,3); printf("FILAS DE PROCESSADORES");
	
	do
	{
		gotoxy(15,8); printf("Quant. de Processadores para serem utilizados: (1-5)");
		gotoxy(22,10); printf("[A]1    [B]2    [C]3    [D]4    [E]5");
		fflush(stdin);
		proc = toupper(getch());
		
		switch(proc)
		{
			case 'A':
				quantProc=1;
				break;
			case 'B':
				quantProc=2;
				break;
			case 'C':
				quantProc=3;
				break;
			case 'D':
				quantProc=4;
				break;
			case 'E':
				quantProc=5;
				break;
			
			default: 
				gotoxy(28,13); printf("Digite uma letra valida!");
				break;
		}
	
	}while(quantProc==0);
	
	gotoxy(7,13); printf("Digite o intervalo (em UT) para que novas tarefas sejam solicitadas:");
	gotoxy(7,14);scanf("%d", &ut);
	
	while(ut<=0)
	{
		gotoxy(25,19);printf("Digite um intervalo maior que 0!");
		Limpar(7,14);
		gotoxy(7,13); printf("Digite o intervalo (em UT) para que novas tarefas sejam solicitadas:");
		gotoxy(7,14);scanf("%d", &ut);
	}
	
	InicioProc(quantProc,ut);
	

	
	
	return 0;
}
