#ifndef MATRICE_H
#define MATRICE_H
#include <vector>
class Matrice
{
    public:
        // Ce sont les différents constructeurs (manière d'initialiser l'objet matrice).
        Matrice(unsigned int l=0, unsigned int c=0);
        Matrice(unsigned int l, unsigned int c, std::vector<std::vector<float> >tab);
        // On initialise la matrice en renseignant lignes, colonne et un tableau dynamique en 2D. Si aucune valeur n'est rensignée, ils prendront une valeur par défaut (0 partout).
        Matrice(Matrice const& MatriceACopier);
        // On initialise une matrice en lui donnant les attributs d'une autre matrice directement.
        //Destructeur de la matrice (inutile ici..)
        virtual ~Matrice();
        void afficher() const;                                       // Affiche la matrice
        void annuler();                                              // Reduit tous les coeff de la matrice à 0.
        //void supprCol(unsigned int n);
        //void supprLi(unsigned int n);
        void Id();                                                   // Convertit la matrice en une matrice identité (besoin piur l'algortihme de calcul de l'inverse apparemment..)
        bool estEgal(Matrice const& B) const;                        // Permet de comparer cette matrice à une autre.
        bool compLignes(Matrice const& A, Matrice const& B) const;   // Permet de comparer les lignes de deux matrices.
        bool compColonnes(Matrice const& A, Matrice const& B) const; // Permet de comparer les colonnes de deux matrices.
        Matrice& operator=(Matrice const& A);                        // Permet de créer une copie de la matrice en utilisant l'opérateur =.
        Matrice& operator+=(Matrice const& A);                       // Permet d'additionner une matrice à celle-ci en utilisant l'opérateur +=.
        Matrice& operator-=(Matrice const& A);                       // Permet de soustraire une matrice à celle-ci en utilisant l'opérateur -=.
        Matrice& operator*=(Matrice const& A);                       // Permet de multiplier la matrice avec une autre matrice en utilisant l'opérateur *=.
        Matrice& operator*=(float const& k);                         // Permet de multiplier la matrice avec un scalaire en utilisant l'opérateur *=.
        Matrice& operator/=(float const& k);
        Matrice& operator/=(Matrice const& A);
        Matrice& operator^(int n);                                   // Permet de calculer une matrice à la puissance n.
        Matrice& operator^(Matrice const& A);
        Matrice inverse();                                           // Permet de calculer inverse de la matrice.
        Matrice transposee(Matrice const& A);                        // Calcule la transposée d'une matrice
        float trace();                                              // Calcule la trace d'une matrice (demandé dans le projet...)
        float det();                                                // Calcule le det d'une matrice.
        unsigned int Getl() const { return m_l; }                                    // Permet d'obtenir le nombre de lignes de la matrice en appelant cette fonction dans le main.
        void Setl(unsigned int val) { m_l = val; }                                   // Permet de modifier le nombre de lignes dans le main.
        unsigned int Getc() const { return m_c; }                                    // Permet d'obtenir le nombre de colonnes.
        void Setc(unsigned int val) { m_c = val; }                                   // Permet de modifier le nombre de colonnes.
        float Getcoeff(unsigned int i, unsigned int j) const {return m_table[i][j];} // Permet d'obtenir le coef à un endroit précis de la matrice.
        void Setcoeff(unsigned int i, unsigned int j, float k) {m_table[i][j]=k;}    // Permet de modifier le coeff à un endroit précis.
        std::vector<std::vector<float> > Gettable() const {return m_table;}          // Permet d'obtenir le tableau dynamique correspondant à la matrice.
        void Settable(unsigned int l=0, unsigned int c=0);                           // Permet de créer le tableau de la matrice avec la taille que l'on veut. Il sera "vide" (en réalité repli de 0). Si rien n'est renseigné, on dira que l et c sont égaux aux attributs m_l et m_c d ela m
    protected:
    private:
        // Attributs de l'objet matrice.
        unsigned int m_l;
        unsigned int m_c;
        std::vector<std::vector<float> > m_table;
};
bool operator== (Matrice const& A, Matrice const& B); // Permet de vérifier si deux matrices sont égales en utiiant l'opérateur ==.
bool operator!= (Matrice const& A, Matrice const& B); // Permet de vérifier si deux matrices sont différentes en utiiant l'opérateur !=.
Matrice operator+(Matrice const& A, Matrice const& B); // Permet d'additionner deux matrices.
Matrice operator-(Matrice const& A, Matrice const& B); // Permet de soustraire une matice à une autre.
Matrice operator*(Matrice const& A, Matrice const& B); // Permet de faire le produit de deux matrices.
Matrice operator*(Matrice const& A, float const& k); // Permet de faire le produit par un scalaire.
Matrice operator/(Matrice const& A, float const& k); // Permet de faire la division d'une matrice par un réel.
Matrice operator/(Matrice const& A, Matrice const& B); // Permet de faire la division de deux matrices.
#endif // MATRICE_H
