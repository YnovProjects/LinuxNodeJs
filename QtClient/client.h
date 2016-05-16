#ifndef CLIENT_H
#define CLIENT_H
#include <QtNetwork>
#include <QtWidgets>
#include <QObject>
#include <QtTest>
#include <QApplication>
#include <QTextEdit>
#include <QFile>
#include <QString>
#include <QTextStream>

class Client: public QWidget
{
    Q_OBJECT
    public:
        explicit Client(QWidget *parent=0);
        void decoupe(QString message);
        int affich(int nbr);
        void paintEvent(QPaintEvent *event);
    private slots:
        void donneesRecues();
    private:
        QTcpSocket *socket;
        quint16 tailleMessage;
        QString *estConnecte;
        QString memoire;
        QString vitesse;
        QString core0;
        QString core1;
        QString core2;
        QString core3;
        QString heure;
        QString minute;
        QString seconde;


};

#endif // CLIENT_H
