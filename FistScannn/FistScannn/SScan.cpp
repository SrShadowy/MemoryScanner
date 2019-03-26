#include "hread.h"
#include "ScanMemory.hpp"
#include "ArgCheats.h"

int main(int argc,const char *argv[]) {

	argcheat(argc, argv);

	OutputAttribute = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(OutputAttribute, 0x0f);
	printf("Enter the PID: \n");
	DWORD pid;
	std::cin >> pid;
	char TemporaryTitle[100];
	snprintf(TemporaryTitle, sizeof(TemporaryTitle), "atacado no processo 0x%x!", pid);
	std::string Title = TemporaryTitle;
	std::wstring Wide(Title.begin(), Title.end());
	SetConsoleTitleW(Wide.c_str());

	HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	
	getchar();
	std::cout << "HANDLE <<" << std::hex << phandle << " >> BY Sr.Shadowy , Smoll.ice" <<  std::endl;
	label:
	mapmemory(phandle, Readable);

	std::cout << "\nNew Value :";

	int ValorScan = 510;
	std::cin >> ValorScan;
	std::vector<uintptr_t> Addres;
	int x = 0;
	Addres = scanner(ValorScan, phandle, pid, x);
	x = 0;
	while (x == 0) {
		std::cout << "\nNew Value :";
		std::cin >> ValorScan;

		Addres = NxtScan(ValorScan, phandle, Addres, x, pid);

		std::cout << "\n>> NextScan[0] Write[1] NewScan[3] Another exit << :";
		std::cin >> x;
		if (x == 1) {
			std::cout << "\n>> Addr... << :";
			std::cin >> x;
			std::cout << "\n>> Value... << :";
			std::cin >> ValorScan;
			auto ret = WriteProcessMemory(phandle, (LPVOID)Addres[x], &ValorScan, sizeof(ValorScan), NULL);

			if (ret)
				std::cout << "Sucess!!! \n";
			else
				std::cout << "Error :C \n";

			std::cout << "NextScan[0] NewScan[1] Another exit: ";
			std::cin >> x;
			switch (x)
			{
			case 0:
				continue;
			case 1:
				goto label;
				break;
			default:
				break;
			}
		}
		else if (x == 3)
		{
			x = 0;
			goto label;
		}


	}

	CloseHandle(phandle);

	std::cout << "Thanks for using me, Shadowy hugs \nThank you to Smoll_ice - Aprendiz - iPower \n\n ";


		
	system("pause");

	getchar();
	return TRUE;
}