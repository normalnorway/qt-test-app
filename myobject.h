#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QNetworkReply>


class MyObject : public QObject
{
    Q_OBJECT

  public:
    MyObject (QObject *parent = 0);
    ~MyObject();   

  public slots:
    void replyFinished (QNetworkReply*);

  private:

};


#endif // MYOBJECT_H
