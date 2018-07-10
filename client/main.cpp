#include <QApplication>
#include "dialog.h"
#include "dataoperationssl.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    char ps[] = "Lev";
    char* sic = ps;
    DataOperationSSL ss(ps);
    ss.keyGen();
    ss.enctypt();
    Dialog w;
    w.show();




    return a.exec();
}
