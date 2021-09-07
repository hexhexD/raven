#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include "asio.hpp"

namespace raven {

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

inline constexpr u8 hexFromDigit(char c) {
  struct HexTable {
    u8 lut [255] = {};
    constexpr HexTable() {
      for (u8 i = 0; i < 255; ++i)
        lut[i] = 0;
      for (u8 i = 0; i < 10; ++i)
        lut['0' + i] = i;
      for (u8 i = 0; i < 6; ++i)
        lut['a' + i] = lut ['A' + i] = i + 10;
    }
  };
  constexpr HexTable table;
  return table.lut[static_cast<u8>(c)];
}

inline constexpr u8 fromNibbles(char msb, char lsb) {
  return hexFromDigit(msb) << 4 | hexFromDigit(lsb);
}

template<typename T, std::size_t N, std::size_t ... Index>
inline constexpr T hexStringToBytes(const char(&src)[N], const std::index_sequence<Index...>&) {
  return T{fromNibbles(src[Index * 2], src[Index * 2 + 1])...};
}

template<typename T, std::size_t N>
inline constexpr T hexStringToBytes(const char(&src)[N]) {
  static_assert(!((N - 1) % 2));
  return hexStringToBytes<T>(src, std::make_index_sequence<N / 2>{});
}

} // namesapce
