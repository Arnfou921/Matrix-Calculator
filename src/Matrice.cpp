#include "Matrice.h"
#include <iostream>
#include "math.h"
#include<stdio.h>
using namespace std;
Matrice::Matrice(unsigned int l, unsigned int c) : m_l(l), m_c(c)
{
    vector<float> null(0);
    m_table.push_back(null);
    m_table.at(0).push_back(0);
}
Matrice::Matrice(unsigned int l, unsigned int c, vector<vector<float> > tab) : m_l(l), m_c(c), m_table(tab)
{
}
Matrice::Matrice(Matrice const& MatriceACopier)
    : m_l(MatriceACopier.m_l), m_c(MatriceACopier.m_c), m_table(MatriceACopier.m_table)
{
}
void Matrice::Settable(unsigned int l, unsigned int c)
{
    m_l=l;
    m_c=c;
    if(l==0 && c==0)
    {
        l=m_l;
        c=m_c;
    }
    int i,j;
    for(i=0; i<l; i++)
    {
        vector<float> perm;
        m_table.push_back(perm);
        for(j=0; j<c; j++)
            m_table.at(i).push_back(0);
    }
}
void Matrice::Id()
{
    if(m_l!=m_c)
      cout<<"Erreur. La matrice n'est pas carrée, impossible de la mettre sous forme d'une matrice identité !"<<endl;
    else
    {
        for (int i=0; i<m_l; i++)
            for(int j=0;j<m_c;j++)
                if(i=j)
                    m_table[i][j]=1;
                else
                    m_table[i][j]=0;
    }
}
void Matrice::afficher() const
{

}
void Matrice::annuler()
{
    for(int i=0;i<m_l;i++)
        for(int j=0;j<m_c;j++)
            m_table[i][j]=0;
}
bool Matrice::estEgal(Matrice const& B) const
{
    if ((m_c != B.m_c) || (m_l != B.m_l))
          return false;
    else
    {
        for(int i=0; i<m_l; i++)
            for(int j=0; j<m_c; j++)
                if(m_table[i][j]!=B.m_table[i][j])
                        return false;
        return true;
    }
}
bool Matrice::compLignes(Matrice const& A, Matrice const& B) const
{
    if(A.m_l==B.m_l)
        return true;
    else
        return false;
}
bool Matrice::compColonnes(Matrice const& A, Matrice const& B) const
{
    if(A.m_c==B.m_c)
        return true;
    else
        return false;
}
Matrice& Matrice::operator=(Matrice const&A)
{
    m_l = A.m_l;
    m_c = A.m_c;
    m_table = A.m_table;
    return *this;
}
Matrice& Matrice::operator+=(Matrice const& A)
{
    if(compLignes(*this, A) && compColonnes(*this, A))
    {
        for(int i=0; i<m_l; i++)
            for(int j=0; j<m_c; j++)
                (m_table[i][j]+=A.m_table[i][j]);
        return *this;
    }
    else
    {
        cout<<"Les deux matrices sont de taille differentes !"<<endl;
        return *this;
    }
}
Matrice& Matrice::operator-=(Matrice const& A)
{
    if(compLignes(*this, A) && compColonnes(*this, A))
    {
        for(int i=0; i<m_l; i++)
            for(int j=0; j<m_c; j++)
                (m_table[i][j]-=A.m_table[i][j]);
        return *this;
    }
    else
    {
        cout<<"Les deux matrices sont de taille differentes !"<<endl;
        return *this;
    }
}
Matrice& Matrice::operator*=(float const& k)
{
    for(int i=0; i<m_l; i++)
        for(int j=0; j<m_c; j++)
            (m_table[i][j]*=k);
    return *this;
}
Matrice& Matrice::operator*=(Matrice const& A)
{
    Matrice copie(*this);
    if(m_c == A.m_l)
    {
        int i,j, k;
        for(i=0; i<m_l; i++)
            for(j=0; j<m_c; j++)
            {
                float temp = 0;
                for(k=0; k<m_c; k++)
                    temp+=copie.m_table[i][k]*A.m_table[k][j];
                m_table[i][j]=temp;
            }
        return *this;
    }
    else if(m_l>1 && m_c>1&&A.m_l==1 && A.m_c==1)
    {
        *this*=A.m_table[0][0];
    }
    else
    {
        cout<<"Le produit est impossible !"<<endl;
        return *this;
    }
}
Matrice& Matrice::operator/=(float const& k)
{
    float a = 1/k;
    return *this*=a;
}
Matrice& Matrice::operator/=(Matrice const& A)
{
    if(m_l==m_c && A.m_l==A.m_c)
    {
        if(A.m_l==1 && A.m_c==1)
        {
            for(int i=0; i<m_l; i++)
                for(int j=0; j<m_c; j++)
                {
                    float a=m_table[i][j], b=A.m_table[0][0];
                    m_table[i][j]=a/b;
                }

            return *this;
        }
        else
        {
            Matrice copie(A);
            Matrice B(copie.inverse());
            return *this*=B;
        }

    }
    if(A.m_l==1 && A.m_c==1)
    {
        return *this/=A.m_table[0][0];
    }
    else
    {
        cout<<"La division est impossible !"<<endl;
        return *this;
    }
}
Matrice& Matrice::operator^(int n)
{
    Matrice copie(*this);
    for(int i=1;i<n; i++)
        *this*=copie;
    return  *this;
}

Matrice& Matrice::operator^(Matrice const& A)
{
    Matrice copie(*this);
    if(A.m_l==1 && A.m_c==1)
    {
        for(int i=1;i<A.m_table[0][0]; i++)
            *this*=copie;
    }
    else
    {
        cout<<"Impossible de faire la puissance d'une matrice par une autre !"<<endl;
    }

    return  *this;
}
float Matrice::trace()
{
    if(m_l==m_c)
    {
        float tr=0;
        for(int i=0;i<m_l; i++)
            tr+=m_table[i][i];
        return tr;
    }
    else
    {
        cout<<"La mtarice n'est pas carrée, la calculatrice ne peut pas afficher la trace !"<<endl;
        return 0;
    }
}
Matrice Matrice::transposee(Matrice const& A)
{
       Matrice copie(A);
       int i, j;
       for(i=0; i<m_l; i++)
            for(j=0; j<m_c;j++)
                if(i!=j)
                    copie.m_table[i][j]=A.m_table[j][i];
       return copie;
}
float Matrice::det()
{
    if(m_l==m_c)
    {
        Matrice mat(*this);
        float det;
        int i,j, n(m_l);
        det = 1;
        for(i=0;i<n-1;i++)
        {
            int rangMax,rang;
            float coeffMax;
            rangMax = i;
            for(rang=i+1; rang<n; rang++)
            {
            if(fabs(mat.m_table[rangMax][i]) < fabs(mat.m_table[rang][i]))
                rangMax = rang;
            }
            coeffMax = mat.m_table[rangMax][i];
            if(fabs(coeffMax) == 0)
            {
                det = 0;
                goto label_end;
            }
            if(rangMax != i)
            {
                for(j=i;j<n;j++)
                {
                    float temp;
                    temp = mat.m_table[i][j];
                    mat.m_table[i][j]=mat.m_table[rangMax][j];
                    mat.m_table[rangMax][j]= temp;
                }
            det *= -1;
            }
            det *= coeffMax;
            for(rang=i+1;rang<n;rang++)
            {
                float coeff;
                coeff = mat.m_table[rang][i]/coeffMax;
                for(j=i;j<n;j++)
                    mat.m_table[rang][j] -= coeff*mat.m_table[i][j];
            }
        }
    det *= mat.m_table[n-1][n-1];
    label_end:
    return det;
    }
    else
    {
        cout<<"La matrice n'est pas carrée, le calcul du déterminant est impossible !"<<endl;
        return 0;
    }
}
Matrice Matrice::inverse()
{
    if (m_l!=m_c)
    {
        cout<<"Erreur, la matrice est non carrée, son inversion n'est pas possible ici !"<<endl;
        return *this;
    }
    float coeffMax, pinv, dum, temp;
    int n=m_l, indxc[n], indxl[n], ilig, icol, i, j, k, l, ll;
    Matrice Minv(*this);
    vector<int> ipiv(n, 0);
    for(i=0;i<n;i++)
    {
        coeffMax=0.0;
        for(j=0;j<n;j++)
        {
            if(ipiv[j]!=1)
            {
                for(k=0;k<n;k++)
                {
                    if(ipiv[k]==0)
                    {
                        if(fabs(Minv.m_table[j][k])>=coeffMax)
                        {
                            coeffMax=fabs(Minv.m_table[j][k]);
                            ilig=j;
                            icol=k;
                        }
                    }
                }
            }
        }
        ipiv[icol]++;
        if(ilig!=icol)
        {
            for(int l=0;l<n;l++)
            {
                temp=Minv.m_table[ilig][l];
                Minv.m_table[ilig][l]=Minv.m_table[icol][l];
                Minv.m_table[icol][l]=temp;
            }
        }
        indxl[i]=ilig;
        indxc[i]=icol;
        if(Minv.m_table[icol][icol]==0)
        {
            cout<<"La matrice est singulière. Son inversion est impossible"<<endl;
            return *this;
        }
        pinv=1.0/Minv.m_table[icol][icol];
        Minv.m_table[icol][icol]=1.0;
        for(l=0;l<n;l++)
            Minv.m_table[icol][l]*=pinv;
        for(ll=0;ll<n;ll++)
        {
            if(icol!=ll)
            {
                dum=Minv.m_table[ll][icol];
                Minv.m_table[ll][icol]=0.0;
                for(l=0;l<n;l++)
                    Minv.m_table[ll][l]-=Minv.m_table[icol][l]*dum;
            }
        }
    }
    for(l=n-1;l>=0;l--)
    {
        if(indxl[l]!=indxc[l])
        {
            for(k=0;k<n;k++)
            {
                temp=Minv.m_table[k][indxl[l]];
                Minv.m_table[k][indxl[l]]=Minv.m_table[k][indxc[l]];
                Minv.m_table[k][indxc[l]]=temp;
            }
        }
    }
    return Minv;
}
bool operator==(Matrice const& A, Matrice const& B)
{
    return A.estEgal(B);
}
bool operator!= (Matrice const& A, Matrice const& B)
{
    if(A.estEgal(B))
        return false;
    else
        return true;
}
Matrice operator+(Matrice const& A, Matrice const& B)
{
    Matrice copie(A);
    copie +=B;
    return copie;
}
Matrice operator-(Matrice const& A, Matrice const& B)
{
    Matrice copie(A);
    copie -=B;
    return copie;
}
Matrice operator*(Matrice const& A, float const& k)
{
    Matrice copie(A);
    copie *=k;
    return copie;
}
Matrice operator*(Matrice const& A, Matrice const& B)
{
    Matrice copie(A);
    copie *=B;
    return copie;
}
Matrice operator/(Matrice const& A, float const& k)
{
    Matrice copie(A);
    copie /=k;
    return copie;
}
Matrice operator/(Matrice const& A, Matrice const& B)
{
    Matrice copie(A);
    copie /=B;
    return copie;
}
Matrice::~Matrice()
{}
