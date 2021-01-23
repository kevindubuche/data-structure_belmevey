/// Cette page contient les fonctions et les variables globales
#include <stdio.h>
#include <stdlib.h>
#include<string.h>//pour gerer les chaines de caracteres
#include<time.h>//Pour gerer la date
#define TailleTableau 50
#define NOM 15
#define FIN { printf("\nPressez une touche pour continuer\n\n");getch();fflush(stdin);  }//Macro, met le programme en pause

/*---------------------------------------------------------------------------------------*/
/* LES STRUCTURES */
typedef struct
{
    int jour;
    int mois;
    int annee;
}Date;

typedef struct
{
    long Id_oeuvr;
    char Titre[TailleTableau];
    char Desc[TailleTableau];
    char Type[TailleTableau];
    long Artist_Id;
    Date Dat_crea;
    char Localisa[TailleTableau];
    char Propriet[TailleTableau];
    float Valeur;
    char Dat_eval[NOM];
}Oeuvre;

typedef struct
{
    int    Id_Artist;
    char   Nom[NOM];
    char   Prenom[NOM];
    char   Pseudo[NOM];
    Date datenaissance;
    char   Nationalite[NOM];
    char   Statut[NOM];
    char   Adresse[TailleTableau];
    char   email[TailleTableau];
}Artiste;

typedef struct
{
    char theme[TailleTableau];
    char exposant[TailleTableau];
    int Id_exposition;
    Date date1;
    Date date2;
}Evenement;

typedef struct
{
    int id_oeuv_expo;
    int id_exposition;
    int id_oeuvr;
}Struct_Oeuvr_Expo;



/*---------------------------------------------------------------------------------------*/
/* PROTOTYPES DES FONCTIONS */

/* Fonctions generales */
void MenuPrincipal();
int Lire_Entier();
float Lire_Flottant();
void LireChaine (char chaine[]);
int diff_date(Date,Date);
int Verifier_Date(Date Date_Debut);
Date Date_Ordi();
void entrer_Date(Date *date, int Pas_Dans_Le_Passe, int Pas_Dans_Le_Futur);
void Garder_Une_Trace( int action,int ID);

//---------------------------------------------------------------------------------------------------------------------------------------
/* Fonctions module oeuvre*/
void modifier_champs_Oeuvre( int Identifiant, int Ce_Champs);
void menu_modifier_oeuvre(int);
int creer_Id_Oeuvre();
void MenuOeuvre();
void ajout_Oeuvr();
void EnregistrerOeuvre(Oeuvre *NouvelleOeuvre);
int verifier_Id_Oeuvr(int);
void Recherche_Oeuvre();
void supprim_Oeuvr();
void save_Id_oeuvre(int Id);
void Recherche_Oeuvre();

//---------------------------------------------------------------------------------------------------------------------------------------
/* Fonctions module artiste*/
void Menu_Artiste();
int ajout_artist(Date date_crea_oeuvre);
void enregistrement_Artiste(Artiste *art);
void modif_artist();
void rechercheartist();
int verifier_Id_Artist(int Id);
void modifier_champs_artiste( int Identifiant, int Ce_Champs);
void menu_modifier_artiste(int Identifiant);
int creer_Id_artiste();
void save_Id_artiste(int Id);

/*---------------------------------------------------------------------------------------*/
/* Fonctions module evenement */
void MenuEvenement();
void Afficher_Exposition();
void modifier_champs_evenement( int,int );
void menu_modifier_evenement(int Identifiant );
void ajou_oeuv_expo(int);
void Creer_expo();
void enregistrer_evenement(Evenement*);
int Evenement_Inclu(Date Date_Debut,Date Date_Fin);
int Enregistrer_Oeuvre_Externe();
void EnregistrerOeuvre_Ext(Oeuvre *NouvelleOeuvre);
void Lien_Oeuvre_Expo( Struct_Oeuvr_Expo *Mon_Lien);
int virifier_si_cet_Oeuvre_est_dans_cet_Expo( int id_oeuvre,int id_expo);
void supprim_oeuv_expo(int Identifiant);
int creer_Id_expo();
void save_Id_expo(int Id);

//---------------------------------------------------------------------------------------------------------------------------------------
/* Fonctions module rapport*/
void List_Evenement();
int verifier_Id_Evenement(int Id);
void Recherche_Evenement();
void List_Oeuv_Art();
void List_Oeuv_Mus();
void List_Artist();
void List_Oeuv_Expo(int);
void List_Artist_Expo(int);
void MenuRapport();
int Prix_Total_des_Oeuvres();

