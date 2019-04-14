#ifndef WALK_H
#define WALK_H


class Walk
{
    public:
        Walk();
        ~Walk();
    virtual const char getItem()
    {
        return item_type;
    }
    protected:

    private:
        const char urma1='-';
const char urma2='|';
const char item_type='%';
};
class TypeI:public Walk
{ const char item_type='&';
const char urma1='-';
const char urma2='|';
const char val='1';
public:
    const char getItem()
    {
        return item_type;
    }
    const char getVal()
    {
        return val;
    }
    friend void movement();
};
class TypeII:public Walk
{ const char item_type='@';
    const char val='2';
const char urma1='-';
const char urma2='|';
public:
    const char getItem()
    {
        return item_type;
    }
};
class TypeIII:public Walk
{    const char item_type='$';
    const char val='3';
const char urma1='-';
const char urma2='|';
public:
const char getItem()
    {
        return item_type;
    }
};
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
    //friend void Move_on_line(char**&harta, int**&warning, int x, int y, int nr_obiecte, const char destinatie);
    friend void Move_on_line(Map &obj, int**&, int, int, int);
    friend int check_bombs_onLine(int, int, Map);
    friend void check(Map obj, int**&warning, int x, int y, Walk robot, int &nr_obiecte);
    Map(int L=15, int H=15, const char B='#', int n_bomb=7, int n_item=3, const char D='X', const char item1=' ',
        const char item2=' ', const char item3=' ', const char item4=' ');

    ~Map(){};

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
#endif // WALK_H
