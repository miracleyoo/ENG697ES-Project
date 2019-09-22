// Author: Miracleyoo
// E-mail: mirakuruyoo@gmail.com
// Date: 2019.09.22

#include <iostream>
#include <fstream>
#include <bitset>
#include <stdint.h>

using namespace std;

// Translate the virtual address to physical address.
uint64_t TranslateAddress(uint64_t address)
{
    int translate_list[] = {2, 4, 1, 7, 3, 5, 6};
    uint64_t bit_mask = (248 << 4);
    int virtual_index = (address & bit_mask) >> 7;
    int new_value = translate_list[virtual_index]; // (this is the value you will set in)
    address = (address & (~bit_mask)) | (new_value << 7);
    return address;
}

// Read file contents as 64bit-long int and send them to be translated
// After processing, write physical address back to file.
void AnalyzeAccessSequenceFromFile(char *file_name)
{
    uint64_t virtual_address;
    uint64_t translated_address;
    ifstream content(file_name, ios::in | ios::binary);
    ofstream fout("output-part1", ios::out | ios::trunc | ios::binary);
    if (!content)
    {
        cout << "Cannot open input file.";
    }
    if (!fout)
    {
        cout << "Cannot open output file.";
    }

    while (true)
    {
        content.read((char *)&virtual_address, sizeof(virtual_address));
        if (content.eof())
        {
            break;
        }
        cout << "Virtual Address: " << hex << virtual_address << dec << endl;
        translated_address = TranslateAddress(virtual_address);
        cout << "Translated Address: " << hex << translated_address << dec << endl;
        fout.write((char *)&translated_address, sizeof(translated_address));
    }
    content.close();
    fout.close();
}

int main(int argc, char *argv[])
{
    char *input_file_name;

    if (argc == 2)
    {
        input_file_name = argv[1];
    }
    AnalyzeAccessSequenceFromFile(input_file_name);
    return 0;
}