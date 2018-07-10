#ifndef DATAOPERATIONSSL_H
#define DATAOPERATIONSSL_H

#include <stdio.h>
#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <fcntl.h>
#include<unistd.h>

class DataOperationSSL
{
public:
    DataOperationSSL(char* password);
    ~DataOperationSSL();
    void keyGen();
    void enctypt();
    void decrypt();

private:
    char* password_;

};

#endif // DATAOPERATIONSSL_H
