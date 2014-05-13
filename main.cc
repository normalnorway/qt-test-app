//#include "mainwindow.h"
#include <QApplication>

#include <QNetworkAccessManager>

#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QUrl url { "http://normal.no" };
    QUrl url("http://normal.no");

    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl (url);

    QNetworkReply *reply = manager->get(request);



    return 0;
    /*
    MainWindow w;
    w.show();
    return a.exec();


    cout << "\nHello world\n";

    vector<string> args (argv, argv+argc);
    for (auto &e: args)
        cout << e << ", ";
    cout << endl;
    */
}
