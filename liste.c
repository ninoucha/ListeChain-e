#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


//la declaration de ma liste

typedef struct Element Element;
struct Element
{
	int valeur;
	Element *suivant
};

typedef Element* llist;

//l'ajout en tete de ma liste
llist AjoutDebut(llist liste, int x)
{
		/* On crée un nouvel élément */
	    Element* nouveau = (Element*)malloc(sizeof(Element));
	
	    /* On assigne la valeur au nouvel élément */
	    nouveau->valeur = x;
	
	    /* On assigne l'adresse de l'élément suivant au nouvel élément */
	    nouveau->suivant = liste;
	    

    /* On retourne la nouvelle liste avec l'ajout de notre element */
    return nouveau;
}
//l'ajout en fin de liste
llist AjoutFin(llist Liste, int x)
{
		llist p;
		p = Liste;
		if(Liste == NULL){
			Liste = AjoutDebut(Liste,x);
		}
		else{
			/* On crée un nouvel élément */
		    Element* nouveau = (Element*)malloc(sizeof(Element));
		
		    /* On assigne la valeur au nouvel élément */
		    nouveau->valeur = x;
		
		    /* On assigne l'adresse de l'élément suivant au nouvel élément */
		    nouveau->suivant = NULL;
		    
		    while(p->suivant != NULL){
		    	p = p->suivant;
			}
			p->suivant = nouveau;
		}    
    return Liste;
}
//remplissage a la fin de notre liste
llist range_append(int n){
	int i;
	llist Liste=NULL;
	for(i=0;i<=n;i++){/* on ajoute puis i++ */
		Liste = AjoutFin(Liste, i);
	}
	return Liste;
}
//remplissage par la tete de notre liste
llist range_insert(int n){
	int i;
	llist Liste=NULL;
	for(i=n;i>=0;i--){/*on part de n et on decremente  jusqu'a i=0*/
		Liste = AjoutDebut(Liste, i);
	}
	return Liste;
}

//fontion d'affichage d'une liste
void AfficherListe(llist p)
{
	if(p != NULL){
		llist temp = p;
        while(temp != NULL)//tant que ya des elements en affiche et avance
          {
             printf(" -> %d",temp->valeur);
             temp = temp->suivant;
          }
	}else{
		printf("la liste ne contient aucun element");
	}
	printf(" -> NULL");//si liste vide retourner null
	    
}
//fonction pour le calcul de temps d'execution de la fonction range_append
void temps_execution_range_append(int taille){
	FILE* fichier=NULL;
	clock_t t1,t2;
	double delta1;
	llist Lf=NULL;
	
	fichier = fopen("C:/Users/Nassima/Desktop/tpcomplexitéDM/fichier/tempsFin2.txt","a");
	printf("\n\n Insertion dans ma liste par la queue\n");
	t1 = clock();
	Lf = range_append(taille); 
	t2 = clock();
	AfficherListe(Lf);
	delta1 = (double)(t2-t1)/CLOCKS_PER_SEC;
	printf("\n\tLe temps d execution de (range_append): \t{%lf} s",delta1);
	fprintf(fichier,"%lf\n",delta1); 
}
//fonction pour calcul du temps d'execution de la fonction range_insert
void temps_execution_temp_range_insert(int taille){//taille du n
	FILE* fichier=NULL;
	clock_t t3,t4;
	double delta2;
	llist Ld=NULL;
	
	fichier = fopen("C:/Users/Nassima/Desktop/tpcomplexitéDM/fichier/tempsDebut2.txt","a");//fichier des resultats
	printf("\n\nInsertion  dans ma liste par la tete de la liste\n");
	t3 = clock();
	Ld = range_insert(taille); 	
	t4 = clock();
	AfficherListe(Ld);
	delta2 = (double)(t4-t3)/CLOCKS_PER_SEC;
	printf("\n\tLe temps d execution de (range_insert): \t{%lf}s",delta2);
	fprintf(fichier,"%lf\n",delta2);
	
}




int main(){
	int taille=1;
	FILE* F1;
	FILE* F2;
  
    F1 = fopen("C:/Users/Nassima/Desktop/tpcomplexitéDM/fichier/tempsFin2.txt","a");
    F2 = fopen("C:/Users/Nassima/Desktop/tpcomplexitéDM/fichier/tempsDebut2.txt","a");
    printf("*****************************************************************************");
	printf("********************************Mes listes**********************************");
	while(taille!=0){//pour tout nombre sup a 1
		printf("\n Donner la taille pour votre liste : \t");
		scanf("%d",&taille);
		//calcule du temps d'execution de range_append()
		temps_execution__range_append(taille);
		//affichage
		fprintf(F1,"La taille: %d\n",taille);
		//calcul de temps d'execution de la fonction range_insert
		temps_execution_range_insert(taille);
		//affichage
		fprintf(F2,"La taille: %d\n",taille);
		
	}
		
 
	printf("\n\nfin");
	return 0;
}
