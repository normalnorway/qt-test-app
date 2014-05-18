//#include "myobject.h"

//#include <QCoreApplication>
#include <QApplication>
#include <QMainWindow>
#include <QBoxLayout>
#include <QLabel>
#include <QFont>
#include <QScrollArea>

#include <QtDebug>
#include <QString>
#include <QFile>
#include <QUrl>
#include <QDateTime>
#include <QList>
//#include <QTextStream>

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
QList<RssEntry> parse_rss (QFile &file);


int main(int argc, char *argv[])
{
//    QCoreApplication app (argc, argv);
    QApplication app (argc, argv);

    //QFile file ("rss.xml");
    QFile file (":/resources/rss.xml");
    if (not file.open (QIODevice::ReadOnly)) return 0;
    QList<RssEntry> rss_entries = parse_rss (file);

//    foreach (const RssEntry &e, rss_entries)
//        qDebug() << e.title;
//    return 0;

    QFont font1 ("sans", 12, QFont::Bold);
    QFont font2 ("sans", 10, -1, true);

    QMainWindow win;
    QBoxLayout *layout = new QVBoxLayout;

    // Pack into layout
    foreach (const RssEntry &e, rss_entries)
    {
        QLabel *title = new QLabel;
        //title->setText (e.title);
        title->setText (QString("<a href='%1'><span style='text-decoration: none;'>%2</span></a>").arg(e.link.toString()).arg(e.title));
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

    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget (vbox);
//    scroll->resize (500, 800);

    //win.resize (400, 800);
    //vbox->setMaximumSize (400, 800);
//    win.setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Fixed);
//    win.setMaximumSize (400, 800);

    win.resize (400, 800);
    win.setCentralWidget (scroll);
    win.show();
    return app.exec();

    /*
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
    for (int i=0; i<nlist.length(); ++i)
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
