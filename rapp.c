/*---------------------------------------------------------------------------------------*/
/* FICHIER : rapp.c */
/* AUTEUR : Theodore Barbara G. */
/* DATE CREATION: 11 avril 2018 */
/* DATE MISE A JOUR : 1er Juin 2018 */
/* DESCRIPTION : Le fichier cree le rapport du Musee BelMevey */
/*---------------------------------------------------------------------------------------*/
#include "Bmevey.h"
///ULTRA IMPORTANT :fe lien entre fichier yo
void MenuRapport(void)
{


    int Identifiant;
    int choix;
     system("cls");
    printf("\n _____________RAPPORT____________\n");
    printf("\n 1- Liste des Oeuvres d'un artiste\n 2- Liste des Oeuvres du Musee \n 3- Liste des Artistes \n 4- Liste des oeuvres d'une exposition \n 5- Liste des artistes ayant participe a une exposition \n 6- Liste des evenements \n 7- Prix total des oeuvres du musee \n 0- Retour au Menu Principal\n\nEntrer votre choix :\n");
    choix=Lire_Entier();
    switch (choix)
    {
        case 1:
             {
                 do
                 {
                     printf("Entrer l'ID de l'artiste :\n<0- Retour>\n");
                 Identifiant=Lire_Entier();
                      if(Identifiant==0) MenuRapport();
                 } while(!verifier_Id_Artist(Identifiant));

                List_Oeuv_Art(Identifiant);

                MenuRapport();
            }
        break;
        case 2:
            {
                List_Oeuv_Mus();
                MenuRapport();
            }
            break;
        case 3:
            {
                List_Artist();
                MenuRapport();
            }
            break;
       case 4:
           {
               printf("Entrer l'ID de l'exposition\n");
                int ID=Lire_Entier();
                List_Oeuv_Expo(ID);
                MenuRapport();
            }
            break;
        case 5:
            {
                  printf("Entrer l'ID de l'exposition\n");
                int ID=Lire_Entier();
                List_Artist_Expo(ID);
                 MenuRapport();
            }
        break;
        case 6:
            {
                List_Evenement();
                MenuRapport();
            }
            break;
            case 7:
            {
              Prix_Total_des_Oeuvres();
                MenuRapport();
            }
            break;
        case 0: MenuPrincipal();
            break;
        default:
            {
                printf("Faites l'un de ces choix :\n");
                MenuRapport();
            }
    }
}

/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction donne une liste des oeuvres d'art d'un artiste donne appartenant au Musee ou ayant ete exposee au Musee lors d'un evenement. */
/* PARAMETRES : Pas de parametres */
/* VALEUR DE RETOUR: Pas de valeur de retour */
/* AUTEUR : Theodore Barbara G. */
/* DATE CREATION: 11 avril 2018 */
/* DATE MISE A JOUR : 19 avril 2018 */
/* REMARQUES : Aucune */
/*---------------------------------------------------------------------------------------*/
void List_Oeuv_Art(int Identifiant)
{
     Artiste Artist;
    Oeuvre mon_Oeuvr;

    FILE *oeuvr;
    oeuvr= fopen("oeuvr.dat","rb");
    FILE *oeuvr_Ext;
    oeuvr_Ext= fopen("oeuvr_Ext.dat","rb");
    printf("\n ____________Liste des Oeuvres appartenant a l'artiste   %d____________",Identifiant);

    if (oeuvr != NULL && oeuvr_Ext!=NULL )
   {
       rewind(oeuvr);rewind(oeuvr_Ext);
        printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
        printf("\n      Identifiant |                                              Titre |                                        Description |                                               Type |      Id_Artiste |     Date de Creation |                                        Localisation|                                        Proprietaire|               Valeur |    Date d'evaluation |");
        printf("\n===================================================================================================================================================================================================================================================================================================================================================================================");
        while ((fread(&mon_Oeuvr,sizeof(mon_Oeuvr),1,oeuvr)==1) )
        {
            if (mon_Oeuvr.Artist_Id==Identifiant)
            {
                     printf("\n  %015d | %50s | %50s | %50s | %015d |   %02i / %02i / %04i     | %50s | %50s | %20.3f | %20s |",mon_Oeuvr.Id_oeuvr,mon_Oeuvr.Titre,mon_Oeuvr.Desc,mon_Oeuvr.Type,mon_Oeuvr.Artist_Id,mon_Oeuvr.Dat_crea,mon_Oeuvr.Localisa,mon_Oeuvr.Propriet,mon_Oeuvr.Valeur,mon_Oeuvr.Dat_eval);
            printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");

            }
         }
        fclose(oeuvr);

        while((fread(&mon_Oeuvr,sizeof(mon_Oeuvr),1,oeuvr_Ext)==1) )
        {
            if (mon_Oeuvr.Artist_Id==Identifiant)
            {
                 printf("\n PM%014d | %50s | %50s | %50s | %015d |   %02i / %02i / %04i     | %50s | %50s | %20f | %20s |",mon_Oeuvr.Id_oeuvr,mon_Oeuvr.Titre,mon_Oeuvr.Desc,mon_Oeuvr.Type,mon_Oeuvr.Artist_Id,mon_Oeuvr.Dat_crea,mon_Oeuvr.Localisa,mon_Oeuvr.Propriet,mon_Oeuvr.Valeur,mon_Oeuvr.Dat_eval);
            printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");

            }
            } fclose(oeuvr_Ext);
   }
   else
        printf("Erreur d'ouverture du fichier oeuvr.dat ou oeuvr_Ext.dat\n");

   FIN
}

/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction donne la liste des oeuvres d'art appartenant au Musee */
/* PARAMETRES : Pas de parametres */
/* VALEUR DE RETOUR: Pas de valeur de retour */
/* AUTEUR : Theodore Barbara G. */
/* DATE CREATION: 11 avril 2018 */
/* DATE MISE A JOUR : 29 avril 2018 */
/* REMARQUES : No, Id_Oeuvr, Nom/Titre, Type, Artist, valeur en USD */
/*---------------------------------------------------------------------------------------*/
void List_Oeuv_Mus(void)
{
    Oeuvre mon_Oeuvr;
    FILE *oeuvr;
    oeuvr= fopen("oeuvr.dat","rb");
   if (oeuvr != NULL)
   {
       printf("\n ____________Liste des Oeuvres du musee____________\n");
        rewind(oeuvr);
        printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
        printf("\n     Identifiant |                                              Titre |                                        Description |                                               Type |      Id_Artiste |     Date de Creation |                                        Localisation|                                        Proprietaire|               Valeur |    Date d'evaluation |");
        printf("\n==================================================================================================================================================================================================================================================================================================================================================================================");
        while(fread(&mon_Oeuvr,sizeof(mon_Oeuvr),1,oeuvr)==1)
        {
            printf("\n %015d | %50s | %50s | %50s | %015d |    %02i / %02i / %04i    | %50s | %50s | %20.3f | %20s |",mon_Oeuvr.Id_oeuvr,mon_Oeuvr.Titre,mon_Oeuvr.Desc,mon_Oeuvr.Type,mon_Oeuvr.Artist_Id,mon_Oeuvr.Dat_crea.jour,mon_Oeuvr.Dat_crea.mois,mon_Oeuvr.Dat_crea.annee,mon_Oeuvr.Localisa,mon_Oeuvr.Propriet,mon_Oeuvr.Valeur,mon_Oeuvr.Dat_eval);
            printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
        }
        printf("\n==================================================================================================================================================================================================================================================================================================================================================================================\n");   }
   else
        printf("Le fichier est vide");
   fclose(oeuvr);
   FIN
}

/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction donne la liste des artistes ayant cree les oeuvres appartenant au Musee */
/* PARAMETRES : Pas de paramètre */
/* VALEUR DE RETOUR: Pas de valeur de retour */
/* AUTEUR : Theodore Barbara G. */
/* DATE CREATION: 11 avril 2018 */
/* DATE MISE A JOUR : 19 avril 2018 */
/* REMARQUES : No, Nom, Prenom, Pseudo, Statut */
/*---------------------------------------------------------------------------------------*/
void List_Artist(void)
{

    Artiste Mon_Artiste;
    FILE *artist;
   artist= fopen("artist.dat","rb");// 22 espaces dans la date de naissance
   if (artist != NULL)
   {
        rewind(artist);
          printf("____________Liste des artistes du musee____________\n");
        printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
        printf("\n     Identifiant |             Nom |          Prenom |          Pseudo |  Date de Naissance |     Nationalite |           Statut|                                            Adresse |                                              Email |");
        printf("\n===========================================================================================================================================================================================================================================");
        while(fread(&Mon_Artiste,sizeof(Mon_Artiste),1,artist)==1)
        {
            printf("\n %015d | %15s | %15s | %15s |   %02i / %02i / %04i   | %15s | %15s | %50s | %50s |",Mon_Artiste.Id_Artist,Mon_Artiste.Nom,Mon_Artiste.Prenom,Mon_Artiste.Pseudo,Mon_Artiste.datenaissance.jour,Mon_Artiste.datenaissance.mois,Mon_Artiste.datenaissance.annee,Mon_Artiste.Nationalite,Mon_Artiste.Statut,Mon_Artiste.Adresse,Mon_Artiste.email);
            printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
        }
        printf("\n===========================================================================================================================================================================================================================================\n");
          }
   else
        printf("Erreur d'ouverture du fichier artist.dat\n");
   fclose(artist);
   FIN
}

/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction donne la liste des oeuvres d'art impliquees dans une exposition donnee */
/* PARAMETRES : int Id_exposition */
/* VALEUR DE RETOUR: Pas valeur de retour */
/* AUTEUR : Theodore Barbara G. */
/* DATE CREATION: 11 avril 2018 */
/* DATE MISE A JOUR : 19 avril 2018 */
/* REMARQUES : No, Id_Oeuvr, Nom/Titre, Type, Artist, Valeur */
/*---------------------------------------------------------------------------------------*/
void List_Oeuv_Expo(int Identifiant)
{
    Oeuvre mon_Oeuvr;
    Struct_Oeuvr_Expo parcourir;
      FILE *Fichier_Lien=NULL;
    Fichier_Lien= fopen("Oeuv_exp.dat","rb");
    FILE *oeuvr=NULL;
    oeuvr= fopen("oeuvr.dat","rb");
    FILE *oeuvr_Ext=NULL;
    oeuvr_Ext= fopen("oeuvr_Ext.dat","rb");
    printf("\n ____________Liste des Oeuvres ayant ete exposees dans l'exposition  %d____________",Identifiant);

    if(Fichier_Lien!=NULL)
    {     rewind(Fichier_Lien);
            printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
        printf("\n     Identifiant |                                              Titre |                                        Description |                                               Type |      Id_Artiste |     Date de Creation |                                        Localisation|                                        Proprietaire|               Valeur |    Date d'evaluation |");
        printf("\n==================================================================================================================================================================================================================================================================================================================================================================================");
        while(fread(&parcourir,sizeof(parcourir),1,Fichier_Lien)==1)
        {
            if(parcourir.id_exposition==Identifiant)
                {
                    rewind(oeuvr);
                    while(fread(&mon_Oeuvr,sizeof(mon_Oeuvr),1,oeuvr)==1)
                    {
                        if(mon_Oeuvr.Id_oeuvr==parcourir.id_oeuvr)
                            {
                                     printf("\n %015d | %50s | %50s | %50s | %015d |   %02i / %02i / %04i     | %50s | %50s | %20.3f | %20s |",mon_Oeuvr.Id_oeuvr,mon_Oeuvr.Titre,mon_Oeuvr.Desc,mon_Oeuvr.Type,mon_Oeuvr.Artist_Id,mon_Oeuvr.Dat_crea,mon_Oeuvr.Localisa,mon_Oeuvr.Propriet,mon_Oeuvr.Valeur,mon_Oeuvr.Dat_eval);
                                    printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");

                            }
                    }

                     rewind(oeuvr_Ext);
                    while(fread(&mon_Oeuvr,sizeof(mon_Oeuvr),1,oeuvr_Ext)==1)
                    {
                        if(mon_Oeuvr.Id_oeuvr==parcourir.id_oeuvr)
                            {
                                     printf("\n %015d | %50s | %50s | %50s | %015d |   %02i / %02i / %04i     | %50s | %50s | %20f | %20s |",mon_Oeuvr.Id_oeuvr,mon_Oeuvr.Titre,mon_Oeuvr.Desc,mon_Oeuvr.Type,mon_Oeuvr.Artist_Id,mon_Oeuvr.Dat_crea,mon_Oeuvr.Localisa,mon_Oeuvr.Propriet,mon_Oeuvr.Valeur,mon_Oeuvr.Dat_eval);
                                    printf("\n__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");

                            }
                    }

                }

        }
    }else printf("Erreur d'ouverture du fichier Oeuvre_exp.dat\n");
    fclose(oeuvr);   fclose(oeuvr_Ext);   fclose(Fichier_Lien);
     FIN
}

/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction donne la liste des artistes ayant cree les oeuvres presentees a une exposition donnee */
/* PARAMETRES : int Id_exposition */
/* VALEUR DE RETOUR: Pas de valeur de retour */
/* AUTEUR : Theodore Barbara G. */
/* DATE CREATION: 11 avril 2018 */
/* DATE MISE A JOUR : 19 avril 2018 */
/* REMARQUES : No, Nom, Prenom, Pseudo, Statut */
/*---------------------------------------------------------------------------------------*/
void List_Artist_Expo(int Id_exposition)
{
    Oeuvre mon_Oeuvr;
    Artiste mon_artiste;
    Struct_Oeuvr_Expo parcourir;
      FILE *Fichier_Lien=NULL;
    Fichier_Lien= fopen("Oeuv_exp.dat","rb");
    FILE *Ficher_artiste=NULL;
    Ficher_artiste= fopen("artist.dat","rb");
    FILE *oeuvr=NULL;
    oeuvr= fopen("oeuvr.dat","rb");
    FILE *oeuvr_Ext=NULL;
    oeuvr_Ext= fopen("oeuvr_Ext.dat","rb");
    printf("\n ____________Liste des artistes ayant ete exposees dans l'exposition  %d____________",Id_exposition);

    if(Fichier_Lien!=NULL)
    {     rewind(Fichier_Lien);
                printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
                printf("\n     Identifiant |             Nom |          Prenom |          Pseudo |  Date de Naissance |     Nationalite |           Statut|                                            Adresse |                                              Email |");
                printf("\n===========================================================================================================================================================================================================================================");
               while(fread(&parcourir,sizeof(parcourir),1,Fichier_Lien)==1)
        {

            if(parcourir.id_exposition==Id_exposition)
                {
                       if(oeuvr!=NULL)
                       {
                           rewind(oeuvr);
                    while(fread(&mon_Oeuvr,sizeof(mon_Oeuvr),1,oeuvr)==1)
                    {
                        if(mon_Oeuvr.Id_oeuvr==parcourir.id_oeuvr)
                            {
                                if(Ficher_artiste!=NULL)
                                {
                                    rewind(Ficher_artiste);
                                    while(fread(&mon_artiste,sizeof(mon_artiste),1,Ficher_artiste)==1)
                                    {
                                        if(mon_Oeuvr.Artist_Id==mon_artiste.Id_Artist)
                                        {
                                                printf("\n %015d | %15s | %15s | %15s |    %02i / %02i / %04i  | %15s | %15s | %50s | %50s |",mon_artiste.Id_Artist,mon_artiste.Nom,mon_artiste.Prenom,mon_artiste.Pseudo,mon_artiste.datenaissance.jour,mon_artiste.datenaissance.mois,mon_artiste.datenaissance.annee,mon_artiste.Nationalite,mon_artiste.Statut,mon_artiste.Adresse,mon_artiste.email);
                                                printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");

                                        }
                                    }
                                }
                            }
                    }
                       }else printf("Erreur d'ouverture du fichier oeuvr.dat\n");

                    if(oeuvr_Ext!=NULL)
                    {
                          while(fread(&mon_Oeuvr,sizeof(mon_Oeuvr),1,oeuvr_Ext)==1)
                    {
                        if(mon_Oeuvr.Id_oeuvr==parcourir.id_oeuvr)
                            {
                                if(Ficher_artiste!=NULL)
                                {
                                    rewind(Ficher_artiste);
                                    while(fread(&mon_artiste,sizeof(mon_artiste),1,Ficher_artiste)==1)
                                    {
                                        if(mon_Oeuvr.Artist_Id==mon_artiste.Id_Artist)
                                        {
                                                printf("\n %015d | %15s | %15s | %15s |    %02i / %02i / %04i  | %15s | %15s | %50s | %50s |",mon_artiste.Id_Artist,mon_artiste.Nom,mon_artiste.Prenom,mon_artiste.Pseudo,mon_artiste.datenaissance.jour,mon_artiste.datenaissance.mois,mon_artiste.datenaissance.annee,mon_artiste.Nationalite,mon_artiste.Statut,mon_artiste.Adresse,mon_artiste.email);
                                                printf("\n_____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");

                                        }
                                    }

                                }

                            }
                    }
                    }else printf("Erreur d'ouverture du fichier oeuvr_Ext.dat\n");
                }

        }
    }else printf("Erreur d'ouverture du fichier Oeuv_exp.dat\n");
    fclose(oeuvr);   fclose(oeuvr_Ext);   fclose(Fichier_Lien);fclose(Ficher_artiste);
     FIN
}
/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction donne la liste des evenements de la base de donnees du Musee*/
/* PARAMETRES : int Id_exposition */
/* VALEUR DE RETOUR: Pas de valeur de retour */
/* AUTEUR : Theodore Barbara G. */
/* DATE CREATION: 11 avril 2018 */
/* DATE MISE A JOUR : 19 avril 2018 */
/* REMARQUES : No, Nom, Prenom, Pseudo, Statut */
/*---------------------------------------------------------------------------------------*/
void List_Evenement()
{
    Evenement Mon_Expo;
    FILE *exposit;
    exposit= fopen("exposit.dat","rb");
    if (exposit != NULL)
   {
        rewind(exposit);
        printf("____________Liste evenements____________\n");
        printf("\n__________________________________________________________________________________________________________________________________________________________________________");
        printf("\n     Identifiant |                                              Theme |                                           Exposant |           Date Debut |             Date fin |");
        printf("\n==========================================================================================================================================================================");
        while(fread(&Mon_Expo,sizeof(Mon_Expo),1,exposit)==1)
        {
            printf("\n %015d | %50s | %50s |    %02i / %02i / %04i    |    %02i / %02i / %04i    |",Mon_Expo.Id_exposition,Mon_Expo.theme,Mon_Expo.exposant,Mon_Expo.date1.jour,Mon_Expo.date1.mois,Mon_Expo.date1.annee,Mon_Expo.date2.jour,Mon_Expo.date2.mois,Mon_Expo.date2.annee);
            printf("\n__________________________________________________________________________________________________________________________________________________________________________");
        }
       printf("\n==========================================================================================================================================================================");
   }
    else
        printf("Le fichier est vide");
   fclose(exposit);
   FIN
}
/*---------------------------------------------------------------------------------------*/
/* DESCRIPTION : Cette fonction permet de donner le prix total des oeuvres du musee*/
/* PARAMETRES : aucun */
/* VALEUR DE RETOUR: Pas de valeur de retour */
/* AUTEUR :  */
/* DATE CREATION: 11 avril 2018 */
/* DATE MISE A JOUR : 19 avril 2018 */
/* REMARQUES : No, Nom, Prenom, Pseudo, Statut */
/*---------------------------------------------------------------------------------------*/
int Prix_Total_des_Oeuvres()
{
     Oeuvre mon_Oeuvr;
      float somme=0;
    FILE *oeuvr;
    oeuvr= fopen("oeuvr.dat","rb");
   if (oeuvr != NULL)
   {
       while(fread(&mon_Oeuvr,sizeof(mon_Oeuvr),1,oeuvr)==1)
            somme=somme+mon_Oeuvr.Valeur;
   }
   else
        printf("Le fichier est vide");
        printf("\nTous les oeuvres du musee peuvent etre estimees a : $ %.3f USD\n",somme);
   fclose(oeuvr);
   FIN
}
