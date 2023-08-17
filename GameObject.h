#pragma once
#include <vector>

std::vector<uintptr_t> componentTempList;

struct GameObjectCache;
struct ComponentCache
{
    char pad[0x28];
    uintptr_t component; // 0x28
    GameObjectCache* gameobject; // 0x30
    bool enabled; // 0x38
};

struct CachedComponentListEntry
{
    char reserved[8];
    ComponentCache* cachedcomponent;
};

struct GameObjectCache
{
    uintptr_t vmt;
    char pad[0x18];
    uintptr_t reversed0; // 0x20
    uintptr_t reversed1; // 0x28
    CachedComponentListEntry* componentlist; // 0x30
    uintptr_t reversed2; // 0x38
    int componentlist_size; // 0x40
    char pad2[0x1C];//char pad2[0x24];
    char** tag; // 0x60
};

std::vector<uintptr_t> GetComponentsFast(uintptr_t gameObject, const char* componentname)
{
    componentTempList.clear();

    auto cache = Read<GameObjectCache*>(gameObject + 0x10);

    if (!cache)
        return componentTempList;

    if (!cache->componentlist)
        return componentTempList;

    for (int i = 0; i < cache->componentlist_size; i++)
    {
        auto& item = cache->componentlist[i];

        if (!item.cachedcomponent)
            continue;

        auto component = item.cachedcomponent->component;

        if (!component)
            continue;

        auto componentBase = *(uintptr_t*)(component);
        if (!componentBase)
            continue;

        auto componentClassName = (char*)*(uintptr_t*)(componentBase + 0x10);

        if (componentClassName != componentname)
            continue;

        componentTempList.push_back(component);

    }

    return componentTempList;
}

uintptr_t GetComponentFast(uintptr_t gameObject, const char* componentname) {
    auto cmp = GetComponentsFast(gameObject, componentname);

    if (cmp.size() > 0)
        return cmp[0];

    return NULL;
}