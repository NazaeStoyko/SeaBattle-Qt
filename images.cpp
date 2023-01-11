#include "images.h"

void Images::load()
{
    images.insert("field",QImage(":/resource/img/background.png"));
    images.insert("dot", QImage(":/resource/img/dot.png"));
    images.insert("full", QImage(":/resource/img/full.png"));
    images.insert("half", QImage(":/resource/img/half.png"));
    images.insert( "redhalf", QImage(":/resource/img/redhalf.png") );
    images.insert( "redfull", QImage(":/resource/img/redfull.png") );
    images.insert( "about", QImage(":/about.png") );
}

QImage& Images::get(const QString& imgName)
{
    QMap<QString,QImage>::Iterator i = images.find(imgName);
    if(i == images.end()) throw 1;
    return i.value();
}


































































//Робочий код

//#include "images.h"

//void Images::load()
//{
//    images.insert("field",QImage(":/resource/img/background.png"));
//    images.insert("dot", QImage(":/resource/img/dot.png"));
//    images.insert("full", QImage(":/resource/img/full.png"));
//    images.insert("half", QImage(":/resource/img/half.png"));
//    images.insert( "redhalf", QImage(":/resource/img/redhalf.png") );
//    images.insert( "redfull", QImage(":/resource/img/redfull.png") );
//    images.insert( "about", QImage(":/about.png") );

//}

//QImage& Images::get(const QString& imgName)
//{
//    QMap<QString,QImage>::Iterator i = images.find(imgName);
//    if(i == images.end()) throw 1;
//    return i.value();
//}
