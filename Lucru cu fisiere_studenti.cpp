#include <stdio.h>
#include <string.h>
#pragma warning (disable:4996)

typedef struct {
	char is;
	int nrMatricol;
	char nume[20];
	int an;
	int grup;
	float nota[10];
} stud;

int aflaCatiStudentiSuntInFisier(FILE* f)
{
	int pozCurenta, nrStudenti;
	pozCurenta = ftell(f);
	fseek(f, 0, SEEK_END); 
	nrStudenti = ftell(f) / sizeof(stud);
	fseek(f, pozCurenta, SEEK_SET);
	return nrStudenti;
}

void populare()
{
	FILE *f;
	stud a;
	int n, i;
	char nume_f[20];
	int nr = sizeof(stud);

	printf("\nnume fisier:");
	gets_s(nume_f);
	f = fopen(nume_f, "wb+");


	printf("\nNumar matricol="); scanf_s("%d", &n);
	while (!feof(stdin))
	{
		if (n > aflaCatiStudentiSuntInFisier(f))
		{
			fseek(f, 0, SEEK_END);
			a.is = 0;
			for (i = aflaCatiStudentiSuntInFisier(f); i < n; i++)
				fwrite(&a, sizeof(stud), 1, f);
			fseek(f, (n - 1) * sizeof(stud), SEEK_SET); 
			a.is = 1;
			a.nrMatricol = n;
			printf("nume= "); getc(stdin); gets_s(a.nume);
			printf("an= "); scanf_s("%d", &a.an);
			printf("grup= "); scanf_s("%d",&a.grup);
			for (i = 0; i < 10; i++)
			{
				printf("nota din luna %d= ", i + 1);
				scanf_s("%f", &a.nota[i]);
			}
			fwrite(&a, sizeof(stud), 1, f);
		}
		else
		{
			fseek(f, (n - 1) * sizeof(stud), SEEK_SET);
			fread(&a, sizeof(stud), 1, f);
			if (a.is == 0) {
				a.is = 1;
				a.nrMatricol = n;
				printf("nume= "); getc(stdin); gets_s(a.nume);
				printf("an= "); scanf_s("%d", &a.an);
				printf("grup= "); scanf_s("%d", &a.grup);
				for (i = 0; i < 10; i++)
				{
					printf("nota din luna %d= ", i+1);
					scanf_s("%f", &a.nota[i]);
				}

				fseek(f, (n - 1) * sizeof(stud), SEEK_SET);
				
				fwrite(&a, sizeof(stud), 1, f);
			}
			else printf("inreg. exista\n");
		}
		printf("\nNumar matricol= "); scanf_s("%d", &n);
	}
	fclose(f);
}

void adaugare()
{
	FILE* f;
	stud a;
	int n, i;
	char nume_f[20];
	int nr = sizeof(stud);

	printf("\nnume fisier:");
	gets_s(nume_f);
	f = fopen(nume_f, "rb+"); 


	if (f == NULL) f = fopen(nume_f, "wb+");
	printf("\nNumar matricol= "); scanf_s("%d", &n);


	while (!feof(stdin))
	{
		if (n > aflaCatiStudentiSuntInFisier(f))
		{
			fseek(f, 0, SEEK_END);
			a.is = 0;
			for (i = aflaCatiStudentiSuntInFisier(f); i < n; i++)
				fwrite(&a, sizeof(stud), 1, f);
			fseek(f, (n - 1) * sizeof(stud), SEEK_SET);
			a.is = 1;
			a.nrMatricol = n;
			printf("nume= "); getc(stdin); gets_s(a.nume);
			printf("an= "); scanf_s("%d", &a.an);
			printf("grup= "); scanf_s("%d", &a.grup);
			for (i = 0; i < 10; i++)
			{
				printf("nota din luna %d= ", i+1);
				scanf_s("%f", &a.nota[i]);
			}
			fwrite(&a, sizeof(stud), 1, f);
		}
		else
		{
			fseek(f, (n - 1) * sizeof(stud), SEEK_SET);
			fread(&a, sizeof(stud), 1, f);
			if (a.is == 0) {
				a.is = 1;
				a.nrMatricol = n;
				printf("nume= "); getc(stdin); gets_s(a.nume);
				printf("an= "); scanf_s("%d", &a.an);
				printf("grup= "); scanf_s("%d", &a.grup);
				for (i = 0; i < 10; i++)
				{
					printf("nota din luna %d= ", i + 1);
					scanf_s("%f", &a.nota[i]);
				}

				fseek(f, (n - 1) * sizeof(stud), SEEK_SET);
				
				fwrite(&a, sizeof(stud), 1, f);
			}
			else printf("inreg. exista\n");
		}
		printf("\nNumar matricol= "); scanf_s("%d", &n);
	}
	fclose(f);
}

void afisare()
{
	FILE *f, *g;
	stud a;
	char nume_f[20];
	printf("\nnume fisier:");
	gets_s(nume_f);
	if (!(f = fopen(nume_f, "rb"))) printf("nu exista fisierul");
	else {
		printf("\n==================afisarea studentilor din fisier===================");
		g = fopen("lista_fis.txt", "w");
		fprintf(g, " NOTE \n ");
		fprintf(g, "==============================================================================================================\n");
		fprintf(g, " NR. MATRICOL||            NUME           ||  AN  ||  GRUPA  || NOTA 1 || NOTA 2 || NOTA 3 || NOTA 4 || NOTA 5 || NOTA 6 || NOTA 7 || NOTA 8 || NOTA 9 || NOTA 10 \n");
		fprintf(g, "===================================================================================================================\n");
		printf(" NOTE \n ");
		printf("=========================================================================================================================\n ");
		printf(" NR. MATRICOL||            NUME           ||  AN  ||  GRUPA  || NOTA 1 || NOTA 2 || NOTA 3 || NOTA 4 || NOTA 5 || NOTA 6 || NOTA 7 || NOTA 8 || NOTA 9 || NOTA 10 \n");
		printf("=========================================================================================================================\n");
		fread(&a, sizeof(stud), 1, f);
		while (!feof(f)) 
		{
			if (a.is == 1)
			{
				printf("\n%14d|| %-25s || %-4d || %-7d || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f", a.nrMatricol, a.nume, a.an, a.grup, a.nota[0], a.nota[1], a.nota[2], a.nota[3], a.nota[4], a.nota[5], a.nota[6], a.nota[7], a.nota[8], a.nota[9]);
				fprintf(g, "\n%14d|| %-25s || %-4d || %-7d || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f", a.nrMatricol, a.nume, a.an, a.grup, a.nota[0], a.nota[1], a.nota[2], a.nota[3], a.nota[4], a.nota[5] , a.nota[6], a.nota[7], a.nota[8], a.nota[9]);
			}
			fread(&a, sizeof(stud), 1, f);
		}
		fclose(f); fclose(g);
	}
}

void afisare_poz()
{
	FILE* f, * g;
	stud a;
	int n;
	char nume_f[20];
	printf("\nnume fisier:");
	gets_s(nume_f);
	if (!(f = fopen(nume_f, "rb"))) printf("nu exista fisierul");
	else {
		printf("\n==================afisarea studentilor a caror numar matricol il citesc de la tastatura====================");
		g = fopen("lista_poz.txt", "w");
		fprintf(g, "                                                                              NOTE \n");
		fprintf(g, "=============================================================================================\n ");
		fprintf(g, " NR. MATRICOL ||           NUME          ||   AN   ||  GRUPA  || NOTA 1 || NOTA 2 || NOTA 3 || NOTA 4 || NOTA 5 || NOTA 6 || NOTA 7 || NOTA 8 || NOTA 9 || NOTA 10 \n");
		fprintf(g, "==============================================================================================\n ");
		printf(" NOTE \n ");
		printf("=========================================================================================================================\n");
		printf(" NR. MATRICOL ||           NUME          ||   AN   ||  GRUPA  || NOTA 1 || NOTA 2 || NOTA 3 || NOTA 4 || NOTA 5 || NOTA 6 || NOTA 7 || NOTA 8 || NOTA 9 || NOTA 10 \n");
		printf("=========================================================================================================================\n");
		printf("\nNumar matricol="); scanf("%d", &n);
		while (!feof(stdin))
		{
			if (n > aflaCatiStudentiSuntInFisier(f)) printf("depaseste lungimea fis.");
			else
			{
				fseek(f, (n - 1) * sizeof(stud), 0);
				fread(&a, sizeof(stud), 1, f);
				if (a.is == 1)
				{
					printf("\n%14d|| %-25s || %-4d || %-7d || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f", a.nrMatricol, a.nume, a.an, a.grup, a.nota[0], a.nota[1], a.nota[2], a.nota[3], a.nota[4], a.nota[5], a.nota[6], a.nota[7], a.nota[8], a.nota[9]);
					fprintf(g, "\n%14d|| %-25s || %-4d || %-7d || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f", a.nrMatricol, a.nume, a.an, a.grup, a.nota[0], a.nota[1], a.nota[2], a.nota[3], a.nota[4], a.nota[5], a.nota[6], a.nota[7], a.nota[8], a.nota[9]);
				}
				else printf("inregistrarea nu exista");
			}
			printf("\nNumar matricol="); scanf("%d", &n);
		}
		fclose(f); fclose(g);
	}
}


void afisare_grupa()
{
	FILE* f, * g;
	stud a;
	int grupa1, vb;
	char nume_f[20];
	printf("\nnume fisier:");
	gets_s(nume_f);
	if (!(f = fopen(nume_f, "rb"))) printf("nu exista fisierul");
	else {
		g = fopen("lista_grupa.txt", "w");
		printf("\n ");
		fprintf(g, " LISTA STUDENTI DIN GRUPA SELECTATA \n ");
		fprintf(g, "==============================================================================================\n");
		fprintf(g, " NR. MATRICOL ||            NUME          ||  AN  || NOTA 1 || NOTA 2 || NOTA 3 || NOTA 4 || NOTA 5 || NOTA 6 || NOTA 7 || NOTA 8 || NOTA 9 || NOTA 10 \n");
		fprintf(g, "==============================================================================================\n");
		printf(" LISTA STUDENTI DIN GRUPA SELECTATA \n ");
		printf("==============================================================================================\n");
		printf(" NR. MATRICOL ||            NUME          ||  AN  || NOTA 1 || NOTA 2 || NOTA 3 || NOTA 4 || NOTA 5 || NOTA 6 || NOTA 7 || NOTA 8 || NOTA 9 || NOTA 10 \n");
		printf("==============================================================================================\n");
		printf("\nGrupa="); scanf("%d", &grupa1);
		while (!feof(stdin))
		{
			printf("\n=============================afisarea inregistrarilor din grupa %4d========================", grupa1);
			rewind(f); vb = 0;
			fread(&a, sizeof(stud), 1, f);
			while (!feof(f))
			{
				if ((a.is == 1) && (a.grup == grupa1))
				{
					printf("\n%14d|| %-25s || %-4d || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f", a.nrMatricol, a.nume, a.an, a.nota[0], a.nota[1], a.nota[2], a.nota[3], a.nota[4], a.nota[5], a.nota[6], a.nota[7], a.nota[8], a.nota[9]);
					fprintf(g, "\n%14d|| %-25s || %-4d || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f", a.nrMatricol, a.nume, a.an, a.nota[0], a.nota[1], a.nota[2], a.nota[3], a.nota[4], a.nota[5], a.nota[6], a.nota[7], a.nota[8], a.nota[9]);
					vb = 1;
				}
				fread(&a, sizeof(stud), 1, f);
			}
			if (vb == 0) printf("inreg. nu exista");
			printf("\nGrupa="); scanf("%d", &grupa1);
		}
		fclose(f); fclose(g);
	}
}

void exmatriculeazaStudent()
{
	FILE* f;
	stud a;
	int n;
	char nume_f[20];
	printf("\nnume fisier:");
	gets_s(nume_f);
	if (!(f = fopen(nume_f, "rb+"))) printf("nu exista fisierul");
	else {
		printf("\nStergerea studentului a carui numar matricol il citesc de la tastatura");
		printf("\nNumar matricol="); scanf("%d", &n);
		printf("\n NR.MATRICOL  ||            NUME           ||  AN  || GRUPA \n");
		while (!feof(stdin))
		{
			if (n > aflaCatiStudentiSuntInFisier(f)) printf("Depaseste lungimea fisierului");
			else
			{
				fseek(f, (n - 1) * sizeof(stud), 0);
				fread(&a, sizeof(stud), 1, f);
				if (a.is == 1)
				{
					printf("\n%14d|| %-25s || %-4d || %-7d \n", n, a.nume, a.an, a.grup);
					a.is = 0;
					fseek(f, (n - 1) * sizeof(stud), 0);
					fwrite(&a, sizeof(stud), 1, f);
				}
				else printf("inreg. nu exista");
			}
			printf("\nNumar matricol="); scanf("%d", &n);
		}
		fclose(f);
	}
}

void afisareStudentIntegralisti()
{
	FILE* f, * g;
	stud a;
	float medie, maxi=0;
	char nume_f[20];
	printf("\nNume fisier:");
	gets_s(nume_f);
	if (!(f = fopen(nume_f, "rb"))) printf("Nu exista fisierul");
	else {
		printf("\n==================Afisarea studentilor integralisti din fisier=============");
		g = fopen("lista_integralisti.txt", "w");
		fprintf(g, "===============================================================NOTE \n");
		fprintf(g, "==============================================================================================================\n ");
		fprintf(g, " NR. MATRICOL||            NUME           ||  AN  ||  GRUPA || NOTA 1 || NOTA 2 || NOTA 3 || NOTA 4 || NOTA 5 || NOTA 6 || NOTA 7|| NOTA 8 || NOTA 9 || NOTA 10 \n");
		fprintf(g, "===================================================================================================================\n ");
		printf(" NOTE \n ");
		printf("==============================================================================================================\n");
		printf(" NR. MATRICOL||            NUME           ||  AN  ||  GRUPA || NOTA 1 || NOTA 2 || NOTA 3 || NOTA 4 || NOTA 5 || NOTA 6 || NOTA 7|| NOTA 8 || NOTA 9 || NOTA 10 \n");
		printf("===================================================================================================================\n");
		fread(&a, sizeof(stud), 1, f);
		while (!feof(f))
		{
			medie = 0;
			if (a.is == 1)
			{
				for (int j = 0; j < 10; j++)
					medie = a.nota[j] + medie;
				medie = medie / 10;
			}
			if (maxi < medie)
				maxi = medie;

			fread(&a, sizeof(stud), 1, f);
		}
		rewind(f);
		fread(&a, sizeof(stud), 1, f);
		printf("Media cea mai mare este = %5.2f\n", maxi);
		while (!feof(f))
		{
			if (a.is == 1 && (a.nota[0]+ a.nota[1] + a.nota[2] + a.nota[3] + a.nota[4] + a.nota[5] + a.nota[6] + a.nota[7] + a.nota[8] + a.nota[9]) / 10 == maxi && maxi >=5)
			{
				printf("\n%14d|| %-25s || %-4d || %-7d || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f ", a.nrMatricol, a.nume, a.an, a.grup, a.nota[0], a.nota[1], a.nota[2], a.nota[3], a.nota[4], a.nota[5], a.nota[6], a.nota[7], a.nota[8], a.nota[9]);
				fprintf(g, "\n%14d|| %-25s || %-4d || %-7d || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f || %-6.2f ", a.nrMatricol, a.nume, a.an, a.grup, a.nota[0], a.nota[1], a.nota[2], a.nota[3], a.nota[4], a.nota[5], a.nota[6], a.nota[7], a.nota[8], a.nota[9]);
			}
			fread(&a, sizeof(stud), 1, f);
		}
		if (maxi < 5) {
			printf("Nu sunt studenti integralisti in fisier");
			fprintf(g, "Nu sunt studenti integralisti in fisier");
		}
		fclose(f); fclose(g);
	}
}

void modificare_note()
{
	FILE* f;
	stud a;
	int n;
	float notaNoua;
	char nume_f[20];
	printf("\nnume fisier:");
	gets_s(nume_f);
	if (!(f = fopen(nume_f, "rb+"))) printf("nu exista fisierul");
	else {
		printf("\nModificarea primei note a studentilor a caror numar matricol il citesc de la tastatura");
		printf("\nNumar matricol="); scanf("%d", &n);
		while (!feof(stdin))
		{
			if (n > aflaCatiStudentiSuntInFisier(f)) printf("depaseste lungimea fis.");
			else
			{
				fseek(f, (n - 1) * sizeof(stud), 0);
				fread(&a, sizeof(stud), 1, f);
				if (a.is == 1)
				{
					printf("\n            NUME          ||  AN  ||  GRUPA  ||  NOTA 1 ");
					printf("\n%25s || %-4d || %-7d || %-8.2f \n", a.nume, a.an, a.grup, a.nota[0]);
					printf("prima nota="); scanf("%f", &notaNoua);
					a.nota[0] = notaNoua;
					fseek(f, (n - 1) * sizeof(stud), 0);
					fwrite(&a, sizeof(stud), 1, f);
				}
				else printf("inreg. nu exista");
			}
			printf("\nNumar matricol="); scanf("%d", &n);
		}
		fclose(f);
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
	printf("\n\nAFISARE DIN FISIER BINAR PE BAZA NUMARULUI MATRICOL");
	afisare_poz();

	printf("\n\nAFISARE DIN FISIER BINAR PE BAZA GRUPEI");
	afisare_grupa();

	printf("\n\nEXMATRICULARE STUDENT PRIN TASTAREA NUMARULUI MATRICOL");
	exmatriculeazaStudent();

	printf("\n\nAFISARE STUDENTI INTEGRALISTI");
	afisareStudentIntegralisti();

	printf("\n\nMODIFICARE PRIMEI NOTE A UNUI STUDENT");
	modificare_note();

	return 0;


	#include <stdio.h>
#include <string.h>
#pragma warning (disable:4996)

typedef struct {
	char is;
	int IDcomanda;
	float pretTotal;
	char numeClient[15];
	char prenumeClient[15];
	int IDprodus[10]; 
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
			printf("Prenume client= "); getc(stdin); gets_s(a.prenumeClient);
			printf("Pretul total al comenzii= "); scanf_s("%d", &a.pretTotal);
			printf("Data plasarii comenzii zi, luna si an:");
			scanf("%d %d %d", &a.data_com.zi, &a.data_com.luna, &a.data_com.an);
			printf("Introduceti pana la 10 ID-uri de produse pe comanda. Pentru a opri citirea scrieti ID-ul produsului = 0");
			i = 0;
			do
			{
				printf("Produsul nr. %d= ", i + 1);
				scanf_s("%f", &a.IDprodus[i]);
				i++;
			} while (a.IDprodus[i - 1] != 0);
			a.IDprodus[i] = NULL;
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
				printf("Prenume client= "); getc(stdin); gets_s(a.prenumeClient);
				printf("Pretul total al comenzii= "); scanf_s("%d", &a.pretTotal);
				printf("Data plasarii comenzii zi, luna si an:");
				scanf("%d %d %d", &a.data_com.zi, &a.data_com.luna, &a.data_com.an);
				printf("Introduceti pana la 10 ID-uri de produse pe comanda. Pentru a opri citirea scrieti ID-ul produsului = 0");
				i = 0;
				do
				{
					printf("Produsul nr. %d= ", i + 1);
					scanf_s("%f", &a.IDprodus[i]);
					i++;
				} while (a.IDprodus[i - 1] != 0);
				a.IDprodus[i] = NULL;

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
			printf("Prenume client= "); getc(stdin); gets_s(a.prenumeClient);
			printf("Pretul total al comenzii= "); scanf_s("%d", &a.pretTotal);
			printf("Data plasarii comenzii zi, luna si an:");
			scanf("%d %d %d", &a.data_com.zi, &a.data_com.luna, &a.data_com.an);
			printf("Introduceti pana la 10 ID-uri de produse pe comanda. Pentru a opri citirea scrieti ID-ul produsului = 0");
			i = 0;
			do
			{
				printf("Produsul nr. %d= ", i + 1);
				scanf_s("%f", &a.IDprodus[i]);
				i++;
			} while (a.IDprodus[i - 1] != 0);
			a.IDprodus[i] = NULL;

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
				printf("Prenume client= "); getc(stdin); gets_s(a.prenumeClient);
				printf("Pretul total al comenzii= "); scanf_s("%d", &a.pretTotal);
				printf("Data plasarii comenzii zi, luna si an:");
				scanf("%d %d %d", &a.data_com.zi, &a.data_com.luna, &a.data_com.an);
				printf("Introduceti pana la 10 ID-uri de produse pe. Pentru a opri citirea scrieti ID-ul produsului = 0");
				i = 0;
				do
				{
					printf("Produsul nr. %d= ", i + 1);
					scanf_s("%f", &a.IDprodus[i]);
					i++;
				} while (a.IDprodus[i - 1] != 0);
				a.IDprodus[i] = NULL;

				fseek(f, (n - 1) * sizeof(comanda), SEEK_SET);
				
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
		fprintf(g, " COMENZI \n ");
		fprintf(g, "==============================================================================================================\n");
		fprintf(g, "  ID COMANDA ||          NUME         ||         PRENUME       ||  PRET TOTAL  ||   DATA  || PRODUSUL 1 || PRODUSUL 2 || PRODUSUL 3 || PRODUSUL 4 || PRODUSUL 5 || PRODUSUL 6 || PRODUSUL 7 || PRODUSUL 8 || PRODUSUL 9 || PRODUSUL 10 \n");
		fprintf(g, "===================================================================================================================\n");
		printf(" NOTE \n ");
		printf("=========================================================================================================================\n ");
		printf(" NR. MATRICOL||          NUME         ||         PRENUME       ||  PRET TOTAL  ||   DATA  || PRODUSUL 1 || PRODUSUL 2 || PRODUSUL 3 || PRODUSUL 4 || PRODUSUL 5 || PRODUSUL 6 || PRODUSUL 7 || PRODUSUL 8 || PRODUSUL 9 || PRODUSUL 10 \n");
		printf("=========================================================================================================================\n");
		fread(&a, sizeof(comanda), 1, f);
		while (!feof(f)) //pana cand ajungi la sf fisierului
		{
			if (a.is == 1)
			{
				printf("\n%13d|| %-21s || %-21s || %-12.2f || %2d/%2d/%4d || %-10d || %-10d || %-10d || %-10d || %-10d || %-10d || %-10d || %-10d || %-10d || %-10d", a.IDcomanda, a.numeClient, a.prenumeClient, a.pretTotal, a.data_com.zi, a.data_com.luna, a.data_com.an,a.IDprodus[0], a.IDprodus[1], a.IDprodus[2], a.IDprodus[3], a.IDprodus[4], a.IDprodus[5], a.IDprodus[6], a.IDprodus[7], a.IDprodus[8], a.IDprodus[9]);
				fprintf(g, "\n%13d|| %-21s || %-21s || %-12.2f || %2d/%2d/%4d || %-10d || %-10d || %-10d || %-10d || %-10d || %-10d || %-10d || %-10d || %-10d || %-10d", a.IDcomanda, a.numeClient, a.prenumeClient, a.pretTotal, a.data_com.zi, a.data_com.luna, a.data_com.an, a.IDprodus[0], a.IDprodus[1], a.IDprodus[2], a.IDprodus[3], a.IDprodus[4], a.IDprodus[5], a.IDprodus[6], a.IDprodus[7], a.IDprodus[8], a.IDprodus[9]);
			}
			fread(&a, sizeof(comanda), 1, f);
		}
		fclose(f); fclose(g);
	}
}

}
