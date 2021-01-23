#include"Bmevey.h"

 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction presente le menu principale a l'utilisateur */
    /* PARAMETRES : Aucune  */
    /* VALEUR DE RETOUR: aucune */
    /* AUTEUR :  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR : 22 Avril 2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
void MenuPrincipal()
{

    system("cls");

    int choix;
    //system("COLOR 6"); ///Fok nou antann nou sou ki couleur nap kite pou projet final lan
    printf("~~~~~~~~~~~~~~~~~~~~~~~\n BEL MEVEY...\n     MENU PRINCIPAL\n~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n| 1- Module Oeuvre d'art\n| 2- Module Artiste\n| 3- Module Evenement\n| 4- Rapports\n| 0- Quitter\n|________________________\nEnter votre choix :\n");
    choix=Lire_Entier();
    switch (choix)
    {
        case 1 :
                MenuOeuvre();
            break;
        case 2:
                Menu_Artiste();
            break;
        case 3 :
                MenuEvenement();
            break;
        case 4 :
                MenuRapport();
            break;
        case 0 :
            {
            system("cls");
            printf("\n\n\n__________Au revoir !!!__________ \n\n\n\n");
            exit(EXIT_SUCCESS);//on sort du programme
            }
            break;
        default:
            {
            system("cls");
            printf("ERREUR !!! : Faites un de ces choix\n");
            MenuPrincipal();
            }
    }
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction gere toutes les restrictions sur la lecture d'une chaine de caracteres */
    /* PARAMETRES : char[]  */
    /* VALEUR DE RETOUR: int */
    /* AUTEUR :   */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR : 22 Avril 2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
void LireChaine (char chaine[])
{
         fgets(chaine,TailleTableau,stdin);//on recupere la chaine de caracteres entree par l'utilisateur
    chaine[strlen(chaine)-1]='\0';//A verifier...on remplce le\n par \0 qui signifie fin de la chaine
    fflush(stdin);//on vide le buffer
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction gere toutes les restrictions sur la lecture d'un entier*/
    /* PARAMETRES : Aucune  */
    /* VALEUR DE RETOUR: int */
    /* AUTEUR : */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR : 22 Avril 2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
int Lire_Entier()
{
    int nbre=0,  retour;
    int ok=0;//c'est une variable temoin

    while(!ok)
    {
        retour=scanf("%d%*[^\n]",&nbre);//seulement les nbres entiers comptent. \n est neglige a l'entree
        if(!retour)//si le scanf n'a pas reussi
        {
            int c;
            printf("ERREUR ! Il faut entrer un nombre .Essayer a nouveau\n");
            while((( c= getchar()!='\n') && c!=EOF) );//on vide la memoire jusqu'a la fin
        }
        else//si tout s'est bien passe
        {
            getchar();//on enleve le \n de la memoire (du buffer)
            ok =1;
        }
    }
    return nbre;//la fontion retourne notre nombre
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction gere toutes les restrictions sur la lecture d'un nombre decimal.*/
    /* PARAMETRES : Aucune  */
    /* VALEUR DE RETOUR: int */
    /* AUTEUR :  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR : 22 Avril 2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
float Lire_Flottant()
{
    float nbre=0;
    int ok=0, retour;

    while(!ok)
    {
        retour=scanf("%f%*[^\n]",&nbre);//seulement les nbres  comptent. \n est neglige a l'entree
        if(!retour)//si le scanf n'a pas reussi
        {
            int c;
            printf("ERREUR ! Il faut entrer un nombre .Essayer a nouveau\n");
            while((( c= getchar()!='\n') && c!=EOF) );//on vide la memoire jusqu'a la fin

        }
        else//si tout s'est bien passe
        {
            getchar();//on enleve le \n de la memoire
            ok =1;
        }
    }
    return nbre;
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction fait la difference entre les deux dates. Ceci aide a respecter la chronologie*/
    /* PARAMETRES : date, date  */
    /* VALEUR DE RETOUR: int */
    /* AUTEUR : DUBUCHE Kevin J  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR : 22 Avril 2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
int diff_date(Date maDate1,Date maDate2)
{
    return    (  (maDate1.jour+maDate1.mois*30+maDate1.annee*365)-
       (maDate2.jour+maDate2.mois*30+maDate2.annee*365)  );
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet d'entrer une date en tenant compte des restrictions*/
    /* PARAMETRES : date, int, int  */
    /* VALEUR DE RETOUR: float */
    /* AUTEUR : DUBUCHE Kevin J  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR : 22 Avril 2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
void entrer_Date(Date *date, int Pas_Dans_Le_Passe, int Pas_Dans_Le_Futur)
{
    int tem=1;
    do
    {
        do
        {
            printf("Entrer l'annee\n");
            date->annee=Lire_Entier();
            if(date->annee<=0 || date->annee>3000)
            printf("Erreur !!!L'annee doit etre inferieure a 3000 et > 0. Essayer a nouveau\n");
        }
        while(date->annee<=0 || date->annee>3000);
        do
        {
            printf("Entrer le numero du mois\n");
            date->mois=Lire_Entier();
            if(date->mois<=0 || date->mois>12)
            printf("Erreur dans la saisie du mois. Essayer a nouveau\n");
        }
        while(date->mois<=0 || date->mois>12);
        do
        {
            printf("Entrer le jour\n");
            date->jour=Lire_Entier();

            if(date->jour <=0 || date->jour >31
                || (date->mois%2==0 && date->mois<=6 &&date->jour>30)
                    || (date->mois%2==1 && date->mois>=9 &&date->jour>30)
                        || (date->mois==2 && date->jour>29)
                            || (date->annee%4!=0 && date->mois==2 && date->jour>28))
            {
                tem=0;
                printf("Erreur dans la saisie du jour!!! Essayer a nouveau\n");
            }
            else tem=1;

        }
        while(tem==0);

        if(Pas_Dans_Le_Futur==1 && diff_date(Date_Ordi(),*date)<0)
        {
            printf("Erreur. Cette date ne pas etre dans le futur!! Essayer a nouveau\n");
            tem=0;
        }
        else if(Pas_Dans_Le_Passe==1 && diff_date(Date_Ordi(),*date)>0)
            {
                printf("Erreur. Cette date ne peut pas etre dans le passe!! Essayer a nouveau\n");
                tem=0;
            }
        else tem=1;
    }
    while(tem==0);
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet de recuperer la date de l'ordinateur*/
    /* PARAMETRES : aucun*/
    /* VALEUR DE RETOUR: date*/
    /* AUTEUR : DUBUCHE Kevin J  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR : 22 Avril 2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
Date Date_Ordi()
{
    time_t secondes;
    Date date_PC;
    struct tm instant;
    time(&secondes);
    instant=*localtime(&secondes);
    date_PC.jour=instant.tm_mday;
    date_PC.mois=(instant.tm_mon+1);
    date_PC.annee=(instant.tm_year+1900);
    return(date_PC);
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet d'enregistrer tout ce qui se fait dans la base de donnees*/
    /* PARAMETRES : int,int*/
    /* VALEUR DE RETOUR: date*/
    /* AUTEUR : DUBUCHE Kevin J  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR : 22 Avril 2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
void Garder_Une_Trace( int action,int ID)
{
    FILE *TRACE=NULL;
     TRACE = fopen("TRACE.dat","a");
    if( TRACE!= NULL)
        {
            switch(action)
            {
                case 1 :  fprintf(TRACE,"%s_______________Enregistrement de l'oeuvre ID : %d\n",__DATE__,ID);
                break;
                case 2 :  fprintf(TRACE,"%s_______________Modification de l'oeuvre ID : %d\n",__DATE__,ID);
                break;
                case 3 :  fprintf(TRACE,"%s_______________Supression de l'oeuvre ID : %d\n",__DATE__,ID);
                break;

                case 4 :  fprintf(TRACE,"%s_______________Enregistrement de l'artiste ID : %d\n",__DATE__,ID);
                break;
                case 5 :  fprintf(TRACE,"%s_______________Modification de l'artiste ID : %d\n",__DATE__,ID);
                break;

                case 6 :  fprintf(TRACE,"%s_______________Enregistrement de l'evenement ID : %d\n",__DATE__,ID);
                break;
                 case 7 :  fprintf(TRACE,"%s_______________Modification de l'evenement ID : %d\n",__DATE__,ID);
                break;
            }

        }
        else printf("Erreur d'ouverture du fichier TRACE.dat\n");
        fclose(TRACE);
}

