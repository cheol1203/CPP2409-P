/*  프로젝트 기반 지식 설명
    시저 암호란 암호학에서 다루는 간단한 치환암호의 일종이다.
    암호화하고자 하는 내용을 알파벳별로 일정한 거리만큼 밀어서 다른 알파벳으로 치환하는 방식이다.
    시저 암호를 통한 암호화 프로그램을 만들 것이기 때문에 시프트 값을 설정해야한다. */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// 암호화/복호화 및 파일 관리 클래스
class CaesarCipher {
private:
    
    // 시저 암호로 텍스트를 암호화하는 함수
    string EncryptCaesar(const string &text, int shift){
        string encrypted_text = text;
        for (char &c : encrypted_text){
            if (isalpha(c)){ // 알파벳만 암호화
                char base = isupper(c) ? 'A' : 'a';
                c = (c - base + shift) % 26 + base;
            }
        }
        return encrypted_text;
    }

    // 시저 암호로 텍스트를 복호화하는 함수
    string DecryptCaesar(const string &text, int shift){
        return EncryptCaesar(text, 26 - shift); // 복호화는 암호화의 반대
    }

public:
    // 암호화된 텍스트를 파일에 저장(단, 덮어쓰기 됨)
    void EncryptedText(){
        string text, shift_input;
        cout << "암호화할 텍스트를 입력하세요: ";
        getline(cin, text);                       // 띄어쓰기를 포함한 암호화할 텍스트 입력하기
        cout << "시프트 값을 입력하세요 (1~25): "; // 알파벳은 총 26자리가 있기때문에 1~25숫자만 가능 26 입력 시 동일한 텍스트가 나옴
        getline(cin, shift_input);                // 시프트 값 입력
        int shift = stoi(shift_input);               

        // 암호화 및 파일 저장 (덮어쓰기)
        string encrypted_text = EncryptCaesar(text, shift);
        ofstream out_file("encrypted.txt");
        if (out_file.is_open()){
            out_file << encrypted_text << endl;
            out_file.close();
            cout << "암호화된 텍스트가 파일에 저장되었습니다." << endl;
        }
        else{
            cout << "파일을 열 수 없습니다." << endl;
        }
    }

    // 암호화된 텍스트를 추가로 파일에 저장
    void AddEncryptedText() {
        string text, shift_input;
        cout << "추가로 암호화할 텍스트를 입력하세요: ";
        getline(cin, text);
        cout << "시프트 값을 입력하세요 (1~25): ";
        getline(cin, shift_input);
        int shift = stoi(shift_input);

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
    void RandomEncryptText() {
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
    
    // 복호화
    void DecryptFile() {
        ifstream in_file("encrypted.txt");
        if (in_file.is_open()) {
            string encrypted_text, shift_input;
            cout << "복호화할 시프트 값을 입력하세요(1~25): ";
            getline(cin, shift_input);
            int shift = stoi(shift_input);

            while (getline(in_file, encrypted_text)) {
                string decrypted_text = DecryptCaesar(encrypted_text, shift);
                cout << "복호화된 텍스트: " << decrypted_text << endl;
            }
            in_file.close();
        } else {
            cout << "파일을 열 수 없습니다." << endl;
        }
    }

};


int main() {
    CaesarCipher cipher;
    string choice_input;

    while (true) {
        cout << endl << "=== 암호화 프로그램 ===" << endl;
        cout << "1. 암호화된 텍스트 저장(덮어쓰기)" << endl;
        cout << "2. 암호화된 텍스트 추가 저장" << endl;
        cout << "3. 암호화된 텍스트 랜덤 강도로 저장" << endl;
        cout << "4. 암호화된 파일 읽기 및 복호화" << endl;
        cout << "0. 종료" << endl;
        cout << "선택: ";
        getline(cin, choice_input);

        int choice = stoi(choice_input); // 문자열을 정수로 변환
        switch (choice) {
        case 1:
            cipher.EncryptedText();
            break;
        case 2:
            cipher.AddEncryptedText();
            break;
        case 3:
            cipher.RandomEncryptText();
            break;
        case 4:
            cipher.DecryptFile();
            break;
        case 0:
            cout << "프로그램을 종료합니다." << endl;
            return 0;
        default:
            cout << "잘못된 선택입니다." << endl;
        }
    }
}