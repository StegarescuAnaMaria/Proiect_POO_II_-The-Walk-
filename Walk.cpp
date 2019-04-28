#include "Walk.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
void efect_item_universal(int&nr_vieti);
void prim(char** &harta, const char destinatie, const int nr_capcane, const char bomb, const int nr_itemi, const char item1,
          const char item2, const char item3, const char item_uni);
int** realocare(int**warning, int& nr_obiecte);
void efect_item3(int& vizor);
void dezalocare(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int&nr_obiecteD, int&nr_obiecte, int&nr_obiecte_aux);
//constructorii primesc valori default
Walk::Walk(const char Urma1, const char Urma2, const char Urma3, const char Urma4, const char Item_type, const char Val, int Nr_vieti, int Vizor, int Acquired):
    urma1(Urma1), urma2(Urma2), urma3(Urma3), urma4(Urma4), item_type(Item_type), val(Val), nr_vieti(Nr_vieti), vizor(Vizor), acquired(Acquired)
{

}

Walk::~Walk()
{

}

TypeI::TypeI(const char Item_type, const char Urma1, const char Urma2, const char Urma3, const char Urma4, const char Val, int Nr_vieti, int Vizor,
             int Acquired) : Walk(Urma1, Urma2, Urma3, Urma4, Item_type, Val, Nr_vieti, Vizor, Acquired)
{

}

TypeII::TypeII(const char Item_type, const char Urma1, const char Urma2, const char Urma3, const char Urma4, const char Val, int Nr_vieti, int Vizor,
               int Acquired) : Walk(Urma1, Urma2, Urma3, Urma4, Item_type, Val, Nr_vieti, Vizor, Acquired)
{

}

TypeIII::TypeIII(const char Item_type, const char Urma1, const char Urma2, const char Urma3, const char Urma4, const char Val, int Nr_vieti, int Vizor, int Acquired)
    :Walk(Urma1, Urma2, Urma3, Urma4, Item_type, Val, Nr_vieti, Vizor, Acquired)
{

}

/*Map::~Map()
{
  int i;
  for(i=0; i<l; i++)
    delete harta[i];
  delete [] harta;
  int*ptr=const_cast<int*>(&l);
    *ptr=0;
ptr=const_cast<int*>(&h);
    *ptr=0;
    char*ptr1=const_cast<char*>(&destinatie);
    *ptr1=' ';
    ptr1=const_cast<char*>(&bomb);
    *ptr1=' ';
    ptr=const_cast<int*>(&nr_capcane);
    *ptr=0;
    ptr=const_cast<int*>(&nr_itemi);
    *ptr=0;
    ptr=const_cast<int*>(&destinatie_x);
    *ptr=0;
    ptr=const_cast<int*>(&destinatie_y);
    *ptr=0;
}
*/
int main()
{
    int raspuns;
    cout<<"Alegeti tipul robotului, 1, 2 sau 3"<<endl;
    cin>>raspuns;
    cout<<endl;
    Map w;
    int x=0, y=0;
int nr_pasi=0;
    int nr_vieti;
    int aux=0;
    switch (raspuns)
    {
    case 1:
    {
        TypeI robot1;
        nr_vieti=robot1.getNr_vieti();
        int inventory=robot1.getInventory();
        int vizor=robot1.getVizor();
        while (aux!=1)
            aux=movementI(robot1, w, x, y, nr_vieti, inventory, vizor, nr_pasi);
        break;
    }
    case 2:
    {
        TypeII robot2;
        nr_vieti=robot2.getNr_vieti();
        int inventory=robot2.getInventory();
        int vizor=robot2.getVizor();
        while (aux!=1)
            aux=movementII(robot2, w, x, y, nr_vieti, inventory, vizor, nr_pasi);
            //cout<<"aux!!!!!!!!!! "<<aux<<endl;
        break;
    }
    case 3:
    {
        TypeIII robot3;
        nr_vieti=robot3.getNr_vieti();
        int inventory=robot3.getInventory();
        int vizor=robot3.getVizor();
        while(aux!=1)
    aux=movementIII(robot3, w, x, y, nr_vieti, inventory, vizor, nr_pasi);
        break;
    }
    }
    return 0;
}

void check_items2(Map obj, int**&warning, int x, int y, int&nr_obiecte, const char item, int cod)
{
    if(obj.harta[x][y]==item)
    {
        int**aux=realocare(warning, nr_obiecte);
        warning=aux;
        warning[nr_obiecte-1][0]=x;
        warning[nr_obiecte-1][1]=y;
        warning[nr_obiecte-1][2]=cod;
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//verifica cu un anumit nr_casute (int vizor, ce poate fi schimbat in constructor) in jurul robotului, si retine intr-o matrice bidimensionala pozitia
//pe linie si coloana a itemului sau destinatiei cu ajutorul functiei check_items2
void check_items1(Map obj, int**&warning, int x, int y, Walk& robot, int &nr_obiecte, const char item, int cod, int vizor)
{
    int i, j;
    for(i=0; i<=vizor; i++)
        for(j=0; j<=vizor; j++)
            //check cadranul 1
            if((x-i>=0) && (y-j>=0))

                check_items2(obj, warning, x-i, y-j, nr_obiecte, item, cod);

    for(i=1; i<=vizor; i++)
        for(j=0; j<=vizor; j++)
            if((x+i<=obj.h-1) && (y+j<=obj.l-1))
                //check cadranul 4
                check_items2(obj, warning, x+i, y+j, nr_obiecte, item, cod);

    for(i=0; i<=vizor; i++)
        for(j=1; j<=vizor; j++)
            if((x-i>=0) && (y+j<=obj.l-1))
                //check cadranul 2
                check_items2(obj, warning, x-i, y+j, nr_obiecte, item, cod);

    for(i=1; i<=vizor; i++)
        for(j=1; j<=vizor; j++)

            if((x+i<=obj.h-1)&&(y-j>=0))

                check_items2(obj, warning, x+i, y-j, nr_obiecte, item, cod);
    //check cadranul 3
}
//----------------------------------------------------------------------------------------------------------
//realoca matricea in care se retine pozitia unui item cu inca o linie de fiecare data cand un nou item e gasit
int** realocare(int**warning, int& nr_obiecte)
{
    int i, j;
    int**aux=new int*[nr_obiecte+1];
    for(i=0; i<3; i++)
        aux[i]=new int;

    for(i=0; i<nr_obiecte; i++)
        for(j=0; j<3; j++)
            aux[i][j]=warning[i][j];         //copie elementele din aux in warning
    int**aux1=warning;
    warning=aux;

    for(i=0; i<nr_obiecte; i++)
        delete aux1[i];
    delete [] aux1;
    nr_obiecte++;
    return warning;
}
//---------------------------------------------------------------------------------------------
//functia intai verifica daca robotul poate fi miscat catre un item, daca nu - il face sa se miste pe linie inainte
//intoarce un int in dependenta daca a avut loc miscarea sau nu, daca e o capcana pe pozitia data, intoarce 0, altfel 1
int Move_on_line_forward(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                         Map& obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    int raspuns=0;
    if(Move_towards_item_line_aux(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                  obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==1)
        return 1;
    else if(Move_towards_item_column_aux(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                         obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==1)
        return 1;
    if(check_bombs(x, y+1, obj)==0)
    {
        obj.harta[x][y+1]=robot.getVal();
        obj.harta[x][y]=robot.getUrma1();
        nr_pasi++;
        y++;
        raspuns=1;
        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
    }
    return raspuns;
}
//-------------------------------------------------------------------------------------
//se printeaza harta la fiecare miscare a robotului
char printare(Map obj, int nr_vieti, int x, int y, int nr_pasi)
{
    int i,j;
    cout<<" ";
    for(i=0; i<obj.h; i++)
        cout<<"- ";
    cout<<endl;
    for(i=0; i<obj.h; i++)
    {
        cout<<"|";
        for(j=0; j<obj.l; j++)
            cout<<obj.harta[i][j]<<" ";
        cout<<"|";
        cout<<endl;
    }
    cout<<" ";
    for(i=0; i<obj.h; i++)
        cout<<"- ";
    cout<<endl;
    cout<<"Pozitia robotului este ("<<x<<","<<y<<")"<<endl;
    cout<<"Numarul de vieti ramase "<<nr_vieti<<"/4"<<endl;
cout<<"Numar pasi: "<<nr_pasi<<endl;
    char raspuns_user;

    cout<<"Doriti sa continuati? (D/N)"<<endl;
    cin>>raspuns_user;
    return raspuns_user;
}
//----------------------------------------------
//functia verifica daca este o capcana pe o anumita pozitie, daca da, intoarce -1, si 0 altfel
int check_bombs(int x, int y, Map obj)
{
    if (obj.harta[x][y]==obj.bomb)
        return -1;
    else
        return 0;
}
//------------------------------------------------------------------------------------------------------
//constructorul pentru harta (harta jocului va fi o matrice de caractere si itemii/capcanele/destinatia sunt plasate random)
Map::Map(const int L, const int H, const char B, int n_bomb, int n_item, const char D, const char item1,
         const char item2, const char item3, const char item4): l(L), h(H), destinatie(D), bomb(B), nr_capcane(n_bomb), nr_itemi(n_item)
{
    srand(time(NULL));
    TypeI robot1;
    TypeII robot2;
    TypeIII robot3;
    Walk aux;
    harta=new char*[l];
    int i,j;
    for(i=0; i<h; i++)
        harta[i]=new char;

    for(i=0; i<h; i++)
        for(j=0; j<l; j++)
            harta[i][j]=' ';      // initializare harta cu spatii libere
    int n, m;
    i=rand()%h;
    j=rand()%l;
    harta[i][j]=destinatie;
    destinatie_x=i;
    destinatie_y=j;
    for(i=0; i<nr_capcane; i++)
    {
        m=rand()%h;
        n=rand()%l;
        if(harta[m][n]==' ')
            harta[m][n]=bomb;
        else
        {
            while(harta[m][n]!=' ')
            {
                m=rand()%h;
                n=rand()%l;
            }
            harta[m][n]=bomb;
        }
    }
    for(i=0; i<nr_itemi; i++)
    {
        n=rand()%h;
        m=rand()%l;
        if(harta[n][m]==' ')
            harta[n][m]=robot1.getItem();
        else
        {
            while(harta[n][m]!=' ')
            {
                n=rand()%h;
                m=rand()%l;
            }
            harta[n][m]=robot1.getItem();
        }
    }
    for(i=0; i<nr_itemi; i++)
    {
        n=rand()%h;
        m=rand()%l;
        if(harta[n][m]==' ')
            harta[n][m]=robot2.getItem();
        else
        {
            while(harta[n][m]!=' ')
            {
                n=rand()%h;
                m=rand()%l;
            }
            harta[n][m]=robot2.getItem();
        }
    }
    for(i=0; i<nr_itemi; i++)
    {
        n=rand()%h;
        m=rand()%l;
        if(harta[n][m]==' ')
            harta[n][m]=robot3.getItem();
        else
        {
            while(harta[n][m]!=' ')
            {
                n=rand()%h;
                m=rand()%l;
            }
            harta[n][m]=robot3.getItem();
        }
    }
    for(i=0; i<nr_itemi; i++)
    {
        n=rand()%h;
        m=rand()%l;
        if(harta[n][m]==' ')
            harta[n][m]=aux.getItem();
        else
        {
            while(harta[n][m]!=' ')
            {
                n=rand()%h;
                m=rand()%l;
            }
            harta[n][m]=aux.getItem();
        }
    }
}
//---------------------------------------------------------------------------------------
//misca robotul cu o casuta pe coloana jos
int Move_on_column_down(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                        Map&obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    int raspuns=0;
    if(Move_towards_item_column_aux(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                    obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==1)
        return 1;
    else if(Move_towards_item_line_aux(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                       obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==1)
        return 1;
    if(check_bombs(x+1, y, obj)==0)
    {
        obj.harta[x+1][y]=robot.getVal();
        obj.harta[x][y]=robot.getUrma2();
        nr_pasi++;
        x++;
        raspuns=1;
        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
    }
    return raspuns;
}
//-------------------------------------------------------------------------------------
//combinatie de miscari pentru robotul de tip 1 pentru prima faza, (acesta isi schimba directia de fiecare data cand intalneste un perete
//un total de 4 miscari (8 combinatii)), daca o miscare nu e posibila din cauza capcanelor(functia returneaza 0), se incearca alta,
//iar daca nici una nu e posibila, robotul va mi miscat dupa incercarea initiala, si pierde o viata daca nimereste intr-o capcana
void Combinatie_tipI_1(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                       Map& obj, Walk& robot, int& x, int& y, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(y==obj.l-1 || obj.harta[x][y+1]==robot.getUrma1() ||
            Move_on_line_forward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                 obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
    {
        if(x==obj.h-1 || obj.harta[x+1][y]==robot.getUrma2() ||
                Move_on_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                    obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
        {
            if(y==0 || obj.harta[x][y-1]==robot.getUrma1() ||
                    Move_on_line_backward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                          obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
            {
                if(x==0 || obj.harta[x-1][y]==robot.getUrma2() ||
                        Move_on_column_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                          obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                {
                    if(y!=obj.l-1)
                    {
                        if(check_bombs(x, y+1, obj)==-1)
                            nr_vieti--;
                        obj.harta[x][y+1]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma1();
                        nr_pasi++;
                        y++;
                        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    }
                }
            }
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------
//primele doua combinatii sunt pentru miscarea de 2 pe linie inainte, 3 pe coloana in jos, daca nu exista obstacole
//am implementat aceasta sub forma de combinatii, pentru ca robotul sa nu stea pe loc mai multe ture daca miscarea nu e posibila
//toate cele 8 combinatii pentru tipul 1 difera
void Combinatie_tipI_2(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                       Map& obj, Walk& robot, int& x, int& y, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(x==obj.h-1 || obj.harta[x+1][y]==robot.getUrma2() ||
            Move_on_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
    {
        if(y==obj.l-1 || obj.harta[x][y+1]==robot.getUrma1() ||
                Move_on_line_forward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                     obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
        {
            if(x==0 || obj.harta[x-1][y]==robot.getUrma2() ||
                    Move_on_column_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                      obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
            {
                if(y==0 || obj.harta[x][y-1]==robot.getUrma1() ||
                        Move_on_line_backward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                              obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                {
                    if(x!=obj.h-1)
                    {
                        if(check_bombs(x+1, y, obj)==-1)
                            nr_vieti--;
                        obj.harta[x+1][y]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma1();
                        nr_pasi++;
                        x++;
                        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    }
                }
            }
        }
    }
}
//--------------------------------------------------------------------------------------------
//combinatiile 3 si 4 sunt pentru miscarea dupa ce a fost intalnit primul perete (cel de jos), robotul se va misca 2 pe linie inainte si 3 pe
//coloana sus
void Combinatie_tipI_3(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                       Map& obj, Walk& robot, int& x, int& y, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(y==obj.l-1 || obj.harta[x][y+1]==robot.getUrma1() ||
            Move_on_line_forward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                 obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
    {
        if(x==0 || obj.harta[x-1][y]==robot.getUrma2() ||
                Move_on_column_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                  obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
        {
            if(y==0||obj.harta[x][y-1]==robot.getUrma1() ||
                    Move_on_line_backward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                          obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
            {
                if(x==obj.h-1||obj.harta[x+1][y]==robot.getUrma2() ||
                        Move_on_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                            obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                {
                    if(y!=obj.l-1)
                    {
                        if(check_bombs(x, y+1, obj)==-1)
                            nr_vieti--;
                        obj.harta[x][y+1]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma1();
                        nr_pasi++;
                        y++;
                        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    }
                }
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------
void Combinatie_tipI_4(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                       Map& obj, Walk& robot, int& x, int& y, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(x==0 || obj.harta[x-1][y]==robot.getUrma2() ||
            Move_on_column_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
    {
        if(y==obj.l-1 || obj.harta[x][y+1]==robot.getUrma1() ||
                Move_on_line_forward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                     obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
        {
            if(x==obj.h-1 || obj.harta[x+1][y]==robot.getUrma2() ||
                    Move_on_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                        obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
            {
                if(y==0 || obj.harta[x][y-1]==robot.getUrma2() ||
                        Move_on_line_backward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                              obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                {
                    if(x!=0)
                    {
                        if(check_bombs(x-1, y, obj)==-1)
                            nr_vieti--;
                        obj.harta[x-1][y]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma1();
                        nr_pasi++;
                        x--;
                        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    }
                }
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------
//combinatiile 5 si 6 sunt pentru miscarea de dupa ce a fost intalnit al doilea perete (dreapta)
//robotul se va misca 2 pe linie inapoi, 3 pe coloana sus
void Combinatie_tipI_5(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                       Map& obj, Walk& robot, int& x, int& y, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(y==0 || obj.harta[x][y-1]==robot.getUrma1() ||
            Move_on_line_backward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                  obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
    {
        if(x==0 || obj.harta[x-1][y]==robot.getUrma2() ||
                Move_on_column_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                  obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
        {
            if(y==obj.l-1 || obj.harta[x][y+1]==robot.getUrma1() ||
                    Move_on_line_forward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                         obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
            {
                if(x==obj.h-1 || obj.harta[x+1][y]==robot.getUrma2() ||
                        Move_on_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                            obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                {
                    if(y!=0)
                    {
                        if(check_bombs(x, y-1, obj)==-1)
                            nr_vieti--;
                        obj.harta[x][y-1]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma1();
                        nr_pasi++;
                        y--;
                        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    }
                }
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void Combinatie_tipI_6(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                       Map& obj, Walk& robot, int& x, int& y, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(x==0 || obj.harta[x-1][y]==robot.getUrma2() ||
            Move_on_column_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
    {
        if(y==0 || obj.harta[x][y-1]==robot.getUrma1() ||
                Move_on_line_backward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                      obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
        {
            if(x==obj.h-1 || obj.harta[x+1][y]==robot.getUrma2() ||
                    Move_on_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                        obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
            {
                if(y==obj.l-1 || obj.harta[x][y+1]==robot.getUrma1() ||
                        Move_on_line_forward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                             obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                {
                    if(x!=0)
                    {
                        if(check_bombs(x-1, y, obj)==-1)
                            nr_vieti--;
                        obj.harta[x-1][y]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma1();
                        nr_pasi++;
                        x--;
                        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    }
                }
            }
        }
    }
}
//combinatiile 7 si 8 sunt pentru ultimul tip de miscare, dupa ce s-a ajuns la peretele de sus si pana se ajunge la peretele din stanga
//robotul se va misca 2 pe linie inapoi si 3 pe coloana in jos, apoi va relua toate combinatiile de la inceput in caz ca nu se ajunge la destinatie intre timp
void Combinatie_tipI_7(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                       Map& obj, Walk& robot, int& x, int& y, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(y==0 || obj.harta[x][y-1]==robot.getUrma1() ||
            Move_on_line_backward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                  obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
    {
        if(x==obj.h-1 || obj.harta[x+1][y]==robot.getUrma2() ||
                Move_on_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                    obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
        {
            if(y==obj.l-1 || obj.harta[x][y+1]==robot.getUrma1() ||
                    Move_on_line_forward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                         obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
            {
                if(x==0 || obj.harta[x-1][y]==robot.getUrma2() ||
                        Move_on_column_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                          obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                {
                    if(y!=0)
                    {
                        if(check_bombs(x, y-1, obj)==-1)
                            nr_vieti--;
                        obj.harta[x][y-1]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma1();
                        nr_pasi++;
                        y--;
                        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    }
                }
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------------------
void Combinatie_tipI_8(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                       Map& obj, Walk& robot, int& x, int& y, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(x==obj.h-1 || obj.harta[x+1][y]==robot.getUrma2() ||
            Move_on_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
    {
        if(y==0 || obj.harta[x][y-1]==robot.getUrma1() ||
                Move_on_line_backward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                      obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
        {
            if(x==0 || obj.harta[x-1][y]==robot.getUrma2() ||
                    Move_on_column_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                      obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
            {
                if(y==obj.l-1 || obj.harta[x][y+1]==robot.getUrma1() ||
                        Move_on_line_forward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                             obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                {
                    if(x!=obj.h-1)
                    {
                        if(check_bombs(x+1, y, obj)==-1)
                            nr_vieti--;
                        obj.harta[x+1][y]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma1();
                        nr_pasi++;
                        x++;
                        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    }
                }
            }
        }
    }
}
//----------------------------------------------------------------------------------
//se dezaloca memoria alocata de functia alocare, pentru matricile ce contin pozitiile itemilor gasiti
//dupa fiecare miscare, acestea se actualizeaza, robotul verificand din nou in jurul sau
void dezalocare(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int&nr_obiecteD, int&nr_obiecte, int&nr_obiecte_aux)
{
   int i;
   for(i=0; i<nr_obiecteD; i++)
        delete verif_destinatie[i];
   delete [] verif_destinatie;
   nr_obiecteD=0;

   for(i=0; i<nr_obiecte; i++)
        delete verif_item[i];
   delete [] verif_item;
   nr_obiecte=0;

   for(i=0; i<nr_obiecte_aux; i++)
        delete verif_item_aux[i];
   delete [] verif_item_aux;
   nr_obiecte_aux=0;
}
//----------------------------------------------------------------------------------------------------------
//functia de miscare pentru robotul de tip 1, care returneaza 1 daca s-a ajuns la destinatie, 0 altfel
//pentru fiecare dintre cele 4 miscari va exista un while diferit, si cate un break daca se ajunge la vreun perete (x-linie intalneste 0 sau 14,
//analog pentru y-coloana)
int movementI(Walk& robot, Map &obj, int&x, int&y, int& nr_vieti, int&inventory, int&vizor, int&nr_pasi)
{
    int i, j;
    Walk aux;
    obj.harta[x][y]=robot.getVal();
    printare(obj, nr_vieti, x, y, nr_pasi);
    int destination=0;
    char raspuns_user=' ';

    int**verif_destinatie=NULL;
    int**verif_item=NULL;
    int**verif_item_aux=NULL;

    int nr_obiecteD=0;
    int nr_obiecte=0;
    int nr_obiecte_aux=0;
//------------------------------------------------I
    while((x<obj.h) && (y<obj.l))
    {
        if(x>=obj.h-1 || y>=obj.l-1)
            break;
        for(i=0; i<2; i++)
        {
            if(x>=obj.h-1 || y>=obj.l-1)
                break;
    //functia va returna (prin referinta) matricele cu pozitiile itemilor gasiti si numarul de itemi
    //itemii vor fi de tip compatibil doar cu robotul dat si de tip universal (pentru toate tipurile de roboti)
            Move_towards_item_general(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux, robot.getItem(),
                                      aux.getItem(), obj, x, y, robot, vizor);

            Combinatie_tipI_1(verif_destinatie, verif_item,
    verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux, obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);

    dezalocare(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux);

            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return 1;
            }
            if(nr_vieti==0)
            {
                cout<<"Sfarsit de joc. Corelatie dintre numar vieti si numar capcane nu a facut castigul posibil.";
                return 1;
            }
            if(raspuns_user=='N')
            {
                cout<<"Sfarsit de joc "<<endl;
                return 1;
            }
            else if(raspuns_user=='D')
                continue;
        }
        for(j=0; j<3; j++)
        {
            if(x>=obj.h-1||y>=obj.l-1)
                break;
            Move_towards_item_general(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux, robot.getItem(),
                                      aux.getItem(), obj, x, y, robot, vizor);

            Combinatie_tipI_2(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
                              //se dezaloca memoria alocata matricilor cu itemi
            dezalocare(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux);

            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return 1;
            }
            if(nr_vieti==0)
            {
                cout<<"Sfarsit de joc. Corelatie dintre numar vieti si numar capcane nu a facut castigul posibil.";
                return 1;
            }
            if(raspuns_user=='N')
            {
                cout<<"Sfarsit de joc "<<endl;
                return 1;
            }
            else if(raspuns_user=='D')
                continue;
        }
    }
    //---------------------------------------------------II
    while((x<obj.h)&&(x>=0)&&(y<obj.l))
    {
        if(y>=obj.l-1)
            break;
        for(i=0; i<2; i++)
        {
            if(y>=obj.l-1)
                break;
            Move_towards_item_general(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux, robot.getItem(),
                                      aux.getItem(), obj, x, y, robot, vizor);

            Combinatie_tipI_3(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);

           dezalocare(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux);

            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return 1;
            }
            if(nr_vieti==0)
            {
                cout<<"Sfarsit de joc. Corelatie dintre numar vieti si numar capcane nu a facut castigul posibil.";
                return 1;
            }
            if(raspuns_user=='N')
            {
                cout<<"Sfarsit de joc "<<endl;
                return 1;
            }
            else if(raspuns_user=='D')
                continue;
        }
        for(j=0; j<3; j++)
        {
            if(x==0)
                break;
            Move_towards_item_general(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux, robot.getItem(),
                                      aux.getItem(), obj, x, y, robot, vizor);

            Combinatie_tipI_4(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);

            dezalocare(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux);

            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return 1;
            }
            if(nr_vieti==0)
            {
                cout<<"Sfarsit de joc. Corelatie dintre numar vieti si numar capcane nu a facut castigul posibil.";
                return 1;
            }
            if(raspuns_user=='N')
            {
                cout<<"Sfarsit de joc "<<endl;
                return 1;
            }
            else if(raspuns_user=='D')
                continue;
        }
    }
    //------------------------------------------------------III-
    while(x>=0 && y>=0)
    {
        if(x==0 || y==0)
            break;
        for(i=0; i<2; i++)
        {
            if(y==0)
                break;
            Move_towards_item_general(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux, robot.getItem(),
                                      aux.getItem(), obj, x, y, robot, vizor);

            Combinatie_tipI_5(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);

            dezalocare(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux);

            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return 1;
            }
            if(nr_vieti==0)
            {
                cout<<"Sfarsit de joc. Corelatie dintre numar vieti si numar capcane nu a facut castigul posibil."<<endl;
                return 1;
            }
            if(raspuns_user=='N')
            {
                cout<<"Sfarsit de joc "<<endl;
                return 1;
            }
            else if(raspuns_user=='D')
                continue;
        }
        for(j=0; j<3; j++)
        {
            if(x==0)
                break;
            Move_towards_item_general(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux, robot.getItem(),
                                      aux.getItem(), obj, x, y, robot, vizor);

            Combinatie_tipI_6(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);

            dezalocare(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux);

            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return 1;
            }
            if(nr_vieti==0)
            {
                cout<<"Sfarsit de joc. Corelatie dintre numar vieti si numar capcane nu a facut castigul posibil."<<endl;
                return 1;
            }
            if(raspuns_user=='N')
            {
                cout<<"Sfarsit de joc "<<endl;
                return 1;
            }
            else if(raspuns_user=='D')
                continue;
        }
    }
    //-------------------------------------IV
    while(x<obj.h && y>=0)
    {
        if(x==obj.h-1 || y==0)
            break;
        for(i=0; i<2; i++)
        {
            if(y==0)
                break;
            Move_towards_item_general(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux, robot.getItem(),
                                      aux.getItem(), obj, x, y, robot, vizor);

            Combinatie_tipI_7(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);

            dezalocare(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux);

            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return 1;
            }
            if(nr_vieti==0)
            {
                cout<<"Sfarsit de joc. Corelatie dintre numar vieti si numar capcane nu a facut castigul posibil."<<endl;
                return 1;
            }
            if(raspuns_user=='N')
            {
                cout<<"Sfarsit de joc "<<endl;
                return 1;
            }
            else if(raspuns_user=='D')
                continue;
        }
        for(j=0; j<3; j++)
        {
            if(x==obj.h-1)
                break;
            Move_towards_item_general(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux, robot.getItem(),
                                      aux.getItem(), obj, x, y, robot, vizor);

            Combinatie_tipI_8(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);

            dezalocare(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux);

            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return 1;
            }
            if(nr_vieti==0)
            {
                cout<<"Sfarsit de joc. Corelatie dintre numar vieti si numar capcane nu a facut castigul posibil."<<endl;
                return 1;
            }
            if(raspuns_user=='N')
            {
                cout<<"Sfarsit de joc "<<endl;
                return 1;
            }
            else if(raspuns_user=='D')
                continue;
        }
    }
    return 0;
}
//-----------------------------------------------------------------------------------------------------------
//functia misca robotul pe coloana sus, cu un spatiu
int Move_on_column_up(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                      Map&obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    int raspuns=0;
    if(Move_towards_item_column_aux(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                    obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==1)
        return 1;
    else if(Move_towards_item_line_aux(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                       obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==1)
        return 1;

    if(check_bombs(x-1, y, obj)==0)
    {
        obj.harta[x-1][y]=robot.getVal();
        obj.harta[x][y]=robot.getUrma2();
        nr_pasi++;
        x--;
        raspuns=1;
        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
    }
    return raspuns;
}
//--------------------------------------------------------------------------------------------------
//se verifica daca e posibila miscarea catre un item, daca da, se returneaza 1 (pentru ca robotul se poate misca o singura data pe runda)
//altfel, se misca robotul pe linie inapoi
int Move_on_line_backward(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                          Map&obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    int raspuns=0;
    if(Move_towards_item_line_aux(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                  obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==1)
        return 1;
    else if(Move_towards_item_column_aux(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                         obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==1)
        return 1;

    if(check_bombs(x, y-1, obj)==0)
    {
        obj.harta[x][y-1]=robot.getVal();
        obj.harta[x][y]=robot.getUrma1();
        nr_pasi++;
        y--;
        raspuns=1;
        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
    }
    return raspuns;
}
//-------------------------------------------------------------------------------------
//functiile de check_path sunt pentru robotul de tip 2 si 3, care pot merge pe diagonala, intrucat acestia au nevoie de cel putin 2 casute libere
//pentru o astfel de miscare
//functiile verifica daca robotul e blocat intre fie 2 capcane, fie o capcana si un perete, daca da, acestuia i se asigura "evaziunea"
//prin miscarea pe linie sau coloana
int check_path_column_down(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                           Map& obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(x==obj.h-1) return 0;
    int raspuns=0;
    if ((check_bombs(x+1, y, obj)==0) && ((y!=0 && y!=obj.l-1 && (check_bombs(x+1, y+1, obj)==-1) && (check_bombs(x+1, y-1, obj)==-1))
                || (y==0 && (check_bombs(x+1, y+1, obj)==-1)) || (y==obj.l-1 && (check_bombs(x+1, y-1, obj)==-1))))
    {
        Move_on_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                            obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        raspuns=1;
    }
    return raspuns;
}
//--------------------------------------------------------------------------------------------------------------------------------
//daca miscarea a avut loc, se returneaza 1
int check_path_line_forward(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                Map& obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{ if(y==obj.l-1) return 0;
    int raspuns=0;
    if ((check_bombs(x, y+1, obj)==0)&&((x==0 && (check_bombs(x+1, y+1, obj)==-1)) || (x!=0 && x!=obj.h-1 &&
        (check_bombs(x+1, y+1, obj)==-1) && (check_bombs(x-1, y+1, obj)==-1)) || (x==obj.h-1 && (check_bombs(x-1, y+1, obj)==-1))))
    {
        Move_on_line_forward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                             obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        raspuns=1;
    }
    return raspuns;
}
//---------------------------------------------------------------------------------------------------------------------------------
int check_path_line_backward(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                             Map& obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{   if(y==0) return 0;
    int raspuns=0;
    if ((check_bombs(x, y-1, obj)==0)&&((x==0 && (check_bombs(x+1, y-1, obj)==-1)) || (x!=0 && x!=obj.h-1 && (check_bombs(x+1, y-1, obj)==-1)
                                        && (check_bombs(x-1, y-1, obj)==-1)) || (x==obj.h-1 && (check_bombs(x-1, y-1, obj)==-1))))
    {
        Move_on_line_backward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        raspuns=1;
    }
    return raspuns;
}
//---------------------------------------------------------------------------------------------------------------------------
//combinatii pentru robotul de tip 2 si 3, pentru miscarea pe diagonala
//primele doua sunt pentru miscarea inainte (fie jos sau sus), celelalte pentru miscarea inapoi, daca se ajunge la perete
void Combinatie_tipII_1(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                        Map& obj, Walk& robot, int& x, int& y, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(check_path_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
    {
        if(check_path_line_forward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                   obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
        {
            if (x==0 || y==obj.l-1 || obj.harta[x-1][y+1]==robot.getUrma3() ||
                    Move_on_the_diagonal_forward_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                                    obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
            {
                if(x==obj.h-1 || y==obj.l-1 || obj.harta[x+1][y+1]==robot.getUrma4() ||
                        Move_on_the_diagonal_forward_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                {
                    if(x==0 || y==0 || obj.harta[x-1][y-1]==robot.getUrma4() ||
                            Move_on_the_diagonal_backward_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                    obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                    {
                        if(y==0 || x==obj.h-1 || obj.harta[x+1][y-1]==robot.getUrma3() ||
                                Move_on_the_diagonal_backward_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                    obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                        {
                            if(x!=0&&y!=obj.l-1)
                            {
                                if(check_bombs(x-1, y+1, obj)==-1)
                                    nr_vieti--;
                                obj.harta[x-1][y+1]=robot.getVal();
                                obj.harta[x][y]=robot.getUrma3();
                                x--;
                                y++;
                                nr_pasi++;
                                raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                            }
                            else if(x!=obj.h-1&&y!=obj.l-1)
                            {
                                if(check_bombs(x+1, y+1, obj)==-1)
                                    nr_vieti--;
                                obj.harta[x+1][y+1]=robot.getVal();
                                obj.harta[x][y]=robot.getUrma3();
                                nr_pasi++;
                                x++;
                                y++;
                                raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                            }
                        }
                    }
                }
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------------------
void Combinatie_tipII_2(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                        Map& obj, Walk& robot, int& x, int& y, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(check_path_line_forward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                               obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
    {
        if(check_path_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                  obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
        {
            if(x==obj.h-1 || y==obj.l-1 || obj.harta[x+1][y+1]==robot.getUrma4() ||
                    Move_on_the_diagonal_forward_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                            obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
            {
                if(x==0 || y==obj.l-1 || obj.harta[x-1][y+1]==robot.getUrma3() ||
                        Move_on_the_diagonal_forward_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                                        obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                {
                    if(y==0 || x==obj.h-1 || obj.harta[x+1][y-1]==robot.getUrma3() ||
                            Move_on_the_diagonal_backward_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                    obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                    {
                        if(x==0 || y==0 || obj.harta[x-1][y-1]==robot.getUrma4() ||
                                Move_on_the_diagonal_backward_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                        obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                        {
                            if(x!=obj.h-1 && y!=obj.l-1)
                            {
                                if(check_bombs(x+1, y+1, obj)==-1)
                                    nr_vieti--;
                                obj.harta[x+1][y+1]=robot.getVal();
                                obj.harta[x][y]=robot.getUrma3();
                                nr_pasi++;
                                x++;
                                y++;
                                raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                            }
                        }
                    }
                }
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------
void Combinatie_tipII_3(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                        Map& obj, Walk& robot, int& x, int& y, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(check_path_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
    {
        if(check_path_line_backward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                    obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
        {
            if(x==0 || y==0 || obj.harta[x-1][y-1]==robot.getUrma4() ||
                    Move_on_the_diagonal_backward_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                            obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
            {
                if(x==obj.h-1 || y==0 || obj.harta[x+1][y-1]==robot.getUrma3() ||
                        Move_on_the_diagonal_backward_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                {
                    if(y==obj.l-1 || x==0 || obj.harta[x-1][y+1]==robot.getUrma3() ||
                            Move_on_the_diagonal_forward_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                                            obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                    {
                        if(y==obj.l-1 || x==obj.h-1 || obj.harta[x+1][y+1]==robot.getUrma4() ||
                                Move_on_the_diagonal_forward_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                        obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                        {
                            if(x!=0 && y!=0)
                            {
                                if(check_bombs(x-1, y-1, obj)==-1)
                                    nr_vieti--;
                                obj.harta[x-1][y-1]=robot.getVal();
                                obj.harta[x][y]=robot.getUrma3();
                                nr_pasi++;
                                x--;
                                y--;
                                raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                            }
                        }
                    }
                }
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------------------
void Combinatie_tipII_4(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                        Map& obj, Walk& robot, int& x, int& y, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    if(check_path_line_backward(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
    {
        if(check_path_column_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                  obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
        {
            if(x==obj.h-1 || y==0 || obj.harta[x+1][y-1]==robot.getUrma3() ||
                    Move_on_the_diagonal_backward_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                            obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
            {
                if(x==0 || y==0 || obj.harta[x-1][y-1]==robot.getUrma4() ||
                        Move_on_the_diagonal_backward_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                {
                    if(x==obj.h-1 || y==obj.l-1 || obj.harta[x+1][y+1]==robot.getUrma4() ||
                            Move_on_the_diagonal_forward_down(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                    obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                    {
                        if(x==0 || y==obj.l-1 || obj.harta[x-1][y+1]==robot.getUrma3() ||
                                Move_on_the_diagonal_forward_up(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                                                obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==0)
                        {
                            if(y!=0 && x!=obj.h-1)
                            {
                                if(check_bombs(x+1, y-1, obj)==-1)
                                    nr_vieti--;
                                obj.harta[x+1][y-1]=robot.getVal();
                                obj.harta[x][y]=robot.getUrma3();
                                nr_pasi++;
                                x++;
                                y--;
                                raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                            }
                        }
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------------
//functia de miscare pentru robotul de tip 2, exista 2 while-uri, unul pentru miscarea inainte, altul-inapoi
int movementII(Walk& robot, Map &obj, int& x, int& y, int& nr_vieti, int&inventory, int&vizor, int&nr_pasi)
{
    int**verif_destinatie=NULL;
    int**verif_item=NULL;
    int**verif_item_aux=NULL;

    int nr_obiecteD=0;
    int nr_obiecte=0;
    int nr_obiecte_aux=0;
    Walk aux_robot;

    srand(time(NULL));
    char**harta=obj.getHarta();
    harta[x][y]=robot.getVal();
    printare(obj, nr_vieti, x, y, nr_pasi);
    int destination=0;
    char raspuns_user=' ';
    while(x>=0 && y>=0 && x<obj.h && y<obj.l)
    {
        if(y==obj.l-1)
            break;
        int aux=rand();
        int aux1=aux%2;

        Move_towards_item_general(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux, robot.getItem(),
                              aux_robot.getItem(), obj, x, y, robot, vizor);
        if(aux1==0)
        {
            Combinatie_tipII_1(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                               obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        }
        else if(aux1==1 && x!=obj.h-1)
        {
            Combinatie_tipII_2(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                               obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        }
        dezalocare(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux);
        if(destination==1)
        {
            cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
            return 1;
        }
        if(nr_vieti==0)
            {
                cout<<"Sfarsit de joc. Corelatie dintre numar vieti si numar capcane nu a facut castigul posibil.";
                return 1;
            }
        if(raspuns_user=='N')
        {
            cout<<"Sfarsit de joc "<<endl;
            return 1;
        }
        else if(raspuns_user=='D')
            continue;
    }
    while(x>=0 && y>=0 && x<obj.h && y<obj.l)
    {
        if(y==0)
            break;
        int aux=rand();
        int aux1=aux%2;
         Move_towards_item_general(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux, robot.getItem(),
                              aux_robot.getItem(), obj, x, y, robot, vizor);
        if(aux1==0 && x!=0)
        {
            Combinatie_tipII_3(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                               obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        }
        else if(aux1==1 && x!=obj.h-1)
        {
            Combinatie_tipII_4(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                               obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        }
        dezalocare(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux);
        if(destination==1)
        {
            cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
            return 1;
        }
        if(nr_vieti==0)
            {
                cout<<"Sfarsit de joc. Corelatie dintre numar vieti si numar capcane nu a facut castigul posibil.";
                return 1;
            }
        if(raspuns_user=='N')
        {
            cout<<"Sfarsit de joc "<<endl;
            return 1;
        }
        else if(raspuns_user=='D')
            continue;
    }
    return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------
//functia misca robotul pe diagonala sus
int Move_on_the_diagonal_forward_up(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                                    Map&obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int &inventory, int&vizor, int&nr_pasi)
{
    int raspuns=0;
    if(Move_towards_item_diagonal_aux(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                      obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==1)
        return 1;

    if(check_bombs(x-1, y+1, obj)==0)
    {
        obj.harta[x-1][y+1]=robot.getVal();
        obj.harta[x][y]=robot.getUrma3();
        nr_pasi++;
        x--;
        y++;
        raspuns=1;
        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
    }
    return raspuns;
}
//----------------------------------------------------------------------------------------------------------
//functia misca robotul pe diagonala jos
int Move_on_the_diagonal_forward_down(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                                      Map&obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    int raspuns=0;
    if(Move_towards_item_diagonal_aux(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                      obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==1)
        return 1;
    if(check_bombs(x+1, y+1, obj)==0)
    {
        obj.harta[x+1][y+1]=robot.getVal();
        obj.harta[x][y]=robot.getUrma4();
        nr_pasi++;
        x++;
        y++;
        raspuns=1;
        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
    }
    return raspuns;
}
//----------------------------------------------------------------------------------------------------------
//functia actualizeaza matricile pentru itemi prin intermediul check_items1
void Move_towards_item_general(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                              const char item, const char item_aux, Map obj, int x, int y, Walk& robot, int vizor)
{
    check_items1(obj, verif_destinatie, x, y, robot, nr_obiecteD, obj.destinatie, 1, vizor);
    check_items1(obj, verif_item, x, y, robot, nr_obiecte, item, 2, vizor);
    check_items1(obj, verif_item_aux, x, y, robot, nr_obiecte_aux, item_aux, 3, vizor);
}
//----------------------------------------------------------------------------------------------------------
//functia misca robotul catre fiecare tip de item pe rand, in primul rand se verifica daca robotul vede destinatia
//daca nu, se verifica daca vede itemul ce i se potriveste ca tip, apoi itemul universal
//acestea au loc dupa prioritate, ex. daca e vazuta destinatia, robotul nu va mai merge catre itemi
int Move_towards_item_column_aux(int**verif_destinatie, int**verif_item, int**verif_item_aux, int nr_obiecteD, int nr_obiecte, int nr_obiecte_aux,
                                 Map& obj, int& x, int& y, Walk &robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    int answer=0;
    answer=Move_towards_item_column(verif_destinatie, nr_obiecteD, 1, obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
    if((answer==0)&&(inventory==0))
        answer=Move_towards_item_column(verif_item, nr_obiecte, 2, obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
    if((answer==0)&&(inventory==0))
        answer=Move_towards_item_column(verif_item_aux, nr_obiecte_aux, 3, obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
    return answer;
}
//-------------------------------------------------------------------------------------------------------------
//robotul va fi miscat catre item sau destinatie in dependenta de pozitia acestora din matrici
//daca robotul a gasit deja un item ce i se potriveste ca tip, nu va mai merge dupa altele (se verifica prin variabila inventory, care e 0
//daca nu s-a gasit un item, si 1 altfel)
//aceasta nu se aplica itemilor universali
int Move_towards_item_column(int**warning, int nr_obiecte, int cod, Map&obj, int& x, int& y, Walk& robot, int& destination,
                             int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    TypeI robot1;
    TypeII robot2;
    TypeIII robot3;
    Walk robot_aux;
    int i;
    int answer=0;
    int aux=0;
    int aux2=0;
    for(i=0; i<nr_obiecte; i++)
    {
        if(warning[i][2]==cod)
        {
            if(warning[i][0]>x)
            {
                if(check_bombs(x+1, y, obj)==0)
                {
                    if(obj.harta[x+1][y]==obj.destinatie)
                        destination=1;
                    else if(obj.harta[x+1][y]==robot.getItem())
                    {
                        inventory=1;
                        aux=1;
                    }
                    else if(obj.harta[x+1][y]==robot_aux.getItem())
                        aux2=1;
                    obj.harta[x+1][y]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma2();
                    nr_pasi++;
                    x++;
                    answer=1;
                    raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    if(aux==1&&(robot.getItem()==robot1.getItem()))
                    {
                        efect_item1(x, y, obj, inventory, robot, nr_vieti, nr_pasi);
                        return 1;
                    }
                    else if(aux==1&&(robot.getItem()==robot2.getItem()))
                    {
                        efect_item2(x, y, obj, robot, nr_vieti, nr_pasi);
                        return 1;
                    }
                    else if(aux==1&&(robot.getItem()==robot3.getItem()))
                    {
                        efect_item3(vizor);
                        return 1;
                    }
                    else if(aux2==1)
                    {
                        efect_item_universal(nr_vieti);
                        return 1;
                    }
                }
            }
            else if(warning[i][0]<x)
            {
                if(check_bombs(x-1, y, obj)==0)
                {
                    if(obj.harta[x-1][y]==obj.destinatie)
                        destination=1;
                    else if(obj.harta[x-1][y]==robot.getItem())
                    {
                        inventory=1;
                        aux=1;
                    }
                    else if(obj.harta[x-1][y]==robot_aux.getItem())
                        aux2=1;
                    obj.harta[x-1][y]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma2();
                    nr_pasi++;
                    x--;
                    answer=1;
                    raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    if(aux==1&&(robot.getItem()==robot1.getItem()))
                    {
                        efect_item1(x, y, obj, inventory, robot, nr_vieti, nr_pasi);
                        return 1;
                    }
                    else if(aux==1&&(robot.getItem()==robot2.getItem()))
                    {
                        efect_item2(x, y, obj, robot, nr_vieti, nr_pasi);
                        return 1;
                    }
                    else if(aux==1&&(robot.getItem()==robot3.getItem()))
                    {
                        efect_item3(vizor);
                        return 1;
                    }
                    else if(aux2==1)
                    {
                        efect_item_universal(nr_vieti);
                        return 1;
                    }
                }
            }
        }
    }
    return answer;
}
//----------------------------------------------------------------------------------------------------------------------------
//se va misca robotul catre item pe linie, analog cu functia move_towards_item_column_aux
int Move_towards_item_line_aux(int** verif_destinatie, int** verif_item, int** verif_item_aux, int nr_obiecteD, int nr_obiecte, int nr_obiecte_aux,
                               Map&obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    int answer=0;
    answer=Move_towards_item_line(verif_destinatie, nr_obiecteD, 1, obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
    if((answer==0)&&(inventory==0))
        answer=Move_towards_item_line(verif_item, nr_obiecte, 2, obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
    if((answer==0)&&(inventory==0))
        answer=Move_towards_item_line(verif_item_aux, nr_obiecte_aux, 3, obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
    return answer;
}
//---------------------------------------------------------------------------------------------------------
//functia e chemata daca robotul de tip 1 a gasit un item care i se potriveste
//aceasta il va misca cu 2 spatii mai aproape de destinatie (sau 1 spatiu daca nu e posibil cu 2), chiar daca robotul nu vede destinatia
void efect_item1(int&x, int&y, Map&obj, int&inventory, Walk& robot, int nr_vieti, int nr_pasi)
{
    cout<<"Robotul a gasit un item care sa il teleporteze cu 2 spatii mai aproape de destinatie. "<<endl;
    if((obj.destinatie_x>x+1)&&(check_bombs(x+2, y, obj)==0))
    {
        obj.harta[x+2][y]=robot.getVal();
        obj.harta[x][y]=robot.getUrma2();
        x+=2;
        printare(obj, nr_vieti, x, y, nr_pasi);
        return;
    }
    else if((obj.destinatie_x<x-1)&&(check_bombs(x-2, y, obj)==0))
    {
        obj.harta[x-2][y]=robot.getVal();
        obj.harta[x][y]=robot.getUrma2();
        x-=2;
        printare(obj, nr_vieti, x, y, nr_pasi);
        return;
    }
    else if((obj.destinatie_y>y+1)&&(check_bombs(x, y+2, obj)==0))
    {
        obj.harta[x][y+2]=robot.getVal();
        obj.harta[x][y]=robot.getUrma1();
        y+=2;
        printare(obj, nr_vieti, x, y, nr_pasi);
        return;
    }
    else if((obj.destinatie_y<y-1)&&(check_bombs(x, y-2, obj)==0))
    {
        obj.harta[x][y-2]=robot.getVal();
        obj.harta[x][y]=robot.getUrma2();
        y-=2;
        printare(obj, nr_vieti, x, y, nr_pasi);
        return;
    }
    else if((obj.destinatie_x>x)&&(check_bombs(x+1, y, obj)==0))
    {
        obj.harta[x+1][y]=robot.getVal();
        obj.harta[x][y]=robot.getUrma2();
        x++;
        printare(obj, nr_vieti, x, y, nr_pasi);
        return;
    }
    else if((obj.destinatie_x<x)&&(check_bombs(x-1, y, obj)==0))
    {
        obj.harta[x-1][y]=robot.getVal();
        obj.harta[x][y]=robot.getUrma2();
        x--;
        printare(obj, nr_vieti, x, y, nr_pasi);
        return;
    }
    else if((obj.destinatie_y>y)&&(check_bombs(x, y+1, obj)==0))
    {
        obj.harta[x][y+1]=robot.getVal();
        obj.harta[x][y]=robot.getUrma1();
        y++;
        printare(obj, nr_vieti, x, y, nr_pasi);
        return;
    }
    else if((obj.destinatie_y<y)&&(check_bombs(x, y-1, obj)==0))
    {
        obj.harta[x][y-1]=robot.getVal();
        obj.harta[x][y]=robot.getUrma2();
        y--;
        printare(obj, nr_vieti, x, y, nr_pasi);
        return;
    }
}
//------------------------------------------------------------------------------
//se misca robotul cu un spatiu pe linie mai aproape de item/destinatie
//variabila destination transmisa prin referinta devine 1 cand s-a ajuns la destinatie, si jocul e oprit
int Move_towards_item_line(int**warning, int nr_obiecte, int cod, Map&obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti,
                           char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    TypeI robot1;
    TypeII robot2;
    TypeIII robot3;
    Walk robot_aux;
    int aux=0;
    int aux2=0;
    int i;
    int answer=0;
    for(i=0; i<nr_obiecte; i++)
    {
        if(warning[i][2]==cod)
        {
            if(warning[i][1]>y)
            {
                if(check_bombs(x, y+1, obj)==0)
                {
                    if(obj.harta[x][y+1]==obj.destinatie)
                        destination=1;
                    else if(obj.harta[x][y+1]==robot.getItem())
                    {
                        inventory=1;
                        aux=1;
                    }
                    else if(obj.harta[x][y+1]==robot_aux.getItem())
                        aux2=1;
                    obj.harta[x][y+1]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma1();
                    nr_pasi++;
                    y++;
                    answer=1;
                    raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    if(aux==1&&(robot.getItem()==robot1.getItem()))
                    {
                        efect_item1(x, y, obj, inventory, robot, nr_vieti, nr_pasi);
                        return 1;
                    }
                    else if(aux==1&&(robot.getItem()==robot2.getItem()))
                    {
                        efect_item2(x, y, obj, robot, nr_vieti, nr_pasi);
                        return 1;
                    }
                    else if(aux==1&&(robot.getItem()==robot3.getItem()))
                    {
                        efect_item3(vizor);
                        return 1;
                    }
                    else if(aux2==1)
                    {
                        efect_item_universal(nr_vieti);
                        return 1;
                    }
                }
            }
            else if(warning[i][1]<y)
            {
                if(check_bombs(x, y-1, obj)==0)
                {
                    if(obj.harta[x][y-1]==obj.destinatie)
                        destination=1;
                    else if(obj.harta[x][y-1]==robot.getItem())
                    {
                        inventory=1;
                        aux=1;
                    }
                    else if(obj.harta[x][y-1]==robot_aux.getItem())
                        aux2=1;
                    obj.harta[x][y-1]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma1();
                    nr_pasi++;
                    y--;
                    answer=1;
                    raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    if(aux==1&&(robot.getItem()==robot1.getItem()))
                    {
                        efect_item1(x, y, obj, inventory, robot, nr_vieti, nr_pasi);
                        return 1;
                    }
                    else if(aux==1&&(robot.getItem()==robot2.getItem()))
                    {
                        efect_item2(x, y, obj, robot, nr_vieti, nr_pasi);
                        return 1;
                    }
                    else if(aux==1&&(robot.getItem()==robot3.getItem()))
                    {
                        efect_item3(vizor);
                        return 1;
                    }
                    else if(aux2==1)
                    {
                        efect_item_universal(nr_vieti);
                        return 1;
                    }
                }
            }
        }
    }
    return answer;
}
//---------------------------------------------------------------------------------------------
//are loc miscarea pe diagonala, inapoi sus
int Move_on_the_diagonal_backward_up(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                                     Map&obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    int raspuns=0;
    if(Move_towards_item_diagonal_aux(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                      obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==1)
        return 1;
    if(check_bombs(x-1, y-1, obj)==0)
    {
        obj.harta[x-1][y-1]=robot.getVal();
        obj.harta[x][y]=robot.getUrma4();
        nr_pasi++;
        x--;
        y--;
        raspuns=1;
        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
    }
    return raspuns;
}
//------------------------------------------------------------------------------------------------------------------------
//are loc miscarea pe diagonala inapoi jos
int Move_on_the_diagonal_backward_down(int**&verif_destinatie, int**&verif_item, int**&verif_item_aux, int& nr_obiecteD, int& nr_obiecte, int& nr_obiecte_aux,
                                       Map&obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    int raspuns=0;
    if(Move_towards_item_diagonal_aux(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                                      obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi)==1)
        return 1;
    if(check_bombs(x+1, y-1, obj)==0)
    {
        obj.harta[x+1][y-1]=robot.getVal();
        obj.harta[x][y]=robot.getUrma3();
        nr_pasi++;
        x++;
        y--;
        raspuns=1;
        raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
    }
    return raspuns;
}
//-------------------------------------------------------------------------------------------------------
//analog cu move_towards_item_column_aux, doar ca pentru miscarea pe diagonala
int Move_towards_item_diagonal_aux(int**verif_destinatie, int**verif_item, int**verif_item_aux, int nr_obiecteD, int nr_obiecte, int nr_obiecte_aux,
                                   Map&obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti, char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    int answer=0;
    answer=Move_towards_item_diagonal(verif_destinatie, nr_obiecteD, 1, obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
    if((answer==0)&&(inventory==0))
        answer=Move_towards_item_diagonal(verif_item, nr_obiecte, 2, obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
    if((answer==0)&&(inventory==0))
        answer=Move_towards_item_diagonal(verif_item_aux, nr_obiecte_aux, 3, obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
    return answer;
}
//----------------------------------------------------------------------------------------------------------------
//robotul e miscat catre un item/destinatie pe diagonala, daca nu e posibil, acesta se va misca pe linie sau coloana
int Move_towards_item_diagonal(int**&warning, int&nr_obiecte, int cod, Map&obj, int& x, int& y, Walk& robot, int& destination, int& nr_vieti,
                               char& raspuns_user, int&inventory, int&vizor, int&nr_pasi)
{
    int i;
    int answer=0;
    int aux=0;
    TypeII robot2;
    TypeIII robot3;
    Walk robot_aux;
    int aux2=0;
    for(i=0; i<nr_obiecte; i++)
    {
        if(warning[i][2]==cod)
        {
            if(warning[i][1]<y && warning[i][0]<x)
            {
                if(check_bombs(x-1, y-1, obj)==0)
                {
                    if(obj.harta[x-1][y-1]==obj.destinatie)
                        destination=1;
                    else if(obj.harta[x-1][y-1]==robot.getItem())
                    {
                        inventory=1;
                        aux=1;
                    }
                    else if(obj.harta[x-1][y-1]==robot_aux.getItem())
                        aux2=1;
                    obj.harta[x-1][y-1]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma4();
                    nr_pasi++;
                    x--;
                    y--;
                    answer=1;
                    raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    if(aux==1&&(robot.getItem()==robot2.getItem()))
                    {
                        efect_item2(x, y, obj, robot, nr_vieti, nr_pasi);
                        return 1;
                    }
                    else if(aux==1&&(robot.getItem()==robot3.getItem()))
                    {
                        efect_item3(vizor);
                        return 1;
                    }
                    else if(aux2==1)
                    {
                        efect_item_universal(nr_vieti);
                        return 1;
                    }
                }
            }
            else if(warning[i][1]>y&&warning[i][0]<x)
            {
                if(check_bombs(x-1, y+1, obj)==0)
                {
                    if(obj.harta[x-1][y+1]==obj.destinatie)
                        destination=1;
                    else if(obj.harta[x-1][y+1]==robot.getItem())
                    {
                        inventory=1;
                        aux=1;
                    }
                    else if(obj.harta[x-1][y+1]==robot_aux.getItem())
                        aux2=1;
                    obj.harta[x-1][y+1]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma3();
                    nr_pasi++;
                    x--;
                    y++;
                    answer=1;
                    raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    if(aux==1&&(robot.getItem()==robot2.getItem()))
                    {
                        efect_item2(x, y, obj, robot, nr_vieti, nr_pasi);
                        return 1;
                    }
                    else if(aux==1&&(robot.getItem()==robot3.getItem()))
                    {
                        efect_item3(vizor);
                        return 1;
                    }
                    else if(aux2==1)
                    {
                        efect_item_universal(nr_vieti);
                        return 1;
                    }
                }
            }
            else if(warning[i][1]<y&&warning[i][0]>x)
            {
                if(check_bombs(x+1, y-1, obj)==0)
                {
                    if(obj.harta[x+1][y-1]==obj.destinatie)
                        destination=1;
                    else if(obj.harta[x+1][y-1]==robot.getItem())
                    {
                        inventory=1;
                        aux=1;
                    }
                    else if(obj.harta[x+1][y-1]==robot_aux.getItem())
                        aux2=1;
                    obj.harta[x+1][y-1]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma3();
                    nr_pasi++;
                    x++;
                    y--;
                    answer=1;
                    raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    if(aux==1&&(robot.getItem()==robot2.getItem()))
                    {
                        efect_item2(x, y, obj, robot, nr_vieti, nr_pasi);
                        return 1;
                    }
                    else if(aux==1&&(robot.getItem()==robot3.getItem()))
                    {
                        efect_item3(vizor);
                        return 1;
                    }
                    else if(aux2==1)
                    {
                        efect_item_universal(nr_vieti);
                        return 1;
                    }
                }
            }
            else if(warning[i][1]>y && warning[i][0]>x)
            {
                if(check_bombs(x+1, y+1, obj)==0)
                {
                    if(obj.harta[x+1][y+1]==obj.destinatie)
                        destination=1;
                    else if(obj.harta[x+1][y+1]==robot.getItem())
                    {
                        inventory=1;
                        aux=1;
                    }
                    else if(obj.harta[x+1][y+1]==robot_aux.getItem())
                        aux2=1;
                    obj.harta[x+1][y+1]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma4();
                    nr_pasi++;
                    x++;
                    y++;
                    answer=1;
                    raspuns_user=printare(obj, nr_vieti, x, y, nr_pasi);
                    if(aux==1&&(robot.getItem()==robot2.getItem()))
                    {
                        efect_item2(x, y, obj, robot, nr_vieti, nr_pasi);
                        return 1;
                    }
                    else if(aux==1&&(robot.getItem()==robot3.getItem()))
                    {
                        efect_item3(vizor);
                        return 1;
                    }
                    else if(aux2==1)
                    {
                        efect_item_universal(nr_vieti);
                        return 1;
                    }
                }
            }
            //daca nu e posibil sa mearga pe diagonala
            if(answer==0)
                answer=Move_towards_item_line(warning, nr_obiecte, cod, obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
            if (answer==0)
                answer=Move_towards_item_column(warning, nr_obiecte, cod, obj, x, y, robot, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        }
    }
    return answer;
}
//--------------------------------------------------------------------------------------
//functia e chemata atunci cand robotul de tip 2 gaseste un item care i se potriveste
//acesta va fi miscat pe linie sau coloana de 2 ori, fiindca miscarea pe diagonala e mai putin practica si mai putin agila
void efect_item2(int&x, int&y, Map&obj, Walk& robot, int nr_vieti, int&nr_pasi)
{
    cout<<"Robotul a gasit un item care sa ii permita sa se miste pe linii si coloane temporar"<<endl;
int i;
for(i=0; i<2; i++)
{
    if((y!=obj.l-1)&&(check_bombs(x, y+1, obj)==0))
    {
        obj.harta[x][y+1]=robot.getVal();
        obj.harta[x][y]=robot.getUrma1();
        y++;
        nr_pasi++;
        printare(obj, nr_vieti, x, y, nr_pasi);
    }
    else if(x!=obj.h-1&&(check_bombs(x+1, y, obj)==0))
    {
        obj.harta[x+1][y]=robot.getVal();
        obj.harta[x][y]=robot.getUrma1();
        nr_pasi++;
        x++;
        printare(obj, nr_vieti, x, y, nr_pasi);
    }
}
}
//--------------------------------------------------------------------------------------------------
//functia e chemata cand robotul de tip 3 a gasit itemul care i se potriveste
//aceasta ii va permite sa vada cu o casuta in jur in plus
void efect_item3(int&vizor)
{
    cout<<"Robotul a gasit un item care sa ii permita sa vada cu o casuta in plus in jurul sau "<<endl;
 vizor++;
}
//---------------------------------------------------------------------------------
//functia pentru item universal, care adauga o viata
void efect_item_universal(int&nr_vieti)
{
    cout<<"Robotul a gasit un item universal, care ii acorda o viata in plus"<<endl;
    nr_vieti++;
}
//--------------------------------------------------------------------------------------------
//functia de miscare pentru robotul de tip 3, care merge random, pe linii, coloane si diagonale
//va exista un singur while
//acesta va folosi combinatiile pentru tipul 1 si 2
int movementIII(Walk& robot, Map &obj, int& x, int& y, int& nr_vieti, int&inventory, int&vizor, int&nr_pasi)
{
    srand(time(NULL));
    int destination=0;
    char**harta=obj.getHarta();
    char raspuns_user=' ';
    harta[x][y]=robot.getVal();
    printare(obj, nr_vieti, x, y, nr_pasi);

    int**verif_destinatie=NULL;
    int**verif_item=NULL;
    int**verif_item_aux=NULL;

    int nr_obiecteD=0;
    int nr_obiecte=0;
    int nr_obiecte_aux=0;
    Walk aux_robot;
    while(x>=0 && y>=0 && x<obj.h && y<obj.l)
    {
        int aux=rand();
        int aux1=aux%8;

Move_towards_item_general(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux, robot.getItem(),
                              aux_robot.getItem(), obj, x, y, robot, vizor);
        if(aux1==0&&x!=0)
            Combinatie_tipI_4(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        else if(aux1==1 && x!=0 && y!=obj.l-1)
            Combinatie_tipII_1(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                               obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        else if(aux1==2 && y!=obj.l-1)
            Combinatie_tipI_1(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        else if(aux1==3 && y!=obj.l-1 && x!=obj.h-1)
            Combinatie_tipII_2(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                               obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        else if(aux1==4 && x!=obj.h-1)
            Combinatie_tipI_2(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        else if(aux1==5 && x!=obj.h-1 && y!=0)
            Combinatie_tipII_4(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                               obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        else if(aux1==6 && y!=0)
            Combinatie_tipI_7(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                              obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);
        else if(aux1==7 && x!=0 && y!=0)
            Combinatie_tipII_3(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux,
                               obj, robot, x, y, destination, nr_vieti, raspuns_user, inventory, vizor, nr_pasi);

        dezalocare(verif_destinatie, verif_item, verif_item_aux, nr_obiecteD, nr_obiecte, nr_obiecte_aux);
        if(destination==1)
        {
            cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
            return 1;
        }
        if(nr_vieti==0)
            {
                cout<<"Sfarsit de joc. Corelatie dintre numar vieti si numar capcane nu a facut castigul posibil.";
                return 1;
            }
        if(raspuns_user=='N')
        {
            cout<<"Sfarsit de joc "<<endl;
            return 1;
        }
        else if(raspuns_user=='D')
            continue;
    }
    return 0;
}
