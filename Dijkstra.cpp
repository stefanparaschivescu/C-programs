//Implementarea algoritmului Dijkstra
#include <stdio.h>
#include <malloc.h>

typedef struct {
	float l;
	int vf;
}eticheta;


void preia_graf(char *nume, float ***w, int *n, int *v0, float MAX)
{
	int i, j, m, u, v;
	float p;

	FILE *f = fopen(nume, "rt");
	fscanf(f, "%i", n);

	float **mw = (float **)malloc(*n * sizeof(float*));
	for (i = 0; i < *n; i++)
		mw[i] = (float *)malloc(*n * sizeof(float));

	fscanf(f, "%i", &m);
	for (i = 0; i < *n; i++)
		for (j = 0; j < *n; j++)
			mw[i][j] = MAX;

	for (i = 0; i < m; i++)
	{
		fscanf(f, "%i", &u);
		fscanf(f, "%i", &v);
		fscanf(f, "%f", &p);
		mw[u - 1][v - 1] = mw[v - 1][u - 1] = p;
	}

	fscanf(f, "%i", v0);
	fclose(f);

	*w = mw;
}


eticheta * Dijkstra(float **w, int n, int v0, float MAX)
{
	int i, *prel, nrit, ui, v, vmin;
	float lmin;

	
	eticheta *v_et = (eticheta *)malloc(n * sizeof(eticheta));

	
	for (i = 0; i < n; i++)
		v_et[i].l = MAX;

	v_et[v0 - 1].l = 0;

	prel = (int*)malloc(n * sizeof(int));
	
	for (i = 0; i < n; i++)
		prel[i] = 0;
	prel[v0 - 1] = 1;

	ui = v0;
	for (nrit = 0; nrit < n - 1; nrit++)
	{
		lmin = MAX;
		
		for (v = 1; v <= n; v++)
		{
			
			if ((prel[v - 1] == 0) && (v_et[v - 1].l > v_et[ui - 1].l + w[v - 1][ui - 1]))
			{
				v_et[v - 1].l = v_et[ui - 1].l + w[v - 1][ui - 1];
				v_et[v - 1].vf = ui;
			}

			
			if ((prel[v - 1] == 0) && v_et[v - 1].l < lmin)
			{
				lmin = v_et[v - 1].l;  vmin = v;
			}
		}
		
		ui = vmin; prel[ui - 1] = 1;
	}
	free(prel); 
	return v_et;
}


void main()
{
	float **w, MAX = 1000000; int n, v0, v, u, i;
	char numef[20];

	printf("Introduceti numele fisierului care contine graful:");
	scanf("%s", numef);

	preia_graf(numef, &w, &n, &v0, MAX);

	eticheta *rez = Dijkstra(w, n, v0, MAX);

	
	for (v = 1; v <= n; v++)
	{
		if (v != v0)
		{
			printf("Costul celui mai ieftin drum de la %i la %i este %8.3f", v, v0, rez[v - 1].l);
			printf("\n Un drum de cost minim: %i ", v);
			u = v;
			while (rez[u - 1].vf != v0)
			{
				printf("%i ", rez[u - 1].vf);
				u = rez[u - 1].vf;
			}
			printf("%i \n\n", v0);
		}
	}

	free(rez);

	for (i = 0; i < n; i++) free(w[i]);
	free(w);
}
