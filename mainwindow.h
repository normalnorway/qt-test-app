#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QEvent>

#include <QDebug>
#include <QApplication>
#include <QGestureEvent>

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
    }

  public slots:
    void showLog() {
        qDebug() << "showLog";
    }

  protected:
    virtual bool event (QEvent *ev)
    {
//        static size_t cnt=0;
//        qDebug() << "Event" << cnt++;
//        @todo print event name/type

        // Q: why never reached? removed by eventFilter? move to eventFilter
        if (ev->type() == QEvent::Scroll) {
            QScrollEvent *se = static_cast <QScrollEvent*> (ev);
            qDebug() << "ScrollEvent"
                     << se->contentPos()
                     << se->overshootDistance();
            //QScroller *scroller = QScroller::scroller (m_widget);
            //QPointF v = scroller->velocity();
            //v.rx() *= scroller->pixelPerMeter().x();
            //v.ry() *= scroller->pixelPerMeter().y();
        }

        return QWidget::event (ev);
        /*
        if (ev->type() == QEvent::TouchBegin) {
            qDebug() << "TouchBegin";
            ev->accept();
            return true;
        }

        if (ev->type() == QEvent::GestureOverride)
            qDebug() << "QGestureOverride";

        if (ev->type() != QEvent::Gesture)
            return QWidget::event (ev);

        qDebug() << "Gesture";
        QGestureEvent *ge = static_cast<QGestureEvent*> (ev);
        QGesture *pan = ge->gesture (Qt::PanGesture);
        if (not pan) return QWidget::event (ev);

        panTriggered (static_cast<QPanGesture*> (pan));
        return true;
        */
    }

  private:
    void panTriggered (QPanGesture *gesture)
    {
        Q_UNUSED (gesture);
        qDebug() << "Pan";
    }
};

#endif // MAINWINDOW_H
