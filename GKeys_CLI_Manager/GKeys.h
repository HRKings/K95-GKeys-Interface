#pragma once

#include <unordered_map>
#include <cstdint>
#include <string>

/* Keys in hex form */
#define GKEY_G1 0x10000
#define GKEY_G2 0x20000
#define GKEY_G3 0x40000
#define GKEY_G4 0x80000
#define GKEY_G5 0x100000
#define GKEY_G6 0x200000

#define GKEY_G7 0x400000
#define GKEY_G8 0x800000
#define GKEY_G9 0x100
#define GKEY_G10 0x200
#define GKEY_G11 0x1
#define GKEY_G12 0x2

#define GKEY_G13 0x4
#define GKEY_G14 0x8
#define GKEY_G15 0x10
#define GKEY_G16 0x20
#define GKEY_G17 0x40
#define GKEY_G18 0x80

extern  std::unordered_map<std::uint32_t, int> GKeys_Map;
extern  std::unordered_map<std::uint32_t, std::string> GKeys_Names_Map;

void G_Pressed(std::uint32_t key);
void G_Released(std::uint32_t key);