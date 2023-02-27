#include "decrypt.cpp"

int main() {
    const string key = "mykey";
    vector<unsigned char> xorKey(key.begin(), key.end());
    decryptPerByte(TaskSampleOutputFile, TaskSampleOutputDecryptedFile, xorKey);

    return 0;
}
