#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <math.h>
#include <string.h>
#include "Matrice.h"
#include <ctype.h>


                //*_____________*Global variables*_____________*//

    GtkBuilder *gtkBuilder;
    GtkBuilder *VBox;
    GtkWidget *table;
    GtkWidget *resultat;
    GtkWidget *CoefMatrice[6][6];
    GtkWidget *Resultat[6][6];
    GtkWidget *ConsoleOpeTexte;

    int i=0, j=0, pos=0, c=0, l=0,compteur=0;
    char stext[10];
    char trace[8]="Trace =";
    char inv[6]="Inv =";
    char det[6]="det =";
    float num=0;
    char output[10];


    gint Lignes=5,Colonnes=5;
    Matrice MatriceA;
    Matrice MatriceB;
    Matrice MatriceAns;

    typedef struct
    {
        GtkBuilder *builder;
        gpointer user_data;
    }   SGlobalData;


                //*_____________*Processus/Fonctions*_____________*//


void afficher(GtkWidget *pBtn, gpointer entry)
{
    strcpy(stext ,gtk_entry_get_text(GTK_ENTRY(entry)));
    strcat(stext,gtk_button_get_label(GTK_BUTTON(pBtn)));
    gtk_entry_set_text(GTK_ENTRY(entry), stext);
}

void CalculResultat(GtkWidget *pBtn, gpointer entry)
{
    printf("\n_________DEBUT Processus Calcul_______\n");

    // On crée dceux matrices opérandes qui contiendront la valeur des deux operandes rentrés (réels et matrices).
  Matrice operande1, operande2;

    // On récupère le texte de la console
    int tailleTexte = gtk_entry_get_text_length(GTK_ENTRY(entry));
    char *texte, ope;
    texte=(char *)malloc(tailleTexte*(sizeof(char)));
    strcpy(texte, gtk_entry_get_text(GTK_ENTRY(entry)));

    // On cherche la position et la valeur de l''opérateur dans la chaîne ( 'r' pour trace, 'v' pour inversion, d pour determinant)
    for(i=0; i<tailleTexte; i++)
    {
        if(texte[i]=='+'|| texte[i]=='-'|| texte[i]=='x'|| texte[i]=='/'|| texte[i]=='v'|| texte[i]=='r'|| texte[i]=='d'|| texte[i]=='^')
        {
            ope = texte[i];
            pos = i;
            break;
        }
    }


    if(ope!='r'&&ope!='v'&&ope!='d') // Si c'est un opérateur classique, on récupère les deux opérandes
    {

        if (pos>1) // Si l'opérande fait plus d'un caractère de longueur, on est sur que c'est un réel, donc on le récupère et l'on crée la matriuce résultat "MatriceAns" de taille (1,1).
        {
            if(texte[1]=='N') // Si l'utilisateur a tapé "ANS"
                operande1=MatriceAns;

            else
            {
                char *nb1=NULL;
                nb1 = (char*)malloc((pos)*sizeof(char));

                for(i=0; i<pos; i++)
                    {
                        nb1[i]=texte[i];

                    }
                    operande1.Settable(1,1);
                    operande1.Setcoeff(0,0,atof(nb1));
            }
        }

        else if(pos==1) // Si l'opérande1 n'est qu'un caractère
        {
            printf("\ntexte[0]=%c\nisalpha=%d\nisdigit=%d\n", texte[0], isalpha(texte[0]), isdigit(texte[0]));
            if(isalpha(texte[0]))// Si c'est une lettre alphabétique on sait que c'est soit "A" soit "B" qui a été appelée.
            {
                if(texte[0]=='A')
                    operande1=MatriceA;
                else if(texte[0]=='B')
                    operande1=MatriceB;
                else
                    gtk_entry_set_text(GTK_ENTRY(entry), "ERROR" );
            }

            else if(isdigit(texte[0]))// Si c'est un nombre, c'est juste un réel.
            {
                char *d;
                d=&texte[0];
                float n=atof(d);
                printf("%f", n);
                operande1.Settable(1,1);
                operande1.Setcoeff(0,0,n);
            }
        }

        else  gtk_entry_set_text(GTK_ENTRY(entry), "ERROR" );

        if(tailleTexte-pos>2) // On détermine l'opérande2 selon le même procédé que précédemment, après avoir récupéré la chaâine de caractère suivant l"opérateur.
        {
            int cmpt=0;
            char *nb2=NULL;
            nb2 = (char*)malloc((tailleTexte-pos+1)*sizeof(char));
            for(i=pos+1; i<tailleTexte; i++)
            {
                 nb2[cmpt]=texte[i];
                 printf("%c", nb2[i]);
                 cmpt++;
            }
            float n=atof(nb2);
            printf("n=%f", n);
            operande2.Settable(1,1);
            operande2.Setcoeff(0,0,n);
        }

        else if(tailleTexte-pos==2)
        {
            if(isdigit(texte[pos+1]))
            {
                char *d;
                d=&texte[pos+1];
                float n=atof(d);

                printf("n=%f", n);
                operande2.Settable(1,1);
                operande2.Setcoeff(0,0,n);
            }

            else if(isalpha(texte[pos+1]))
            {


                if(texte[pos+1]=='A')
                    operande2=MatriceA;

                else if(texte[pos+1]=='B')
                    operande2=MatriceB;

                else
                    gtk_entry_set_text(GTK_ENTRY(entry), "ERROR" );

            }
            else
                gtk_entry_set_text(GTK_ENTRY(entry), "ERROR" );

        }
        else
            gtk_entry_set_text(GTK_ENTRY(entry), "ERROR" );


  {

    }

printf("\n    Processus choisit :   ");
switch (ope) // On fait un switch pour agir selon les diffé"rentes valeurs que peut prendre l'opérateur
{
    case 'r' : printf("__Trace__ \n"); // On calcule la trace de la matrice, on la met dans une matriceAns de taille (1,1) et on l'affiche dans la Console.

            if(texte[tailleTexte-1]=='A')
                {
                    printf("\n Trace(A) = %f \n",MatriceA.trace());
                    MatriceAns.Settable(1,1);
                    MatriceAns.Setcoeff(0,0, MatriceA.trace());

                    num=MatriceA.trace();

                    snprintf(output,50,"%f",num);
                    gtk_entry_set_text(GTK_ENTRY(entry), output );
                    gtk_entry_set_text(GTK_ENTRY(ConsoleOpeTexte) , trace );
                }

            else if(texte[tailleTexte-1]=='B')
                {
                    printf("\n Trace(B) = %f \n",MatriceB.trace());
                    MatriceAns.Settable(1,1);
                    MatriceAns.Setcoeff(0,0, MatriceB.trace());

                    num=MatriceB.trace();

                    snprintf(output,50,"%f",num);
                    gtk_entry_set_text(GTK_ENTRY(entry), output );
                    gtk_entry_set_text(GTK_ENTRY(ConsoleOpeTexte) , trace );
                }
            else if (texte[tailleTexte-1]=='S')
            {
                    printf("\n Trace(Ans) = %f \n",MatriceAns.trace());
                    Matrice copie(MatriceAns);
                    MatriceAns.Settable(1,1);
                    MatriceAns.Setcoeff(0,0, copie.trace());

                    num=copie.trace();

                    snprintf(output,50,"%f",num);
                    gtk_entry_set_text(GTK_ENTRY(entry), output );
                    gtk_entry_set_text(GTK_ENTRY(ConsoleOpeTexte) , trace );
            }

            else
                {
                    gtk_entry_set_text(GTK_ENTRY(entry), "ERROR" );
                }break;

    case 'v' : printf("__Inverse__ \n"); // Si c'est 'v', on calcule l'inverse de la matrice appelée.

            if(texte[tailleTexte-1]=='A')
                {
                    MatriceAns.Settable(MatriceA.Getl(),MatriceA.Getc());
                    MatriceAns=MatriceA.inverse();
                }
            else if(texte[tailleTexte-1]=='B')
                {
                    MatriceAns.Settable(MatriceB.Getl(),MatriceB.Getc());
                    MatriceAns=MatriceB.inverse();
                }
            else if (texte[tailleTexte-1]=='S')
            {
                    printf("\n Trace(Ans) = %f \n",MatriceAns.trace());
                    Matrice copie(MatriceAns);
                    MatriceAns.Settable(copie.Getl(),copie.Getc());
                    MatriceAns=copie.inverse();
            }
            else
                {
                    gtk_entry_set_text(GTK_ENTRY(entry), "ERROR texte[tailleTexte]" );
                }break;

    case 'd' : printf("__Determinant__ \n"); // Déterminant

            if(texte[tailleTexte-1]=='A')
                {
                    printf("\n Det(A) = %f \n",MatriceA.det());
                    MatriceAns.Settable(1,1);
                    MatriceAns.Setcoeff(0,0, MatriceA.det());

                    num=MatriceA.det();

                    snprintf(output,50,"%f",num);
                    gtk_entry_set_text(GTK_ENTRY(entry), output );
                    gtk_entry_set_text(GTK_ENTRY(ConsoleOpeTexte) , det );

                }
            else if(texte[tailleTexte-1]=='B')
                {
                    printf("\n Det(B) = %f \n",MatriceB.det());
                    MatriceAns.Settable(1,1);
                    MatriceAns.Setcoeff(0,0, MatriceB.det());

                    num=MatriceB.det();

                    snprintf(output,50,"%f",num);
                    gtk_entry_set_text(GTK_ENTRY(entry), output );
                    gtk_entry_set_text(GTK_ENTRY(ConsoleOpeTexte) , det );
                }
            else if (texte[tailleTexte-1]=='S')
            {
                    printf("\n Trace(Ans) = %f \n",MatriceAns.det());
                    Matrice copie(MatriceAns);
                    MatriceAns.Settable(1,1);
                    MatriceAns.Setcoeff(0,0, copie.det());

                    num=copie.det();

                    snprintf(output,50,"%f",num);
                    gtk_entry_set_text(GTK_ENTRY(entry), output );
                    gtk_entry_set_text(GTK_ENTRY(ConsoleOpeTexte) , det );
            }
            else
                {
                    gtk_entry_set_text(GTK_ENTRY(entry), "ERROR" );
                }break;

    case '+' : printf("__Somme__ \n");
                if(operande1.Getl()==operande2.Getl() && operande1.Getc()==operande2.Getc())
                {
                    MatriceAns = operande1+operande2;
                    for(i=1;i<=MatriceAns.Getl();i++)
                    {
                        printf("\n| ");
                        for(j=1;j<=MatriceAns.Getc();j++)
                        {
                            char Coef[1];
                            printf("%1.3f ", MatriceAns.Getcoeff(i-1,j-1) );

                        }printf("| ");
                        }printf("\n||\n\n");
                    }

            else
                {
                    gtk_entry_set_text(GTK_ENTRY(entry), "ERROR " );
                }break;

    case '-' : printf("__Soustraction__ \n");

            if(operande1.Getl()==operande2.Getl() && operande1.Getc()==operande2.Getc())
                {
                    MatriceAns= operande1-operande2;
                    for(i=1;i<=MatriceAns.Getl();i++)
                    {
                        printf("\n| ");
                        for(j=1;j<=MatriceAns.Getc();j++)
                        {
                            char Coef[1];
                            printf("%1.3f ", MatriceAns.Getcoeff(i-1,j-1) );

                        }printf("| ");
                        }printf("\n||\n\n");
                    }

            else
                {
                    gtk_entry_set_text(GTK_ENTRY(entry), "ERROR" );
                }break;

    case 'x' : printf("__Multiplication__ \n");

            if(operande1.Getc()==operande2.Getl() || (operande2.Getl()==1&&operande2.Getc()==1))
                {
                    MatriceAns= operande1*operande2;
                    MatriceAns.afficher();
                    for(i=1;i<=MatriceAns.Getl();i++)
                    {
                        printf("\n| ");
                        for(j=1;j<=MatriceAns.Getc();j++)
                        {
                            char Coef[1];
                            printf("%1.3f ", MatriceAns.Getcoeff(i-1,j-1) );

                        }printf("| ");
                    }printf("\n||\n\n");
                    }

            else
                {
                    gtk_entry_set_text(GTK_ENTRY(entry), "ERROR" );
                }break;

    case '/' :printf("__Division__ \n");

            if(operande1.Getl()==operande1.Getc() && operande2.Getl()==operande2.Getc()&&operande1.Getl()==operande2.Getc() ||(operande2.Getl()==1&&operande2.Getc()==1))
                {

                    MatriceAns = operande1/operande2;
                    for(i=1;i<=MatriceAns.Getl();i++)
                    {
                        printf("\n| ");
                        for(j=1;j<=MatriceAns.Getc();j++)
                        {
                            char Coef[1];
                            printf("%1.3f ", MatriceAns.Getcoeff(i-1,j-1) );

                        }printf("| ");
                        }printf("\n||\n\n");
                    }

                else
                {
                    gtk_entry_set_text(GTK_ENTRY(entry), "ERROR" );
                }break;

    case '^' : printf("__Puissance__\n");

            if(operande2.Getl()==1 && operande2.Getc()==1)
                {
                    MatriceAns= operande1^operande2;
                    for(i=1;i<=MatriceAns.Getl();i++)
                    {
                        printf("\n| ");
                        for(j=1;j<=MatriceAns.Getc();j++)
                        {
                            char Coef[1];
                            printf("%1.3f ", MatriceAns.Getcoeff(i-1,j-1) );

                        }printf("| ");
                        }printf("\n||\n\n");
                    }

            else
                {
                    gtk_entry_set_text(GTK_ENTRY(entry), "ERROR(operande 2 n'est pas un nombre)" );break;
                }break;

    default : break;

    }

    // Affichage de la matrice dans la matrice résultat.

    if(MatriceAns.Getl()==1&&MatriceAns.Getc()==1)
    {
        num=MatriceAns.Getcoeff(0,0);
        printf("\nnum=%d\n", num);
        snprintf(output,50,"%f",num);
        printf("\noutput=%d\n", output);
        gtk_entry_set_text(GTK_ENTRY(ConsoleOpeTexte) , "Resultat :" );
        gtk_entry_set_text(GTK_ENTRY(entry) , output );
    }
    for(i=0;i<MatriceAns.Getl();i++)
        for(j=0;j<MatriceAns.Getc();j++)
        {
            num=MatriceAns.Getcoeff(i,j);
            snprintf(output,50,"%f",num);
            gtk_entry_set_text(GTK_ENTRY(Resultat[i+1][j+1]) , output  );
        }


    printf("\n_________Fin Processus Calcul_______\n");
}


    if (compteur==0)
    {compteur++;}
}

void ResetResultat(GtkWidget *pBtn, gpointer entry)
{

for(i=1;i<=5;i++)
  {
      for(j=1;j<=5;j++)
      {
        //Reset Table/Matrice de droite (resultats)
        gtk_entry_set_text(GTK_ENTRY(Resultat[i][j]),"0");
      }
   }
}

void compteurR(GtkWidget *pBtn, gpointer entry)
{
    compteur=2;
}

void ResetConsole(GtkWidget *pBtn, gpointer entry)
{
    gtk_entry_set_text(GTK_ENTRY(entry), "");
    compteur=0;
}

void AffectationMatriceA(GtkWidget *pBtn, gpointer CoefM)
{
     MatriceA.Settable(Lignes,Colonnes);

    for(i=1;i<=Lignes;i++)
  {
      printf("\n| ");
        for(j=1;j<=Colonnes;j++)
        {
            char Coef[1];
            strcpy(Coef,gtk_entry_get_text(GTK_ENTRY(CoefMatrice[i][j])));
            MatriceA.Setcoeff(i-1,j-1,atof(Coef));
            printf("%1.3f ", MatriceA.Getcoeff(i-1,j-1) );

        }printf("| ");
  }printf("\n||\n\n");
}

void AffectationMatriceB(GtkWidget *pBtn, gpointer CoefM)
{

    MatriceB.Settable(Lignes,Colonnes);

    for(i=1;i<=Lignes;i++)
   {
     printf("\n| ");
      for(j=1;j<=Colonnes;j++)
        {
            char Coef[1];
            strcpy(Coef,gtk_entry_get_text(GTK_ENTRY(CoefMatrice[i][j])));
            MatriceB.Setcoeff(i-1,j-1,atof(Coef));
            printf("%1.3f ", MatriceB.Getcoeff(i-1,j-1) );

        }printf("| ");
    }printf("\n||\n\n");
}

void RentreInVisible(GtkWidget *pBtn, gpointer BoutonInvisible)
{
    gtk_widget_set_sensitive(GTK_WIDGET(BoutonInvisible),FALSE);
}

void RentreVisibleOpe(GtkWidget *pBtn, gpointer Boutonvisible)
{
    if(compteur<1)
    {compteur++;}
}

void RentreVisible(GtkWidget *pBtn, gpointer Boutonvisible)
{
    if(compteur<1)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(Boutonvisible),TRUE);
        gtk_widget_set_visible(GTK_WIDGET(Boutonvisible),TRUE);
        gtk_widget_set_can_focus(GTK_WIDGET(Boutonvisible),FALSE);
    }
}
void RendreVisibleA(GtkComboBoxText *BOX, gpointer A)

{
    if (c==1 && l==1)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(A),TRUE);

    }
}


void ModifColonnes(GtkComboBoxText *BOX, gpointer entry)
{
    char C[1];

    strcpy(C,gtk_combo_box_text_get_active_text (BOX));
    Colonnes=atoi(C);
    c=1;
    Lignes=atoi(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(entry)));


    printf("\nNB_Colonnes_changed = %d\n",Colonnes);

    for(i=1;i<=5;i++)
    {
      for(j=1;j<=5;j++)
      {
            gtk_widget_set_sensitive(CoefMatrice[i][j], FALSE);
            gtk_widget_set_visible(CoefMatrice[i][j], FALSE);
      }
    }

    for(i=1;i<=Lignes;i++)
    {
      for(j=1;j<=Colonnes;j++)
      {
            gtk_widget_set_sensitive(CoefMatrice[i][j], TRUE);
            gtk_widget_set_visible(CoefMatrice[i][j], TRUE);
      }
    }

}

void ModifLignes(GtkComboBoxText *BOX, gpointer entry)
{
    char L[1];

    strcpy(L,gtk_combo_box_text_get_active_text (BOX));
    Lignes=atoi(L);
    l=1;
    Colonnes=atoi(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(entry)));
    printf("\nNB_Lignes_changed = %d\n",Lignes);

    for(i=1;i<=5;i++)
    {
      for(j=1;j<=5;j++)
      {
            gtk_widget_set_sensitive(CoefMatrice[i][j], FALSE);
            gtk_widget_set_visible(CoefMatrice[i][j], FALSE);
      }
    }

    for(i=1;i<=Lignes;i++)
    {
      for(j=1;j<=Colonnes;j++)
      {
            gtk_widget_set_sensitive(CoefMatrice[i][j], TRUE);
            gtk_widget_set_visible(CoefMatrice[i][j], TRUE);
      }
    }
}

                    //*_____________* M A I N *_____________*//

int main(int argc, char *argv[])
{


//Variables
    GtkWidget *window;
    GError *error = NULL;
//    SGlobalData data;  /* variable propagée à tous les callbacks. */


// Initialisation de GTK+
    gtk_init(&argc, &argv);
    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "InterfaceGraphique 2.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "MainWindow"));
    ConsoleOpeTexte = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "ConsoleOpe"));


//Personnalisation de la Fenêtre
    // Titre
        gtk_window_set_title(GTK_WINDOW(window), "Calculatrice de matrices");  //SET Titre
    // Position
        gtk_window_set_position(GTK_WINDOW (window), GTK_WIN_POS_CENTER);      //Set Position d'ouverture
    //New
        gtk_window_set_modal(GTK_WINDOW(window), TRUE);
        g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL );


    //*________________Création de la table_______________*//

table = gtk_grid_new();
resultat = gtk_grid_new();

    gtk_container_add(GTK_CONTAINER(gtk_builder_get_object(gtkBuilder, "VBox")), table);
    gtk_container_add(GTK_CONTAINER(gtk_builder_get_object(gtkBuilder, "vboxR")), resultat);

    gtk_grid_attach(GTK_GRID(table),GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "VBox")),1, 1, 0, 0);
    gtk_grid_attach(GTK_GRID(resultat),GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "vboxR")),1, 1, 0, 0);


    //*________________Création des Matrices Sur l'interface graphique_______________*//

for(i=1;i<=5;i++)
  {
      for(j=1;j<=5;j++)
      {
        //Creation Table/Matrice de gauche(A ou B)
        CoefMatrice[i][j] = gtk_entry_new();
        gtk_entry_set_width_chars(GTK_ENTRY(CoefMatrice[i][j]),6);
        gtk_grid_attach(GTK_GRID(table), CoefMatrice[i][j], j, i, 1,1);
        gtk_entry_set_text(GTK_ENTRY(CoefMatrice[i][j]),"0");
        gtk_widget_set_can_focus(CoefMatrice[i][j],TRUE);
        gtk_widget_set_sensitive(CoefMatrice[i][j], FALSE);

        //Creation Table/Matrice de droite (resultats)
        Resultat[i][j] = gtk_entry_new();
        gtk_entry_set_width_chars(GTK_ENTRY(Resultat[i][j]),6);
        gtk_entry_set_overwrite_mode(GTK_ENTRY(Resultat[i][j]),FALSE);
        gtk_widget_set_can_focus(Resultat[i][j],FALSE);
        gtk_grid_attach(GTK_GRID(resultat), Resultat[i][j], j, i, 1 ,1);
        gtk_entry_set_text(GTK_ENTRY(Resultat[i][j]),"0");
      }
   }


        //Signaux de Renvoie Clavier vers console :
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "0")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "1")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "2")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "3")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "4")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "5")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "6")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "7")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "8")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "9")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "+")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(afficher), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));

        //Reset console
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(ResetConsole), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Console"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(ResetConsole),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ConsoleOpe"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(compteurR), NULL);
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(compteurR), NULL);
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(compteurR), NULL);
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ResetResultat")), "clicked", G_CALLBACK(ResetResultat), NULL);


        //Matrices
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Lignes")), "changed", G_CALLBACK(ModifLignes), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Colonnes"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Lignes")), "changed", G_CALLBACK(RendreVisibleA),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A="));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Colonnes")), "changed", G_CALLBACK(ModifColonnes), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "Lignes"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Colonnes")), "changed", G_CALLBACK(RendreVisibleA), (GtkWidget*) gtk_builder_get_object(gtkBuilder, "A="));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(AffectationMatriceA),NULL);
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B=")), "clicked", G_CALLBACK(AffectationMatriceB), (GtkWidget*) *CoefMatrice);
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(CalculResultat), (GtkWidget*) GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "Console")));





///RENDRE INVISIBLE
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Entrer"));


        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "0")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "1")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "2")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "3")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "4")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "5")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "6")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "7")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "8")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "9")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "0")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "1")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "2")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "3")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "4")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "5")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "6")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "7")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "8")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "9")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "0")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "1")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "2")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "3")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "4")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "5")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "6")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "7")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "8")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "9")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "0")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "1")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "2")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "3")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "4")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "5")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "6")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "7")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "8")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "9")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "0")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "1")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "2")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "3")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "4")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "5")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "6")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "7")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "8")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "9")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "0")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "1")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "2")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "3")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "4")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "5")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "6")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "7")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "8")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "9")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "+")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "+")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "+")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "+")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "+")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "+")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "+")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "+")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));


        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "inv")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Trc")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));



        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "det")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));

///RENDRE VISIBLE

    //Signaux de visibilité :
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Reset"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B="));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Entrer"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "+")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "+")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "+")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "*"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "ANS")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "inv"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "det"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Trc"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Entrer"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B=")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "*"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "A")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "*"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "B")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "A"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "x")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "B"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "-")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ANS"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "Reset"));



        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "/")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "^")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "0")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "0")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "0")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "0")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "1")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "1")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "1")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "1")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "2")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "2")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "2")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "2")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "3")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "3")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "3")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "3")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "4")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "4")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "4")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "4")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "5")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "5")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "5")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "5")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "6")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "6")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "6")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "6")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "7")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "7")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "7")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "7")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "8")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "8")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "8")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "8")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "9")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "x"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "9")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "/"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "9")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "+"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "9")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "-"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "0")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "1")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "2")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "3")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "4")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "5")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "6")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "7")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "8")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "9")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "0"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "1"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "2"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "3"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "4"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "5"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "6"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "7"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "8"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "9"));
        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Reset")), "clicked", G_CALLBACK(RentreInVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "^"));

        g_signal_connect(G_OBJECT(gtk_builder_get_object(gtkBuilder, "Entrer")), "clicked", G_CALLBACK(RentreVisible),(GtkWidget*) gtk_builder_get_object(gtkBuilder, "ResetResultat"));




        /* Affichage de la fenêtre principale. */
        gtk_widget_show_all (window);
        g_object_unref(G_OBJECT(gtkBuilder));
        gtk_widget_show(window);
        gtk_main();
        return 0;
}

                    //*______________* E N D *______________*//


//*_____________________________ A FN05 CUSTOM PROJECT _____________________________*//
