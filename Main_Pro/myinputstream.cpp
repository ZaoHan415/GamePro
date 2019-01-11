#include "myinputstream.h"
myInputStream::myInputStream(const string &_s, ios_base::openmode _mode )
{
    s = _s;
    mode = _mode;
}

QList<QPoint> myInputStream::getPos(myInput::dataType t)
{
    this->open(s,mode);
    using myInput::dataType;
    string s;
    switch (t)
    {
    case dataType::coords_of_block:
        s = "coords_of_block";
        break;
    case dataType::coords_of_killer:
        s = "coords_of_killer";
        break;
    case dataType::coords_of_door:
        s = "coords_of_door";
        break;
    case dataType::miceEntrance:
        s = "miceEntrance";
        break;
    case dataType::catEntrance:
        s = "catEntrance";
        break;
    case dataType::coords_of_food:
        s = "coords_of_food";
        break;
    case dataType::mapWidth:
        s = "mapWidth";
        break;
    }
    s = s + ":";
    char m[100];
    while (m != s){
        this->getline(m,80);
    }
    int n;
    (*this) >> n;
    QList<QPoint> l;
    QPoint temp;
    for(int i = 0; i < n ;i++){
        *this >> temp;
        l.append(temp);
    }
    this->close();
    return l;
}

ifstream& myInputStream::operator>>(QPoint& p)
{
    int p1,p2;
    (*this) >> p1 >> p2;
    p = QPoint(p1,p2);
    return *this;
}
