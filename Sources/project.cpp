/*  프로젝트 기반 지식 설명
    시저 암호란 암호학에서 다루는 간단한 치환암호의 일종이다.
    암호화하고자 하는 내용을 알파벳별로 일정한 거리만큼 밀어서 다른 알파벳으로 치환하는 방식이다.
    시저 암호를 통한 암호화 프로그램을 만들 것이기 때문에 시프트 값을 설정해야한다. */

#include <iostream>
#include "CaesarCipher.h"

using namespace std;

int main() {
    CaesarCipher cipher;
    string choice_input;

    while (true) {
        cout << endl << "=== 암호화 프로그램 ===" << endl;
        cout << "1. 암호화된 텍스트 저장(덮어쓰기)" << endl;
        cout << "2. 암호화된 텍스트 추가 저장" << endl;
        cout << "3. 암호화된 텍스트 랜덤 강도로 저장" << endl;
        cout << "4. 암호화된 파일 삭제" << endl;
        cout << "5. 비밀번호 설정" << endl;
        cout << "6. 암호화된 파일 읽기 및 복호화" << endl;
        cout << "0. 종료" << endl;
        cout << "선택: ";
        getline(cin, choice_input);

        int choice;
        try {
            choice = stoi(choice_input);
        } catch (exception &e) {
            cout << "유효하지 않은 선택입니다." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            if (cipher.VerifyPassword()) cipher.EncryptedText();
            break;
        case 2:
            if (cipher.VerifyPassword()) cipher.AddEncryptedText();
            break;
        case 3:
            if (cipher.VerifyPassword()) cipher.RandomEncryptText();
            break;
        case 4:
            if (cipher.VerifyPassword()) cipher.DeleteEncryptedFile();
            break;
        case 5:
            if (cipher.VerifyPassword()) cipher.SetPassword();
            break;
        case 6:
            if (cipher.VerifyPassword()) cipher.DecryptFile();
            break;
        case 0:
            cout << "프로그램을 종료합니다." << endl;
            return 0;
        default:
            cout << "잘못된 선택입니다." << endl;
        }
    }
}