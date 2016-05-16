#include "client.h"

Client::Client( QWidget *parent): QWidget(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    socket->connectToHost(QHostAddress("81.65.44.91"),3000);
    QTimer *monTimer = new QTimer(this);
    connect(monTimer, SIGNAL(timeout()), this, SLOT(update()));
    monTimer->start(1000);
    setWindowTitle(tr("Mon serveur"));
    setFixedSize(1500,800);
    memoire="1.0T";
    vitesse="16000";
    core0="30";
    core1="26";
    core2="26";
    core3="28";
    heure="00";
    minute="00";
    seconde="00";
}


void Client::donneesRecues()
{

    QDataStream in(socket);

    if (tailleMessage == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> tailleMessage;
    }
    QString messageRecu;
    in >> messageRecu;
    decoupe (messageRecu);
    tailleMessage = 0;
}
void Client::paintEvent(QPaintEvent *)
{
    static const QPoint C0[4] = {
        QPoint(620,570),
        QPoint(675,570),
        QPoint(675, 20),
        QPoint(620,20)
    };
    static const QPoint C1[4] = {
        QPoint(685,570),
        QPoint(740,570),
        QPoint(740, 20),
        QPoint(685,20)
    };
    static const QPoint C2[4] = {
        QPoint(750,570),
        QPoint(805,570),
        QPoint(805, 20),
        QPoint(750,20)
    };
    static const QPoint C3[4] = {
        QPoint(815,570),
        QPoint(870,570),
        QPoint(870, 20),
        QPoint(815,20)
    };


    static const QPoint Jm[4] = {
        QPoint(330,570),
        QPoint(570,570),
        QPoint(570,70),
        QPoint(330,70)
    };
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(),heure+":"+minute+":"+seconde);
    painter.drawLine(300,0,300,800);
    painter.drawLine(600,0,600,800);
    painter.drawLine(900,0,900,800);
    painter.drawLine(0,650,1200,650);

    painter.setFont(QFont("Arial", 20));
    painter.drawText(10,730, "Vitesse du processeur");
    painter.drawText(310,730,"   Capacite memoire  ");
    painter.drawText(610,730,"      temperature    ");
    painter.drawText(910,730,"        UPTIME       ");

    painter.setFont(QFont("Arial", 15));
    painter.setPen(Qt::red);
    painter.drawText(620,620,"Core0");
    painter.drawText(685,620,"Core1");
    painter.drawText(750,620,"Core2");
    painter.drawText(815,620,"Core3");

    painter.drawConvexPolygon(C0,4);
    painter.setBrush(Qt::red);
    painter.drawRect(620,570-affich(3),55,affich(3));
    painter.setBrush(Qt::NoBrush);
    painter.drawText(625,570-affich(3)-15,core0);
    painter.drawConvexPolygon(C1,4);
    painter.setBrush(Qt::red);
    painter.drawRect(685,570-affich(4),55,affich(4));
    painter.setBrush(Qt::NoBrush);
    painter.drawText(690,570-affich(4)-15,core1);
    painter.drawConvexPolygon(C2,4);
    painter.setBrush(Qt::red);
    painter.drawRect(750,570-affich(5),55,affich(5));
    painter.setBrush(Qt::NoBrush);
    painter.drawText(755,570-affich(5)-15,core2);
    painter.drawConvexPolygon(C3,4);
    painter.setBrush(Qt::red);
    painter.drawRect(815,570-affich(6),55,affich(6));
    painter.setBrush(Qt::NoBrush);
    painter.drawText(820,570-affich(6)-15,core3);


    painter.setPen(Qt::blue);
    painter.setBrush(Qt::NoBrush);
    painter.drawConvexPolygon(Jm,4);
    painter.setBrush(Qt::blue);
    painter.drawRect(330,570-affich(2),240,affich(2));
    painter.setBrush(Qt::NoBrush);


    painter.setPen(Qt::black);
    QList<QChar> uptime;
    uptime[0]=heure[0];
    uptime[1]=heure[1];
    uptime[2]=minute[0];
    uptime[3]=minute[1];
    uptime[4]=seconde[0];
    uptime[5]=seconde[1];
    int x=0;
    for(int i=0;i<6;i++)
    {
        QChar a=uptime[i];
        if(a=='0')
        {
            painter.drawLine(916+x,115,944+x,115);//haut
            painter.drawLine(944+x,125,944+x,300);//haut-droit
            painter.drawLine(916+x,125,916+x,300);//haut-gauche
            painter.drawLine(944+x,320,944+x,520);//bas-droite
            painter.drawLine(916+x,320,916+x,520);//bas-gauche
            painter.drawLine(916+x,535,944+x,535);//bas
        }
        else if(a=='1')
        {
            painter.drawLine(944+x,125,944+x,300);//haut-droit
            painter.drawLine(944+x,320,944+x,520);//bas-droite
        }
        else if(a=='2')
        {
            painter.drawLine(916+x,115,944+x,115);//haut
            painter.drawLine(944+x,125,944+x,300);//haut-droit
            painter.drawLine(916+x,310,944+x,310);//milieu
            painter.drawLine(916+x,320,916+x,520);//bas-gauche
            painter.drawLine(916+x,535,944+x,535);//bas
        }
        else if(a=='3')
        {
            painter.drawLine(916+x,115,944+x,115);//haut
            painter.drawLine(944+x,125,944+x,300);//haut-droit
            painter.drawLine(916+x,310,944+x,310);//milieu
            painter.drawLine(944+x,320,944+x,520);//bas-droite
            painter.drawLine(916+x,535,944+x,535);//bas
        }
        else if(a=='4')
        {
            painter.drawLine(944+x,125,944+x,300);//haut
            painter.drawLine(916+x,125,916+x,300);//haut-droit
            painter.drawLine(916+x,310,944+x,310);//haut-gauche
            painter.drawLine(916+x,310,944+x,310);//milieu
            painter.drawLine(944+x,320,944+x,520);//bas-droite
        }
        else if(a=='5')
        {
            painter.drawLine(916+x,115,944+x,115);//haut
            painter.drawLine(916+x,125,916+x,300);//haut-gauche
            painter.drawLine(916+x,310,944+x,310);//milieu
            painter.drawLine(944+x,320,944+x,520);//bas-droite
            painter.drawLine(916+x,535,944+x,535);//bas
        }
        else if(a=='6')
        {
            painter.drawLine(916+x,115,944+x,115);//haut
            painter.drawLine(916+x,125,916+x,300);//haut-gauche
            painter.drawLine(916+x,310,944+x,310);//milieu
            painter.drawLine(944+x,320,944+x,520);//bas-droite
            painter.drawLine(916+x,320,916+x,520);//bas-gauche
            painter.drawLine(916+x,535,944+x,535);//bas
        }
        else if(a=='7')
        {
            painter.drawLine(916+x,115,944+x,115);//haut
            painter.drawLine(944+x,125,944+x,300);//haut-droit
            painter.drawLine(944+x,320,944+x,520);//bas-droite
        }
        else if(a=='8')
        {
            painter.drawLine(916+x,115,944+x,115);//haut
            painter.drawLine(944+x,125,944+x,300);//haut-droit
            painter.drawLine(916+x,125,916+x,300);//haut-gauche
            painter.drawLine(916+x,310,944+x,310);//milieu
            painter.drawLine(944+x,320,944+x,520);//bas-droite
            painter.drawLine(916+x,320,916+x,520);//bas-gauche
            painter.drawLine(916+x,535,944+x,535);//bas
        }
        else if(a=='9')
        {
            painter.drawLine(916+x,115,944+x,115);//haut
            painter.drawLine(944+x,125,944+x,300);//haut-droit
            painter.drawLine(916+x,125,916+x,300);//haut-gauche
            painter.drawLine(916+x,310,944+x,310);//milieu
            painter.drawLine(944+x,320,944+x,520);//bas-droite
            painter.drawLine(916+x,535,944+x,535);//bas
        }
        x+=50;
    }
}
void Client::decoupe(QString message)
{
    int j=0;
    for(int i=0;i<2;i++)
    {
        core0[i]=message[i];
    }
    for(int i=2;i<5;i++)
    {
        core1[j]=message[i];
        j++;
    }
    j=0;
    for(int i=5;i<8;i++)
    {
        core2[j]=message[i];
        j++;
    }
    j=0;
    for(int i=8;i<11;i++)
    {
        core3[j]=message[i];
        j++;
    }
    j=0;
    for(int i=11;i<20;i++)
    {
        vitesse[j]=message[i];
        j++;
    }
    j=0;
    for(int i=21;i<23;i++)
    {
        heure[j]=message[i];
        j++;
    }
    j=0;
    for(int i=24;i<26;i++)
    {
        minute[j]=message[i];
        j++;
    }
    j=0;
    for(int i=27;i<30;i++)
    {
        seconde[j]=message[i];
        j++;
    }
    j=0;
    int i=30;
    while (!(message[i].isNull()))
    {
        memoire[j]=message[i];
        i++;
        j++;
    }
}

int Client::affich(int nbr)
{
    int nombre=50;
    if(nbr==2)
    {
        nombre=memoire.toLong()/2000000;
    }
    if(nbr==3)
    {
        nombre=core0.toLong()/0.18;
    }
    if(nbr==4)
    {
        nombre=core1.toLong()/0.18;
    }
    if(nbr==5)
    {
        nombre=core2.toLong()/0.18;
    }
    if(nbr==6)
    {
        nombre=core3.toLong()/0.18;
    }
    return nombre;
}

