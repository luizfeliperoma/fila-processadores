#define MAXFILA 5

struct TpElem {
	char Nome;
	int Prioridade, Status, Ut, Entrou;
};

struct TpFila {
	int Fim, Status, Ut;
	TpElem Fila[MAXFILA];
};

void Inicializar(TpFila &F)
{
	F.Fim=-1;
	F.Status=0;
	F.Ut=0;
}

char FilaCheia(int Fim)
{
	return Fim == MAXFILA-1;
}

char FilaVazia(int Fim)
{
	return Fim == -1;
}

void Inserir(TpFila &F, TpElem aux)
{
	F.Fila[++F.Fim] = aux;
	
	for(int i=F.Fim; i>0 && F.Fila[i].Prioridade < F.Fila[i-1].Prioridade && F.Fila[i-1].Status == 0; i--)	
	{
		aux = F.Fila[i];
		F.Fila[i] = F.Fila[i-1];
		F.Fila[i-1] = aux;
	}
}

TpElem Retirar(TpFila &F)
{
	TpElem aux;
	aux = F.Fila[0];
	for(int i=0;i<F.Fim;i++)
		F.Fila[i] = F.Fila[i+1];
		
	F.Fila[0].Status = 1;
	F.Fim--;
	return aux;
}

TpElem ElementoInicio(TpFila F)
{
	return F.Fila[0];
}

TpElem ElementoFim(TpFila F)
{
	return F.Fila[F.Fim];
}

void ExibirFila(TpFila F)
{
	TpElem aux;
	while(!FilaVazia(F.Fim))
	{
		aux = Retirar(F);
		printf("%c %d",aux.Nome,aux.Prioridade);
	}
}

char VerificaTermino(TpFila F[5])
{
	for(int i=0;i<5;i++)
		if(!FilaVazia(F[i].Fim))
			return 0;
			
	return 1;
}
