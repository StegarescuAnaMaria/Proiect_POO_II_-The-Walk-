#ifndef WALK_H
#define WALK_H
//class Map;
class Walk
{
public:
    Walk(const char Urma1='-', const char Urma2='|', const char Urma3='/', const char Urma4='\\', const char Item_type='%', const char Val=' ',
         int Nr_vieti=4, int Vizor=3, int Acquired=0 );
    virtual ~Walk();
    virtual const char getItem()
    {
        return item_type;
    }
    const char getVal()
    {
        return val;
    }
    const char getUrma1()
    {
        return urma1;

    }
    const char getUrma2()
    {
        return urma2;
    }
    int getNr_vieti()
    {
        return nr_vieti;
    }
    int getVizor()
    {
        return vizor;
    }
    void setInventory(int inventory)
    {
        acquired=inventory;
    }
    int getInventory()
    {
        return acquired;
    }
    const char getUrma3()
    {
        return urma3;
    }
    const char getUrma4()
    {
        return urma4;
    }
protected:

private:
    const char urma1;
    const char urma2;
    const char urma3;
    const char urma4;
    const char item_type;
    const char val;
    int nr_vieti;
    int vizor;
    int acquired;
};
class TypeII;
class Map:public Walk
{
    const int l;
    const int h;
    const char destinatie;
    const char bomb;
    int nr_capcane;
    int nr_itemi;
    char**harta;
    int destinatie_x;
    int destinatie_y;
public:
    friend void efect_item2(int&, int&, Map&, Walk&, int, int&);
    friend void efect_item1(int&, int&, Map&, int&, Walk&, int, int);
    friend void Move_towards_item_general(int**&, int**&, int**&, int&, int&, int&, const char, const char, Map obj, int, int, Walk&, int);
    friend char printare(Map, int, int, int, int);
    friend void Combinatie_tipI_1(int**&, int**&, int**&, int&, int&, int&, Map&, Walk&, int&, int&, int&, int&, char&, int&, int&, int&);
    friend void Combinatie_tipI_2(int**&, int**&, int**&, int&, int&, int&, Map&, Walk&, int&, int&, int&, int&, char&, int&, int&, int&);
    friend void Combinatie_tipI_3(int**&, int**&, int**&, int&, int&, int&, Map&, Walk&, int&, int&, int&, int&, char&, int&, int&, int&);
    friend void Combinatie_tipI_4(int**&, int**&, int**&, int&, int&, int&, Map&, Walk&, int&, int&, int&, int&, char&, int&, int&, int&);
    friend void Combinatie_tipI_5(int**&, int**&, int**&, int&, int&, int&, Map&, Walk&, int&, int&, int&, int&, char&, int&, int&, int&);
    friend void Combinatie_tipI_6(int**&, int**&, int**&, int&, int&, int&, Map&, Walk&, int&, int&, int&, int&, char&, int&, int&, int&);
    friend void Combinatie_tipI_7(int**&, int**&, int**&, int&, int&, int&, Map&, Walk&, int&, int&, int&, int&, char&, int&, int&, int&);
    friend void Combinatie_tipI_8(int**&, int**&, int**&, int&, int&, int&, Map&, Walk&, int&, int&, int&, int&, char&, int&, int&, int&);
    friend void Combinatie_tipII_1(int**&, int**&, int**&, int&, int&, int&, Map&, Walk&, int&, int&, int&, int&, char&, int&, int&, int&);
    friend void Combinatie_tipII_2(int**&, int**&, int**&, int&, int&, int&, Map&, Walk&, int&, int&, int&, int&, char&, int&, int&, int&);
    friend void Combinatie_tipII_3(int**&, int**&, int**&, int&, int&, int&, Map&, Walk&, int&, int&, int&, int&, char&, int&, int&, int&);
    friend void Combinatie_tipII_4(int**&, int**&, int**&, int&, int&, int&, Map&, Walk&, int&, int&, int&, int&, char&, int&, int&, int&);
    friend int check_path_line_forward(int**&, int**&, int**&, int&, int&, int&, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int check_path_column_down(int**&, int**&, int**&, int&, int&, int&, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int check_path_line_backward(int**&, int**&, int**&, int&, int&, int&, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int movementIII(Walk&, Map&, int&, int&, int&, int&, int&, int&);
    friend int movementII(Walk&, Map&, int&, int&, int&, int&, int&, int&);
    friend int movementI(Walk&, Map&, int&, int&, int&, int&, int&, int&);
    friend int Move_on_column_down(int**&, int**&, int**&, int&, int&, int&, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int Move_on_column_up(int**&, int**&, int**&, int&, int&, int&, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int Move_on_line_backward(int**&, int**&, int**&, int&, int&, int&, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int Move_on_line_forward(int**&, int**&, int**&, int&, int&, int&, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int check_bombs(int, int, Map);
    friend void check_items1(Map, int**&, int, int, Walk&, int&, const char, int, int);
    friend void check_items2(Map, int**&, int, int, int&, const char, int);
    friend int Move_on_the_diagonal_forward_up(int**&, int**&, int**&, int&, int&, int&, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int Move_on_the_diagonal_forward_down(int**&, int**&, int**&, int&, int&, int&, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int Move_on_the_diagonal_backward_up(int**&, int**&, int**&, int&, int&, int&, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int Move_on_the_diagonal_backward_down(int**&, int**&, int**&, int&, int&, int&, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int Move_towards_item_column(int**, int, int, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int Move_towards_item_line(int**, int, int, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int Move_towards_item_diagonal(int**&, int&, int, Map&, int&, int&, Walk&, int&, int&,
                                          char&, int&, int&, int&);
    friend int Move_towards_item_column_aux(int**, int**, int**, int, int, int, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int Move_towards_item_line_aux(int**, int**, int**, int, int, int, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    friend int Move_towards_item_diagonal_aux(int**, int**, int**, int, int, int, Map&, int&, int&, Walk&, int&, int&, char&, int&, int&, int&);
    Map(const int L=15,const int H=15, const char B='#', int n_bomb=40, int n_item=3, const char D='X', const char item1=' ',
        const char item2=' ', const char item3=' ', const char item4=' ');
    //~Map(){};
    int getL()
    {
        return l;
    }
    int getH()
    {
        return h;
    }
    const char getDestinatie()
    {
        return destinatie;
    }
    const char getBomb()
    {
        return bomb;
    }
    int getNr_capcane()
    {
        return nr_capcane;
    }
    int getNr_itemi()
    {
        return nr_itemi;
    }
    char**getHarta()
    {
        return harta;
    }
};

class TypeI:public Walk
{
public:
    TypeI(const char Item_type='&', const char Urma1='-', const char Urma2='|', const char Urma3=' ', const char Urma4=' ',
          const char Val='1', int Nr_vieti=4, int Vizor=3, int Acquired=0);
};
class TypeII:public Walk
{
public:
    TypeII(const char Item_type='@', const char Urma1='-', const char Urma2='|', const char Urma3='/', const char Urma4='\\', const char Val='2',
           int Nr_vieti=4, int Vizor=3, int Acquired=0);
   // ~TypeII() {};
};
class TypeIII:public Walk
{
public:
    TypeIII(const char Item_type='$', const char Urma1='-', const char Urma2='|',const char Urma3='/', const char Urma4='\\', const char Val='3',
            int Nr_vieti=4, int Vizor=3, int Acquired=0);
    //~TypeIII() {};
};
#endif // WALK_H
