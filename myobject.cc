#include "myobject.h"
#include <QDebug>
//#include <QApplication>
#include <QCoreApplication>
#include <QNetworkRequest>


MyObject::MyObject (QObject *parent) :
    QObject (parent)
{
    qDebug() << "ctor";
}


MyObject::~MyObject()
{
    qDebug() << "dtor";
}


void MyObject::replyFinished (QNetworkReply *reply)
{
    qDebug() << reply->isFinished();
    qDebug() << reply->error();
//    qDebug() << reply->errorString();
    qDebug() << reply->attribute (QNetworkRequest::HttpStatusCodeAttribute);
    qDebug() << reply->readAll();

    qApp->quit();
}
