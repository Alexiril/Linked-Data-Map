#pragma once
#ifndef SHARED_HPP
#define SHARED_HPP

#include <cstdint>
#include <memory>
#include <map>
#include <set>

namespace LDM {

    using i8 = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;

    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    using std::shared_ptr;
    using std::unique_ptr;
    using std::map;
    using std::set;

}

#endif // !SHARED_HPP