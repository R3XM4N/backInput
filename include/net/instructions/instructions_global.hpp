#ifndef INSTRUCTIONS_GLOBAL_HPP
#define INSTRUCTIONS_GLOBAL_HPP

///-------------------------------------------------------------
///------------INCLUDES WHAT ALL INSTRUCTIONS NEED--------------
///-------------------------------------------------------------

#include <cstddef>
#include <cinttypes>

#pragma pack(push, 1)
struct instruction_header
{
    std::byte instruction_type;
    std::byte instruction_length;
};
#pragma pack(pop)

#endif