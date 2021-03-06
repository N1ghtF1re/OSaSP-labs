// Dll1.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>

#define DLL_EXPORT __declspec(dllexport)


extern "C" void DLL_EXPORT _stdcall ReplaceData(DWORD pid, const char* data, size_t len, const char* replacement, size_t replacementLength)
{
	HANDLE process = OpenProcess(PROCESS_VM_READ | PROCESS_TRUST_LABEL_SECURITY_INFORMATION | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION, FALSE, pid);
	if (process)
	{
		SYSTEM_INFO si;
		GetSystemInfo(&si);

		MEMORY_BASIC_INFORMATION info;
		std::vector<char> chunk;
		char* p = 0;
		while (p < si.lpMaximumApplicationAddress)
		{

			if (VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info))
			{

				if (info.State == MEM_COMMIT && info.AllocationProtect == PAGE_READWRITE)
				{
					p = (char*)info.BaseAddress;

					chunk.resize(info.RegionSize);
					SIZE_T bytesRead;

					try {
						if (ReadProcessMemory(process, p, &chunk[0], info.RegionSize, &bytesRead))
						{
							for (size_t i = 0; i < (bytesRead - len); ++i)
							{
								if (memcmp(data, &chunk[i], len) == 0)
								{
									char* ref = (char*)p + i;
									for (int j = 0; j < replacementLength; j++) {
										ref[j] = replacement[j];
									}
									ref[replacementLength] = 0;
								}
							}
						}
					}
					catch (std::bad_alloc& e) {

					}
				}
				p += info.RegionSize;
			}
		}
	}
}
