/*  프로젝트 기반 지식 설명
    시저 암호란 암호학에서 다루는 간단한 치환암호의 일종이다.
    암호화하고자 하는 내용을 알파벳별로 일정한 거리만큼 밀어서 다른 알파벳으로 치환하는 방식이다.
    시저 암호를 통한 암호화 프로그램을 만들 것이기 때문에 시프트 값을 설정해야한다. */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// 시저 암호로 텍스트를 암호화하는 함수
string encryptCaesar(const string &text, int shift){
    string encryptedText = text;
    for (char &c : encryptedText){
        if (isalpha(c)){ // 알파벳만 암호화
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + shift) % 26 + base;
        }
    }
    return encryptedText;
}

// 시저 암호로 텍스트를 복호화하는 함수
string decryptCaesar(const string &text, int shift){
    return encryptCaesar(text, 26 - shift); // 복호화는 암호화의 반대
}

int main(){
    int mode;
    cout << "모드를 선택하세요 (1: 암호화, 2: 복호화, 3: 암호화된 텍스트 추가 저장, 4: 모든 텍스트 복호화): ";
    cin >> mode;
    cin.ignore(); // 입력 버퍼 비우기

    if (mode == 1){
        // 암호화 모드
        string text;
        int shift;
        cout << "암호화할 텍스트를 입력하세요: ";
        getline(cin, text);                        // 띄어쓰기를 포함한 암호화할 텍스트 입력하기
        cout << "시프트 값을 입력하세요 (1~25): "; // 알파벳은 총 26자리가 있기때문에 1~25숫자만 가능 26 입력 시 동일한 텍스트가 나옴
        cin >> shift;                              // 시프트 값 입력

        // 암호화 및 파일 저장 (덮어쓰기)
        string encryptedText = encryptCaesar(text, shift);
        ofstream outFile("encrypted.txt");
        if (outFile.is_open()){
            outFile << encryptedText;
            outFile.close();
            cout << "암호화된 텍스트가 'encrypted.txt'에 저장되었습니다." << endl;
        }
        else{
            cout << "파일을 열 수 없습니다." << endl;
        }
    }
    else if (mode == 2){
        // 복호화 모드
        int shift;
        cout << "복호화할 시프트 값을 입력하세요 (1~25): ";
        cin >> shift;

        // 파일에서 암호화된 텍스트 읽기 및 복호화
        ifstream inFile("encrypted.txt");
        if (inFile.is_open()){
            string encryptedText;
            getline(inFile, encryptedText);
            inFile.close();

            string decryptedText = decryptCaesar(encryptedText, shift);
            cout << "복호화된 텍스트: " << decryptedText << endl;
        }
        else{
            cout << "파일을 읽을 수 없습니다." << endl;
        }
    }
    else if (mode == 3){
        // 추가 저장 모드
        string text;
        int shift;
        cout << "추가로 암호화할 텍스트를 입력하세요: ";
        cin.ignore();
        getline(cin, text); // 텍스트 입력

        cout << "시프트 값을 입력하세요 (1~25): ";
        cin >> shift; // 시프트 값 입력

        // 암호화 및 파일에 추가 저장
        string encryptedText = encryptCaesar(text, shift);
        ofstream outFile("encrypted.txt", ios::app); // 추가 모드로 파일 열기
        if (outFile.is_open()){
            outFile << encryptedText << endl;
            outFile.close();
            cout << "암호화된 텍스트가 파일에 추가되었습니다." << endl;
        }
        else{
            cout << "파일을 열 수 없습니다." << endl;
        }
    }
    
    else if (mode == 4) {
        // 모든 텍스트 복호화 모드
        int shift;
        cout << "복호화할 시프트 값을 입력하세요 (1~25): ";
        cin >> shift;

        // 파일에서 모든 줄 읽기 및 복호화
        ifstream inFile("encrypted.txt");
        if (inFile.is_open()) {
            string encryptedText;
            while (getline(inFile, encryptedText)) {
                string decryptedText = decryptCaesar(encryptedText, shift);
                cout << "복호화된 텍스트: " << decryptedText << endl;
            }
            inFile.close();
        } else {
            cout << "파일을 읽을 수 없습니다." << endl;
        }
    }
    else{
        cout << "잘못된 선택입니다." << endl;
    }

    return 0;
}