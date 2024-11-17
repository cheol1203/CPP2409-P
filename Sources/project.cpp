/*  프로젝트 기반 지식 설명
    시저 암호란 암호학에서 다루는 간단한 치환암호의 일종이다.
    암호화하고자 하는 내용을 알파벳별로 일정한 거리만큼 밀어서 다른 알파벳으로 치환하는 방식이다.
    시저 암호를 통한 암호화 프로그램을 만들 것이기 때문에 시프트 값을 설정해야한다. */

#include <iostream>
#include <string>

using namespace std;

// 시저 암호로 텍스트를 암호화하는 함수
string encryptCaesar(const string &text, int shift) {
    string encryptedText = text;
    for (char &c : encryptedText) {
        if (isalpha(c)) {  // 알파벳만 암호화
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + shift) % 26 + base;
        }
    }
    return encryptedText;
}

// 시저 암호로 텍스트를 복호화하는 함수
string decryptCaesar(const string &text, int shift) {
    return encryptCaesar(text, 26 - shift);  // 복호화는 암호화의 반대
}

int main() {
    int mode;
    cout << "모드를 선택하세요 (1: 암호화, 2: 복호화): ";
    cin >> mode;
    cin.ignore();  // 입력 버퍼 비우기

    if (mode == 1) {
        // 암호화 모드
        string text;
        int shift;
        cout << "암호화할 텍스트를 입력하세요: ";
        getline(cin, text);  // 띄어쓰기를 포함한 암호화할 텍스트 입력하기
        cout << "시프트 값을 입력하세요 (1~25): "; // 알파벳은 총 26자리가 있기때문에 1~25숫자만 가능 26 입력 시 동일한 텍스트가 나옴
        cin >> shift;  // 시프트 값 입력

        // 암호화 및 출력
        string encryptedText = encryptCaesar(text, shift);
        cout << "암호화된 텍스트: " << encryptedText << endl;

    } else if (mode == 2) {
        // 복호화 모드
        string encryptedText;
        int shift;
        cout << "복호화할 텍스트를 입력하세요: ";
        getline(cin, encryptedText);  // 암호화된 텍스트 입력
        cout << "시프트 값을 입력하세요 (1~25): ";
        cin >> shift;  // 시프트 값 입력

        // 복호화 및 출력
        string decryptedText = decryptCaesar(encryptedText, shift);
        cout << "복호화된 텍스트: " << decryptedText << endl;
    } else {
        cout << "잘못된 선택입니다." << endl;
    }

    return 0;
}