#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/QuestTypes.h>
#include "include/shaiya/include/SVector.h"

namespace shaiya
{
    enum struct NpcTeam : UINT32
    {
        Light,
        Fury,
        Neutral
    };

    #pragma pack(push, 1)
    struct Npc
    {
        NpcType type;         //0x00
        PAD(1);
        UINT16 typeId;        //0x02
        UINT32 shape;         //0x04
        PAD(8);
        NpcTeam team;         //0x10
        CharArray<256> name;  //0x14
        // 0x114
        PAD(16);
        // 0x124
    };
    #pragma pack(pop)

    static_assert(sizeof(Npc) == 0x124);

    #pragma pack(push, 1)
    struct NpcGate
    {
        UINT16 mapId;         //0x00
        PAD(2);
        SVector pos;          //0x04
        CharArray<256> desc;  //0x10
        UINT32 price;         //0x110
        // 0x114
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct NpcGateKeeper
    {
        Npc npc;
        // 0x124
        Array<NpcGate, 3> gates;
        // 0x460
    };
    #pragma pack(pop)

    static_assert(sizeof(NpcGateKeeper) == 0x460);

    #pragma pack(push, 1)
    struct NpcItem
    {
        UINT8 type;
        UINT8 typeId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct NpcMerchant
    {
        Npc npc;           //0x00
        // 0x124
        MerchantType merchantType;
        PAD(3);
        UINT32 itemCount;  //0x128
        NpcItem* items;    //0x12C
        // 0x130
    };
    #pragma pack(pop)

    static_assert(sizeof(NpcMerchant) == 0x130);

    template<typename T>
    struct CNpcData
    {
        static T GetNpc(int npcType/*ecx*/, int npcTypeId/*eax*/);
    };

    template<typename T>
    T CNpcData<T>::GetNpc(int npcType/*ecx*/, int npcTypeId/*eax*/)
    {
        unsigned u0x424450 = 0x424450;

        __asm
        {
            mov eax,npcTypeId
            mov ecx,npcType
            call u0x424450
        }
    }
}
