#include <stdio.h>
#include <string.h>
#pragma warning (disable:4996)

typedef struct {
	char is;
	int IDcomanda;
	float pretTotal;
	char numeClient[15];
	char prenumeClient[15];
	int IDprodus[5]; //pot exista pana la 5 produse in comanda
	struct data
	{
		int zi;
		int luna;
		int an;
	} data_com;
} comanda;

int aflaCateComenziSuntInFisier(FILE* f)
{
	int pozCurenta, nrComenzi;
	pozCurenta = ftell(f);
	fseek(f, 0, SEEK_END);
	nrComenzi = ftell(f) / sizeof(comanda);
	fseek(f, pozCurenta, SEEK_SET);
	return nrComenzi;
}

void populare()
{
	FILE* f;
	comanda a;
	int n, i;
	char nume_f[20];
	int nr = sizeof(comanda);

	printf("\nNume fisier:");
	gets_s(nume_f);
	f = fopen(nume_f, "wb+");


	printf("\nID Comanda="); scanf_s("%d", &n);
	while (!feof(stdin))
	{
		if (n > aflaCateComenziSuntInFisier(f))
		{
			fseek(f, 0, SEEK_END);
			a.is = 0;
			for (i = aflaCateComenziSuntInFisier(f); i < n; i++)
				fwrite(&a, sizeof(comanda), 1, f);
			fseek(f, (n - 1) * sizeof(comanda), SEEK_SET); 
			a.is = 1;
			a.IDcomanda = n;
			printf("Nume client= "); getc(stdin); gets_s(a.numeClient);
			printf("Prenume client= "); gets_s(a.prenumeClient);
			printf("Pretul total al comenzii= "); scanf_s("%f", &a.pretTotal);
			for (i = 0; i < 5; i++)
			{
				printf("Produsul nr. %d= ", i + 1);
				scanf_s("%d", &a.IDprodus[i]);
			}
			printf("Data plasarii comenzii zi_luna_an: " );
			scanf("%d %d %d", &a.data_com.zi, &a.data_com.luna, &a.data_com.an);
			fwrite(&a, sizeof(comanda), 1, f);
		}
		else
		{
			fseek(f, (n - 1) * sizeof(comanda), SEEK_SET);
			fread(&a, sizeof(comanda), 1, f);
			if (a.is == 0) {
				a.is = 1;
				a.IDcomanda = n;
				printf("Nume client= "); getc(stdin); gets_s(a.numeClient);
				printf("Prenume client= "); gets_s(a.prenumeClient);
				printf("Pretul total al comenzii= "); scanf_s("%f", &a.pretTotal);
				for (i = 0; i < 5; i++)
				{
					printf("Produsul nr. %d= ", i + 1);
					scanf_s("%d", &a.IDprodus[i]);
				}
				printf("Data plasarii comenzii zi_luna_an: ");
				scanf("%d %d %d", &a.data_com.zi, &a.data_com.luna, &a.data_com.an);
				fseek(f, (n - 1) * sizeof(comanda), SEEK_SET);
				fwrite(&a, sizeof(comanda), 1, f);
			}
			else printf("Inreg. exista\n");
		}
		printf("\nID comanda= "); scanf_s("%d", &n);
	}
	fclose(f);
}

void adaugare()
{
	FILE* f;
	comanda a;
	int n, i;
	char nume_f[20];
	int nr = sizeof(comanda);

	printf("\nNume fisier:");
	gets_s(nume_f);
	f = fopen(nume_f, "rb+"); 


	if (f == NULL) f = fopen(nume_f, "wb+");
	printf("\nID comanda= "); scanf_s("%d", &n);


	while (!feof(stdin))
	{
		if (n > aflaCateComenziSuntInFisier(f))
		{
			fseek(f, 0, SEEK_END);
			a.is = 0;
			for (i = aflaCateComenziSuntInFisier(f); i < n; i++)
				fwrite(&a, sizeof(comanda), 1, f);
			fseek(f, (n - 1) * sizeof(comanda), SEEK_SET);
			a.is = 1;
			a.IDcomanda = n;
			printf("Nume client= "); getc(stdin); gets_s(a.numeClient);
			printf("Prenume client= "); gets_s(a.prenumeClient);
			printf("Pretul total al comenzii= "); scanf_s("%f", &a.pretTotal);
			printf("Data plasarii comenzii zi, luna si an:");
			scanf("%d %d %d", &a.data_com.zi, &a.data_com.luna, &a.data_com.an);
			for (i = 0; i < 5; i++)
			{
				printf("Produsul nr. %d= ", i + 1);
				scanf_s("%d", &a.IDprodus[i]);
			}
			fwrite(&a, sizeof(comanda), 1, f);
		}
		else
		{
			fseek(f, (n - 1) * sizeof(comanda), SEEK_SET);
			fread(&a, sizeof(comanda), 1, f);
			if (a.is == 0) {
				a.is = 1;
				a.IDcomanda = n;
				printf("Nume client= "); getc(stdin); gets_s(a.numeClient);
				printf("Prenume client= "); gets_s(a.prenumeClient);
				printf("Pretul total al comenzii= "); scanf_s("%f", &a.pretTotal);
				printf("Data plasarii comenzii zi, luna si an:");
				scanf("%d %d %d", &a.data_com.zi, &a.data_com.luna, &a.data_com.an);
				for (i = 0; i < 5; i++)
				{
					printf("Produsul nr. %d= ", i + 1);
					scanf_s("%d", &a.IDprodus[i]);
				}
				fseek(f, (n - 1) * sizeof(comanda), SEEK_SET);
				//fseek(f, ftell(f) - sizeof(stud), SEEK_CUR);
				fwrite(&a, sizeof(comanda), 1, f);
			}
			else printf("Inreg. exista\n");
		}
		printf("\nID comanda= "); scanf_s("%d", &n);
	}
	fclose(f);
}

void afisare()
{
	FILE* f, * g;
	comanda a;
	char nume_f[20];
	printf("\nNume fisier:");
	gets_s(nume_f);
	if (!(f = fopen(nume_f, "rb"))) printf("Nu exista fisierul");
	else {
		printf("\n==================Afisarea comenzilor din fisier===================");
		g = fopen("lista_fis.txt", "w");
		fprintf(g, "======================================================= COMENZI ======================================================= \n ");
		fprintf(g, "===================================================================================================================================================================\n");
		fprintf(g, "  ID COMANDA ||          NUME         ||         PRENUME       ||  PRET TOTAL  ||    DATA    || PRODUSUL 1 || PRODUSUL 2 || PRODUSUL 3 || PRODUSUL 4 || PRODUSUL 5 \n");
		fprintf(g, "===================================================================================================================================================================\n");
		printf("========================================================================================================================================================\n ");
		printf("  ID COMANDA ||          NUME         ||         PRENUME       ||  PRET TOTAL  ||    DATA    || PRODUSUL 1 || PRODUSUL 2 || PRODUSUL 3 || PRODUSUL 4 || PRODUSUL 5 \n");
		printf("========================================================================================================================================================\n");
		fread(&a, sizeof(comanda), 1, f);
		while (!feof(f)) 
		{
			if (a.is == 1)
			{
				printf("\n%13d|| %-21s || %-21s || %-12.2f || %2d/%2d/%4d || %-10d || %-10d || %-10d || %-10d || %-10d", a.IDcomanda, a.numeClient, a.prenumeClient, a.pretTotal, a.data_com.zi, a.data_com.luna, a.data_com.an, a.IDprodus[0], a.IDprodus[1], a.IDprodus[2], a.IDprodus[3], a.IDprodus[4]);
				fprintf(g, "\n%13d|| %-21s || %-21s || %-12.2f || %2d/%2d/%4d || %-10d || %-10d || %-10d || %-10d || %-10d", a.IDcomanda, a.numeClient, a.prenumeClient, a.pretTotal, a.data_com.zi, a.data_com.luna, a.data_com.an, a.IDprodus[0], a.IDprodus[1], a.IDprodus[2], a.IDprodus[3], a.IDprodus[4]);
			}
			fread(&a, sizeof(comanda), 1, f);
		}
		fclose(f); fclose(g);
	}
}

void modificare_comenzi()
{
	FILE* f;
	comanda a;
	int n, i;
	float pretTotalNou;
	int IDprodusNou[5];
	int ziNou, lunaNou, anNou;
	char nume_f[20];
	printf("\nNume fisier:");
	gets_s(nume_f);
	if (!(f = fopen(nume_f, "rb+"))) printf("Nu exista fisierul");
	else {
		printf("\nModificarea comenzilor a caror ID il citesti de la tastatura");
		printf("\nID comanda="); scanf("%d", &n);
		while (!feof(stdin))
		{
			if (n > aflaCateComenziSuntInFisier(f)) printf("Depaseste lungimea fis.");
			else
			{
				fseek(f, (n - 1) * sizeof(comanda), 0);
				fread(&a, sizeof(comanda), 1, f);
				if (a.is == 1)
				{
					printf("\n          NUME         ||         PRENUME       ||  PRET TOTAL  ||    DATA    || PRODUSUL 1 || PRODUSUL 2 || PRODUSUL 3 || PRODUSUL 4 || PRODUSUL 5\n");
					printf(" %-21s || %-21s || %-12.2f || %2d/%2d/%4d || %-10d ||  %-10d  ||  %-10d ||  %-10d ||  %-10d\n", a.numeClient, a.prenumeClient, a.pretTotal, a.data_com.zi, a.data_com.luna, a.data_com.an, a.IDprodus[0], a.IDprodus[1], a.IDprodus[2], a.IDprodus[3], a.IDprodus[4]);
					printf("Noul pret al comenzii="); scanf("%f", &pretTotalNou);
					a.pretTotal = pretTotalNou;
					printf("Ziua emiterii comenzii="); scanf("%d", &ziNou);
					a.data_com.zi = ziNou;
					printf("Luna emiterii comenzii="); scanf("%d", &lunaNou);
					a.data_com.luna = lunaNou;
					printf("Anul emiterii comenzii="); scanf("%d", &anNou);
					a.data_com.an = anNou;
					for (i = 0; i < 5; i++)
					{
						printf("Produsul nr. %d= ", i + 1);
						scanf_s("%d", &IDprodusNou[i]);
						a.IDprodus[i] = IDprodusNou[i];
					}
					fseek(f, (n - 1) * sizeof(comanda), 0);
					fwrite(&a, sizeof(comanda), 1, f);
				}
				else printf("Inreg. nu exista");
			}
			printf("\nID comanda="); scanf("%d", &n);
		}
		fclose(f);
	}
}

void elimiareComanda()
{
	FILE* f;
	comanda a;
	int n;
	char nume_f[20];
	printf("\nNume fisier:");
	gets_s(nume_f);
	if (!(f = fopen(nume_f, "rb+"))) printf("Nu exista fisierul");
	else {
		printf("\nStergerea comenzii a carui ID il citesti de la tastatura");
		printf("\nID comanda="); scanf("%d", &n);
		printf("\n  ID COMANDA ||          NUME         ||         PRENUME       ||    DATA    ||  PRET TOTAL \n");
		while (!feof(stdin))
		{
			if (n > aflaCateComenziSuntInFisier(f)) printf("Depaseste lungimea fisierului\n");
			else
			{
				fseek(f, (n - 1) * sizeof(comanda), 0);
				fread(&a, sizeof(comanda), 1, f);
				if (a.is == 1)
				{
					printf("%13d || %-21s || %-21s || %2d/%2d/%4d || %-12.2f \n", n, a.numeClient, a.prenumeClient, a.data_com.zi, a.data_com.luna, a.data_com.an, a.pretTotal);
					a.is = 0;
					fseek(f, (n - 1) * sizeof(comanda), 0);
					fwrite(&a, sizeof(comanda), 1, f);
				}
				else printf("Inreg. nu exista");
			}
			printf("\nID comanda="); scanf("%d", &n);
		}
		fclose(f);
	}
}

void afisareComenziDinDataSelectata()
{
	FILE* f, * g;
	comanda a;
	int zi, luna, an, vb;
	char nume_f[20];
	printf("\nNume fisier:");
	gets_s(nume_f);
	if (!(f = fopen(nume_f, "rb"))) printf("nu exista fisierul");
	else {
		g = fopen("lista_comenzi_data.txt", "w");
		printf("\nData (zi_luna_an)= "); scanf("%d %d %d", &zi, &luna, &an);

		fprintf(g, "===================================================================================================================================================================\n");
		fprintf(g, "  ID COMANDA ||          NUME         ||         PRENUME       ||  PRET TOTAL  || PRODUSUL 1 || PRODUSUL 2 || PRODUSUL 3 || PRODUSUL 4 || PRODUSUL 5 \n");
		fprintf(g, "==========================================================================================================================================");
		printf("\n ");
		printf("====================================================================================================================================================\n");
		printf("  ID COMANDA ||          NUME         ||         PRENUME       ||  PRET TOTAL || PRODUSUL 1 || PRODUSUL 2 || PRODUSUL 3 || PRODUSUL 4 || PRODUSUL 5 \n");
		printf("====================================================================================================================================================");

		while (!feof(stdin))
		{
			printf("\n=============================Afisarea comenzilor din data de %2d/%2d/%4d========================", zi, luna, an);
			rewind(f); vb = 0;
			fread(&a, sizeof(comanda), 1, f);
			while (!feof(f))
			{
				if ((a.is == 1) && (a.data_com.zi == zi) && (a.data_com.luna == luna) && (a.data_com.an == an))
				{
					printf("\n%13d|| %-21s || %-21s || %-12.2f || %-10d || %-10d || %-10d || %-10d || %-10d", a.IDcomanda, a.numeClient, a.prenumeClient, a.pretTotal, a.IDprodus[0], a.IDprodus[1], a.IDprodus[2], a.IDprodus[3], a.IDprodus[4]);
					fprintf(g, "\n%13d|| %-21s || %-21s || %-12.2f || %-10d || %-10d || %-10d || %-10d || %-10d", a.IDcomanda, a.numeClient, a.prenumeClient, a.pretTotal, a.IDprodus[0], a.IDprodus[1], a.IDprodus[2], a.IDprodus[3], a.IDprodus[4]);
					vb = 1;
				}
				fread(&a, sizeof(comanda), 1, f);
			}
			if (vb == 0) printf("inreg. nu exista");
			printf("\nData (zi_luna_an)= "); scanf("%d %d %d", &zi, &luna, &an);
		}
		fclose(f); fclose(g);
	}
}

int main()
{
	printf("POPULARE IN FISIER BINAR");
	populare();

	printf("\nADAUGARE IN FISIER BINAR");
	adaugare();

	printf("\n\nAFISARE DIN FISIER BINAR");
	afisare();

	printf("\n\nSTERGEREA UNEI COMENZI");
	elimiareComanda();

	printf("\n\nMODIFICARE COMENZILOR");
	modificare_comenzi();

	printf("\n\nAFISARE COMENZI DIN DATA ALEASA");
	afisareComenziDinDataSelectata();

	printf("\n\nAFISARE DIN FISIER BINAR");
	afisare();
	return 0;
}
