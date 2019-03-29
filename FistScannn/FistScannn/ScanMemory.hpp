#pragma once
HANDLE OutputAttribute = nullptr;
enum protectType : DWORD
{
	Readable = (PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY | PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY),
	Writable = (PAGE_EXECUTE_READWRITE | PAGE_READWRITE)
};

enum TypeV : DWORD
{
	Bytes = 0x0,
	D2Bytes = 0x1,
	D4Bytes = 0x3,
	D8Bytes = 0x7
};

std::vector<MEMORY_BASIC_INFORMATION>mapp;

bool mapmemory(HANDLE phandle, protectType pTopy) {//aprendiz saiu correndo, pau no cu de quem ta lendo!

	DWORD Proibido = (PAGE_NOCACHE | PAGE_GUARD | PAGE_NOACCESS);

	MEMORY_BASIC_INFORMATION mbi;
	mapp.clear();
	uint8_t* Addrs = NULL;

	while (VirtualQueryEx(phandle, Addrs, &mbi, sizeof(mbi)) != 0) {

		if (mbi.State & MEM_COMMIT && !(mbi.State & MEM_RELEASE) && mbi.AllocationProtect & pTopy && mbi.Protect & pTopy && !(mbi.Protect & Proibido))
			mapp.push_back(mbi);


		Addrs = reinterpret_cast<uint8_t*>(mbi.BaseAddress) + mbi.RegionSize;
	}


	return true;
}

BOOL ListProcessModules(HANDLE hModuleSnap, uintptr_t addr)
{
	MODULEENTRY32 me32;
	if (hModuleSnap == INVALID_HANDLE_VALUE)
		return(FALSE);


	me32.dwSize = sizeof(MODULEENTRY32);

	if (!Module32First(hModuleSnap, &me32))
		return(FALSE);


	do
	{
		DWORD base = (uintptr_t)(me32.modBaseAddr) + me32.modBaseSize;
		DWORD cmp = addr;
		if (cmp < base && cmp >(DWORD)me32.modBaseAddr) {
			SetConsoleTextAttribute(OutputAttribute, 0x0A);
			return(TRUE);
		}
		else if (cmp > (DWORD)me32.modBaseAddr) {}
		else
		{
			exit;
			SetConsoleTextAttribute(OutputAttribute, 0x0f);
		}
	} while (Module32Next(hModuleSnap, &me32));
	return(TRUE);
}



template <typename T>
std::vector<uintptr_t> scanner(T valor, HANDLE phandle, DWORD pid, int x, TypeV TheValue) {
	std::vector<uintptr_t> Addres;
	Addres.clear();
	HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	for (auto&catchorra : mapp) {
		auto bf = reinterpret_cast<uint8_t*>(LocalAlloc(NULL, catchorra.RegionSize));
		auto ret = ReadProcessMemory(phandle, catchorra.BaseAddress, bf, catchorra.RegionSize, NULL);

		if (!ret)
		{
			continue;
		}


		for (int i = 0; i < catchorra.RegionSize; ++i) {
			auto allocadPoint = uintptr_t(&bf[i]);

			auto vVal = *reinterpret_cast<T*>(allocadPoint);
			if (vVal == valor || vVal <= (valor + 1) && vVal >= (valor - 1))
			{
				Addres.push_back((uintptr_t)catchorra.BaseAddress + i);
				i += TheValue;
			}

		}

		LocalFree(bf);
	}

	printf("Found : %d\n", Addres.size());
	if (Addres.size() > 100) {
		printf("Ops :o > Are more than 100 addresses, do you want to show ? YES[1], Another NO :");
		std::cin >> x;
		switch (x)
		{
		case 1:
			for (auto&list : Addres) {
				ListProcessModules(hModuleSnap, list);

				printf("[%d]	0x%p \n", x, list);


				x++;
				SetConsoleTextAttribute(OutputAttribute, 0x0f);
			}
			break;

		default:
			break;
		}
	}
	else {


		for (auto&list : Addres) {
			ListProcessModules(hModuleSnap, list);

			printf("[%d]	0x%p \n", x, list);


			x++;
			SetConsoleTextAttribute(OutputAttribute, 0x0f);
		}
	}

	CloseHandle(hModuleSnap);
	return Addres;
}
template <typename T>
std::vector<uintptr_t> NxtScan(T valor, HANDLE phandle, std::vector<uintptr_t>Old, int x, DWORD pid) {
	x = 0;
	std::vector<uintptr_t> Addres;
	Addres.clear();
	T OldValue = valor;
	HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	for (int i = 0; i < Old.size(); ++i) {

		ReadProcessMemory(phandle, (LPVOID)Old[i], &OldValue, sizeof(OldValue), NULL);
		if (OldValue == valor || OldValue >= (valor - 1) && OldValue <= (valor + 1)) {
			Addres.push_back(Old[i]);
		}

	}
	printf("Found %d \n", Addres.size());
	if (Addres.size() > 100) {
		printf("Ops :o > Are more than 100 addresses, do you want to show ? YES[1], Another NO :");
		std::cin >> x;
		switch (x)
		{
		case 1:
			for (auto&list : Addres) {
				ListProcessModules(hModuleSnap, list);

				printf("[%d]	0x%p \n", x, list);


				x++;
				SetConsoleTextAttribute(OutputAttribute, 0x0f);
			}
			break;

		default:
			break;
		}
	}
	else {

		for (auto&list : Addres) {
			ListProcessModules(hModuleSnap, list);
			printf("[%d]	0x%p \n", x, list);
			x++;
			SetConsoleTextAttribute(OutputAttribute, 0x0f);
		}
	}

	CloseHandle(hModuleSnap);
	return Addres;
}
