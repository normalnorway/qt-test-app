/*
QString location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
*/

#define ANDROID 0
#if ANDROID != 0
#  define HAVE_TOUCH
#endif

//#include "myobject.h"
#include "mainwindow.h"

#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QFont>
#include <QScrollArea>
#include <QDesktopWidget>
#include <QPushButton>

#include <QtGlobal>
#include <QtDebug>
#include <QString>
#include <QFile>
#include <QUrl>
#include <QDateTime>
#include <QList>
#include <QTextStream>

#include <QScroller>
//#include <QGesture>
//#include <QPanGesture>

//#include <QNetworkAccessManager>
//#include <QNetworkRequest>
//#include <QNetworkReply>

#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include <QDomNode>
#include <QDomText>


/** Types */
struct RssEntry
{
    QString title;
    QDateTime pubDate;
    QUrl link;
    QString description;
};


/** Functions */
QList<RssEntry>     parse_rss               (QFile&);

QScroller*          install_kinetic_scoller (QWidget*);

void                my_message_handler      (QtMsgType,
                                             const QMessageLogContext&,
                                             const QString&);



/** Program entry point */
int main(int argc, char *argv[])
{
    //qInstallMessageHandler (my_message_handler);
    QApplication app (argc, argv);
    MainWindow win;

//    QDesktopWidget *desk = QApplication::desktop();
//    qDebug() << desk->screenCount() << desk->screenGeometry() << desk->availableGeometry();
//    return 0;

    //QFile file ("rss.xml");
    QFile file (":/resources/rss.xml");
    if (not file.open (QIODevice::ReadOnly)) return 0;
    QList<RssEntry> rss_entries = parse_rss (file);

    /** Layout */
    QBoxLayout *layout = new QVBoxLayout;
    QFont font1 ("sans", 12, QFont::Bold);
    QFont font2 ("sans", 10, -1, true);

    // Header
    {
        // resources/logo.png PNG 397x142
        QPixmap pixmap (":/resources/logo.png");
        QLabel *l = new QLabel;
        l->setPixmap (pixmap.scaledToWidth (280, Qt::SmoothTransformation));
        l->setAlignment (Qt::AlignHCenter);
        layout->addWidget (l);
        layout->addSpacing (15);
    }

    QLabel label ("<h2>Destroy <em>the</em> phone?</h2>");
    label.setAlignment (Qt::AlignHCenter);
    layout->addWidget (&label);
    layout->addSpacing (10);

    QPushButton *btn;
    btn = new QPushButton ("&Yes");
    layout->addWidget (btn);
    btn = new QPushButton ("&No");
    layout->addWidget (btn);
    btn = new QPushButton ("&Maybe");
    layout->addWidget (btn);
    btn = new QPushButton ("&Show Log");
    QObject::connect (btn, SIGNAL(clicked(bool)),
                      &win, SLOT(showLog()));
    layout->addWidget (btn);

    layout->addSpacing (20);
    layout->addWidget (new QLabel ("<b>News feed:</b>"));
    layout->addSpacing (10);


    // Rss-section
    foreach (const RssEntry &e, rss_entries)
    {
        QLabel *title = new QLabel;
        title->setText (e.title);
//        title->setText (QString("<a href='%1'><span style='text-decoration: none;'>%2</span></a>").arg(e.link.toString()).arg(e.title));
//        title->setText (QString("<a href='%1'>%2</a>").arg(e.link.toString()).arg(e.title));
        title->setOpenExternalLinks (true);
        title->setFont (font1);
        title->setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Fixed);
        title->setFixedWidth (360);
        title->setWordWrap (true);
        layout->addWidget (title);

        QLabel *date = new QLabel;
        date->setText (e.pubDate.toString());
        date->setFont (font2);
        date->setStyleSheet ("QLabel { color : #444; }");
        layout->addWidget (date);

        /*
        QLabel *link = new QLabel;
        link->setText (QString("<a href='%1'>%2</a>").arg(e.link.toString()).arg(e.link.toString()));
        link->setOpenExternalLinks (true);
        layout->addWidget (link);
        */

        layout->addSpacing (10);
    }

    QWidget *vbox = new QWidget;
    vbox->setLayout (layout);
    vbox->setSizePolicy (QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    QScrollArea *area = new QScrollArea;
    area->setWidget (vbox);
//    area->resize (500, 800);
//    area->grabGesture (Qt::PanGesture);

    // Kinetic scrolling
    // BUG: screws up scrollbar; so grab gesture on scroll->viewport()?
#ifdef HAVE_TOUCH
    QScroller::grabGesture (area);
    area->setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
#else
    QScroller::grabGesture (area, QScroller::LeftMouseButtonGesture);
//    QScroller *scroll = QScroller::scroller (area);
//    qDebug() << scroll->pixelPerMeter();
#endif
    // @todo setSnapPositionsY, stop, velocity, scrollTo, ensureVisible
    // class QFlickGestureRecognizer;
    // class QMouseFlickGestureRecognizer;
    // QScrollArea::ensureWidgetVisible

//    MainWindow win;

    // trying to get gestures to work ...
//    win.setAttribute (Qt::WA_AcceptTouchEvents);
//    win.setAttribute (Qt::WA_TouchPadAcceptSingleTouchEvents);
//    win.setAttribute (Qt::WA_WState_AcceptedTouchBeginEvent);
//    win.setAttribute (Qt::WA_MouseTracking);
//    win.grabGesture (Qt::PanGesture);

    win.resize (400, 800);
    win.setCentralWidget (area);
    win.show();
    return app.exec();

    /*
    smallscreen ? win.showMaximized() : win.show();
#if defined(Q_WS_MAC)
    mw.raise();
#endif


    QNetworkAccessManager manager;
    MyObject obj;
    connect (&manager, SIGNAL(finished(QNetworkReply*)),
             &obj, SLOT(replyFinished(QNetworkReply*)));
    QUrl url ("http://sirus.no/?template=norRssNews");
    manager.get (QNetworkRequest (url));
    */
}



QList<RssEntry> parse_rss (QFile &file)
{
    QDomDocument dom;
    if (not dom.setContent (&file))
        qFatal ("Error parsing rss document");
    file.close();

    QDomNodeList nlist = dom.elementsByTagName ("item");
    QList<RssEntry> rss_entries;
    rss_entries.reserve (nlist.length());
    for (int i=0; i<nlist.length(); ++i)    // rename nlist -> L ?
    {
        QDomNode node, item = nlist.item(i);
        QDomText text;
        RssEntry entry;

        node = item.namedItem ("title");
        text = node.firstChild().toText();
        Q_ASSERT (!text.isNull());
        // @todo assert only one child
        entry.title = text.data();

        node = item.namedItem ("pubDate");
        text = node.firstChild().toText();
        entry.pubDate = QDateTime::fromString (text.data(), Qt::RFC2822Date);

        node = item.namedItem ("link");
        text = node.firstChild().toText();
        entry.link = QUrl (text.data());

        rss_entries.append (entry);
//        qDebug() << entry.pubDate.toString();
//        break;
    }

    return rss_entries;
}



void my_message_handler (QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QFile logfile ("logfile.txt");
    static QTextStream stream;
    if (not logfile.isOpen()) {
        logfile.open (QIODevice::Append | QIODevice::Text);
        stream.setDevice (&logfile);
    }

    const char* level;
    switch (type) {
    case QtDebugMsg:    level="Debug";      break;
    case QtWarningMsg:  level="Warning";    break;
    case QtCriticalMsg: level="Critical";   break;
    case QtFatalMsg:    level="Fatal";      break;
    default:            level="Unknown";
    }
    Q_UNUSED (context); // context.file, context.line, context.function
    // @todo add timestamp
    stream << QString("%1: %2").arg(level).arg(msg) << "\n";
    stream.flush();
}




QScroller* install_kinetic_scoller (QWidget *w)
{
    QAbstractScrollArea *area = qobject_cast<QAbstractScrollArea *> (w);
    Q_ASSERT (area);
#ifdef HAVE_TOUCH
    QScroller::grabGesture (area->viewport());
#else
    QScroller::grabGesture (area->viewport(), QScroller::LeftMouseButtonGesture);
#endif
    return QScroller::scroller (w);
}
