#include <string>
using namespace std;

// 암호화/복호화 및 파일 관리 클래스
class CaesarCipher {
private:
    string password;

    string EncryptCaesar(const string &text, int shift);
    string DecryptCaesar(const string &text, int shift);

public:
    void SetPassword();
    bool VerifyPassword();
    void EncryptedText();
    void AddEncryptedText();
    void RandomEncryptText();
    void DeleteEncryptedFile();
    void DecryptFile();
};
