#include"Bmevey.h"
/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction presente le menu du module oeuvre a l'utilisateur */
/* PARAMETRES : Aucune  */
/* VALEUR DE RETOUR:  Aucun */
/* AUTEUR : DUBUCHE Kevin J  */
/* DATE CREATION: 6 Avril 2018  */
/* DATE MISE A JOUR : 2 Juillet 2018  */
/* REMARQUES : Aucune */
/*---------------------------------------------------------------------------------------*/
void MenuOeuvre()
{
    system("cls");//Nettoyer l'ecran
    int choix;
    printf("\n_______________OEUVRES_______________\n\n 1- Ajouter une oeuvre\n 2- Modifier une oeuvre\n 3- Rechercher une oeuvre\n 4- Supprimer une oeuvre\n 0- Retour\n\nEntrer votre choix :\n");
    choix=Lire_Entier();
    switch (choix)
    {
    case 1:
    {
        ajout_Oeuvr();
        system("cls");
        MenuOeuvre();
    }
    break;
    case 2:
    {
        int Identifiant;
        printf("____________MODIFIER OEUVRE____________\n\n Connaissez-vous l'ID de l'oeuvre que vous voulez modifier?\n");
        int choix1;
        printf("  1- Oui\n  2- Non. Rechercher  d'abord l'oeuvre\n  0- Retour\n");
        choix1=Lire_Entier();
        switch(choix1)
        {
        case 1:
        {
            do
            {
                printf("\nEntrer l'identifiant de l'oeuvre que vous voulez modifier :\n<0- Retour>\n\n");
                Identifiant=Lire_Entier();
                if (Identifiant==0)
                    MenuOeuvre();//on retourne au mennu
            }
            while(! verifier_Id_Oeuvr(Identifiant) );//on demande l'ID jusqu'a ce qu'on entre un ID qui existe
        }
        break;
        case 2 :
        {
            Recherche_Oeuvre();
            MenuOeuvre();
        }
        break;
        case 0 :
        {
            system("cls");
            MenuOeuvre();
        }
        break;
        default :
            MenuOeuvre();// on revient au menu
        }
        menu_modifier_oeuvre(Identifiant);//on fait notre modification
        MenuOeuvre();
    }
    break;
    case 3:
    {
        system("cls");
        Recherche_Oeuvre();
        MenuOeuvre();
    }
    break;
    case 4:
    {
        supprim_Oeuvr();
        MenuOeuvre();
    }
    break;
    case 0:
        MenuPrincipal();
        break;
    default :
    {
        printf("ERREUR !!! : Faites un de ces choix\n");
        MenuOeuvre();
    }
    }

}
/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction permet de rentrer les informations concernant une oeuvre */
/* PARAMETRES : Aucune  */
/* VALEUR DE RETOUR: Aucune*/
/* AUTEUR : DUBUCHE Kevin J  */
/* DATE CREATION: 6 Avril 2018  */
/* DATE MISE A JOUR : 22 Avril 2018  */
/* REMARQUES : Aucune */
/*---------------------------------------------------------------------------------------*/
void ajout_Oeuvr()
{
    Oeuvre NouvelleOeuvre={0};
    int confirmation;

    printf("\n____________AJOUTER UNE OEUVRE____________\n<Entrer 0 pour anuler>\n\nEntrer le titre de l'oeuvre :\n");
    LireChaine(NouvelleOeuvre.Titre);if(NouvelleOeuvre.Titre[0]=='0')MenuOeuvre();
    printf("\nEntrer une description de l'oeuvre :\n");
    LireChaine(NouvelleOeuvre.Desc);if(NouvelleOeuvre.Desc[0]=='0')MenuOeuvre();
    printf("\nEntrer le type de l'oeuvre :\n");
    LireChaine(NouvelleOeuvre.Type);if(NouvelleOeuvre.Type[0]=='0')MenuOeuvre();
    printf("\n Entrez la date de creation de l'oeuvre\n");
    entrer_Date(&NouvelleOeuvre.Dat_crea,0,1);
    printf("\nEntrer la localisation de l'oeuvre :\n");
    LireChaine(NouvelleOeuvre.Localisa);if(NouvelleOeuvre.Localisa[0]=='0')MenuOeuvre();
    printf("\nEntrer le nom du proprietaire de l'oeuvre :\n");
    LireChaine(NouvelleOeuvre.Propriet);if(NouvelleOeuvre.Propriet[0]=='0')MenuOeuvre();
    printf("\nEntrer la valeur de l'oeuvre en USD :\n");
    NouvelleOeuvre.Valeur=Lire_Flottant();if(NouvelleOeuvre.Valeur==0)MenuOeuvre();
    strcpy(NouvelleOeuvre.Dat_eval,__DATE__);
    NouvelleOeuvre.Id_oeuvr =creer_Id_Oeuvre();

    printf("\n_____Voici la liste des artistes du musee_____\n");
    List_Artist();
    __Label3:
    printf(" 1- Choisir un de ces artistes\n 2- Creer un nouvel artiste\n 0- Retour\n Enrez votre choix\n\n");
    int choix;
    choix=Lire_Entier();
    switch(choix)
    {
        case 1:
            {
                do
                {
                printf("\nEntrer l'identifiant de l'artiste qui a cree l'oeuvre :\n<0- Retour>\n\n");
                NouvelleOeuvre.Artist_Id =Lire_Entier();
                if(NouvelleOeuvre.Artist_Id==0)
                MenuPrincipal();
                }while(!verifier_Id_Artist(NouvelleOeuvre.Artist_Id));
            }
        break;
       case 2:
          {
              NouvelleOeuvre.Artist_Id= ajout_artist(NouvelleOeuvre.Dat_crea);
              if(NouvelleOeuvre.Artist_Id==0){printf("Enregistrement annule\n"); FIN MenuOeuvre();}
          }
            break;
       case 0:
           {
            system("cls");
            MenuOeuvre();
            }
            break;
        default :
            {
            printf("Faites l'un de ces choix :\n");
            goto __Label3;
            }
    }

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
                printf("\n %015d | %50s | %50s | %50s | %015d |    %02i / %02i / %04i    | %50s | %50s | %20.3f | %20s |",NouvelleOeuvre.Id_oeuvr,NouvelleOeuvre.Titre,
                    NouvelleOeuvre.Desc,NouvelleOeuvre.Type,NouvelleOeuvre.Artist_Id,NouvelleOeuvre.Dat_crea.jour,NouvelleOeuvre.Dat_crea.mois,
                    NouvelleOeuvre.Dat_crea.annee,NouvelleOeuvre.Localisa,NouvelleOeuvre.Propriet,
             NouvelleOeuvre.Valeur,NouvelleOeuvre.Dat_eval);
            printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
            printf("\nEnregistrement de l'oeuvre reussi\n");
            }
            break;
        case 2:
            {
                system("cls");
                printf("Enregistrement de l'oeuvre annule\n");
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
            EnregistrerOeuvre(&NouvelleOeuvre);//on enregistre toute la structure dans un fichier
        }
    FIN
}
/*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet d'enregistrer une oeuvre dans un fichier externe */
    /* PARAMETRES : Aucune  */
    /* VALEUR DE RETOUR: Aucune*/
    /* AUTEUR :   */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
void EnregistrerOeuvre(Oeuvre *NouvelleOeuvre)
{
    FILE *oeuvr= NULL;//on declare un pointeur de type FILE pour creer notre fichier et on l'initialise
    oeuvr = fopen("oeuvr.dat","ab");// on ouvre notre fichier en mode "ab", i.e ajout sous forme binaire
    if(oeuvr != NULL)// teste d'erreur d'ouverture du fichier
    {
            fwrite(NouvelleOeuvre,sizeof(*NouvelleOeuvre),1,oeuvr);//on ecrit notre structure dans le fichier
            Garder_Une_Trace( 1,NouvelleOeuvre->Id_oeuvr);//on enregistre cette action dans un fichier
    }
    else printf("\nERREUR lors de l'ouverture du fichier oeuvr.dat\n");//message d'erreur
    fclose(oeuvr);//on referme notre fichier
}
/*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet de verifier que l'identifiant en question existe dans la base de donnee */
    /* PARAMETRES : int identifiant  */
    /* VALEUR DE RETOUR: int */
    /* AUTEUR : DUBUCHE Kevin J  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune */
    /*---------------------------------------------------------------------------------------*/
int verifier_Id_Oeuvr(int Id)
{
    Oeuvre compare;
    FILE *oeuvr= NULL;
    oeuvr = fopen("oeuvr.dat","rb");
    if(oeuvr != NULL)//teste d'erreur
        {
            rewind(oeuvr);
            while(fread(&compare,sizeof(compare),1,oeuvr)==1) //tant que mpa nan fin fichier a
            {
                if(compare.Id_oeuvr==Id)
                {//on entre ici si on a trouve l'oeuvre
                    fclose(oeuvr);
                    return 1;
                }
            }
        }
        else printf("Erreur d'ouverture du fichier oeuv.dat\n");//message d'erreur
    printf("ERREUR !!! Cet identifiant n'existe pas\nVeuillez essayer a nouveau\n"); //on a parcouru le fichier sans trouver l'ID
    fclose(oeuvr);
    return 0;
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet de creer l'ID de l'oeuvre sans demander a l'utilisateur de rentrer quoi que ce soit*/
    /* PARAMETRES : Aucun */
    /* VALEUR DE RETOUR: int */
    /* AUTEUR :   */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : On sctokera cet ID dans un fichier. On recupere d'abord le dernier ID enregistre puis on l'incremente*/
    /*---------------------------------------------------------------------------------------*/
int creer_Id_Oeuvre()
{
    FILE *Fichier_Id_Oeuvre=NULL;
    int Id;
    Fichier_Id_Oeuvre = fopen("Fichier_Id_Oeuvre.dat","r");
    if(Fichier_Id_Oeuvre != NULL)
    {
        fscanf(Fichier_Id_Oeuvre,"%d",&Id);//on recupere le dernier identifiant enregistre
        Id++;//on incremente l'ID
    }
    else printf("\nErreur d'ouverture du fichier Fichier_Id_Oeuvre\n");//message d'erreur
    fclose(Fichier_Id_Oeuvre);
    return Id;
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction intervient dans la sauvegarde de l'ID de l'oeuvre*/
    /* PARAMETRES : int*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void save_Id_oeuvre(int Id)
{
    FILE *Fichier_Id_Oeuvre= NULL;
    Fichier_Id_Oeuvre = fopen("Fichier_Id_Oeuvre.dat","w");//ouverture en mode 'w' pour supprimer le contenu du fichier des l'ouverture
    if(Fichier_Id_Oeuvre != NULL)
          fprintf(Fichier_Id_Oeuvre,"%d",Id);
    else printf("Erreur d'ouverture du fichier Fichier_Id_Oeuvre.dat");
    fclose(Fichier_Id_Oeuvre);
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction aide a rechercher une oeuvre*/
    /* PARAMETRES : Aucun*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void Recherche_Oeuvre()
{
    Oeuvre Oeuvre_recherchee;
    char titre[TailleTableau];
    int temoin=0;
    int  choix , ID;
    printf("\n_______________RECHERCHER OEUVRES_______________\n\n 1- Recherche par ID de l'oeuvre\n 2- Recherche par titre de l'oeuvre\n 0- Retour Menu Oeuvre\nEntrez votre choix :\n");
    choix=Lire_Entier();
    switch (choix )
    {
        case 1 :
            {
                printf("Entrez l'ID de l'oeuvre recherchee\n");
                ID=Lire_Entier();
            }
            break;
        case 2:
            {
                printf("Entrez le titre de l'oeuvre recherchee\n");
                LireChaine(titre);
            }
            break;
        case 0:
            {
                MenuOeuvre();
            }
            break;
        default :
            {
                system("cls");
                printf("Faites l'un de ces choix\n");
                Recherche_Oeuvre();
            }
    }
    FILE *oeuvr= NULL;//on declare un pointeur de type FILE pour creer notre fichier et on l'initialise
    oeuvr = fopen("oeuvr.dat","rb");// on ouvre notre fichier en mode "rb", i.e lecture sous forme binaire
    if(oeuvr != NULL)// teste d'erreur d'ouverture du fichier
        {
            printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
            printf("\n     Identifiant |                                              Titre |                                        Description |                                               Type |      Id_Artiste |     Date de Creation |                                        Localisation|                                        Proprietaire|               Valeur |    Date d'evaluation |");
            printf("\n==================================================================================================================================================================================================================================================================================================================================================================================");        rewind(oeuvr);
            while(fread(&Oeuvre_recherchee,sizeof(Oeuvre_recherchee),1,oeuvr)==1)//on recupere les structures stocker dans le fichier
            {
                if(  (choix==1 && (Oeuvre_recherchee.Id_oeuvr==ID )) ||(choix==2 && strcmp(Oeuvre_recherchee.Titre, titre) == 0 ) )//on compare les id
                {
                    temoin=1;
                    printf("\n %015d | %50s | %50s | %50s | %015d |   %02i / %02i / %04i     | %50s | %50s | %20.3f | %20s |",Oeuvre_recherchee.Id_oeuvr,Oeuvre_recherchee.Titre,
                    Oeuvre_recherchee.Desc,Oeuvre_recherchee.Type,Oeuvre_recherchee.Artist_Id,Oeuvre_recherchee.Dat_crea.jour,Oeuvre_recherchee.Dat_crea.mois,Oeuvre_recherchee.Dat_crea.annee,Oeuvre_recherchee.Localisa,Oeuvre_recherchee.Propriet,
                    Oeuvre_recherchee.Valeur,Oeuvre_recherchee.Dat_eval);
                    printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
                }
            }
            if(temoin==0) printf("\nCet oeuvre n'existe pas\n");
        }
    else printf("\nErreur d'ouverture du fichier oeuvr.dat\n");//message d'erreur
    fclose(oeuvr);
   FIN
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet de supprimer une oeuvre*/
    /* PARAMETRES : Aucun*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Comme pour la fonction modifier, on enregistre toutes nos structures dans un autre fichier sauf celui qu'on veut supprimer*/
    /*---------------------------------------------------------------------------------------*/
void supprim_Oeuvr()
{
    system("cls");
    int choix,confirmation=0;
    Oeuvre Modification={0}, oeuvrTampon={0};//l'utilisateur va enter ses modification dans la structure Modification et oeuvreTampon c'est pour l'echange entre les deux fichiers
    printf("\n_______________SUPPRIMER OEUVRE_______________\n\n");
    printf(" 1- Vous connaissez l'ID de l'oeuvre a supprimer\n 2- Rechercher  d'abord l'oeuvre\n 0- Retour\n");
    choix=Lire_Entier();
    switch(choix)
    {
        case 1:
            {
                do
                    {
                        printf("\nEntrer l'identifiant de l'oeuvre que vous voulez supprimer :\n<0- Retour>\n");
                        Modification.Id_oeuvr=Lire_Entier();
                         if (Modification.Id_oeuvr==0) supprim_Oeuvr();
                    }
                while(! verifier_Id_Oeuvr(Modification.Id_oeuvr) );//on demande l'identifiant et on verifie s'il existe dans notre fichier
            }
            break;
        case 2 :
            {
                Recherche_Oeuvre();
                supprim_Oeuvr();
            }
            break;
        case 0 :
                MenuOeuvre();
            break;
        default : supprim_Oeuvr();
    }
    printf("Confirmer la supression :\n 1- Oui\n 0- Non\n");
    confirmation=Lire_Entier();
    if (confirmation==1)
    {
          FILE *oeuvr= NULL, *oeuvr_Intermed= NULL;
    oeuvr = fopen("oeuvr.dat","rb");//on ouvre le fichier en mode lecture binaire
    oeuvr_Intermed = fopen("oeuvr_Intermed.dat","ab");//on ouvre le fichier en mode ajout binaire
    if(oeuvr != NULL && oeuvr_Intermed != NULL)
    {
        rewind(oeuvr);//on met le curseur au debut du fichier oeuvr
        while( fread(&oeuvrTampon,sizeof(oeuvrTampon),1,oeuvr)==1 )
            {
                if(oeuvrTampon.Id_oeuvr==Modification.Id_oeuvr)//
                {
                    printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
                    printf("\n     Identifiant |                                              Titre |                                        Description |                                               Type |      Id_Artiste |     Date de Creation |                                        Localisation|                                        Proprietaire|               Valeur |    Date d'evaluation |");
                    printf("\n==================================================================================================================================================================================================================================================================================================================================================================================");
                    printf("\n %015d | %50s | %50s | %50s | %015d |   %02i / %02i / %04i   | %50s | %50s | %20.3f | %20s |",oeuvrTampon.Id_oeuvr,oeuvrTampon.Titre,
                       oeuvrTampon.Desc,oeuvrTampon.Type,oeuvrTampon.Artist_Id,oeuvrTampon.Dat_crea.jour,oeuvrTampon.Dat_crea.mois,oeuvrTampon.Dat_crea.annee,oeuvrTampon.Localisa,oeuvrTampon.Propriet,
                       oeuvrTampon.Valeur,oeuvrTampon.Dat_eval);
                    printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
          printf("\nOeuvre supprimee avec SUCCES\n");
             Garder_Une_Trace(3,oeuvrTampon.Id_oeuvr);
              }
            else if(oeuvrTampon.Id_oeuvr!=Modification.Id_oeuvr)
            fwrite(&oeuvrTampon,sizeof(oeuvrTampon),1,oeuvr_Intermed);//on les copie dans le fichier intermediare
            }
        fclose(oeuvr);
        fclose(oeuvr_Intermed);
        remove("oeuvr.dat");//on supprime l'ancien fichier
        rename("oeuvr_Intermed.dat", "oeuvr.dat");//on enregistre le nouveau qui contient les modification
    }
    else printf("\nErreur lors de l'ouverture du fichier oeuvr.dat et oeuvr_Intermer.dat\n");
 FIN
   }
   else
    supprim_Oeuvr();



}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction affiche les differentes modifications possibles sur une oeuvre du Musee*/
    /* PARAMETRES : int identifiant*/
    /* VALEUR DE RETOUR: Aucune */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void menu_modifier_oeuvre(int Identifiant)
{
    int choix;
    printf("____________MODIFIER OEUVRE   %d____________\n\n 1- Modifier titre\n 2- Modifier description\n 3- Modifier type\n 4- Modifier localisation\n 5- Modifier proprietaire\n 6- Modifier valeur\n 7- Modifier Date Creation\n 0- Retour\n\n Entrer votre choix:\n",Identifiant);
    choix=Lire_Entier();
    switch(choix)
    {
        case 1: modifier_champs_Oeuvre(Identifiant,1);
            break;
        case 2: modifier_champs_Oeuvre(Identifiant,2);
            break;
        case 3: modifier_champs_Oeuvre(Identifiant,3);
            break;
        case 4: modifier_champs_Oeuvre(Identifiant,4);
            break;
        case 5: modifier_champs_Oeuvre(Identifiant,5);
            break;
        case 6: modifier_champs_Oeuvre(Identifiant,6);
            break;
        case 7: modifier_champs_Oeuvre(Identifiant,7);
            break;
        case 8: modifier_champs_Oeuvre(Identifiant,8);
            break;
        case 0:
            {
                system("cls");
                MenuOeuvre();
            }
            break;
        default:
            {
                system("cls");
                printf("Faites l'un de ces choix :\n\n");
                menu_modifier_oeuvre(Identifiant);
            }
    }
}
 /*---------------------------------------------------------------------------------------*/
    /* DESCRIPTION : Cette fonction permet de faire les modifications appliquables sur une oeuvre*/
    /* PARAMETRES : int identifiant, int le champ a modifier*/
    /* VALEUR DE RETOUR: Aucune */
     /* AUTEUR : Dubuche kevin  */
    /* DATE CREATION: 6 Avril 2018  */
    /* DATE MISE A JOUR :22 Avril 2018  */
    /* REMARQUES : Aucune*/
    /*---------------------------------------------------------------------------------------*/
void modifier_champs_Oeuvre( int Identifiant, int Ce_Champs)
{
    Oeuvre Mon_Oeuvre={0};
    Oeuvre tampOeuvr={0};
    switch(Ce_Champs)
    {
        case 1:
             {
                printf("\nEntrez le nouveau titre:\n");
                LireChaine(Mon_Oeuvre.Titre);
            }
            break;
        case 2:
            {
                printf("\nEntrez la nouvelle description:\n");
                LireChaine(Mon_Oeuvre.Desc);
            }
            break;
        case 3:
            {
                printf("\nEntrez le nouveau type:\n");
                LireChaine(Mon_Oeuvre.Type);
            }
            break;
        case 4:
            {
                printf("\nEntrez la nouvelle localisation:\n");
                LireChaine(Mon_Oeuvre.Localisa);
            }
            break;
        case 5:
            {
                printf("\nEntrez le nouveau proprietaire:\n");
                LireChaine(Mon_Oeuvre.Propriet);
            }
            break;
        case 6:
            {
                printf("\nEntrez la nouvelle valeur:\n");
                Mon_Oeuvre.Valeur=Lire_Entier();
            }
            break;
        case 7:
            {
                printf("\nEntrez la nouvelle Date de creation:\n");
                entrer_Date(&Mon_Oeuvre.Dat_crea,0,1);
            }
            break;
        default:
            {
                 printf("Faites l'un de ces choix\n");
                modifier_champs_Oeuvre(Identifiant, Ce_Champs);
            }
    }
    FILE *oeuvr=NULL;
    oeuvr=fopen("oeuvr.dat","rb");
    FILE* temoin=NULL;
    temoin=fopen("temoin.dat","ab");
    if(oeuvr!=NULL && temoin !=NULL)
    {
         while(fread(&tampOeuvr,sizeof(tampOeuvr),1,oeuvr) ==1 && Identifiant!=tampOeuvr.Id_oeuvr)
            fwrite(&tampOeuvr,sizeof(tampOeuvr),1,temoin);
            if(Identifiant==tampOeuvr.Id_oeuvr)
            {

    switch(Ce_Champs)
            {
                case 1: strcpy(tampOeuvr.Titre,Mon_Oeuvre.Titre);
                        break;
                case 2: strcpy(tampOeuvr.Desc,Mon_Oeuvre.Desc);
                        break;
                case 3: strcpy(tampOeuvr.Type,Mon_Oeuvre.Type);
                        break;
                case 4: strcpy(tampOeuvr.Localisa,Mon_Oeuvre.Localisa);
                        break;
                case 5: strcpy(tampOeuvr.Propriet,Mon_Oeuvre.Propriet);
                        break;
                case 6: tampOeuvr.Valeur=Mon_Oeuvre.Valeur;
                        break;
                case 7: tampOeuvr.Dat_crea=Mon_Oeuvre.Dat_crea;
                        break;
            }
    strcpy(tampOeuvr.Dat_eval,__DATE__);//update la date d'evaluation
    fwrite(&tampOeuvr,sizeof(tampOeuvr),1,temoin);
    Garder_Une_Trace(2,Identifiant);
    printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
    printf("\n     Identifiant |                                              Titre |                                        Description |                                               Type |      Id_Artiste |     Date de Creation |                                        Localisation|                                        Proprietaire|               Valeur |    Date d'evaluation |");
    printf("\n==================================================================================================================================================================================================================================================================================================================================================================================");
    printf("\n %015d | %50s | %50s | %50s | %015d |    %02i / %02i / %04i    | %50s | %50s | %20.3f | %20s |",tampOeuvr.Id_oeuvr,tampOeuvr.Titre,
            tampOeuvr.Desc,tampOeuvr.Type,tampOeuvr.Artist_Id,tampOeuvr.Dat_crea.jour,tampOeuvr.Dat_crea.mois,tampOeuvr.Dat_crea.annee,tampOeuvr.Localisa,tampOeuvr.Propriet,
             tampOeuvr.Valeur,tampOeuvr.Dat_eval);
    printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
    printf("\n\nModification reussie \n\n");
    while(fread(&tampOeuvr,sizeof(tampOeuvr),1,oeuvr)==1)
            fwrite(&tampOeuvr,sizeof(tampOeuvr),1,temoin);

            }
    fclose(oeuvr) ;
    fclose(temoin);
    remove("oeuvr.dat");
    rename("temoin.dat","oeuvr.dat");
    }else printf("Erreur d'ouverture des fichiers oeuvr.dat ou temoin.dat\n");
   FIN
    menu_modifier_oeuvre(Identifiant);
}


