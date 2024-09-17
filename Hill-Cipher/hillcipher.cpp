#include <iostream>
#include <vector>
#include <string>

using namespace std;

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

int determinant2x2(vector<vector<int>> matrix) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

vector<vector<int>> inverseMatrix2x2(vector<vector<int>> matrix, int modulus) {
    int det = determinant2x2(matrix) % modulus;
    if (det < 0) det += modulus;
    
    int detInv = modInverse(det, modulus);
    if (detInv == -1) {
        cout << "Matriks tidak memiliki invers, tidak bisa dekripsi." << endl;
        exit(1);
    }

    vector<vector<int>> inverse(2, vector<int>(2));
    inverse[0][0] = matrix[1][1] * detInv % modulus;
    inverse[0][1] = -matrix[0][1] * detInv % modulus;
    inverse[1][0] = -matrix[1][0] * detInv % modulus;
    inverse[1][1] = matrix[0][0] * detInv % modulus;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (inverse[i][j] < 0) inverse[i][j] += modulus;
        }
    }

    return inverse;
}

vector<int> encrypt(vector<int> plainteks, vector<vector<int>> keyMatrix) {
    vector<int> cipher(2);
    cipher[0] = (keyMatrix[0][0] * plainteks[0] + keyMatrix[0][1] * plainteks[1]) % 26;
    cipher[1] = (keyMatrix[1][0] * plainteks[0] + keyMatrix[1][1] * plainteks[1]) % 26;
    return cipher;
}

vector<int> decrypt(vector<int> cipherteks, vector<vector<int>> inverseKeyMatrix) {
    vector<int> plainteks(2);
    plainteks[0] = (inverseKeyMatrix[0][0] * cipherteks[0] + inverseKeyMatrix[0][1] * cipherteks[1]) % 26;
    plainteks[1] = (inverseKeyMatrix[1][0] * cipherteks[0] + inverseKeyMatrix[1][1] * cipherteks[1]) % 26;
    return plainteks;
}

void process(string text, vector<vector<int>> keyMatrix, bool isEncrypt) {
    if (text.length() % 2 != 0) text += 'X';

    vector<int> textNumeric(2);
    string result = "";

    vector<vector<int>> inverseKeyMatrix;
    if (!isEncrypt) {
        inverseKeyMatrix = inverseMatrix2x2(keyMatrix, 26);
    }

    for (int i = 0; i < text.length(); i += 2) {
        textNumeric[0] = toupper(text[i]) - 'A';
        textNumeric[1] = toupper(text[i + 1]) - 'A';

        vector<int> processedText;
        if (isEncrypt) {
            processedText = encrypt(textNumeric, keyMatrix);
        } else {
            processedText = decrypt(textNumeric, inverseKeyMatrix);
        }

        result += (char)(processedText[0] + 'A');
        result += (char)(processedText[1] + 'A');
    }

    cout << (isEncrypt ? "Cipherteks" : "Plainteks") << ": " << result << endl;
}

void inputKeyMatrix(vector<vector<int>>& keyMatrix) {
    cout << "Masukkan matriks kunci 2x2 (nilai integer):" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << "Key[" << i << "][" << j << "]: ";
            cin >> keyMatrix[i][j];
        }
    }
}

int main() {
    vector<vector<int>> keyMatrix(2, vector<int>(2));
    int pil;
    string text;
    bool stop = false;

    inputKeyMatrix(keyMatrix);

    while (!stop) {
        cout << "\nMenu: " << endl;
        cout << "1. Enkripsi" << endl;
        cout << "2. Dekripsi" << endl;
        cout << "3. Ganti Key" << endl;
        cout << "4. Exit" << endl;
        cout << "Pilih menu: ";
        cin >> pil;

        switch (pil) {
            case 1:
                cout << "Masukkan plainteks: ";
                cin.ignore();
                getline(cin, text);
                process(text, keyMatrix, true);
                break;
            case 2:
                cout << "Masukkan cipherteks: ";
                cin.ignore();
                getline(cin, text);
                process(text, keyMatrix, false);
                break;
            case 3:
                inputKeyMatrix(keyMatrix);
                break;
            case 4:
                stop = true;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}
