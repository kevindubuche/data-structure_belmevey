#include"Bmevey.h"
/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction presente le menu du module artiste a l'utilisateur */
/* PARAMETRES : Aucune  */
/* VALEUR DE RETOUR:  Aucun */
/* AUTEUR : LUC Yvrans  */
/* DATE CREATION: 6 Avril 2018  */
/* DATE MISE A JOUR : 2 Juillet 2018  */
/* REMARQUES : Aucune */
/*---------------------------------------------------------------------------------------*/
void Menu_Artiste()
{
    system("cls");//efface tout l'ecran
    int choix, Identifiant;
    printf("____________MODULE ARTISTE____________\n\n 1- Modifier les donnees d'un artiste\n 2- Rechercher un artiste\n 0- Retour au menu principal\n");
    choix=Lire_Entier();
    switch(choix)
    {
    case 1:
    {
        printf("____________MODIFIER ARTISTE____________\n\n Connaissez-vous l'ID de l'artiste que vous voulez modifier?\n");
        int choix1;
        printf("  1- Oui\n  2- Non. Rechercher  d'abord l'artiste\n  0- Retour\n");
        choix1=Lire_Entier();
        switch(choix1)
        {
        case 1:
        {
            do
            {
                printf("\nEntrer l'identifiant de l'artiste que vous voulez modifier :\n<0- Retour>\n");
                Identifiant=Lire_Entier();
                if(Identifiant==0)
                    Menu_Artiste();
            }
            while(! verifier_Id_Artist(Identifiant) );
        }
        break;
        case 2 :
        {
            rechercheartist();
            Menu_Artiste();
        }
        break;
        case 0 :
        {
            system("cls");
            MenuPrincipal();
        }
        break;
        default :
            Menu_Artiste();
        }
        menu_modifier_artiste(Identifiant);
        Menu_Artiste();
    }
    break;
    case 2:
    {
        system("cls");
        rechercheartist();
        Menu_Artiste();
    }
    break;
    case 0:
        MenuPrincipal();
        break;
    default :
        Menu_Artiste();// pour forcer l utilisateur a choisir une option
    }
}
/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction permet de rentrer les informations concernant un artiste */
/* PARAMETRES : Aucune  */
/* VALEUR DE RETOUR: Aucune*/
/* AUTEUR : LUC Yvrans  */
/* DATE CREATION: 6 Avril 2018  */
/* DATE MISE A JOUR : 15 mai 2018  */
/* REMARQUES : Aucune */
/*---------------------------------------------------------------------------------------*/
int ajout_artist(Date date_crea_oeuvre)//pour verifier que l'artiste soit ne avant la date de creation de l'oeuvre
{
    printf("\n\n____________AJOUTER ARTISTE____________\n<Entrer 0 pour annuler>\n\n");
    Artiste Atis={0};//Declarer et initialiser la structure
    printf("Entrer le nom de l'artiste:\n");
    LireChaine(Atis.Nom);if(Atis.Nom[0]=='0')MenuOeuvre();
    printf("Prenom de l'artiste:\n");
    LireChaine(Atis.Prenom);if(Atis.Prenom[0]=='0')MenuOeuvre();
    printf("Pseudo :\n");
    LireChaine(Atis.Pseudo);if(Atis.Pseudo[0]=='0')MenuOeuvre();
   do
   {
        printf("Entrer la date de naissance de l'artiste:\n");
    entrer_Date(&Atis.datenaissance,0,1);
    if(diff_date(Atis.datenaissance,date_crea_oeuvre)>0)printf("Erreur ! L'artiste doit etre plus grand que l'oeuvre\n");
   }while(diff_date(Atis.datenaissance,date_crea_oeuvre)>0);//on verifie que l'artiste est nea avant l'oeuvre

    printf("Entrer la nationalite de l'artiste :\n");
    LireChaine(Atis.Nationalite);if(Atis.Nationalite[0]=='0')MenuOeuvre();
    printf("Entrer le statut:\n");
    LireChaine(Atis.Statut);if(Atis.Statut[0]=='0')MenuOeuvre();
    printf("Entrer l'adresse de l'artiste :\n");
    LireChaine(Atis.Adresse);if(Atis.Adresse[0]=='0')MenuOeuvre();
    printf("Entrer l'email de l'artiste :\n");
    LireChaine(Atis.email);if(Atis.email[0]=='0')MenuOeuvre();


    int confirmation;
    __Label1:  printf("\nConfirmez l'enregistrement de l'artiste :\n 1- Oui\n 2- Annuler\n");
    confirmation=Lire_Entier();
    switch(confirmation)
    {
        case 1:
            {
                system("cls"); // 5eme element a partir de la fin a modifier /// date
                Atis.Id_Artist =creer_Id_artiste();
                save_Id_artiste(Atis.Id_Artist);
                printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
                printf("\n     Identifiant |             Nom |          Prenom |          Pseudo |  Date de Naissance |     Nationalite |           Statut|                                            Adresse |                                              Email |");
                printf("\n===========================================================================================================================================================================================================================================");
                printf("\n %015d | %15s | %15s | %15s |    %02i / %02i / %04i  | %15s | %15s | %50s | %50s |",Atis.Id_Artist,Atis.Nom,Atis.Prenom,Atis.Pseudo,Atis.datenaissance.jour,Atis.datenaissance.mois,Atis.datenaissance.annee,Atis.Nationalite,Atis.Statut,Atis.Adresse,Atis.email);
                printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
                printf("\nEnregistrement de l'artiste reussi\n");
            }
            break;
        case 2:
            {
                system("cls");
                return(0);
            }
            break;
        default :
            {
                system("cls");
                printf("Faites l'un de ces choix\n");
                goto __Label1;
            }
    }
    if(confirmation==1)
    enregistrement_Artiste(&Atis);
    FIN
    return (Atis.Id_Artist);
}
/*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet d'enregistrer un artiste dans un fichier externe */
    /* PARAMETRES : Aucune  */
    /* VALEUR DE RETOUR: Aucune*/
    /* AUTEUR :  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :17 mai 2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
void enregistrement_Artiste(Artiste *art)
{
    FILE *artist= NULL;
    artist = fopen("artist.dat","ab");//ouvri fichier
    if(artist != NULL)// teste d'erreur d'ouverture du fichier
      {
        fwrite(art,sizeof(*art),1,artist); //on ecrit notre structure dans le fichier
        Garder_Une_Trace(4,art->Id_Artist);
      }
    else
        printf("\nErreur lors de l'ouverture du fichier artist.dat\n");//message d'erreur
    fclose(artist);//femen fiche an
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction aide a rechercher un artiste*/
    /* PARAMETRES : Aucun*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :18 mai2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void rechercheartist()
{
    Artiste Artiste_recherche;
    char titre[TailleTableau];
    int temoin=0;
    int  choix , ID;
    printf("\n_______________RECHERCHER ARTISTE_______________\n\n 1- Recherche par ID de l'artiste\n 2- Recherche par nom/prenom/pseudo de l'artiste\n 0- Menu artiste\nEntrez votre choix :\n");
    choix=Lire_Entier();
    switch (choix )
        {
            case 1 :
                {
                    do
                    {
                    printf("Entrez l'ID de l'artiste recherche\n<0- Retour>\n");
                    ID=Lire_Entier();
                    if(ID==0) rechercheartist();
                    }while(!verifier_Id_Artist(ID));
                }
                break;
            case 2:
                {
                    printf("Entrez le nom (prenom ou pseudo) de l'artiste recherchee :\n");
                    LireChaine(titre);
                }
                break;
            case 0:
                    Menu_Artiste();
                break;
            default :
                {
                    system("cls");
                    printf("Faites l'un de ces choix\n");
                    rechercheartist();
                }
        }

    FILE *artist= NULL;//on declare un pointeur de type FILE pour creer notre fichier et on l'initialise
    artist = fopen("artist.dat","rb");// on ouvre notre fichier en mode "rb", i.e lecture sous forme binaire
    if(artist != NULL)// teste d'erreur d'ouverture du fichier
        {
            printf("\n____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
            printf("\n      Identifiant |             Nom |          Prenom |          Pseudo |  Date de Naissance |     Nationalite |           Statut|                                            Adresse |                                              Email |");
            printf("\n============================================================================================================================================================================================================================================");
            while(fread(&Artiste_recherche,sizeof(Artiste_recherche),1,artist)==1)
                {//on lit notre structure  a partir fichier
                    if(  (choix==1 && (Artiste_recherche.Id_Artist==ID )) ||(choix==2 && strcmp(Artiste_recherche.Nom, titre) == 0 )||(choix==2 && strcmp(Artiste_recherche.Prenom, titre) == 0 ) ||(choix==2 && strcmp(Artiste_recherche.Pseudo, titre) == 0 ))//on compare les id
                    {
                        temoin=1;
                        printf("\n %015d  | %15s | %15s | %15s |   %02i / %02i / %04i   | %15s | %15s | %50s | %50s |",Artiste_recherche.Id_Artist,Artiste_recherche.Nom,Artiste_recherche.Prenom,Artiste_recherche.Pseudo,Artiste_recherche.datenaissance.jour,Artiste_recherche.datenaissance.mois,Artiste_recherche.datenaissance.annee,Artiste_recherche.Nationalite,Artiste_recherche.Statut,Artiste_recherche.Adresse,Artiste_recherche.email);
                        printf("\n____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
                    }
                }
            if(temoin==0) printf("\nCet artiste n'existe pas\n");
        }
    else printf("\nErreur d'ouverture du fichier artist.dat\n");
    fclose(artist);
    FIN
}
/*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet de verifier que l'identifiant en question existe dans la base de donnee */
    /* PARAMETRES : int identifiant  */
    /* VALEUR DE RETOUR: int */
    /* AUTEUR :  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :18 mai2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
int verifier_Id_Artist(int Id)
{
    Artiste compare;
    FILE *artist= NULL;
    artist = fopen("artist.dat","rb");
    if(artist != NULL)
    {
        rewind(artist);
        while( fread(&compare,sizeof(compare),1,artist)==1) //tant que mpa nan fin fichier a
        {
            if(Id==compare.Id_Artist)
                {
                    fclose(artist);
                    return 1;
                }
        }
    }
    else printf("Erreur d'ouverture du fichier artist.dat");
    printf("\n Cet identifiant n'existe pas. Veuillez essayer a nouveau\n\n");
    fclose(artist);
    return 0;
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction affiche les differentes modifications possibles sur un artiste du Musee*/
    /* PARAMETRES : int identifiant*/
    /* VALEUR DE RETOUR: Aucune */
    /* AUTEUR :Luc yvrans   */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :17 mai 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void menu_modifier_artiste(int Identifiant)
{
    int choix;
    printf("____________MODIFIER ARTISTE   %d____________\n\nQuelle donnee vous voulez modifier ?\n 1-  Nom\n 2-  Prenom\n 3-  Pseudo\n 4-  Date de naissance\n 5-  Nationnallite\n 6-  Statut\n 7-  Adresse\n 8-  Email\n 0-  Retour\n\n",Identifiant);
    choix=Lire_Entier();
    switch(choix)
        {
            case 1: modifier_champs_artiste(Identifiant,1);
                break;
            case 2: modifier_champs_artiste(Identifiant,2);
                break;
            case 3: modifier_champs_artiste(Identifiant,3);
                break;
            case 4: modifier_champs_artiste(Identifiant,4);
                break;
            case 5: modifier_champs_artiste(Identifiant,5);
                break;
            case 6: modifier_champs_artiste(Identifiant,6);
                break;
            case 7: modifier_champs_artiste(Identifiant,7);
                break;
            case 8: modifier_champs_artiste(Identifiant,8);
                break;
            case 0:
                    Menu_Artiste();
                break;
            default:
                {
                    system("cls");
                    printf("Faites l'un de ces choix :\n\n");
                    menu_modifier_artiste(Identifiant);
                }
        }
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet de faire les modifications appliquables sur une oeuvre*/
    /* PARAMETRES : int identifiant, int le champ a modifier*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 mai 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void modifier_champs_artiste( int Identifiant, int Ce_Champs)
{
     Artiste Atist={0};
     Artiste temp={0};
    switch(Ce_Champs)
        {
            case 1:
                {
                    printf("\nEntrez le nouveau nom:\n");
                    LireChaine(Atist.Nom);
                }
                break;
            case 2:
                {
                    printf("\nEntrez le nouveau prenom:\n");
                    LireChaine(Atist.Prenom);
                }
                break;
            case 3:
                {
                    printf("\nEntrez le nouveau pseudo:\n");
                    LireChaine(Atist.Pseudo);
                }
                break;
            case 4:
                {
                    printf("Entrez la nouvelle date de naissance\n");
                    entrer_Date(&Atist.datenaissance,0,1);
                }
                break;
            case 5:
                {
                    printf("\nEntrez la nouvelle nationalite:\n");
                    LireChaine(Atist.Nationalite);
                }
                break;
            case 6:
                {
                    printf("\nEntrez le nouveau statut:\n");
                    LireChaine(Atist.Statut);
                }
                break;
            case 7:
                {
                    printf("\nEntrez la nouvelle adresse:\n");
                    LireChaine(Atist.Adresse);
                }
                break;
            case 8:
                {
                    printf("\nEntrez le nouveau email:\n");
                    LireChaine(Atist.email);
                }
                break;
            default:
                {
                    printf("Faites l'un de ces choix\n");
                    modifier_champs_artiste(Identifiant, Ce_Champs);//on retourne au menu de modification
                }
        }
    FILE *artist=NULL;
    artist=fopen("artist.dat","rb");
    FILE* fichier_temp=NULL;
fichier_temp=fopen("fichier_temp.dat","ab");
    if(artist!=NULL && fichier_temp !=NULL)
    {
        while(fread(&temp,sizeof(temp),1,artist) ==1 && Identifiant!=temp.Id_Artist)
        fwrite(&temp,sizeof(temp),1,fichier_temp);
            if(Identifiant==temp.Id_Artist)//quand on trouve l'artiste en question
            {
                switch(Ce_Champs)
                    {//on fait notre modification
                        case 1: strcpy(temp.Nom,Atist.Nom);
                                break;
                        case 2:strcpy(temp.Prenom,Atist.Prenom);
                                break;
                        case 3: strcpy(temp.Pseudo,Atist.Pseudo);
                                break;
                        case 4: temp.datenaissance=Atist.datenaissance;
                                break;
                        case 5:strcpy(temp.Nationalite,Atist.Nationalite);
                                break;
                        case 6:strcpy(temp.Statut,Atist.Statut);
                                break;
                        case 7: strcpy(temp.Adresse,Atist.Adresse);
                                break;
                        case 8: strcpy(temp.email,Atist.email);
                                break;
                    }
    fwrite(&temp,sizeof(temp),1,fichier_temp);
    printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
    printf("\n      Identifiant |             Nom |          Prenom |          Pseudo |  Date de Naissance |     Nationalite |           Statut|                                            Adresse |                                              Email |");
    printf("\n=============================================================================================================================================================================================================================================");
    printf("\n %015d  | %15s | %15s | %15s |   %02i / %02i / %04i   | %15s | %15s | %50s | %50s |",temp.Id_Artist,temp.Nom,temp.Prenom,temp.Pseudo,temp.datenaissance.jour,temp.datenaissance.mois,temp.datenaissance.annee,temp.Nationalite,temp.Statut,temp.Adresse,temp.email);
    printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
    printf("\n\nModification reussie \n\n");
     Garder_Une_Trace(5,Identifiant);
    while(fread(&temp,sizeof(temp),1,artist)==1)//on enregistre le reste du fichier
        fwrite(&temp,sizeof(temp),1,fichier_temp);
        }

        fclose(artist) ;
    fclose(fichier_temp);
    remove("artist.dat");
    rename("fichier_temp.dat","artist.dat");
    }else printf("Erreur d'ouverture des fichiers artist.dat ou Nouveau_fichier.dat\n");

    FIN
    menu_modifier_artiste(Identifiant);
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet de creer l'ID de l'artiste sans demander a l'utilisateur de rentrer quoi que ce soit*/
    /* PARAMETRES : Aucun */
    /* VALEUR DE RETOUR: int */
    /* AUTEUR :*/
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 mai 2018  */
    /* REMARQUES : On sctokera cet ID dans un fichier. On recupere d'abord le dernier ID enregistre puis on l'incremente*/
    /*---------------------------------------------------------------------------------------*/
int creer_Id_artiste()
{
    FILE *Fichier_Id_artiste= NULL;
    int Id;
    Fichier_Id_artiste = fopen("Fichier_Id_artiste.dat","r");
    if(Fichier_Id_artiste != NULL)
    {
        fscanf(Fichier_Id_artiste,"%d",&Id);
        Id++;
    }
    else printf("\nErreur d'ouverture du fichier Fichier_Id_artiste.dat\n");
    fclose(Fichier_Id_artiste);
    return Id;
}

 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction intervient dans la sauvegarde de l'ID de l'artiste*/
    /* PARAMETRES : int*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void save_Id_artiste(int Id)
{
    FILE *Fichier_Id_artiste= NULL;
    Fichier_Id_artiste = fopen("Fichier_Id_artiste.dat","w");
    if(Fichier_Id_artiste != NULL)
    fprintf(Fichier_Id_artiste,"%d",Id);
    else printf("Erreur d'ouverture du fichier Fichier_Id_artiste.dat\n");
    fclose(Fichier_Id_artiste);
}
