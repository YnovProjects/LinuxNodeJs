#include "serveur.h"

Serveur::Serveur(QObject *parent): QObject(parent)
{

}
void Serveur::start()
{
    serv = new QTcpServer(this);
    timer = 1000;
    tailleMessage=0;
    if(!serv->listen(QHostAddress::Any,3000))
    {
        qDebug()<<"problème sur le listen()"<<endl;
    }
    else
    {
        qDebug()<<"serveur demarre normalement"<<endl;
        connect(serv,SIGNAL(newConnection()),this,SLOT(connexion()));
    }
    while (1)
    {
        if(clients.length()>=1)
        {
            QString message = infoSys();
            envoyer(message);
            QTest::qWait(timer);
        }
        else
        {
            qDebug()<<"en attente de connexion"<<endl;
            QTest::qWait(timer);
        }
    }
}
void Serveur::connexion()
{
    QTcpSocket *nouveauClient = serv->nextPendingConnection();
    qDebug()<<"nouveau client"<<endl;
    clients << nouveauClient;
    connect(nouveauClient,SIGNAL(readyRead()),this,SLOT(donneesRecues()));
    connect(nouveauClient,SIGNAL(disconnected()),this,SLOT(deconnexion()));
}

void Serveur::donneesRecues()
{
    QTcpSocket *socket =qobject_cast<QTcpSocket *>(sender());
    QDataStream in(socket);
    if(tailleMessage==0){
        in>>tailleMessage;
    }
    QString message;
    in>>message;
    qDebug()<<message;
    tailleMessage=0;
    timer-=100;
}

void Serveur::deconnexion()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0)return;
    clients.removeOne(socket);
    socket->deleteLater();
}
void Serveur::envoyer(const QString &message)
{
    qDebug()<<"envoye de message";
    QByteArray paquet;
    QDataStream out(&paquet,QIODevice::WriteOnly);
    out << (quint16)0;
    out << message;
    out.device()->seek(0);
    out<<(quint16)(paquet.size()-sizeof(quint16));
    for (int i = 0; i < clients.size(); i++)
        {
            clients[i]->write(paquet);
        }
}
QString Serveur::infoSys()
{
    system("./script.sh");
    QFile fichier("text2");
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
         QString texte = fichier.readAll();
         fichier.close();
         return texte;
    }
    else
    {
        qDebug()<<"impossible d ouvrir le fichier"<<endl;
        return "error";
    }
}
