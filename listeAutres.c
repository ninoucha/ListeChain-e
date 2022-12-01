#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Déclaration de ma list de donnée
typedef struct Element Element;
struct Element
{
	int nombre;
	Element * suivant
};

typedef struct Liste Liste;
struct Liste
{
	Element *premier
};

//initialisation de ma liste
Liste *initialisation()
{
	Liste *liste = malloc(sizeof(*liste));
	Element *element = malloc(sizeof(*element));
	
	if (liste == NULL || element == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	element->nombre = 0;
	element->suivant = NULL;
	liste->premier = element;
	
	return liste;
}
//insertion de mon élement dans une liste
void insertion (Liste *liste, int nvNombre)
{
	/*Création du nouvel élément*/
	Element *nouveau = malloc(sizeof(*nouveau));
	if (liste == NULL || nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}
	nouveau->nombre = nvNombre;
	
	/*Insertion de l'élément au début de la liste */
	nouveau->suivant = liste->premier;
	liste->premier = nouveau;
}
//affichage de ma liste
void afficherListe(Liste *liste)
{
	if (liste == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	Element *actuel = liste->premier;
	
	while(actuel != NULL)
	{
		printf("%d -> ", actuel->nombre);
		actuel = actuel->suivant;
	}
	printf("NULL\n");
}
//fonction random qui recupére les entier aleatoirement entre 0 et 99
int entierAleatoire()
{
	int nombre = 0;
	const int MIN = 1, MAX = 99;
	srand(time(NULL));
	nombre  = (rand() % (MAX + 1 - MIN)) + MIN;
	return nombre;
}
//recherche du max dans ma liste
int cherche_max(Liste *liste)
{
	Element *current = liste->premier;
    int Max = liste->premier->nombre;
    while(current != NULL)
    {
       //traitement du max
       if(Max < current->nombre)
          Max = current->nombre;
          
        //Passage au maillon suivant:
        current = current->suivant;
   }
   return Max;    
}


//Reconstruire la structure en mémoire.
//declaration avec typedef des liste vertical et horizontale pour effectuer la creation des 100 listes.
typedef    struct    ListeH    *pListH; //on definie une liste H normale.
typedef   struct  ListeH
{
    int     val;
    pListH   svt;
} ListeH;
// cette liste vertical contient les tetes des listes horizontal
typedef    struct    ListeV    *pListV; // on definie une liste V qui contient pour elements les tetes des listes H.
typedef   struct  ListeV
{
    pListH   teteH ;
    pListV   svt;
} ListeV;


// ajoute Element en Tete de listeH

pListH    ajoutEnTeteH(pListH L, int V) // on cree une fonction qui ajoute en tete de la liste H le premier element.
{
    pListH    p;
    p = malloc(sizeof(ListeH));

    if (p == NULL)
    {
        printf("Erreur Probleme d'allocation Memoire malloc ...\n");
        exit(0);
    }

    p->val = V;
    p->svt = L;

    return p;
}


// Ajoute Element apres l'élément prcd listeH
pListH    ajoutApresH(pListH prcd, int V) // on cree une fonction qui ajoute apres l'element precedent un nouvel element.
{
    pListH    p;
    p = malloc(sizeof(ListeH));

    if (p == NULL)
    {
        printf("Erreur Probleme d'allocation Memoire malloc ...\n");
        exit(0);
    }

    p->val = V;
    p->svt = prcd->svt;
    prcd->svt = p;
    return p;
}

//creation de la liste fifo horizontale de nombre entiers

pListH  CreerListH(int iL, int M) // on cree les listes H sous forme fifo car on veut que les elements soit dans le meme ordre etabli par l'utilisateur.
{
    pListH    tete, prcd;

    int   i;
	int nombre1, val;
	
	const int MIN = 1, MAX = 99;
	
	
    tete = NULL;
    nombre1  = (rand() % (MAX + 1 - MIN)) + MIN;//on recupére les valeurs aleatoire dans nombre1.
    tete = ajoutEnTeteH(tete, nombre1) ;// on appelle donc la fct ajoutEnTeteH pour ajouter le premier element a la liste H.
    
    prcd=tete;
    M = M + 10;
    for (i = 2; i <= M; i++)
    {
        val  = (rand() % (MAX + 1 - MIN)) + MIN;
        prcd = ajoutApresH(prcd, val); // puis on appelle la fct ajoutApresH pour ajouter le reste des elements (M-1) fois.
    }
    
    

    return tete;
}


void  afficherListeH(pListH L, int M) // on cree une procedure pour afficher la liste H.
{
    printf("Liste de %d entiers:     ", M);
    
    while (L != NULL)
    {
        printf("%d->", L->val);
        L = L->svt;
    }
    printf("Null\n");
}



// ajoute Element en Tete de listeV 

pListV    ajoutEnTeteV( pListV L, int M) // de meme que pour la liste H on cree une fct pour ajouter en tete la tete de la premiere liste H.
{
    pListV    p;
    pListH    p1;
    
    p = malloc(sizeof(ListeV));

    if (p == NULL)
    {
        printf("Erreur Probleme d'allocation Memoire malloc ...\n");
        exit(0);
    }

    p->teteH = CreerListH(1, M);
    
    p->svt = L;

    return p;
}



// Ajoute Element apres prcd de la listeV

pListV    ajoutApresV( pListV prcd, int i, int M) // on cree une fct pour ajouter apres la tete de la liste H precedente la tete de la liste H suivante.
{
    pListV    p;

    p = malloc(sizeof(ListeV));

    if (p == NULL)
    {
        printf("Erreur Probleme d'allocation Memoire malloc ...\n");
        exit(0);
    }

    p->teteH = CreerListH(i, M);
    p->svt = prcd->svt;
    prcd->svt = p;

    return p;
}


//creation de la liste fifo verticale

/* (ou N represente le nombre de listes horizontales que l'utilisateur veut creer.)*/

pListV     CreerListV()
{
    pListV    teteV, prcd;
    int   i, N;
    int M = 0;

    do
    {
    	printf("Donner le nombre de listes horizontales souhaité...\n");
        scanf("%d", &N);
    }while (N <= 0);
    
    teteV = NULL;
    teteV = ajoutEnTeteV(teteV, M) ; //on appelle donc la fct ajoutEnTeteV pour ajouter la tete de la premiere liste H a la liste V.

    prcd = teteV;

    for (i = 2; i <= N; i++)
    {
    	M = M + 10;
        prcd = ajoutApresV(prcd, i, M); // puis on appelle la fct ajoutApresV pour ajouter les tetes des listes H restantes (N-1) fois.
    }

    return teteV;
}



void  afficherListeV(pListV L) // on cree une procedure pour afficher la liste V.
{
	int M = 10;
	
    printf("Liste Verticale: \n");
    while (L != NULL)
    {
        afficherListeH(L->teteH, M); // on appelle a chaque fois la procedure afficherListeH pour afficher les listes H comme sur le schema.
        L = L->svt;
        M = M +10;
    }
    printf("\n\n");
}
//écrire l’algorithme qui supprime toutes les sous chaines de la première puis de la deuxième … etc

	

int main() {
	
	//DECLARATION DU FICHIERS POUR LES RESULTATS
    FILE* fichier=NULL;
    
	//DECLARATION DES VARIABLES DE MESURE DU TEMPS
    clock_t t1,t2;
    double delta;
    float reel;
    //********************************************
	
	int n,i;
	int nombre = 0;
	const int MIN = 1, MAX = 99;
	srand(time(NULL));
	
	Liste *maListe1 = initialisation();
	Liste *maListe2 = initialisation();
	Liste *maListe3 = initialisation();
	Liste *maListe4 = initialisation();
	Liste *maListe5 = initialisation();
	Liste *maListe6 = initialisation();
	Liste *maListe7 = initialisation();
	Liste *maListe8 = initialisation();
	Liste *maListe9 = initialisation();
	Liste *maListe10 = initialisation();
	
	int nb = 100000;
	//remplir liste 1
	for(i=0; i<nb; i++)
	{
		nombre  = (rand() % (MAX + 1 - MIN)) + MIN;
		insertion(maListe1, nombre);
	}
	//remplir liste 2
	for(i=0; i<nb+1000000; i++)
	{
		nombre  = (rand() % (MAX + 1 - MIN)) + MIN;
		insertion(maListe2, nombre);
	}
	//remplir liste 3
	for(i=0; i<nb+2000000; i++)
	{
		nombre  = (rand() % (MAX + 1 - MIN)) + MIN;
		insertion(maListe3, nombre);
	}
	//remplir liste 4
	for(i=0; i<nb+3000000; i++)
	{
		nombre  = (rand() % (MAX + 1 - MIN)) + MIN;
		insertion(maListe4, nombre);
	}
	//remplir liste 5
	for(i=0; i<nb+4000000; i++)
	{
		nombre  = (rand() % (MAX + 1 - MIN)) + MIN;
		insertion(maListe5, nombre);
	}
	//remplir liste 6
	for(i=0; i<nb+5000000; i++)
	{
		nombre  = (rand() % (MAX + 1 - MIN)) + MIN;
		insertion(maListe6, nombre);
	}
	//remplir liste 7
	for(i=0; i<nb+6000000; i++)
	{
		nombre  = (rand() % (MAX + 1 - MIN)) + MIN;
		insertion(maListe7, nombre);
	}
	//remplir liste 8
	for(i=0; i<nb+7000000; i++)
	{
		nombre  = (rand() % (MAX + 1 - MIN)) + MIN;
		insertion(maListe8, nombre);
	}
	//remplir liste 9
	for(i=0; i<nb+8000000; i++)
	{
		nombre  = (rand() % (MAX + 1 - MIN)) + MIN;
		insertion(maListe9, nombre);
	}
	//remplir liste 10
	for(i=0; i<nb+9000000; i++)
	{
		nombre  = (rand() % (MAX + 1 - MIN)) + MIN;
		insertion(maListe10, nombre);
	}
	
	//CREATION DU FICHIER QUI VA STOCKER LES RESULTATS 
	fichier = fopen("C:/Users/Nassima/Desktop/tpcomplexitéDM/RESULTATS.txt","w");
	
	//TABLEAU DES LISTES
	Liste (*Tab[10]) = { maListe1, maListe2, maListe3, maListe4, maListe5, maListe6, maListe7, maListe8, maListe9, maListe10 };
	
	//BOUCLE DE PARCOUR DU TABLEAU
    for(i=0;i<10;i++)
    {
        //1ERE VAR DE TEMPS
        t1 = clock();
        
        printf("\n Information sur la liste n %d", i);

        int max = cherche_max(Tab[i]);
	    printf("\n La valeur max de la liste est %d: %d", i+1, max);
        
        //2EME VAR DE TEMPS
        t2 = clock();
        
        //LA MOYENNE DU TEMPS D'EXECUTION
        delta = (double)(t2-t1)/CLOCKS_PER_SEC;
        reel = (float)delta;
        
        //AFFICHAGE DU TEMPS D'EXECUTION
        printf("\n Le temps d'execution pour la liste n: %d est: ( %lf )\n\n", i+1, delta);
        fprintf(fichier,"%lf|", delta);
	}
	fprintf(fichier,"\n");

//pour la qst2
    srand(time(NULL));
    pListV LV;
    pListH L1, L2, LH;
	pListV TV, TS, TP;
	
    LV = CreerListV();
    afficherListeV(LV);
    
    
    
	return 0;
}
