#include "Walk.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
void prim(char** &harta, const char destinatie, const int nr_capcane, const char bomb, const int nr_itemi, const char item1,
          const char item2, const char item3, const char item_uni);
int** realocare(int**warning, int& nr_obiecte);
//void Move_on_line(char**&harta, int**&warning, int x, int y, int nr_obiecte, const char destinatie);
//void check(char**harta, int**&warning, int x, int y, Walk robot, int &nr_obiecte, const char destinatie);
void printare(char**harta);

Walk::Walk(const char Urma1, const char Urma2, const char Item_type, const char Val, int Nr_vieti):
    urma1(Urma1), urma2(Urma2), item_type(Item_type), val(Val), nr_vieti(Nr_vieti)
{

}

Walk::~Walk()
{
    //dtor
}
TypeI::TypeI(const char Item_type, const char Urma1, const char Urma2, const char Val, int Nr_vieti):Walk(Urma1, Urma2, Item_type, Val, Nr_vieti)
{

}
TypeII::TypeII(const char Item_type, const char Urma1, const char Urma2, const char Urma3, const char Urma4, const char Val, int Nr_vieti)
    :Walk(Urma1, Urma2, Item_type, Val, Nr_vieti), urma3(Urma3), urma4(Urma4)
{

}
TypeIII::TypeIII(const char Item_type, const char Urma1, const char Urma2, const char Urma3, const char Urma4, const char Val, int Nr_vieti)
    :Walk(Urma1, Urma2, Item_type, Val, Nr_vieti), urma3(Urma3), urma4(Urma4)
{

}
int main()
{
    int raspuns;
    cout<<"Alegeti tipul robotului, 1, 2 sau 3"<<endl;
    cin>>raspuns;
    cout<<endl;

    //TypeI robot1;
    //TypeII robot2;
    //TypeIII robot3;


    //cout<<robot1.getVal()<<" "<<robot2.getVal()<<" "<<robot3.getVal()<<endl;

    //Walk aux;

    int i,j;

    //int nr_obiecte=0;

    Map w;
    //cout<<"here";
    int x=0, y=0;
//char**harta1=w.getHarta();
    //harta1[x][y]=robot1.getVal();
    //cout<<"got here";

    //Move_on_line(w, x, y, robot1);
    //int x=0, y=0;
    //Walk* robot=&robot1;
    int nr_vieti;
    switch (raspuns)
    {
    case 1:
        {
             TypeI robot1;
        nr_vieti=robot1.getNr_vieti();
        movementI(robot1, w, x, y, nr_vieti);
        break;
        }

    case 2:
        {
           TypeII robot2;
        nr_vieti=robot2.getNr_vieti();
        //movementII(robot2, w, x, y, nr_vieti);
        break;
        }

    case 3:
        {
            TypeIII robot3;
        nr_vieti=robot3.getNr_vieti();
        //movementIII(robot3, w, x, y, nr_vieti);
        break;
        }

    }


    //movementII(robot2, w, x, y);
    //cout<<"Primul "<<endl;
    //movementII(robot2, w, x, y);
    //movementII(robot2, w, x, y);
    //movementII(robot2, w, x, y);

//movementIII(robot3, w, x, y);

    return 0;
}

void check(Map obj, int**&warning, int x, int y, Walk& robot, int &nr_obiecte)
{
    int i, j;
    //int* poz=new int[2];
    int counter;
    for(i=0; i<=4; i++)
        for(j=0; j<=4; j++)
        {
            //check cadranul 1
            if((x-i>=0)&&(y-j>=0))
            {
                if(obj.harta[x-i][y-j]==obj.destinatie)
                {
                    //nr_obiecte++;
                    int**aux=realocare(warning, nr_obiecte);
                    warning=aux;

                    warning[nr_obiecte-1][0]=x-i;
                    warning[nr_obiecte-1][1]=y-j;
                    warning[nr_obiecte-1][2]=1;

                    /*nr_obiecte++;


                    warning=realocare(warning, nr_obiecte);*/

                }
                else if(obj.harta[x-i][y-j]==robot.getItem())
                {
                    //nr_obiecte++;

                    int**aux=realocare(warning, nr_obiecte);
                    warning=aux;

                    warning[nr_obiecte-1][0]=x-i;
                    warning[nr_obiecte-1][1]=y-j;
                    warning[nr_obiecte-1][2]=2;

                }
            }


        }

    for(i=1; i<=4; i++)
        for(j=0; j<=4; j++)
        {
            if((x+i<=14)&&(y+j<=14))
            {
                //check cadranul 4
                if(obj.harta[x+i][y+j]==obj.destinatie)
                {
                    //nr_obiecte++;

                    int**aux=realocare(warning, nr_obiecte);
                    warning=aux;

                    warning[nr_obiecte-1][0]=x+i;
                    warning[nr_obiecte-1][1]=y+j;
                    warning[nr_obiecte-1][2]=1;


                }
                else if(obj.harta[x+i][y+j]==robot.getItem())
                {
                    //nr_obiecte++;


                    int**aux=realocare(warning, nr_obiecte);
                    warning=aux;

                    warning[nr_obiecte-1][0]=x+i;
                    warning[nr_obiecte-1][1]=y+j;
                    warning[nr_obiecte-1][2]=2;

                }
            }
        }
    for(i=0; i<=4; i++)
        for(j=1; j<=4; j++)
        {
            if((x-i>=0)&&(y+j<=14))
            {
                //check cadranul 2
                if(obj.harta[x-i][y+j]==obj.destinatie)
                {
                    //nr_obiecte++;

                    int**aux=realocare(warning, nr_obiecte);
                    warning=aux;

                    warning[nr_obiecte-1][0]=x-i;
                    warning[nr_obiecte-1][1]=y+j;
                    warning[nr_obiecte-1][2]=1;


                }
                else if(obj.harta[x-i][y+j]==robot.getItem())
                {
                    //nr_obiecte++;


                    int**aux=realocare(warning, nr_obiecte);
                    warning=aux;

                    warning[nr_obiecte-1][0]=x-i;
                    warning[nr_obiecte-1][1]=y+j;
                    warning[nr_obiecte-1][2]=2;

                }
            }
        }
    for(i=1; i<=4; i++)
        for(j=1; j<=4; j++)
        {
            if((x+i<=14)&&(y-j>=0))
            {
                //check cadranul 3
                if(obj.harta[x+i][y-j]==obj.destinatie)
                {
//nr_obiecte++;


                    int**aux=realocare(warning, nr_obiecte);
                    warning=aux;

                    warning[nr_obiecte-1][0]=x+i;
                    warning[nr_obiecte-1][1]=y-j;
                    warning[nr_obiecte-1][2]=1;

                }
                else if(obj.harta[x+i][y-j]==robot.getItem())
                {
                    //nr_obiecte++;


                    int**aux=realocare(warning, nr_obiecte);
                    warning=aux;

                    warning[nr_obiecte-1][0]=x+i;
                    warning[nr_obiecte-1][1]=y-j;
                    warning[nr_obiecte-1][2]=2;

                }
            }
        }

    cout<<"Obiect "<<endl;
    for(i=0; i<nr_obiecte; i++)
    {
        for(j=0; j<3; j++)
            cout<<warning[i][j]<<" ";
        cout<<endl;
        cout<<nr_obiecte<<endl;
    }


}

int** realocare(int**warning, int& nr_obiecte)
{
    int i, j;
    int**aux=new int*[nr_obiecte+1];
    for(int i=0; i<3; i++)
        aux[i]=new int;

    for(i=0; i<nr_obiecte; i++)
        for(j=0; j<3; j++)
            aux[i][j]=warning[i][j];
    int**aux1=warning;
    warning=aux;

    for(i=0; i<nr_obiecte; i++)
        delete aux1[i];
    delete [] aux1;
    nr_obiecte++;
    return warning;
}

int Move_on_line_forward(Map&obj, int& x, int& y, Walk& robot, int& destination)
{
    int raspuns=0;
    if(Move_towards_item_line(obj, x, y, robot, destination)==1)
        return 1;
    if(check_bombs(x, y+1, obj)==0)
    {
        obj.harta[x][y+1]=robot.getVal();
        obj.harta[x][y]=robot.getUrma1();
        y++;
        raspuns=1;
        printare(obj.harta);
    }
    return raspuns;
}

void printare(char**harta)
{
    int i,j;
    for(i=0; i<32; i++)
        cout<<"-";
    cout<<endl;
    for(i=0; i<15; i++)
    {
        cout<<"|";
        for(j=0; j<15; j++)
            cout<<harta[i][j]<<" ";
        cout<<"|";
        cout<<endl;
    }
    for(i=0; i<32; i++)
        cout<<"-";
    cout<<endl;
}

int check_bombs(int x, int y, Map obj)
{
    if (obj.harta[x][y]==obj.bomb)
        return -1;
    else
        return 0;
}

Map::Map(int L, int H, const char B, int n_bomb, int n_item, const char D, const char item1,
         const char item2, const char item3, const char item4): l(L), h(H), bomb(B), nr_capcane(n_bomb),
    nr_itemi(n_item), destinatie(D)
{

    harta=new char*[l];
    //cout<<"here";
    int i,j;
    for(i=0; i<h; i++)
        harta[i]=new char;
//cout<<"here";
    for(i=0; i<l; i++)
        for(j=0; j<h; j++)
            harta[i][j]=' ';

    //cout<<"here";

//harta[0][0]=val;

    i=rand()%15;
    j=rand()%15;
    harta[i][j]=destinatie;
    cout<<i<<" "<<j<<endl;


    for(i=0; i<nr_capcane; i++)
    {
        int m=rand()%15, n=rand()%15;
        if(harta[m][n]==' ')
            harta[m][n]=bomb;
        else
        {
            while(harta[m][n]!=' ')
            {
                m=rand()%15;
                n=rand()%15;
            }
            harta[m][n]=bomb;
        }

    }

    for(i=0; i<nr_itemi; i++)
    {
        int b=rand()%15, c=rand()%15;
        if(harta[b][c]==' ')
            harta[b][c]=item1;
        else
        {
            while(harta[b][c]!=' ')
            {
                b=rand()%15;
                c=rand()%15;
            }
            harta[b][c]=item1;
        }

    }

    for(i=0; i<nr_itemi; i++)
    {
        int d=rand()%15, e=rand()%15;
        if(harta[d][e]==' ')
            harta[d][e]=item2;
        else
        {
            while(harta[d][e]!=' ')
            {
                d=rand()%15;
                e=rand()%15;
            }
            harta[d][e]=item2;
        }

    }
    //cout<<"here";
    //printare(harta);
}

int Move_on_column_down(Map&obj, int& x, int& y, Walk& robot, int& destination)
{
    int raspuns=0;
    if(Move_towards_item_column(obj, x, y, robot, destination)==1)
        return 1;

    if(check_bombs(x+1, y, obj)==0)
    {
        obj.harta[x+1][y]=robot.getVal();
        obj.harta[x][y]=robot.getUrma2();
        x++;
        raspuns=1;
        printare(obj.harta);
    }
    return raspuns;
}

void movementI(Walk& robot, Map &obj, int&x, int&y, int& nr_vieti)
{
    int i, j;
    //int x=0, y=0;

    //char**harta=obj.getHarta();
    TypeI* robot1=(TypeI *)&robot;
    obj.harta[x][y]=robot.getVal();
    printare(obj.harta);
    int destination=0;
//------------------------------------------------I
    while((x<15)&&(y<15))
    {
        if(x>=14||y>=14)
            break;
        for(i=0; i<2; i++)
        {
            if(x>=14||y>=14)
                break;
            if(obj.harta[x][y+1]=='-' || Move_on_line_forward(obj, x, y, robot, destination)==0)
            {
                if(obj.harta[x+1][y]=='|' || Move_on_column_down(obj, x, y, robot, destination)==0)
                {
                    if(obj.harta[x][y-1]=='-' || Move_on_line_backward(obj, x, y, robot, destination)==0)
                    {
                        if(obj.harta[x-1][y]=='|' || Move_on_column_up(obj, x, y, robot, destination)==0)
                        {
                            obj.harta[x][y+1]=robot.getVal();
                            obj.harta[x][y]=robot.getUrma1();
                            y++;
                            //raspuns=1;
                            printare(obj.harta);
                            nr_vieti--;
                        }
                    }
                }
            }
            cout<<"Pozitia robotului ";
            cout<<x<<" "<<y<<endl;
            cout<<"Numarul de vieti ramase "<<nr_vieti<<"/3"<<endl;
            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return;
            }

        }
        for(j=0; j<3; j++)
        {
            if(x>=14||y>=14)
                break;
            if(obj.harta[x+1][y]=='|' || Move_on_column_down(obj, x, y, robot, destination)==0)
            {
                if(obj.harta[x][y+1]=='-' || Move_on_line_forward(obj, x, y, robot, destination)==0)
                {
                    if(obj.harta[x-1][y]=='|' || Move_on_column_up(obj, x, y, robot, destination)==0)
                    {
                        if(obj.harta[x][y-1]=='-' || Move_on_line_backward(obj, x, y, robot, destination)==0)
                        {
                            obj.harta[x+1][y]=robot.getVal();
                            obj.harta[x][y]=robot.getUrma1();
                            x++;
                            //raspuns=1;
                            printare(obj.harta);
                            nr_vieti--;
                        }
                    }
                }
            }
            cout<<"Pozitia robotului ";
            cout<<x<<" "<<y<<endl;
            cout<<"Numarul de vieti ramase "<<nr_vieti<<"/3"<<endl;
            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return;
            }

        }

    }
    //---------------------------------------------------II
    while((x<15)&&(x>=0)&&(y<15))
    {
        if(y>=14)
            break;
        for(i=0; i<2; i++)
        {
            //cout<<"Here i "<<i<<endl;
            if(y>=14)
                break;
            if(obj.harta[x][y+1]=='-' || Move_on_line_forward(obj, x, y, robot, destination)==0)
            {
                if(obj.harta[x-1][y]=='|' || Move_on_column_up(obj, x, y, robot, destination)==0)
                {
                    if(obj.harta[x][y-1]=='-' || Move_on_line_backward(obj, x, y, robot, destination)==0)
                    {
                        if(obj.harta[x+1][y]=='|' || Move_on_column_down(obj, x, y, robot, destination)==0)
                        {
                            obj.harta[x][y+1]=robot.getVal();
                            obj.harta[x][y]=robot.getUrma1();
                            y++;
                            //raspuns=1;
                            printare(obj.harta);
                            nr_vieti--;
                        }
                    }
                }
            }
            cout<<"Pozitia robotului ";
            cout<<x<<" "<<y<<endl;
            cout<<"Numarul de vieti ramase "<<nr_vieti<<"/3"<<endl;
            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return;
            }
        }
        for(j=0; j<3; j++)
        {
            if(x==0)
                break;
            if(obj.harta[x-1][y]=='|' || Move_on_column_up(obj, x, y, robot, destination)==0)
            {
                if(obj.harta[x][y+1]=='-' || Move_on_line_forward(obj, x, y, robot, destination)==0)
                {
                    if(obj.harta[x+1][y]=='|' || Move_on_column_down(obj, x, y, robot, destination)==0)
                    {
                        if(obj.harta[x][y-1]=='-' || Move_on_line_backward(obj, x, y, robot, destination)==0)
                        {
                            obj.harta[x-1][y]=robot.getVal();
                            obj.harta[x][y]=robot.getUrma1();
                            x--;
                            //raspuns=1;
                            printare(obj.harta);
                            nr_vieti--;
                        }
                    }
                }
            }
            cout<<"Pozitia robotului ";
            cout<<x<<" "<<y<<endl;
            cout<<"Numarul de vieti ramase "<<nr_vieti<<"/3"<<endl;
            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return;
            }

        }

    }
    //------------------------------------------------------III-
    while(x>=0&&y>=0)
    {
        //cout<<"Pas 3 "<<endl;
        if(x==0||y==0)
            break;
        for(i=0; i<2; i++)
        {
            if(y==0)
                break;
            if(obj.harta[x][y-1]=='-' || Move_on_line_backward(obj, x, y, robot, destination)==0)
            {
                if(obj.harta[x-1][y]=='|' || Move_on_column_up(obj, x, y, robot, destination)==0)
                {
                    if(obj.harta[x][y+1]=='-' || Move_on_line_forward(obj, x, y, robot, destination)==0)
                    {
                        if(obj.harta[x+1][y]=='|' || Move_on_column_down(obj, x, y, robot, destination)==0)
                        {
                            obj.harta[x][y-1]=robot.getVal();
                            obj.harta[x][y]=robot.getUrma1();
                            y--;
                            //raspuns=1;
                            printare(obj.harta);
                            nr_vieti--;
                        }
                    }
                }
            }
            cout<<"Pozitia robotului ";
            cout<<x<<" "<<y<<endl;
            cout<<"Numarul de vieti ramase "<<nr_vieti<<"/3"<<endl;
            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return;
            }
        }
        for(j=0; j<3; j++)
        {
            if(x==0)
                break;
            if(obj.harta[x-1][y]=='|' || Move_on_column_up(obj, x, y, robot, destination)==0)
            {
                if(obj.harta[x][y-1]=='-' || Move_on_line_backward(obj, x, y, robot, destination)==0)
                {
                    if(obj.harta[x+1][y]=='|' || Move_on_column_down(obj, x, y, robot, destination)==0)
                    {
                        if(obj.harta[x][y+1]=='-' || Move_on_line_forward(obj, x, y, robot, destination)==0)
                        {
                            obj.harta[x-1][y]=robot.getVal();
                            obj.harta[x][y]=robot.getUrma1();
                            x--;
                            //raspuns=1;
                            printare(obj.harta);
                            nr_vieti--;
                        }
                    }
                }
            }
            cout<<"Pozitia robotului ";
            cout<<x<<" "<<y<<endl;
            cout<<"Numarul de vieti ramase "<<nr_vieti<<"/3"<<endl;
            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return;
            }
        }

    }
    //-------------------------------------IV
    while(x<15&&y>=0)
    {
        //cout<<"Hey "<<endl;
        if(x==14||y==0)
            break;
        for(i=0; i<2; i++)
        {
            if(y==0)
                break;
            if(obj.harta[x][y-1]=='-' || Move_on_line_backward(obj, x, y, robot, destination)==0)
            {
                if(obj.harta[x+1][y]=='|' || Move_on_column_down(obj, x, y, robot, destination)==0)
                {
                    if(obj.harta[x][y+1]=='-' || Move_on_line_forward(obj, x, y, robot, destination)==0)
                    {
                        if(obj.harta[x-1][y]=='|' || Move_on_column_up(obj, x, y, robot, destination)==0)
                        {
                            obj.harta[x][y-1]=robot.getVal();
                            obj.harta[x][y]=robot.getUrma1();
                            y--;
                            //raspuns=1;
                            printare(obj.harta);
                            nr_vieti--;
                        }
                    }
                }
            }
            cout<<"Pozitia robotului ";
            cout<<x<<" "<<y<<endl;
            cout<<"Numarul de vieti ramase "<<nr_vieti<<"/3"<<endl;
            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return;
            }
        }
        for(j=0; j<3; j++)
        {
            if(x==14)
                break;
            if(obj.harta[x+1][y]=='|' || Move_on_column_down(obj, x, y, robot, destination)==0)
            {
                if(obj.harta[x][y-1]=='-' || Move_on_line_backward(obj, x, y, robot, destination)==0)
                {
                    if(obj.harta[x-1][y]=='|' || Move_on_column_up(obj, x, y, robot, destination)==0)
                    {
                        if(obj.harta[x][y+1]=='-' || Move_on_line_forward(obj, x, y, robot, destination)==0)
                        {
                            obj.harta[x+1][y]=robot.getVal();
                            obj.harta[x][y]=robot.getUrma1();
                            x++;
                            //raspuns=1;
                            printare(obj.harta);
                            nr_vieti--;
                        }
                    }
                }
            }
            cout<<"Pozitia robotului ";
            cout<<x<<" "<<y<<endl;
            cout<<"Numarul de vieti ramase "<<nr_vieti<<"/3"<<endl;
            if(destination==1)
            {
                cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
                return;
            }
        }

    }
}

int Move_on_column_up(Map&obj, int& x, int& y, Walk& robot, int& destination)
{
    int raspuns=0;
    if(Move_towards_item_column(obj, x, y, robot, destination)==1)
        return 1;

    if(check_bombs(x-1, y, obj)==0)
    {
        obj.harta[x-1][y]=robot.getVal();
        obj.harta[x][y]=robot.getUrma2();
        x--;
        raspuns=1;
        printare(obj.harta);
    }
    return raspuns;
}

int Move_on_line_backward(Map&obj, int& x, int& y, Walk& robot, int& destination)
{
    int raspuns=0;
    if(Move_towards_item_line(obj, x, y, robot, destination)==1)
        return 1;
    if(check_bombs(x, y-1, obj)==0)
    {
        obj.harta[x][y-1]=robot.getVal();
        obj.harta[x][y]=robot.getUrma1();
        y--;
        raspuns=1;
        printare(obj.harta);
    }
    return raspuns;
}

void movementII(Walk& robot, Map &obj, int&x, int&y)
{
    //srand(time(0));
    //int aux=rand()%1-1;
    int seed=0;
    char**harta=obj.getHarta();
    harta[x][y]=robot.getVal();
    printare(obj.harta);
    //TypeII *robot2 =  (TypeII *) &robot;
    int destination=0;
    while(x>=0&&y>=0&&x<15&&y<15)
    {
        if(y==14)
            break;
        int aux=rand();
        int aux1=aux%2;
        cout<<x<<" "<<y<<endl;
        cout<<"aux1 este "<<aux1<<endl;
        if(aux1==0&&x!=0)
            Move_on_the_diagonal_forward_up(obj, x, y, robot, destination);
        else if(aux1==1&&x!=14)
            Move_on_the_diagonal_forward_down(obj, x, y, robot, destination);
        //else if(x==0||x==14) break;
        if(destination==1)
        {
            cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
            return;
        }
        cout<<x<<" "<<y<<endl;
    }

    while(x>=0&&y>=0&&x<15&&y<15)
    {
        if(y==0)
            break;
        int aux=rand();
        int aux1=aux%2;
        cout<<x<<" "<<y<<endl;
        cout<<"aux1 este "<<aux1<<endl;
        if(aux1==0&&x!=0)
            Move_on_the_diagonal_backward_up(obj, x, y, robot, destination);
        else if(aux1==1&&x!=14)
            Move_on_the_diagonal_backward_down(obj, x, y, robot, destination);
        //else if(x==0||x==14) break;
        if(destination==1)
        {
            cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
            return;
        }
        cout<<x<<" "<<y<<endl;
    }

}

int Move_on_the_diagonal_forward_up(Map&obj, int& x, int& y, Walk& robot, int& destination)
{
    int raspuns=0;
    if(Move_towards_item_diagonal(obj, x, y, robot, destination)==1)
        return 1;

    if(check_bombs(x-1, y+1, obj)==0)
    {
        TypeII *robot2 =  (TypeII *) &robot;
        obj.harta[x-1][y+1]=robot.getVal();
        obj.harta[x][y]=robot2->getUrma3();       //downcasting
        x--;
        y++;
        raspuns=1;
        printare(obj.harta);
    }
    return raspuns;
}

int Move_on_the_diagonal_forward_down(Map&obj, int& x, int& y, Walk& robot, int& destination)
{
    int raspuns=0;
    if(Move_towards_item_diagonal(obj, x, y, robot, destination)==1)
        return 1;
    if(check_bombs(x+1, y+1, obj)==0)
    {
        TypeII *robot2 =  (TypeII *) &robot;
        obj.harta[x+1][y+1]=robot.getVal();
        obj.harta[x][y]=robot2->getUrma4();       //downcasting
        x++;
        y++;
        raspuns=1;
        printare(obj.harta);
    }
    return raspuns;
}

int Move_towards_item_column(Map&obj, int& x, int& y, Walk& robot, int& destination)
{
    int**warning=NULL;
    int nr_obiecte=0;
    check(obj, warning, x, y, robot, nr_obiecte);
    //cout<<"here"<<endl;
    int i,j;
    int answer=0;
    for(i=0; i<nr_obiecte; i++)
    {
        if(warning[i][2]==1)
        {
            //answer=1;
            if(warning[i][0]>x)
            {
                if(obj.harta[x+1][y]==obj.destinatie)
                    destination=1;
                if(check_bombs(x+1, y, obj)==0)
                {
                    obj.harta[x+1][y]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma2();
                    x++;
                    answer=1;
                    printare(obj.harta);
                }
            }
            else if(warning[i][0]<x)
            {
                if(obj.harta[x-1][y]==obj.destinatie)
                    destination=1;
                if(check_bombs(x-1, y, obj)==0)
                {
                    obj.harta[x-1][y]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma2();
                    x--;
                    answer=1;
                    printare(obj.harta);
                }

            }
            else
            {
                if(warning[i][1]>y)
                {
                    if(obj.harta[x][y+1]==obj.destinatie)
                        destination=1;
                    if(check_bombs(x, y+1, obj)==0)
                    {
                        obj.harta[x][y+1]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma1();
                        y++;
                        answer=1;
                        printare(obj.harta);
                    }

                }
                else if(warning[i][1]<y)
                {
                    if(obj.harta[x][y-1]==obj.destinatie)
                        destination=1;
                    if(check_bombs(x, y-1, obj)==0)
                    {
                        obj.harta[x][y-1]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma1();
                        y--;
                        answer=1;
                        printare(obj.harta);
                    }

                }
            }

        }
    }
    return answer;
}

int Move_towards_item_line(Map&obj, int& x, int& y, Walk& robot, int& destination)
{
    int**warning=NULL;
    int nr_obiecte=0;
    check(obj, warning, x, y, robot, nr_obiecte);
    //cout<<"here"<<endl;
    int i,j;
    int answer=0;
    for(i=0; i<nr_obiecte; i++)
    {
        if(warning[i][2]==1)
        {
            //answer=1;
            if(warning[i][1]>y)
            {
                if(obj.harta[x][y+1]==obj.destinatie)
                    destination=1;
                if(check_bombs(x, y+1, obj)==0)
                {
                    obj.harta[x][y+1]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma1();
                    y++;
                    answer=1;
                    printare(obj.harta);
                }

            }
            else if(warning[i][1]<y)
            {
                if(obj.harta[x][y-1]==obj.destinatie)
                    destination=1;
                if(check_bombs(x, y-1, obj)==0)
                {
                    obj.harta[x][y-1]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma1();
                    y--;
                    answer=1;
                    printare(obj.harta);
                }
            }
            else
            {
                if(warning[i][0]>x)
                {
                    if(obj.harta[x+1][y]==obj.destinatie)
                        destination=1;
                    if(check_bombs(x+1, y, obj)==0)
                    {
                        obj.harta[x+1][y]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma2();
                        x++;
                        answer=1;
                        printare(obj.harta);
                    }
                }
                else if(warning[i][0]<x)
                {
                    if(obj.harta[x-1][y]==obj.destinatie)
                        destination=1;
                    if(check_bombs(x-1, y, obj)==0)
                    {
                        obj.harta[x-1][y]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma2();
                        x--;
                        answer=1;
                        printare(obj.harta);
                    }
                }

            }
            //printare(obj.harta);
        }
    }
    return answer;
}

int Move_on_the_diagonal_backward_up(Map&obj, int& x, int& y, Walk& robot, int& destination)
{
    int raspuns=0;
    if(Move_towards_item_diagonal(obj, x, y, robot, destination)==1)
        return 1;
    if(check_bombs(x-1, y-1, obj)==0)
    {
        TypeII* robot2=(TypeII*)&robot;
        obj.harta[x-1][y-1]=robot.getVal();
        obj.harta[x][y]=robot2->getUrma4();
        x--;
        y--;
        raspuns=1;
        printare(obj.harta);
    }
    return raspuns;
}

int Move_on_the_diagonal_backward_down(Map&obj, int& x, int& y, Walk& robot, int& destination)
{
    int raspuns=0;
    if(Move_towards_item_diagonal(obj, x, y, robot, destination)==1)
        return 1;

    if(check_bombs(x+1, y-1, obj)==0)
    {
        TypeII* robot2=(TypeII*)&robot;
        obj.harta[x+1][y-1]=robot.getVal();
        obj.harta[x][y]=robot2->getUrma3();
        x++;
        y--;
        raspuns=1;
        printare(obj.harta);
    }
    return raspuns;
}

int Move_towards_item_diagonal(Map&obj, int& x, int& y, Walk& robot, int& destination)
{
    int**warning=NULL;
    int nr_obiecte=0;
    check(obj, warning, x, y, robot, nr_obiecte);
    //cout<<"here"<<endl;
    int i,j;
    int answer=0;
    TypeII* robot2=(TypeII*)&robot;
    for(i=0; i<nr_obiecte; i++)
    {
        if(warning[i][2]==1)
        {
            //answer=1;
            if(warning[i][1]<y&&warning[i][0]<x)
            {
                if(obj.harta[x-1][y-1]==obj.destinatie)
                    destination=1;
                if(check_bombs(x-1, y-1, obj)==0)
                {
                    obj.harta[x-1][y-1]=robot.getVal();
                    obj.harta[x][y]=robot2->getUrma4();
                    x--;
                    y--;
                    answer=1;
                    printare(obj.harta);
                }
            }
            else if(warning[i][1]>y&&warning[i][0]<x)
            {
                if(obj.harta[x-1][y+1]==obj.destinatie)
                    destination=1;
                if(check_bombs(x-1, y+1, obj)==0)
                {
                    obj.harta[x-1][y+1]=robot.getVal();
                    obj.harta[x][y]=robot2->getUrma3();
                    x--;
                    y++;
                    answer=1;
                    printare(obj.harta);
                }

            }
            else if(warning[i][1]<y&&warning[i][0]>x)
            {
                if(obj.harta[x+1][y-1]==obj.destinatie)
                    destination=1;
                if(check_bombs(x+1, y-1, obj)==0)
                {
                    obj.harta[x+1][y-1]=robot.getVal();
                    obj.harta[x][y]=robot2->getUrma3();
                    x++;
                    y--;
                    answer=1;
                    printare(obj.harta);
                }

            }
            else if(warning[i][1]>y&&warning[i][0]>x)
            {
                if(obj.harta[x+1][y+1]==obj.destinatie)
                    destination=1;
                if(check_bombs(x+1, y+1, obj)==0)
                {
                    obj.harta[x+1][y+1]=robot.getVal();
                    obj.harta[x][y]=robot2->getUrma4();
                    x++;
                    y++;
                    answer=1;
                    printare(obj.harta);
                }
            }
            //daca nu e posibil sa mearga pe diagonala
            else if(warning[i][1]>y)
            {
                if(obj.harta[x][y+1]==obj.destinatie)
                    destination=1;
                if(check_bombs(x, y+1, obj)==0)
                {
                    obj.harta[x][y+1]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma1();
                    y++;
                    answer=1;
                    printare(obj.harta);
                }
            }
            else if(warning[i][1]<y)
            {
                if(obj.harta[x][y-1]==obj.destinatie)
                    destination=1;
                if(check_bombs(x, y-1, obj)==0)
                {
                    obj.harta[x][y-1]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma1();
                    y--;
                    answer=1;
                    printare(obj.harta);
                }
            }
            else
            {
                if(warning[i][0]>x)
                {
                    if(obj.harta[x+1][y]==obj.destinatie)
                        destination=1;
                    if(check_bombs(x+1, y, obj)==0)
                    {
                        obj.harta[x+1][y]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma2();
                        x++;
                        answer=1;
                        printare(obj.harta);
                    }

                }
                else if(warning[i][0]<x)
                {
                    if(obj.harta[x-1][y]==obj.destinatie)
                        destination=1;
                    if(check_bombs(x-1, y, obj)==0)
                    {
                        obj.harta[x-1][y]=robot.getVal();
                        obj.harta[x][y]=robot.getUrma2();
                        x--;
                        answer=1;
                        printare(obj.harta);
                    }
                }
            }
            //printare(obj.harta);
        }
    }
    return answer;
}

void movementIII(Walk& robot, Map &obj, int&x, int&y)
{
    int destination=0;
    int seed=0;
    char**harta=obj.getHarta();
    harta[x][y]=robot.getVal();
    printare(obj.harta);

    while(x>=0&&y>=0&&x<15&&y<15)
    {
        //if(x==14||y==14||x==0||y==0) break;
        int aux=rand();
        int aux1=aux%8;
        cout<<x<<" "<<y<<endl;
        cout<<"aux1 este "<<aux1<<endl;

        if(aux1==0&&x!=0)
            Move_on_column_up(obj, x, y, robot, destination);
        else if(aux1==1&&x!=0&&y!=14)
            Move_on_the_diagonal_forward_up(obj, x, y, robot, destination);
        else if(aux1==2&&y!=14)
            Move_on_line_forward(obj, x, y, robot, destination);
        else if(aux1==3&&y!=14&&x!=14)
            Move_on_the_diagonal_forward_down(obj, x, y, robot, destination);
        else if(aux1==4&&x!=14)
            Move_on_column_down(obj, x, y, robot, destination);
        else if(aux1==5&&x!=14&&y!=0)
            Move_on_the_diagonal_backward_down(obj, x, y, robot, destination);
        else if(aux1==6&&y!=0)
            Move_on_line_backward(obj, x, y, robot, destination);
        else if(aux1==7&&x!=0&&y!=0)
            Move_on_the_diagonal_backward_up(obj, x, y, robot, destination);
        cout<<x<<" "<<y<<endl;
        cout<<destination<<endl;
        if(destination==1)
        {
            cout<<"S-a ajuns la destinatie cu succes! Sfarsit de joc."<<endl;
            break;
        }
    }

}
