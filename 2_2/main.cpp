#include <stdio.h>
#include <iostream>
#include <cctype>
#include "modBetaCipher.h"
#include <locale>
using namespace std;
bool isValid(const wstring& s)
{
    for (auto c:s){
        if (!iswalpha(c) || !iswupper(c)){
            throw cipher_error(std::string("A string can contain only a letter"));
            return false;
        }
    }
    return true;
}

void check( wstring text, wstring key)
{
	try {
        if(text.size() == 0){
            throw cipher_error(std::string("String empty"));
        }
		wstring cipherText;
		wstring decryptedText;
        isValid(text);
		modBetaCipher cipher(key);
        cipherText = cipher.encrypt(text);
        decryptedText = cipher.decrypt(cipherText);
        wcout<<L"key="<<key<<endl;
        wcout<<text<<endl;
        wcout<<cipherText<<endl;
        wcout<<decryptedText<<endl;

	} catch (const cipher_error & e) {
		wcerr<<"Error: "<<e.what()<<endl;
	}
}

void interface_program(){
    wstring text;
    int key;
    int op;
    modBetaCipher cipher(key);
    wcout<<L"Cipher ready. Input key: ";
    wcin>>key;
    if (!wcin.good()) {
        wcerr<<L"Key not valid\n";
    }
    do{
    wcout<<L"Cipher ready. Input operation (0-exit, 1-encrypt, 2-decrypt): ";
        wcin>>op;
        if (op > 2) {
            wcout<<L"Wrong operation\n";
        } else if (op >0) {
            wcout<<L"Cipher ready. Input text: ";
            wcin>>text;
            if (isValid(text)) {
                if (op==1) {
                    wcout<<L"Encrypted text: "<<cipher.encrypt(text)<<endl;
                } else {
                    wcout<<L"Decrypted text: "<<cipher.decrypt(text)<<endl;
                }
            } else {
                wcout<<L"Operation aborted: Invalid text\n";
            }
        }
    } while (op!=0);
    
}

int main()
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    int key;
    wstring text;
    unsigned mode_program;
    modBetaCipher cipher(key);
    do {
        wcout<<L"Если хотите перейти к интерфейсу введите (1), если хотите перейти к тестированию введите (2). Выход (0). Ввод: ";
		wcin>>mode_program;
        if (mode_program == 1) {
            interface_program();
        } else if (mode_program == 2){
            wstring lines = L"------------------------------";
			check(L"АНДРЕЙ",L"0");
			wcout<<lines<<endl;
			check(L"АНДРЕЙ",L"");
			wcout<<lines<<endl;
			check(L"АНДРЕЙ",L">!-*k");
			wcout<<lines<<endl;
			check(L"ANDREY",L"3");
			wcout<<lines<<endl;
			check(L"ANDREY22PI1",L"3");
			wcout<<lines<<endl;
			check(L"А/НДРЕЙ!",L"3");
			wcout<<lines<<endl;
			check(L"АНДРЕЙ22ПИ1",L"3");
			wcout<<lines<<endl;
            check(L"КУЧЕРЕНКОВ",L"3");
			wcout<<lines<<endl;
			check(L"",L"3");
			wcout<<lines<<endl;
			return 0;
        }

    }while (mode_program!=0);
    return 0;
}
