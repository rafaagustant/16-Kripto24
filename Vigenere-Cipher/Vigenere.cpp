#include <iostream>
#include <string>
using namespace std;

// Fungsi untuk mengubah huruf menjadi angka (A=0, B=1, ..., Z=25)
int charToNum(char c) {
    return toupper(c) - 'A';
}

// Fungsi untuk mengubah angka menjadi huruf
char numToChar(int n) {
    return (n % 26) + 'A';
}

// Fungsi enkripsi Vigenere Cipher
string encryptVigenere(string plaintext, string key) {
    string ciphertext = "";
    int keyLen = key.length();
    for (int i = 0; i < plaintext.length(); i++) {
        if (isalpha(plaintext[i])) {
            int ptNum = charToNum(plaintext[i]);
            int keyNum = charToNum(key[i % keyLen]);
            int cipherNum = (ptNum + keyNum) % 26;
            ciphertext += numToChar(cipherNum);
        } else {
            ciphertext += plaintext[i]; // Jika bukan huruf, langsung tambahkan
        }
    }
    return ciphertext;
}

// Fungsi dekripsi Vigenere Cipher
string decryptVigenere(string ciphertext, string key) {
    string plaintext = "";
    int keyLen = key.length();
    for (int i = 0; i < ciphertext.length(); i++) {
        if (isalpha(ciphertext[i])) {
            int ctNum = charToNum(ciphertext[i]);
            int keyNum = charToNum(key[i % keyLen]);
            int plainNum = (ctNum - keyNum + 26) % 26;
            plaintext += numToChar(plainNum);
        } else {
            plaintext += ciphertext[i]; // Jika bukan huruf, langsung tambahkan
        }
    }
    return plaintext;
}

// Fungsi untuk menampilkan menu
void showMenu() {
    cout << "\nVigenere Cipher Program\n";
    cout << "1. Enkripsi\n";
    cout << "2. Dekripsi\n";
    cout << "3. Keluar\n";
    cout << "Pilih: ";
}

int main() {
    int pilihan;
    string plaintext, key, ciphertext;

    do {
        showMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: // Enkripsi
                cout << "Masukkan Plaintext: ";
                cin.ignore();
                getline(cin, plaintext);
                cout << "Masukkan Key: ";
                getline(cin, key);
                ciphertext = encryptVigenere(plaintext, key);
                cout << "Ciphertext: " << ciphertext << endl;
                break;

            case 2: // Dekripsi
                cout << "Masukkan Ciphertext: ";
                cin.ignore();
                getline(cin, ciphertext);
                cout << "Masukkan Key: ";
                getline(cin, key);
                plaintext = decryptVigenere(ciphertext, key);
                cout << "Plaintext: " << plaintext << endl;
                break;

            case 3:
                cout << "Keluar dari program...\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 3);

    return 0;
}
