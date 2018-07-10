#include "dataoperationssl.h"


#ifndef MASSEGE_FILE
#define MASSEGE_FILE "/Users/levkargalov/Documents/Projects/Programming/C++/NetworkingTest/sslTest/message.txt"
#endif

#ifndef OUTMASSEGE_FILE
#define OUTMASSEGE_FILE "/Users/levkargalov/Documents/Projects/Programming/C++/NetworkingTest/sslTest/out.txt"
#endif

#ifndef CYPHER_FILE
#define CYPHER_FILE "/Users/levkargalov/Documents/Projects/Programming/C++/NetworkingTest/sslTest/rsa.file"
#endif

#ifndef PUB_KEY_FILE
#define PUB_KEY_FILE "/Users/levkargalov/Documents/Projects/Programming/C++/NetworkingTest/sslTest/pivate.key"
#endif

#ifndef PRIV_KEY_FILE
#define PRIV_KEY_FILE "/Users/levkargalov/Documents/Projects/Programming/C++/NetworkingTest/sslTest/public.key"
#endif

DataOperationSSL::DataOperationSSL(char* password)
: password_(password)
{

}

DataOperationSSL::~DataOperationSSL()
{

}

void DataOperationSSL::keyGen()
{
    /* указатель на структуру для хранения ключей */
    RSA * rsa = NULL;
    unsigned long bits = 1024; /* длина ключа в битах */
    FILE * privKey_file = NULL, *pubKey_file = NULL;
    /* контекст алгоритма шифрования */
    const EVP_CIPHER *cipher = NULL;
    /*Создаем файлы ключей*/


    privKey_file = fopen(PRIV_KEY_FILE, "wb");
    pubKey_file = fopen(PUB_KEY_FILE, "wb");

    /* Генерируем ключи */
    rsa = RSA_generate_key(bits, RSA_F4, NULL, NULL);
    /* Формируем контекст алгоритма шифрования */
    cipher = EVP_get_cipherbyname("bf-ofb");
    //Получаем из структуры rsa открытый и секретный ключи и сохраняем в файлах.
    //Секретный ключ шифруем с помощью парольной фразы

    PEM_write_RSAPrivateKey(privKey_file, rsa, cipher, NULL, 0, NULL, password_);
    PEM_write_RSAPublicKey(pubKey_file, rsa);

    /* Освобождаем память, выделенную под структуру rsa */
    RSA_free(rsa);
    fclose(privKey_file);
    fclose(pubKey_file);
    std::cout << "Ключи сгенерированы и помещены в папку с исполняемым файлом" << std::endl;
}

void DataOperationSSL::enctypt()
{
    /* структура для хранения открытого ключа */
    RSA * pubKey = NULL;
    FILE * pubKey_file = NULL;
    unsigned char *ctext, *ptext;
    int inlen, outlen;
    /* Считываем открытый ключ */
    pubKey_file = fopen(PUB_KEY_FILE, "rb");
    pubKey = PEM_read_RSAPublicKey(pubKey_file, NULL, NULL, NULL);
    fclose(pubKey_file);

    /* Определяем длину ключа */
    int key_size = RSA_size(pubKey);
    ctext = (unsigned char *)malloc(key_size); // указатель на крипто текст
    ptext = (unsigned char *)malloc(key_size); //указатель на текст
    OpenSSL_add_all_algorithms();


    int in = open(MASSEGE_FILE, O_RDWR);
    int out = open(CYPHER_FILE, O_CREAT|O_TRUNC|O_RDWR, 0600);
    /* Шифруем содержимое входного файла */
    while (1) {

        inlen = read(in, ptext, key_size - 11);

        if (inlen <= 0) break;
        outlen = RSA_public_encrypt(inlen, ptext, ctext, pubKey, RSA_PKCS1_PADDING);

        if (outlen != RSA_size(pubKey)) exit(-1);
        write(out, ctext, outlen);
    }
    std::cout << "Содержимое файла in.txt было зашифровано и помещено в файл rsa.file" << std::endl;
}

void DataOperationSSL::decrypt()
{

        RSA * privKey = NULL;
        FILE * privKey_file;
        unsigned char *ptext, *ctext;
        int inlen, outlen;

        /* Открываем ключевой файл и считываем секретный ключ */
        OpenSSL_add_all_algorithms();
        privKey_file = fopen(PRIV_KEY_FILE, "rb");
        privKey = PEM_read_RSAPrivateKey(privKey_file, NULL, NULL, password_);

        /* Определяем размер ключа */
        int key_size = RSA_size(privKey);
        ptext = (unsigned char *)malloc(key_size);
        ctext = (unsigned char *)malloc(key_size);

        int out = open(OUTMASSEGE_FILE, O_CREAT | O_TRUNC | O_RDWR, 0600);
        int in = open(CYPHER_FILE, O_RDWR);

        /* Дешифруем файл */
        while (1) {
            inlen = read(in, ctext, key_size);
            if (inlen <= 0) break;
            outlen = RSA_private_decrypt(inlen, ctext, ptext, privKey, RSA_PKCS1_PADDING);
            if (outlen < 0) exit(0);
            write(out, ptext, outlen);
        }
        std::cout << "Содержимое файла rsa.file было дешифровано и помещено в файл out.txt" << std::endl;


}
