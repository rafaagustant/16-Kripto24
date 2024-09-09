#include <iostream>
#include <string>

using namespace std;

void enkripsi() {
    string plainteks, cipherteks;
    int i, k;
    char c;

    cout << "Ketikkan pesan: ";
    cin.ignore();
    getline(cin, plainteks);

    cout << "Masukkan jumlah pergesaran (0-25): ";
    cin >> k;

    cipherteks = ""; // inisialisasi cipherteks dengan string kosong

    for (i = 0; i < plainteks.length(); i++) {
        c = plainteks[i];

        if (isalpha(c)) { // hanya memproses huruf alfabet saja
            c = toupper(c); // ubah menjadi huruf kapital
            c = c - 65; // kodekan huruf ke angka 0 s/d 25

            c = (c + k) % 26; // enkripsi dengan menggeser sejauh k ke kanan
            c = c + 65; // kodekan kembali ke huruf semula
        }

        cipherteks += c; // sambungkan ke cipherteks
    }

    cout << "Cipherteks: " << cipherteks << endl; // cetak cipherteks
}

void dekripsi() {
    string plainteks, cipherteks;
    int i, k;
    char c;

    cout << "Ketikkan cipherteks: ";
    cin.ignore();
    getline(cin, cipherteks);

    cout << "Masukkan jumlah pergesaran (0-25): ";
    cin >> k;

    plainteks = ""; // inisialisasi plainteks dengan string kosong

    for (i = 0; i < cipherteks.length(); i++) {
        c = cipherteks[i];

        if (isalpha(c)) { // hanya memproses huruf alfabet saja
            c = toupper(c); // ubah menjadi huruf kapital
            c = c - 65; // kodekan huruf ke angka 0 s/d 25

            if (c - k < 0) {
                c = 26 + (c - k); // kasus bilangan negatif
            } else {
                c = (c - k) % 26; // dekripsi dengan menggeser sejauh k ke kiri
            }

            c = c + 65; // kodekan kembali ke huruf semula
            c = tolower(c); // plainteks dinyatakan sebagai huruf kecil
        }

        plainteks += c; // sambungkan ke plainteks
    }

    cout << "Plainteks: " << plainteks << endl; // cetak plainteks
}

int main() {
    int pil;
    bool stop = false;

    while (!stop) {
        cout << "Menu: " << endl;
        cout << "1. Enkripsi" << endl;
        cout << "2. Dekripsi" << endl;
        cout << "3. Exit" << endl;
        cout << "Pilih menu: ";
        cin >> pil;

        switch (pil) {
            case 1:
                enkripsi();
                break;
            case 2:
                dekripsi();
                break;
            case 3:
                stop = true;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}
