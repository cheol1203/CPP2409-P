#include "CaesarCipher.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

// 시저 암호로 텍스트를 암호화하는 함수
string CaesarCipher::EncryptCaesar(const string &text, int shift) {
    string encrypted_text = text;
    for (char &c : encrypted_text) {
        if (isalpha(c)) { // 알파벳만 암호화
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + shift) % 26 + base;
        }
    }
    return encrypted_text;
}

// 시저 암호로 텍스트를 복호화하는 함수
string CaesarCipher::DecryptCaesar(const string &text, int shift) {
    return EncryptCaesar(text, 26 - shift); // 복호화는 암호화의 반대
}

// 비밀번호 설정 함수
void CaesarCipher::SetPassword() {
    cout << "새 비밀번호를 설정하세요: ";
    getline(cin, password);
    cout << "비밀번호가 설정되었습니다." << endl;
}

bool CaesarCipher::VerifyPassword() {
    if (password.empty()) return true; // 비밀번호가 설정되지 않은 경우 바로 접근

    string entered_password;
    cout << "비밀번호를 입력하세요: ";
    getline(cin, entered_password);

    if (entered_password == password) {
        cout << "비밀번호가 확인되었습니다." << endl;
        return true;
    } else {
        cout << "비밀번호가 일치하지 않습니다!" << endl;
        return false;
    }
}

// 암호화된 텍스트를 파일에 저장(단, 덮어쓰기 됨)
void CaesarCipher::EncryptedText() {
    string text, shift_input;
    cout << "암호화할 텍스트를 입력하세요: ";
    getline(cin, text);                     // 띄어쓰기를 포함한 암호화할 텍스트 입력하기

    cout << "시프트 값을 입력하세요 (1~25): ";// 알파벳은 총 26자리가 있기때문에 1~25숫자만 가능 26 입력 시 동일한 텍스트가 나옴
    getline(cin, shift_input);              // 시프트 값 입력

    int shift;
    try {
        shift = stoi(shift_input);
        if (shift < 1 || shift > 25) throw out_of_range("1~25 범위를 벗어남");
    } catch (exception &e) {
        cout << "유효하지 않은 시프트 값입니다: " << e.what() << endl;
        return;
    }

    // 암호화 및 파일 저장 (덮어쓰기)
    string encrypted_text = EncryptCaesar(text, shift);
    ofstream out_file("encrypted.txt");
    if (out_file.is_open()) {
        out_file << encrypted_text << endl;
        out_file.close();
        cout << "암호화된 텍스트가 파일에 저장되었습니다." << endl;
    } else {
        cout << "파일을 열 수 없습니다." << endl;
    }
}

// 암호화된 텍스트를 추가로 파일에 저장
void CaesarCipher::AddEncryptedText() {
    string text, shift_input;
    cout << "추가로 암호화할 텍스트를 입력하세요: ";
    getline(cin, text);

    cout << "시프트 값을 입력하세요 (1~25): ";
    getline(cin, shift_input);

    int shift;
    try {
        shift = stoi(shift_input);
        if (shift < 1 || shift > 25) throw out_of_range("1~25 범위를 벗어남");
    } catch (exception &e) {
        cout << "유효하지 않은 시프트 값입니다: " << e.what() << endl;
        return;
    }

    string encrypted_text = EncryptCaesar(text, shift);
    ofstream out_file("encrypted.txt", ios::app); // 추가 모드
    if (out_file.is_open()) {
        out_file << encrypted_text << endl;
        out_file.close();
        cout << "암호화된 텍스트가 파일에 추가되었습니다." << endl;
    } else {
        cout << "파일을 열 수 없습니다." << endl;
    }
}

// 랜덤 강도 암호화
void CaesarCipher::RandomEncryptText() {
    string text;
    cout << "암호화할 텍스트를 입력하세요: ";
    getline(cin, text);

    srand(time(0));
    int random_shift = rand() % 25 + 1; // 1 ~ 25 사이의 무작위 값
    cout << "랜덤 시프트 값: " << random_shift << endl;

    string encrypted_text = EncryptCaesar(text, random_shift);
    ofstream out_file("encrypted.txt", ios::app);
    if (out_file.is_open()) {
        out_file << encrypted_text << endl;
        out_file.close();
        cout << "암호화된 텍스트가 파일에 저장되었습니다." << endl;
    } else {
        cout << "파일을 열 수 없습니다." << endl;
    }
}

// 파일 삭제 함수
void CaesarCipher::DeleteEncryptedFile() {
    if (remove("encrypted.txt") == 0) {
        cout << "파일이 삭제되었습니다." << endl;
    } else {
        cout << "파일을 삭제할 수 없습니다." << endl;
    }
}

// 복호화 함수
void CaesarCipher::DecryptFile() {
    ifstream in_file("encrypted.txt");
    if (in_file.is_open()) {
        string encrypted_text, shift_input;
        cout << "복호화할 시프트 값을 입력하세요 (1~25): ";
        getline(cin, shift_input);

        int shift;
        try {
            shift = stoi(shift_input);
            if (shift < 1 || shift > 25) throw out_of_range("1~25 범위를 벗어남");
        } catch (exception &e) {
            cout << "유효하지 않은 시프트 값입니다: " << e.what() << endl;
            return;
        }

        while (getline(in_file, encrypted_text)) {
            string decrypted_text = DecryptCaesar(encrypted_text, shift);
            cout << "복호화된 텍스트: " << decrypted_text << endl;
        }
        in_file.close();
    } else {
        cout << "파일을 열 수 없습니다." << endl;
    }
}
