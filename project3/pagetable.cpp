// Author: Miracleyoo
// E-mail: mirakuruyoo@gmail.com
// Date: 2019.09.22
// Mainly hold all functions that manages the page table for the process

#include <stdint.h>
#include <iostream>
#include <math.h>
#include "pagetable.hh"
#include "phyframes.hh"
#include "assign1part3.hh"

int physical_2_virtual = 0; // The counter of the list physical_tp_virtual_list
int page_fault_counter = 0; // The counter of total page fault

// Translate the virtual address to physical address.
uint64_t TranslateAddress(uint64_t address, int new_value)
{
    int sum = 0;
    int mask_tail_zeros_number = bits_of_page % 4;
    for (int i = 0; i < bits_of_virtual_memory; i++)
    {
        sum += pow(2, (mask_tail_zeros_number + i));
    }
    uint64_t bit_mask = (sum << 4 * (bits_of_page / 4));
    address = (address & (~bit_mask)) | (new_value << bits_of_page);
    return address;
}

// Extract the page table index from virtual address input.
int GetVirtualIndex(uint64_t address)
{
    int sum = 0;
    int mask_tail_zeros_number = bits_of_page % 4;
    for (int i = 0; i < bits_of_virtual_memory; i++)
    {
        sum += pow(2, (mask_tail_zeros_number + i));
    }
    uint64_t bit_mask = (sum << 4 * (bits_of_page / 4));
    int virtual_index = (address & bit_mask) >> bits_of_page;
    return virtual_index;
}

/*  The main function to handle the allocation. It take in the virtual address and extract
    the virtual page number, then allocate a physical address to it depending on the condition
    of the overall situation of virtual and physical memory. At last, it translate and return 
    the physical address.
*/
uint64_t HandleAllocation(uint64_t address)
{
    int virtual_page_number = GetVirtualIndex(address); // The index of the virtual_to_physical_list
    int physical_page_number = 0;                       // The index of the physical_to_virtual_list
    if (virtual_to_physical_list[virtual_page_number] == 0)
    {
        if (physical_2_virtual < number_of_physical_memory-1)
        {
            virtual_to_physical_list[virtual_page_number] = physical_2_virtual + 1;
            physical_to_virtual_list[physical_2_virtual] = virtual_page_number;
            physical_page_number = physical_2_virtual;
            physical_2_virtual++;
            push(virtual_page_number);
        }
        else
        {
            physical_page_number = virtual_to_physical_list[tail_ref->data];
            virtual_to_physical_list[tail_ref->data] = 0;
            virtual_to_physical_list[virtual_page_number] = physical_page_number;
            physical_to_virtual_list[physical_page_number] = virtual_page_number;
            cutTailAddHead(virtual_page_number);
        }
        page_fault_counter++;
    }
    else
    {
        physical_page_number = virtual_to_physical_list[virtual_page_number];
        searchAndPush(virtual_page_number);
    }
    std::cout << "virtual_page_number: " << virtual_page_number << "\tphysical_page_number: " << physical_page_number << std::endl;
    return TranslateAddress(address, physical_page_number);
}