#ifndef SERVEUR_H
#define SERVEUR_H
#include <QtNetwork>
#include <QtWidgets>
#include <QObject>
#include <QtTest>
#include <QApplication>
#include <QTextEdit>
#include <QFile>
#include <QString>
#include <QTextStream>

class Serveur : public QObject
{
    Q_OBJECT
    public:
        explicit Serveur(QObject *parent =0);
        void start();
        void envoyer(const QString &message);
        QString infoSys();
    private slots:
        void connexion();
        void donneesRecues();
        void deconnexion();
    private:
        quint16 timer;
        QTcpServer *serv;
        QList<QTcpSocket *> clients;
        quint16 tailleMessage;

};

#endif // SERV_H
