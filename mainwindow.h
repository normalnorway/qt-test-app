#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow (QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent (QKeyEvent *ev)
    {
        switch (ev->key()) {
        case Qt::Key_Escape:
        case Qt::Key_Q:
            qApp->quit();
        }
//        qDebug() << ev->text();
    }

private:
};

#endif // MAINWINDOW_H
