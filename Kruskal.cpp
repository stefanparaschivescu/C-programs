#include<stdio.h>
#include<conio.h>

int radacina(int v, int *tata)
{
	int u = v;
	while (tata[u] >= 0)
		u = tata[u];
	return u;
}

//a - tabela muchiilor in ordinea crescatoare a costurilor
//nm - numarul de muchii
//nv - numarul de noduri
int kruskall(int a[][3], int nm, int nv)
{
	int tata[50], i, j;
	int v1, v2, k, p, c = 0;
	
	for (i = 0; i < nv; i++)
		tata[i] = -1;
	
	for (j = i = 0; i < nv - 1; j++)
	{
		v1 = a[j][0];
		v2 = a[j][1];

		k = radacina(v2, tata);
		p = radacina(v1, tata);

		if (k - p)
		{
			if (tata[k] < tata[p])
			{
				tata[k] += tata[p];
				tata[p] = k;
			}
			else
			{
				tata[p] += tata[k];
				tata[k] = p;
			}
			c += a[j][2];
			printf("%i -> %i cost %i\n", v1 + 1, v2 + 1, a[j][2]);
			i++;
		}
	}
	return c;
}

void main()
{
	int cost, i, j, nv, nm, a[100][3];

	printf("Numarul de virfuri:"); scanf("%i", &nv);
	printf("Numarul de muchii:"); scanf("%i", &nm);
	
	printf("Matricea de reprezentare\n");
	for (i = 0; i < nm; i++)
	{
		printf("Muchia %i si ponderea:", i + 1);
		for (j = 0; j < 3; j++)
			scanf("%i", &a[i][j]);
	}

	
	for (i = 0; i < nm; i++)
		for (j = 0; j < 2; j++)a[i][j]--;
	
	printf("Arborele de cost minim: \n");
	cost = kruskall(a, nm, nv);

	printf("\ncu costul %i", cost);
	getch();
}
