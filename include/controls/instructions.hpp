#ifndef INTRUCTIONS_HPP
#define INTRUCTIONS_HPP

#include <cstddef>

#pragma pack(push, 1)
struct instruction_header
{
    std::byte instruction_type;
    std::byte instruction_length;
};
#pragma pack(pop)


#endif