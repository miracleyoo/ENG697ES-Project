// Author: Miracleyoo
// E-mail: mirakuruyoo@gmail.com
// Date: 2019.09.22
/* Overview: Read a sequence of 64-bits address and then simulate a
    Memory allocation process which is implemented by double linked
    list. At last, translate the virtual memory address to a physical
    memory address and write it to a binary file. */

#include <iostream>
#include <fstream>
#include <stdint.h>

#include "phyframes.hh"
#include "pagetable.hh"

using namespace std;

/* Read file contents as 64bit-long int and send them to be translated
   After processing, write physical address back to file. */
void AnalyzeAccessSequenceFromFile(char *file_name)
{
    int address_sequence_counter = 0; // Counter to record the number of input address
    uint64_t virtual_address;  // Virtual address which is directly read from the file
    uint64_t translated_address; // Address translated to physical address
    ifstream content(file_name, ios::in | ios::binary);
    ofstream fout("output-part2", ios::out | ios::trunc | ios::binary);
    if (!content)
    {
        cout << "Cannot open input file.";
    }
    if (!fout)
    {
        cout << "Cannot open output file.";
    }

    // Read the virtual address from file until it comes to the end
    while (true)
    {
        content.read((char *)&virtual_address, sizeof(virtual_address));
        if (content.eof())
        {
            break;
        }
        cout << "Virtual Address: " << hex << virtual_address << dec << endl;
        translated_address = HandleAllocation(virtual_address);
        cout << "Translated Address: " << hex << translated_address << dec << endl;
        fout.write((char *)&translated_address, sizeof(translated_address));
        address_sequence_counter++;
    }
    content.close();
    fout.close();
    cout << "Overall adress sequence number: " << address_sequence_counter << endl;
}

int main(int argc, char *argv[])
{
    char *input_file_name;
    if (argc == 2)
    {
        input_file_name = argv[1];
    }
    AnalyzeAccessSequenceFromFile(input_file_name);
    cout << "page_fault_counter: " << page_fault_counter << endl;
    return 0;
}
