#ifndef WALK_H
#define WALK_H

class Walk
{
public:
    Walk(const char Urma1='-', const char Urma2='|', const char Item_type='%', const char Val=' ');
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
protected:

private:
    const char urma1;
    const char urma2;
    const char item_type;
    const char val;
};
class TypeII;
class Map:public Walk
{
    int l;
    int h;
    const char destinatie;
    const char bomb;
    int nr_capcane;
    int nr_itemi;
    char**harta;
public:
    friend void movementIII(Walk& robot, Map &obj, int&x, int&y);
    friend void movementII(Walk& robot, Map &obj, int&x, int&y);
    friend void movementI(Walk&, Map&, int&, int&);
    friend void Move_on_column_down(Map&obj, int& x, int& y, Walk& robot, int& destination);
    friend void Move_on_column_up(Map&obj, int& x, int& y, Walk& robot, int& destination);
    friend void Move_on_line_backward(Map&obj, int& x, int& y, Walk& robot, int& destination);
    friend void Move_on_line_forward(Map &obj, int&, int&, Walk&, int& destination);
    friend int check_bombs_onLine(int, int, Map);
    friend void check(Map obj, int**&warning, int x, int y, Walk& robot, int &nr_obiecte);
    friend void Move_on_the_diagonal_forward_up(Map&obj, int& x, int& y, Walk& robot, int& destination);
    friend void Move_on_the_diagonal_forward_down(Map&obj, int& x, int& y, Walk& robot, int& destination);
    friend void Move_on_the_diagonal_backward_up(Map&obj, int& x, int& y, Walk& robot, int& destination);
    friend void Move_on_the_diagonal_backward_down(Map&obj, int& x, int& y, Walk& robot, int& destination);
    friend int Move_towards_item_column(Map&obj, int& x, int& y, Walk& robot, int& destination);
    friend int Move_towards_item_line(Map&obj, int& x, int& y, Walk& robot, int& destination);
    friend int Move_towards_item_diagonal(Map&obj, int& x, int& y, Walk& robot, int& destination);

    Map(int L=15, int H=15, const char B='#', int n_bomb=7, int n_item=3, const char D='X', const char item1=' ',
        const char item2=' ', const char item3=' ', const char item4=' ');
    ~Map() {};

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
    //const char item_type;
//const char urma1;
//const char urma2;
//const char val;
public:
    friend void movementI(Walk&, Map&);
    TypeI(const char Item_type='&', const char Urma1='-', const char Urma2='|', const char Val='1');
    ~TypeI() {};
    /*const char getItem()
    {
        return item_type;
    }
    const char getVal()
    {
        return val;
    }*/

};
class TypeII:public Walk
{
    //const char item_type;
    //const char val;
//const char urma1;
//const char urma2;
    const char urma3;
    const char urma4;
public:
    friend void movementII(Walk& robot, Map &obj, int&x, int&y);
    TypeII(const char Item_type='@', const char Urma1='-', const char Urma2='|', const char Urma3='/', const char Urma4='\\', const char Val='2');
    ~TypeII() {};
    /*const char getItem()
    {
        return item_type;
    }*/
    const char getUrma3()
    {
        return urma3;

    }
    const char getUrma4()
    {
        return urma4;

    }
};
class TypeIII:public Walk
{
    //const char item_type;
    //const char val;
    const char urma3;
    const char urma4;
public:
    TypeIII(const char Item_type='$', const char Urma1='-', const char Urma2='|',const char Urma3='/', const char Urma4='\\', const char Val='3');
    ~TypeIII() {};

    const char getUrma3()
    {
        return urma3;

    }
    const char getUrma4()
    {
        return urma4;

    }

};

#endif // WALK_H
