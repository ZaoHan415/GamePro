#ifndef MYINPUTSTREAM_H
#define MYINPUTSTREAM_H

#include<fstream>
#include<ios>
#include<QPoint>
#include<QList>
#include<string>
#include <QDebug>
using std::string;
using std::ios_base;
using std::ifstream;
namespace myInput {
enum class dataType{
    coords_of_block,
    coords_of_killer,
    coords_of_door,
    miceEntrance,
    catEntrance,
    coords_of_food,
    mapWidth,
    aiModeSetting,
    speedDecaySetting
};
}
class myInputStream : public ifstream
{
public:
    myInputStream(const string &_s = "dataFile.txt", ios_base::openmode _mode = ios_base::in );
    QList<QPoint> getPos(myInput::dataType t);
    using ifstream::operator>>;
    ifstream& operator>>(QPoint& p);
private:
    string s;
    ios_base::openmode mode;

};

#endif // MYINPUTSTREAM_H
