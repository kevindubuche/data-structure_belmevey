#include"Bmevey.h"
/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction presente le menu du module Evenement a l'utilisateur */
/* PARAMETRES : Aucune  */
/* VALEUR DE RETOUR:  Aucun */
/* AUTEUR : Compas Elisabeth */
/* DATE CREATION: 6 Avril 2018  */
/* DATE MISE A JOUR : 2 Juillet 2018  */
/* REMARQUES : Aucune */
/*---------------------------------------------------------------------------------------*/
void MenuEvenement()
{
    system("cls");
    int choix;
    printf("____________EVENEMENT____________\n\n 1- Creer une exposition\n 2- Modifier une exposition\n 3- Rechercher une exposition\n 0-Retour\n\nEntrer votre choix :\n");
    choix=Lire_Entier();
    switch(choix)
    {
        case 1:
            {
                system("cls");
                Creer_expo();
                MenuEvenement();
            }
            break;
        case 2:
            {
                int Identifiant;
                printf("____________MODIFIER EVENEMENT____________\n\n Connaissez-vous l'ID de l'evenement que vous voulez modifier?\n");
                int choix1;
                printf("  1- Oui\n  2- Non. Rechercher  d'abord l'evenement\n  0- Retour\n");
                choix1=Lire_Entier();
                switch(choix1)
                {
                    case 1:
                        {
                            do
                                {
                                    printf("\nEntrer l'identifiant de l'evenement que vous voulez modifier :\n");
                                    Identifiant=Lire_Entier();
                                }
                            while(! verifier_Id_Evenement(Identifiant) );
                        }
                        break;
                    case 2 :
                        {
                            Recherche_Evenement();
                            MenuEvenement();
                        }
                        break;
                    case 0 :
                            MenuEvenement();
                        break;
                    default : MenuEvenement();
                }
              menu_modifier_evenement(Identifiant);system("cls");MenuEvenement();/// Wait, sak passer laa?
            }
            break;
        case 3:
            {
                system("cls");
                Recherche_Evenement();
                MenuEvenement();
            }
            break;
        case 0: MenuPrincipal();
            break;
        default:
            {
                printf("Faites l'un de ces choix :\n");
                MenuEvenement();
            }
    }
}
/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction permet de rentrer les informations concernant une exposition */
/* PARAMETRES : Aucune  */
/* VALEUR DE RETOUR: Aucune*/
/* AUTEUR : Compas Elisabeth */
/* DATE CREATION: 6 Avril 2018  */
/* DATE MISE A JOUR : 23 juin 2018  */
/* REMARQUES : Aucune */
/*---------------------------------------------------------------------------------------*/
void Creer_expo()
{
    Evenement expo={0};
    printf("___________CREER UN EVENEMENT____________\n<Entrer 0 pour anuler>\n\n");
    printf("\nEntrez le theme:\n");
    LireChaine(expo.theme);
    if(expo.theme[0]=='0')
        MenuEvenement();
__Label_saisir_Dates:
    do
    {
        printf("\nEntrez la date du debut de l'exposition\n");
        entrer_Date(&expo.date1,1,0);
    }
    while(Verifier_Date(expo.date1)==0);
    do
    {
        printf("\n Entrez la date de la fin de l'exposition\n");
        entrer_Date(&expo.date2,1,0);
        if(diff_date(expo.date1,expo.date2)>0)
            printf("Cette date ne peut pas etre avant la date du debut\nEssayer a nouveau\n");
    }
    while(diff_date(expo.date1,expo.date2)>0  || (Verifier_Date(expo.date2)==0 ));
    if(Evenement_Inclu(expo.date1,expo.date2)==1)
        goto __Label_saisir_Dates;
    printf("\nEntrez le nom de l'exposant\n");
    LireChaine(expo.exposant);
    if(expo.exposant[0]=='0')
        MenuEvenement();
    expo.Id_exposition =creer_Id_expo();
__Label :
    printf("Confirmer l'enregistrement :\n 1- Oui\n 2- Non\n");
    int confirmation;
    confirmation=Lire_Entier();
    switch(confirmation)
    {
    case 1:
    {
        save_Id_expo(expo.Id_exposition);
        enregistrer_evenement(&expo);
        printf("\n__________________________________________________________________________________________________________________________________________________________________________");
        printf("\n     Identifiant |                                              Theme |                                        Proprietaire|           Date Debut |    Date d'evaluation |");
        printf("\n==========================================================================================================================================================================");
        printf("\n %015d | %50s | %50s |   %02i / %02i / %04i     |   %02i / %02i / %04i     |",expo.Id_exposition,expo.theme,expo.exposant,expo.date1.jour,expo.date1.mois,expo.date1.annee,expo.date2.jour,expo.date2.mois,expo.date2.annee);
        printf("\n__________________________________________________________________________________________________________________________________________________________________________");
        FIN
        MenuEvenement();
    }
    break;
    case 2:
        MenuEvenement();
        break;
    default:
        goto __Label;
    }
}
/*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet d'enregistrer une oeuvre dans un fichier externe */
    /* PARAMETRES : Aucune  */
    /* VALEUR DE RETOUR: Aucune*/
    /* AUTEUR :  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 juin 2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
void enregistrer_evenement(Evenement* exposition)
{
    FILE* exposit=NULL;
    exposit=fopen("exposit.dat","ab");
    if(exposit!=NULL)
   {
       fwrite(exposition,sizeof(*exposition),1,exposit);
       Garder_Une_Trace(6,exposition->Id_exposition);
   }
    else printf("\nErreur d'ouverture du fichier exposit.dat\n\n");
    fclose(exposit);
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction affiche les differentes modifications possibles sur un evenement du Musee*/
    /* PARAMETRES : int identifiant*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 juin 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void menu_modifier_evenement(int Identifiant )
{
    int choix ;
    printf("____________MODIFIER EXPOSITION   %d____________\n\n 1- Modifier theme\n 2- Modifier dates d'une exposition\n 3- Modifier nom de l'exposant\n",Identifiant);
    printf(" 4- Ajouter des oeuvres a une expo\n 5- Effacer des oeuvres dans une expo\n 0- Retour\n\nEntrer votre choix :\n");
    choix=Lire_Entier();
    switch(choix)
    {
        case 1: modifier_champs_evenement(Identifiant,1);
            break;
        case 2: modifier_champs_evenement(Identifiant,2);
            break;
        case 3: modifier_champs_evenement(Identifiant,3);
            break;
        case 4: ajou_oeuv_expo(Identifiant);
            break;
        case 5:supprim_oeuv_expo(Identifiant);
         break;
        case 0:
            MenuEvenement();
            break;
        default:
            {
                system("cls");
                printf("Faites l'un de ces choix :\n\n");
                menu_modifier_evenement(Identifiant);
            }
    }
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION :  Cette fonction permet d'ajouter une oeuvre a une exposition du Musee*/
    /* PARAMETRES : int identifiant*/
    /* VALEUR DE RETOUR: Aucune */
    /* AUTEUR :Compas Elisabeth  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :2 mai 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void ajou_oeuv_expo(int Identifiant)
{
    int choix;   Struct_Oeuvr_Expo Mon_Lien={0};
    printf("\nCette oeuvre appartient-elle au Musee?");
    printf("\n Faites votre choix! \n 1- Oui\n 2- Non\n<0- Retour>\n");
    choix=Lire_Entier();
    switch(choix)
    {
        case 1:
            {
                List_Oeuv_Mus();
          do
          {printf("Entrer l'ID de l'oeuvre que vous avez choisie\n<0- Retour>\n");
              Mon_Lien.id_oeuvr=Lire_Entier();
              if( Mon_Lien.id_oeuvr==0)    menu_modifier_evenement(Identifiant);
              }while(!verifier_Id_Oeuvr(Mon_Lien.id_oeuvr));

                Mon_Lien.id_exposition=Identifiant;

                if(virifier_si_cet_Oeuvre_est_dans_cet_Expo(Mon_Lien.id_oeuvr,Identifiant)==0)
                {Lien_Oeuvre_Expo(&Mon_Lien);
                    printf("\nCette oeuvre a ete ajoutee a l'exposition %d avec SUCCES\n",Identifiant);

                }
                FIN
               menu_modifier_evenement(Identifiant);
            }
            break;
        case 2:
            {
                   Mon_Lien.id_oeuvr= Enregistrer_Oeuvre_Externe();
                   if(Mon_Lien.id_oeuvr==0){printf("Anuler\n");FIN menu_modifier_evenement(Identifiant);;}
                Mon_Lien.id_exposition=Identifiant;
                if(virifier_si_cet_Oeuvre_est_dans_cet_Expo(Mon_Lien.id_oeuvr,Identifiant)==0)
               {
                   Lien_Oeuvre_Expo(&Mon_Lien);
                printf("\nCette oeuvre a ete ajoutee a l'exposition %d avec SUCCES\n",Identifiant);
               }
                FIN
                menu_modifier_evenement(Identifiant);
            }
            break;
             case 0:
                menu_modifier_evenement(Identifiant);
            break;
        default: ajou_oeuv_expo(Identifiant);
            break;
    }
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION :  Cette fonction permet de supprimer une oeuvre d'une exposition du Musee*/
    /* PARAMETRES : int identifiant*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void supprim_oeuv_expo(int Identifiant)
{
    int id_oeuvre;
    Struct_Oeuvr_Expo Mon_Lien={0};
    List_Oeuv_Expo(Identifiant);
    do
    {
        printf("Entrer l'ID de l'oeuvre que vous avez choisie\n<0- Retour>\n");
        id_oeuvre=Lire_Entier();
        if(id_oeuvre==0)
            menu_modifier_evenement(Identifiant);
    }
    while(!verifier_Id_Oeuvr(id_oeuvre));

    if(virifier_si_cet_Oeuvre_est_dans_cet_Expo(id_oeuvre,Identifiant)==1)
    {
        FILE *oeuvr= NULL, *oeuvr_Intermed= NULL;
        oeuvr = fopen("Oeuv_exp.dat","rb");//on ouvre le fichier en mode lecture binaire
        oeuvr_Intermed = fopen("Oeuv_exp_interm.dat","ab");//on ouvre le fichier en mode ajout binaire
        if(oeuvr != NULL && oeuvr_Intermed != NULL)
        {
            rewind(oeuvr);//on met le curseur au debut du fichier oeuvr
            while( fread(&Mon_Lien,sizeof(Mon_Lien),1,oeuvr)==1 )
            {
                if(Mon_Lien.id_exposition==Identifiant && Mon_Lien.id_oeuvr==id_oeuvre)
                    printf("Cette oeuvre a ete supprimee de l'exposition  %i avec SUCCES\n",Identifiant);
                else
                    fwrite(&Mon_Lien,sizeof(Mon_Lien),1,oeuvr_Intermed);//on les copie dans le fichier intermediare
            }
            fclose(oeuvr_Intermed);
            fclose(oeuvr);
            remove("Oeuv_exp.dat");//on supprime l'ancien fichier
            rename("Oeuv_exp_interm.dat", "Oeuv_exp.dat");//on enregistre le nouveau qui contient les modification
        }
        else
            printf("\nERREUR lors de l'ouverture du fichier oeuvr.dat et oeuvr_Intermer.dat\n");
    }
    FIN
    menu_modifier_evenement(Identifiant);
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet de faire les modifications appliquables sur un evenement*/
    /* PARAMETRES : int identifiant, int le champ a modifier*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void modifier_champs_evenement( int Identifiant, int Ce_Champs)
{
    Evenement exposition={0};
    Evenement expo={0};
    Date Date_Debut, Date_Fin;
    int confirmation=0;
    switch(Ce_Champs)
    {
        case 1:
            {
                printf("\nEntrez le nouveau theme:\n");
                LireChaine(exposition.theme);
            }
            break;
    case 2:
        {
__Label_saisir_Dates_modif:
            do
            {
                printf("\nEntrez la nouvelle date du debut de l'exposition\n\n");
                entrer_Date(&Date_Debut,1,0);
            }
            while(Verifier_Date(Date_Debut)==0);
            do
            {
                printf("\nEntrez la nouvelle date de la fin de l'exposition\n\n");
                entrer_Date(&Date_Fin,1,0);
                if(diff_date(Date_Debut,Date_Fin)>0)
                    printf("Cette date ne peut pas etre avant la date du debut\nEssayer a nouveau\n");
            }
            while(diff_date(Date_Debut,Date_Fin)>0  || (Verifier_Date(Date_Fin)==0 ));
            if(Evenement_Inclu(Date_Debut,Date_Fin)==1)
                goto __Label_saisir_Dates_modif;
        }
        break;
        case 3:
            {
                printf("Entrez le nom du nouveau exposant\n");
                LireChaine(exposition.exposant);
            }
            break;
        default:
            {
                printf("Faites l'un de ces choix\n");
                modifier_champs_evenement(Identifiant, Ce_Champs);
            }
    }
    printf("Confirmer la modification\n 1- Oui\n 0- Non\n");confirmation=Lire_Entier();
    switch(confirmation)
    {
    case 1:
        {
             FILE *exposit=NULL;
    exposit=fopen("exposit.dat","rb");
    FILE* temoin=NULL;
    temoin=fopen("temoin.dat","ab");
    while (fread(&expo,sizeof(expo),1,exposit) ==1 && Identifiant!=expo.Id_exposition)
                fwrite(&expo,sizeof(expo),1,temoin);

            if(Identifiant==expo.Id_exposition)
            {

                        switch(Ce_Champs)
                            {
                                case 1: strcpy(expo.theme,exposition.theme);
                                    break;
                                case 2:
                                    {expo.date1=Date_Debut;
                                    expo.date2=Date_Fin;
                                    }
                                    break;
                                case 3: strcpy(expo.exposant,exposition.exposant);
                                    break;
                            }
                        fwrite(&expo,sizeof(expo),1,temoin);
                        printf("\n__________________________________________________________________________________________________________________________________________________________________________");
                        printf("\n     Identifiant |                                              Theme |                                           Exposant |           Date Debut |    Date d'evaluation |");
                        printf("\n==========================================================================================================================================================================");
                        printf("\n %015d | %50s | %50s |    %02i / %02i / %04i    |    %02i / %02i / %04i    |",expo.Id_exposition,expo.theme,expo.exposant,expo.date1.jour,expo.date1.mois,expo.date1.annee,expo.date2.jour,expo.date2.mois,expo.date2.annee);
                        printf("\n__________________________________________________________________________________________________________________________________________________________________________");
                        printf("\n\nModification reussie \n\n");
                       Garder_Une_Trace(7,Identifiant);
                        while(fread(&expo,sizeof(expo),1,exposit)==1)
                                fwrite(&expo,sizeof(expo),1,temoin);
            }
           fclose(exposit) ;
    fclose(temoin);
    remove("exposit.dat");
    rename("temoin.dat","exposit.dat");
       menu_modifier_evenement(Identifiant);
        }
        break;
            default : menu_modifier_evenement(Identifiant);

    }

}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet de verifier si la date est disponible pour un evenement*/
    /* PARAMETRES : Date*/
    /* VALEUR DE RETOUR: int  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
int Verifier_Date(Date Date_Debut)
{
    FILE* exposit=NULL;
    Evenement exposition;
    exposit=fopen("exposit.dat","rb");
    if (exposit!=NULL)
    {
        while(fread(&exposition,sizeof(exposition),1,exposit)==1)
        {
            if(diff_date(exposition.date1,Date_Debut)<=0  && diff_date(exposition.date2,Date_Debut)>=0)
            {
                printf("\nCette date n'est pas disponible\n Essayer a nouveau\n\n");
                printf("\nLes evenements ne peuvent pas se chevaucher\nIl y a deja un evenement de %i/%i/%i a %i/%i/%i.  Essayer a nouveau\n\n",exposition.date1,exposition.date2);
                fclose(exposit);
                return (0);
            }
        }
    }
    else printf("Erreur d'ouverture du fichier exposit.dat \n");
    fclose(exposit);
    return (1);
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet de verifier si des evenements se chevauchent*/
    /* PARAMETRES : Date, Date*/
    /* VALEUR DE RETOUR: int  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
int Evenement_Inclu(Date Date_Debut,Date Date_Fin)
{
    FILE* exposit=NULL;
    Evenement exposition;
    exposit=fopen("exposit.dat","rb");
    if (exposit!=NULL)
    {
        while(fread(&exposition,sizeof(exposition),1,exposit)==1)
        {
                if(diff_date(Date_Debut,exposition.date1)<=0  && diff_date(exposition.date1,Date_Fin)<=0)
            {
                printf("\nLes evenements ne peuvent pas se chevaucher\nIl y a deja un evenement de %i/%i/%i a %i/%i/%i.  Essayer a nouveau\n\n",exposition.date1,exposition.date2);
                fclose(exposit);
                return (1);
            }
        }
    }
    else printf("Erreur d'ouverture du fichier exposit.dat \n");
    fclose(exposit);
    return (0);
}
/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction permet de rentrer les informations concernant une oeuvre externe */
/* PARAMETRES : Aucune  */
/* VALEUR DE RETOUR: Aucune*/
/* AUTEUR :   */
/* DATE CREATION: 6 Avril 2018  */
/* DATE MISE A JOUR : 22 Avril 2018  */
/* REMARQUES : Aucune */
/*---------------------------------------------------------------------------------------*/
int Enregistrer_Oeuvre_Externe()
{
    Oeuvre NouvelleOeuvre;
    int confirmation;
    printf("\n____________ENREGISTRER OEUVRE EXTERIEURE____________\n<Entrer 0 pour annuler>\n\nEntrer le titre de l'oeuvre :\n");
    LireChaine(NouvelleOeuvre.Titre);if(NouvelleOeuvre.Titre[0]=='0')return(0);//on quite la foction si on entre 0
    printf("\nEntrer une description de l'oeuvre :\n");
    LireChaine(NouvelleOeuvre.Desc);if(NouvelleOeuvre.Desc[0]=='0')return(0);
    printf("\nEntrer le type de l'oeuvre :\n");
    LireChaine(NouvelleOeuvre.Type);if(NouvelleOeuvre.Type[0]=='0')return(0);
    printf("\n Entrez la date de creation de l'oeuvre\n");
    entrer_Date(&NouvelleOeuvre.Dat_crea,0,1);
    printf("\nEntrer la localisation de l'oeuvre :\n");
    LireChaine(NouvelleOeuvre.Localisa);if(NouvelleOeuvre.Localisa[0]=='0')return(0);
    printf("\nEntrer le nom du proprietaire de l'oeuvre :\n");
    LireChaine(NouvelleOeuvre.Propriet);if(NouvelleOeuvre.Propriet[0]=='0')return(0);
    printf("\nEntrer la valeur de l'oeuvre en USD :\n");
    NouvelleOeuvre.Valeur=Lire_Flottant();
    strcpy(NouvelleOeuvre.Dat_eval,__DATE__);
     NouvelleOeuvre.Id_oeuvr =creer_Id_Oeuvre();
     List_Artist();
     do
     {
         printf("\nEntrer l'identifiant de l'artiste qui a cree l'oeuvre :\n");
    NouvelleOeuvre.Artist_Id =Lire_Entier();
     }while(!verifier_Id_Artist(NouvelleOeuvre.Artist_Id));

    __Label1:  printf("Confirmez l'enregistrement de l'oeuvre :\n 1- Oui\n 2- Annuler\n");
    confirmation=Lire_Entier();
    switch(confirmation)
    {
        case 1:
            {
                system("cls");
                printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
                printf("\n     Identifiant |                                              Titre |                                        Description |                                               Type |      Id_Artiste |     Date de Creation |                                        Localisation|                                        Proprietaire|               Valeur |    Date d'evaluation |");
                printf("\n==================================================================================================================================================================================================================================================================================================================================================================================");
                printf("\n %015d | %50s | %50s | %50s | %015d |    %02i / %02i / %04i    | %50s | %50s | %20f | %20s |",NouvelleOeuvre.Id_oeuvr,NouvelleOeuvre.Titre,
                NouvelleOeuvre.Desc,NouvelleOeuvre.Type,NouvelleOeuvre.Artist_Id,NouvelleOeuvre.Dat_crea.jour,NouvelleOeuvre.Dat_crea.mois,NouvelleOeuvre.Dat_crea.annee,NouvelleOeuvre.Localisa,NouvelleOeuvre.Propriet,
                NouvelleOeuvre.Valeur,NouvelleOeuvre.Dat_eval);
                printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
                printf("\nEnregistrement reussi\n");
            }
            break;
        case 2:
            {
                system("cls");
                printf("Enregistrement annule\n");
            }
            break;
        default :
            {
                printf("Faites l'un de ces choix\n");
                goto __Label1;
            }
    }
    if(confirmation==1)
    {
        save_Id_oeuvre(NouvelleOeuvre.Id_oeuvr);
        EnregistrerOeuvre_Ext(&NouvelleOeuvre);//on enregistre toute la structure dans un fichier
        Garder_Une_Trace( 1,NouvelleOeuvre.Id_oeuvr);
    }
    FIN
    return NouvelleOeuvre.Id_oeuvr;
}
/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction permet d'enregistrer des oeuvres ayant ete exposees lors d'un evenement mais qui n'appartiennent pas au Musee */
/* PARAMETRES : Aucune  */
/* VALEUR DE RETOUR: Aucune*/
/* AUTEUR :   */
/* DATE CREATION: 6 Avril 2018  */
/* DATE MISE A JOUR : 22 Avril 2018  */
/* REMARQUES : Aucune */
/*---------------------------------------------------------------------------------------*/
void EnregistrerOeuvre_Ext(Oeuvre *NouvelleOeuvre)
{
    FILE *oeuvr= NULL;//on declare un pointeur de type FILE pour creer notre fichier et on l'initialise
    oeuvr = fopen("oeuvr_Ext.dat","ab");// on ouvre notre fichier en mode "ab", i.e ajout sous forme binaire
    if(oeuvr != NULL)// teste d'erreur d'ouverture du fichier
        fwrite(NouvelleOeuvre,sizeof(*NouvelleOeuvre),1,oeuvr);//on ecrit notre structure dans le fichier
    else printf("\nERREUR lors de l'ouverture du fichier oeuvr_Ext.dat\n");
    fclose(oeuvr);//on referme notre fichier
}
/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION :Cette fonction permet de verifier l'ID d'un evenement*/
/* PARAMETRES : int  */
/* VALEUR DE RETOUR: int*/
/* AUTEUR :   */
/* DATE CREATION: 6 Avril 2018  */
/* DATE MISE A JOUR : 22 Avril 2018  */
/* REMARQUES : Aucune */
/*---------------------------------------------------------------------------------------*/
int verifier_Id_Evenement(int Id)
{
    Evenement compare;
    FILE *expo= NULL;
    expo = fopen("exposit.dat","rb");
    if(expo != NULL)
    {
        rewind(expo);
         while( fread(&compare,sizeof(compare),1,expo)==1) //tant que mpa nan fin fichier a
            {
                if(compare.Id_exposition==Id)
                 {
                    fclose(expo);
                    return 1;
                }
            }
    }
    else printf("Erreur d'ouverture du fichier exposit.dat ");
    printf("ERREUR !!! Cet identifiant n'existe pas\nVeuillez essayer a nouveau\n");
    fclose(expo);
    return 0;
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction aide a rechercher un evenement*/
    /* PARAMETRES : Aucun*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void Recherche_Evenement()
{
    Evenement Event_recherchee;
    char theme[TailleTableau];
    int temoin=0;
    int  choix , ID;
    printf("\n_______________RECHERCHER EVENEMENT_______________\n 1- Recherche par ID de l'evenement\n 2- Recherche par theme de l'evenement\n 3- Recherche par Exposant\n 0- Retour\nEntrez votre choix :\n");
    choix=Lire_Entier();
    switch (choix )
    {
        case 1 :
            {
                printf("Entrez l'ID de l'evenement recherchee\n");
                ID=Lire_Entier();
            }
            break;
        case 2:
            {
                printf("Entrez le theme de l'evenement recherchee\n");
                LireChaine(theme);
            }
            break;
        case 3 :
            {
                printf("Entrez le nom de l'exposant\n");
                LireChaine(theme); // Pour economiser notre memoire, gardons la meme variable "theme"
            }
            break;
        case 0:
            {
                system("cls");
                MenuEvenement();
            }
            break;
        default :
            {
                system("cls");
                printf("Faites l'un de ces choix\n");
                Recherche_Evenement();
            }
    }
    FILE *expo= NULL;//on declare un pointeur de type FILE pour creer notre fichier et on l'initialise
    expo = fopen("exposit.dat","rb");// on ouvre notre fichier en mode "ab", i.e ajout sous forme binaire
    if(expo != NULL)// teste d'erreur d'ouverture du fichier
    {
        printf("\n__________________________________________________________________________________________________________________________________________________________________________");
        printf("\n     Identifiant |                                              Theme |                                           Exposant |           Date Debut |             Date fin |");
        printf("\n==========================================================================================================================================================================");
        while(fread(&Event_recherchee,sizeof(Event_recherchee),1,expo)==1)
        {
            //on lit notre structure  a partir du fichier
            if ( (choix==1 && (Event_recherchee.Id_exposition==ID )) ||(choix==2 && strcmp(Event_recherchee.theme, theme) == 0 )  || (choix==3 && strcmp(Event_recherchee.exposant, theme) == 0 ) )
            {
                temoin=1;
                printf("\n %015d | %50s | %50s |    %02i / %02i / %04i    |    %02i / %02i / %04i    |",Event_recherchee.Id_exposition,Event_recherchee.theme,Event_recherchee.exposant,Event_recherchee.date1.jour,Event_recherchee.date1.mois,Event_recherchee.date1.annee,Event_recherchee.date2.jour,Event_recherchee.date2.mois,Event_recherchee.date2.annee);
                printf("\n__________________________________________________________________________________________________________________________________________________________________________");
            }
        }
        if(temoin==0&&choix==3) printf("\nCet exposant n'existe pas\n");
        else if(temoin==0) printf("\nCette exposition n'existe pas\n");
    }
    else printf("\nErreur d'ouverture du fichier exposit.dat\n");
    fclose(expo);
    FIN
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction enregistre dans un fichier  l'ID d'un artiste ainsi que son oeuvre*/
    /* PARAMETRES : Struct_Oeuvr_artiste * */
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Cette fonction fait un lien entre oeuvre et evenement*/
    /*---------------------------------------------------------------------------------------*/
void Lien_Oeuvre_Expo( Struct_Oeuvr_Expo *Mon_Lien)
{
    FILE *Oeuv_exp= NULL;
    Oeuv_exp = fopen("Oeuv_exp.dat","ab");
    if(Oeuv_exp != NULL)
        fwrite(Mon_Lien,sizeof(*Mon_Lien),1,Oeuv_exp);
    else printf("Erreur d'ouverture du fichier oeuvre_expo.dat\n");
    fclose(Oeuv_exp);
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction aide a verifier si une oeuvre exite deja dans une exposition*/
    /* PARAMETRES : Aint , int*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
int virifier_si_cet_Oeuvre_est_dans_cet_Expo( int id_oeuvre,int id_expo)
{
    int temoin=0;
    Struct_Oeuvr_Expo  Mon_Lien;
    FILE *Oeuv_exp= NULL;
    Oeuv_exp = fopen("Oeuv_exp.dat","rb");
    if(Oeuv_exp != NULL)
    {
        while( fread(&Mon_Lien,sizeof(Mon_Lien),1,Oeuv_exp)==1)
        {
            if(id_expo==Mon_Lien.id_exposition && id_oeuvre==Mon_Lien.id_oeuvr)
            {
                temoin=1;
                printf("Cette oeuvre existe deja dans l'expo %i\n",id_expo);
                fclose(Oeuv_exp);
                return 1;
            }
        }
    }
    else
        printf("Erreur d'ouverture du fichier oeuvre_expo.dat\n");
    fclose(Oeuv_exp);
    if(temoin==0)
        printf("Cette oeuvre n'etait pas enregistree dans l'expo  %i\n",id_expo);
    return 0;
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet de creer l'ID de l'evenement sans demander a l'utilisateur de rentrer quoi que ce soit*/
    /* PARAMETRES : Aucun */
    /* VALEUR DE RETOUR: int */
    /* AUTEUR :  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : On sctokera cet ID dans un fichier. On recupere d'abord le dernier ID enregistre puis on l'incremente*/
    /*---------------------------------------------------------------------------------------*/
int creer_Id_expo()
{
    FILE *Fichier_Id_expo= NULL;
    int Id;
    Fichier_Id_expo = fopen("Fichier_Id_expo.dat","r");
    if(Fichier_Id_expo!= NULL)
    {
        fscanf(Fichier_Id_expo,"%d",&Id);
        Id++;
    }
    else printf("\nErreur d'ouverture du fichier Fichier_Id_expo.dat\n");
    fclose(Fichier_Id_expo);
    return Id;
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction intervient dans la sauvegarde de l'ID de l'evenement*/
    /* PARAMETRES : int*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void save_Id_expo(int Id)
{
    FILE *Fichier_Id_expo= NULL;
    Fichier_Id_expo = fopen("Fichier_Id_expo.dat","w");
    if(Fichier_Id_expo != NULL)
        fprintf(Fichier_Id_expo,"%d",Id);
        else printf("Erreur d'ouverture du fichier Fichier_Id_expo.dat\n ");
    fclose(Fichier_Id_expo);
}

