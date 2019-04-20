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

Walk::Walk(const char Urma1, const char Urma2, const char Item_type, const char Val):
    urma1(Urma1), urma2(Urma2), item_type(Item_type), val(Val)
{

}

Walk::~Walk()
{
    //dtor
}
TypeI::TypeI(const char Item_type, const char Urma1, const char Urma2, const char Val):Walk(Urma1, Urma2, Item_type, Val)
{

}
TypeII::TypeII(const char Item_type, const char Urma1, const char Urma2, const char Val):Walk(Urma1, Urma2, Item_type, Val)
{

}
TypeIII::TypeIII(const char Item_type, const char Urma1, const char Urma2, const char Val):Walk(Urma1, Urma2, Item_type, Val)
{

}
int main()
{
    int raspuns;
    cout<<"Alegeti tipul robotului, 1, 2 sau 3"<<endl;
    cin>>raspuns;
    cout<<endl;

    TypeI robot1;
    TypeII robot2;
    TypeIII robot3;


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
    //movementI(robot1, w, x, y);
    movementII(robot2, w, x, y);


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

void Move_on_line_forward(Map&obj, int& x, int& y, Walk& robot)
{

    if(Move_towards_item_line(obj, x, y, robot)==1)
        return;
    obj.harta[x][y+1]=robot.getVal();
    obj.harta[x][y]=robot.getUrma1();
    y++;

    printare(obj.harta);
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

int check_bombs_onLine(int x, int y, Map obj)
{
    //int i, j;
    if (obj.harta[x][y+1]==obj.bomb)
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
    harta[i][j]='X';
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

void Move_on_column_down(Map&obj, int& x, int& y, Walk& robot)
{

    if(Move_towards_item_column(obj, x, y, robot)==1)
        return;
    obj.harta[x+1][y]=robot.getVal();
    obj.harta[x][y]=robot.getUrma2();
    x++;

    printare(obj.harta);
}

void movementI(Walk& robot, Map &obj, int&x, int&y)
{
    int i, j;
    //int x=0, y=0;

    char**harta=obj.getHarta();
    harta[x][y]=robot.getVal();
    printare(obj.harta);
//------------------------------------------------
    while((x<15)&&(y<15))
    {
        if(x>=14||y>=14)
            break;
        for(i=0; i<2; i++)
        {
            if(x>=14||y>=14)
                break;
            Move_on_line_forward(obj, x, y, robot);
            cout<<x<<" "<<y<<endl;

        }
        for(j=0; j<3; j++)
        {
            if(x>=14||y>=14)
                break;
            Move_on_column_down(obj, x, y, robot);
            cout<<x<<" "<<y<<endl;

        }

    }
    //---------------------------------------------------
    while((x<15)&&(x>=0)&&(y<15))
    {
        if(y>=14)
            break;
        for(i=0; i<2; i++)
        {
            //cout<<"Here i "<<i<<endl;
            if(y>=14)
                break;
            Move_on_line_forward(obj, x, y, robot);
            cout<<x<<" "<<y<<endl;
        }
        for(j=0; j<3; j++)
        {
            if(x==0)
                break;
            Move_on_column_up(obj, x, y, robot);
            cout<<x<<" "<<y<<endl;

        }
    }
    //-------------------------------------------------------
    while(x>=0&&y>=0)
    {
        cout<<"Pas 3 "<<endl;
        if(x==0||y==0)
            break;
        for(i=0; i<2; i++)
        {
            if(y==0)
                break;
            Move_on_line_backward(obj, x, y, robot);
            cout<<x<<" "<<y<<endl;
        }
        for(j=0; j<3; j++)
        {
            if(x==0)
                break;
            Move_on_column_up(obj, x, y, robot);
            cout<<x<<" "<<y<<endl;
        }
    }
    //-------------------------------------
    while(x<15&&y>=0)
    {
        cout<<"Hey "<<endl;
        if(x==14||y==0)
            break;
        for(i=0; i<2; i++)
        {
            if(y==0)
                break;
            Move_on_line_backward(obj, x, y, robot);
            cout<<x<<" "<<y<<endl;
        }
        for(j=0; j<3; j++)
        {
            if(x==14)
                break;
            Move_on_column_down(obj, x, y, robot);
            cout<<x<<" "<<y<<endl;
        }
    }



}

void Move_on_column_up(Map&obj, int& x, int& y, Walk& robot)
{

    if(Move_towards_item_column(obj, x, y, robot)==1)
        return;
    obj.harta[x-1][y]=robot.getVal();
    obj.harta[x][y]=robot.getUrma2();
    x--;

    printare(obj.harta);
}

void Move_on_line_backward(Map&obj, int& x, int& y, Walk& robot)
{
    if(Move_towards_item_line(obj, x, y, robot)==1)
        return;

    obj.harta[x][y-1]=robot.getVal();
    obj.harta[x][y]=robot.getUrma1();
    y--;

    printare(obj.harta);
}

void movementII(Walk& robot, Map &obj, int&x, int&y)
{ //srand(time(0));
    //int aux=rand()%1-1;
int seed=0;
    char**harta=obj.getHarta();
    harta[x][y]=robot.getVal();
    printare(obj.harta);
while(x>=0&&y>=0&&x<15&&y<15)
{  if(x==14||y==14) break;
    int aux=rand();
int aux1=aux%2;
cout<<x<<" "<<y<<endl;
    cout<<"aux1 este "<<aux1<<endl;
    if(aux1==0&&x!=0&&y!=14) Move_on_the_diagonal_forward_up(obj, x, y, robot);
    else if(aux1==1&&x!=14&&y!=14) Move_on_the_diagonal_forward_down(obj, x, y, robot);
    //else if(aux1==0&&y!=14)Move_on_line_forward(obj, x, y, robot);
}

}

void Move_on_the_diagonal_forward_up(Map&obj, int& x, int& y, Walk& robot)
{
    if(Move_towards_item_column(obj, x, y, robot)==1) return;
    if(Move_towards_item_line(obj, x, y, robot)==1) return;


    obj.harta[x-1][y+1]=robot.getVal();
    obj.harta[x][y]=robot.getUrma1();
    x--;
    y++;

    printare(obj.harta);
}

void Move_on_the_diagonal_forward_down(Map&obj, int& x, int& y, Walk& robot)
{
    if(Move_towards_item_column(obj, x, y, robot)==1) return;
    if(Move_towards_item_line(obj, x, y, robot)==1) return;


    obj.harta[x+1][y+1]=robot.getVal();
    obj.harta[x][y]=robot.getUrma1();
    x++;
    y++;

    printare(obj.harta);
}

int Move_towards_item_column(Map&obj, int& x, int& y, Walk& robot)
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
            answer=1;
            if(warning[i][0]>x)
            {
                obj.harta[x+1][y]=robot.getVal();
                obj.harta[x][y]=robot.getUrma2();
                x++;
            }
            else if(warning[i][0]<x)
            {
                obj.harta[x-1][y]=robot.getVal();
                obj.harta[x][y]=robot.getUrma2();
                x--;
            }
            else
            {
                if(warning[i][1]>y)
                {
                    obj.harta[x][y+1]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma1();
                    y++;
                }
                else if(warning[i][1]<y)
                {
                    obj.harta[x][y-1]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma1();
                    y--;
                }


            }
            printare(obj.harta);
        }
    }
    return answer;
}

int Move_towards_item_line(Map&obj, int& x, int& y, Walk& robot)
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
            answer=1;
            if(warning[i][1]>y)
            {
                obj.harta[x][y+1]=robot.getVal();
                obj.harta[x][y]=robot.getUrma1();
                y++;
            }
            else if(warning[i][1]<y)
            {
                obj.harta[x][y-1]=robot.getVal();
                obj.harta[x][y]=robot.getUrma1();
                y--;
            }
            else
            {
                if(warning[i][0]>x)
                {
                    obj.harta[x+1][y]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma2();
                    x++;
                }
                else if(warning[i][0]<x)
                {
                    obj.harta[x-1][y]=robot.getVal();
                    obj.harta[x][y]=robot.getUrma2();
                    x--;
                }

            }
            printare(obj.harta);
        }
    }
    return answer;
}
void Move_on_the_diagonal_backward_up(Map&obj, int& x, int& y, Walk& robot)
{
    if(Move_towards_item_column(obj, x, y, robot)==1) return;
    if(Move_towards_item_line(obj, x, y, robot)==1) return;


    obj.harta[x-1][y-1]=robot.getVal();
    obj.harta[x][y]=robot.getUrma1();
    x--;
    y--;

    printare(obj.harta);
}
void Move_on_the_diagonal_backward_down(Map&obj, int& x, int& y, Walk& robot)
{
    if(Move_towards_item_column(obj, x, y, robot)==1) return;
    if(Move_towards_item_line(obj, x, y, robot)==1) return;


    obj.harta[x+1][y-1]=robot.getVal();
    obj.harta[x][y]=robot.getUrma1();
    x++;
    y--;

    printare(obj.harta);
}
