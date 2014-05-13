#include "mainwindow.h"
#include <QApplication>

#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "\nHello world\n";

    vector<string> args (argv, argv+argc);
    for (auto &e: args)
        cout << e << ", ";
    cout << endl;

    return 0;

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
