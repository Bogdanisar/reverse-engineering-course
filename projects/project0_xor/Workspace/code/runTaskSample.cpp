#include "decrypt.h"


const char * const TaskSampleInputFile = "input/taskSample_input.txt";
const char * const TaskSampleOutputFile = "input/taskSample_inputEncrypted.txt";
const char * const TaskSampleOutputDecryptedFile = "temp/taskSample_output_decrypted.txt";


int main() {
    const string key = "mykey";
    vector<unsigned char> xorKey(key.begin(), key.end());
    decryptPerByte(TaskSampleOutputFile, TaskSampleOutputDecryptedFile, xorKey);

    return 0;
}
