#include "modBetaCipher.h"
using namespace std;

modBetaCipher::modBetaCipher(std::wstring & ws_key)
{
	key1 = getValidKey(ws_key);
}

inline int modBetaCipher::getValidKey(std::wstring & ws_key)
{
	if (ws_key.empty())
		throw cipher_error("Empty key");
	std::string s_key = codec.to_bytes(ws_key);
	for (auto & c:ws_key) {
		if (!iswdigit(c)) {
			throw cipher_error(std::string("Invalid key") + s_key);
		}
	}
	int key = std::stoi(ws_key);
	if (key<=0) {
		throw cipher_error(std::string("Invalid key. Enter a number > 0"));
	}
	return key;
}

std::wstring modBetaCipher::encrypt(const std::wstring& open_text) // шифрование
{
    wstring tabl = open_text;
    int dl, nstrok, index, x;
    dl = open_text.length(); // введенный текст
    nstrok = (dl - 1) / key1 + 1; // кол-во столбцов
    x = 0;
    for (int i = key1; i > 0; i--) { // столбцы
        for (int j = 0; j < nstrok; j++) { // строки
            index = i+key1*j;
            if (index-1 < dl) {
                tabl[x] = open_text[index-1];
                x++;
            }
        }
    }
    return tabl;
}

std::wstring modBetaCipher::decrypt(const std::wstring& cipher_text) // расшифрование
{
    wstring tabl = cipher_text;
    int dl, nstrok, index, x;
    dl = cipher_text.length();
    nstrok = (dl - 1) / key1 + 1; // кол-во столбцов
    x = 0;
    for (int i = key1; i > 0; i--) { // столбцы
        for (int j = 0; j < nstrok; j++) { // строки
            index = i+key1*j;
            if (index-1 < dl) {
                tabl[index-1] = cipher_text[x];
                x++;
            }
        }
    }
    return tabl;
}
