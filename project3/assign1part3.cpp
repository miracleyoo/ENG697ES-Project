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
#include <cmath>
#include <algorithm>

#include "phyframes.hh"
#include "pagetable.hh"

using namespace std;

int *virtual_to_physical_list = NULL;
int *physical_to_virtual_list = NULL;
int bits_of_page;
int bits_of_virtual_memory;
int bits_of_physical_memory;
int number_of_physical_memory;
int number_of_virtual_memory;

/* Read file contents as 64bit-long int and send them to be translated
   After processing, write physical address back to file. */
void AnalyzeAccessSequenceFromFile(char *file_name)
{
    int address_sequence_counter = 0; // Counter to record the number of input address
    uint64_t virtual_address;         // Virtual address which is directly read from the file
    uint64_t translated_address;      // Address translated to physical address
    ifstream content(file_name, ios::in | ios::binary);
    ofstream fout("output-part3", ios::out | ios::trunc | ios::binary);
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
    if (argc != 5)
    {
        cout << "Please input 4 parameters in order:\n\
        size_of_page, size_of_virtual_memory, size_of_physical_memory, sequence_file ";
        return -1;
    }
    double size_of_page = atof(argv[1]);
    double size_of_virtual_memory = atof(argv[2]);
    double size_of_physical_memory = atof(argv[3]);
    char *input_file_name = argv[4];

    bits_of_page = (int)ceil(log2(size_of_page));
    number_of_virtual_memory = (int)floor(size_of_virtual_memory / size_of_page);
    number_of_physical_memory = (int)floor(size_of_physical_memory / size_of_page);
    bits_of_virtual_memory = (int)ceil(log2(number_of_virtual_memory));
    bits_of_physical_memory = (int)ceil(log2(number_of_physical_memory));

    virtual_to_physical_list = new int[number_of_virtual_memory];
    physical_to_virtual_list = new int[number_of_physical_memory];
    fill_n(virtual_to_physical_list, number_of_virtual_memory, 0);
    fill_n(physical_to_virtual_list, number_of_physical_memory, 0);

    cout << bits_of_page << " " << bits_of_virtual_memory << " " << bits_of_physical_memory << " " << number_of_virtual_memory << " " << number_of_physical_memory << " " << endl;
    cout << virtual_to_physical_list[0] << virtual_to_physical_list[1] << physical_to_virtual_list[0] << physical_to_virtual_list[1]<<endl;
    AnalyzeAccessSequenceFromFile(input_file_name);
    cout << "page_fault_counter: " << page_fault_counter << endl;
    return 0;
}
