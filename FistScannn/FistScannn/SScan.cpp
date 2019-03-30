#include "hread.h"
#include "ScanMemory.hpp"
#include "ArgCheats.h"

enum type_s
{
	//< "Type Value choice = bytes[1] - 2bytes[2] - 4bytes[4] - float[3] - 8bytes[8]...:";
	byBytes = 1,
	by2Bytes = 2,
	by8Bytes = 8,
	by4Bytes = 4,
	byFloat = 3
};

int main(int argc, const char *argv[]) {

	argcheat(argc, argv); //Function

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
	std::cout << "HANDLE <<" << std::hex << phandle << " >> BY Sr.Shadowy , Smoll.ice" << std::endl;
label:

	//Inicio começa aqui.
	mapmemory(phandle, Readable);
	double ValorScan = 0;
	int typ;
	TypeV Tp;
	std::cout << "Type Value choice = bytes[1] - 2bytes[2] - 4bytes[4] - float[3] - 8bytes[8]...:";
	std::cin >> typ;
	std::cout << "\nNew Value :";

	std::vector<uintptr_t> Addres;
	int x = 0;

	switch (typ)
	{
	case byBytes:
		//byte vl = 0xc;
		Tp = Bytes;
		std::cin >> ValorScan;

		Addres = scanner<byte>(ValorScan, phandle, pid, x, Tp, typ);
		break;

	case by2Bytes:
		//__int32 vl = 0;
		Tp = D2Bytes;
		//scanf_s("%i", vl);
		std::cin >> ValorScan;
		Addres = scanner<__int32>(ValorScan, phandle, pid, x, Tp, typ);
		break;

	case by8Bytes:
		Tp = D8Bytes;
		std::cin >> ValorScan;
		Addres = scanner<DWORD>(ValorScan, phandle, pid, x, Tp, typ);
		break;


	case by4Bytes:
		Tp = D4Bytes;
		std::cin >> ValorScan;
		Addres = scanner<int>(ValorScan, phandle, pid, x, Tp, typ);
		break;

	case byFloat:
		//float vl = 1.0;
		Tp = D4Bytes;
		/*std::cin >> vl;
		std::cout << "\n\n" << vl << "\n\n";
		ValorScan = vl;*/
		std::cin >> ValorScan;
		Addres = scanner<float>(ValorScan, phandle, pid, x, Tp, typ);

	default:
		break;
	}


	//Addres = scanner<float>(ValorScan, phandle, pid, x, Tp);
	x = 0;
	while (x == 0) {
		std::cout << "\nNew Value :";
		std::cin >> ValorScan;


		switch (typ)
		{
		case byBytes:
			Addres = NxtScan<byte>(ValorScan, phandle, Addres, x, pid, typ);
			break;

		case by2Bytes:
			Addres = NxtScan<__int32>(ValorScan, phandle, Addres, x, pid, typ);
			break;

		case by8Bytes:
			Addres = NxtScan<DWORD>(ValorScan, phandle, Addres, x, pid, typ);
			break;

		case by4Bytes:
			Addres = NxtScan<int>(ValorScan, phandle, Addres, x, pid, typ);
			break;

		case byFloat:
			Addres = NxtScan<float>(ValorScan, phandle, Addres, x, pid, typ);

		default:
			break;
		}
		

		std::cout << "\n>> NextScan[0] Write[1] NewScan[3]  Read[4] Another exit << :";
		std::cin >> x;
		if (x == 1) {
			std::cout << "\n>> Addr... << :";
			std::cin >> x;
			std::cout << "\n>> Value... << :";
			auto ret = 0;
			if (typ == 1) {
				byte vl = 0xc;
				Tp = Bytes;
				std::cin >> vl;
				std::cout << "\n\n" << vl << "\n\n";
				ret = WriteProcessMemory(phandle, (LPVOID)Addres[x], &vl, sizeof(vl), NULL);
			}
			else if (typ == 2)
			{
				__int32 vl = 0;
				Tp = D2Bytes;
				std::cin >> vl;
				std::cout << "\n\n" << vl << "\n\n";
				ret = WriteProcessMemory(phandle, (LPVOID)Addres[x], &vl, sizeof(vl), NULL);
			}
			else if (typ == 3) {
				float vl = 1.0;
				Tp = D4Bytes;
				std::cin >> vl;
				std::cout << "\n\n" << vl << "\n\n";
				ret = WriteProcessMemory(phandle, (LPVOID)Addres[x], &vl, sizeof(vl), NULL);

			}
			else if (typ == 8) {
				Tp = D8Bytes;
				std::cin >> ValorScan;
				ret = WriteProcessMemory(phandle, (LPVOID)Addres[x], &ValorScan, sizeof(ValorScan), NULL);
			}
			else {
				Tp = D4Bytes;
				std::cin >> ValorScan;
				ret = WriteProcessMemory(phandle, (LPVOID)Addres[x], &ValorScan, sizeof(ValorScan), NULL);
			}
		

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
		else if (x == 4)
		{
			std::cout << "\n>> Addr... << :";
			std::cin >> x;
			auto ret = 0;
			if (typ == 1) {
				byte vl = 0xc;
				Tp = Bytes;
				ret = ReadProcessMemory(phandle, (LPVOID)Addres[x], &vl, sizeof(vl), NULL);
				std::cout << vl << std::endl;
			}
			else if (typ == 2)
			{
				__int32 vl = 0;
				Tp = D2Bytes;
				ret = ReadProcessMemory(phandle, (LPVOID)Addres[x], &vl, sizeof(vl), NULL);
				std::cout << vl << std::endl;
			}
			else if (typ == 3) {
				float vl = 1.0;
				Tp = D4Bytes;
				ret = ReadProcessMemory(phandle, (LPVOID)Addres[x], &vl, sizeof(vl), NULL);
				std::cout << vl << std::endl;

			}
			else if (typ == 8) {
				Tp = D8Bytes;		
				ret = ReadProcessMemory(phandle, (LPVOID)Addres[x], &ValorScan, sizeof(ValorScan), NULL);
				std::cout << ValorScan << std::endl;
			}
			else {
				Tp = D4Bytes;
				ret = ReadProcessMemory(phandle, (LPVOID)Addres[x], &ValorScan, sizeof(ValorScan), NULL);
				std::cout << ValorScan << std::endl;
			}


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
	}
	

	CloseHandle(phandle);

	std::cout << "Thanks for using me, Shadowy hugs \nThank you to Smoll_ice - Aprendiz - iPower \n\n ";


		
	system("pause");

	getchar();
	return TRUE;
}