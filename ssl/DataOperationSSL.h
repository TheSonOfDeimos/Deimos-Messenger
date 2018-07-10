#ifndef DataSSL
#define DataSSL

#include <stdio.h>
#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <unistd.h>
#include <fcntl.h>

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



#endif
