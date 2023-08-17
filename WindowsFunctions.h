#pragma once
#include "n.hpp"
PEB* GetPEBInternal()
{
#ifdef _WIN64
    PEB* peb = (PEB*)__readgsqword(0x60);

#else
    PEB* peb = (PEB*)__readfsdword(0x30);
#endif

    return peb;
}

LDR_DATA_TABLE_ENTRY* GetLDREntryInternal(const wchar_t* modName)
{
    LDR_DATA_TABLE_ENTRY* modEntry = nullptr;

    PEB* peb = GetPEBInternal();

    LIST_ENTRY head = peb->Ldr->InMemoryOrderModuleList;

    LIST_ENTRY curr = head;

    for (auto curr = head; curr.Flink != &peb->Ldr->InMemoryOrderModuleList; curr = *curr.Flink)
    {
        LDR_DATA_TABLE_ENTRY* mod = (LDR_DATA_TABLE_ENTRY*)CONTAINING_RECORD(curr.Flink, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

        if (mod->BaseDllName.Buffer)
        {
            if (_wcsicmp(modName, mod->BaseDllName.Buffer) == 0)
            {
                modEntry = mod;
                break;
            }
        }
    }
    return modEntry;
}

uintptr_t GetModuleBaseAddressInternalPEB(const wchar_t* modName)
{
    LDR_DATA_TABLE_ENTRY* modEntry = GetLDREntryInternal(modName);

    return (uintptr_t)modEntry->DllBase;
}

BYTE* GetProcAddressA(HINSTANCE hDll, const char* szFunc)
{
    if (!hDll)
        return nullptr;

    BYTE* pBase = reinterpret_cast<BYTE*>(hDll);
    auto* pNT = reinterpret_cast<IMAGE_NT_HEADERS*>(pBase + reinterpret_cast<IMAGE_DOS_HEADER*>(pBase)->e_lfanew);
    auto* pExportDir = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(pBase + pNT->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

    if (reinterpret_cast<UINT_PTR>(szFunc) <= MAXWORD)
    {
        WORD Ordinal = (WORD)szFunc;
        DWORD RVA = reinterpret_cast<DWORD*>(pBase + pExportDir->AddressOfFunctions)[Ordinal];
        return pBase + RVA;
    }

    DWORD max = pExportDir->NumberOfNames - 1;
    DWORD min = 0;

    while (min <= max)
    {
        DWORD mid = (min + max) >> 1;

        DWORD CurrNameRVA = reinterpret_cast<DWORD*>(pBase + pExportDir->AddressOfNames)[mid];
        char* szName = reinterpret_cast<char*>(pBase + CurrNameRVA);

        int cmp = strcmp(szName, szFunc);
        if (cmp < 0)
            min = mid + 1;
        else if (cmp > 0)
            max = mid - 1;
        else
        {
            WORD Ordinal = reinterpret_cast<WORD*>(pBase + pExportDir->AddressOfNameOrdinals)[mid];
            DWORD RVA = reinterpret_cast<DWORD*>(pBase + pExportDir->AddressOfFunctions)[Ordinal];
            return pBase + RVA;
        }
    }

    return nullptr;
}
