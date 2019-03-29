#pragma once
using std::cout;
using std::cin;
using std::endl;
bool argcheat(int argc, const char *argv[]) {
	if (argc >= 3) {
		if (argv[1] != "" && argv[2] != "")
		{
			char readorwrite, typo;

			HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, strtoul(argv[1], NULL, 10));
			
			DWORD addr = strtoul(argv[2], NULL, 16);
			printf("Address %X PID: %d\n\n", addr, strtoul(argv[1], NULL, 10));
			cout << "if yes what should we do? [r] read [w] write: ";
			cin >> readorwrite;

			if (readorwrite == 'w') {
				cout << "\n\n\ntype [4] or [8] for 4bytes (8bytes) [2] for 2bytes [f] for float: ";
				cin >> typo;
				if (typo == '4' || typo == '8')
				{
					int value;
					cout << "Lets set a new value : ";
					std::cin >> value;
					WriteProcessMemory(phandle, (LPVOID)addr, &value, sizeof(value), nullptr);
					cout << "If everything went well, thank you for using me :)";
				}
				else if (typo == '2')
				{
					__int32 value;
					cout << "Lets set a new value : ";
					std::cin >> value;
					WriteProcessMemory(phandle, (LPVOID)addr, &value, sizeof(value), nullptr);
					cout << "If everything went well, thank you for using me :)";
				}
				else if (typo == 'f')
				{
					float value;
					cout << "Lets set a new value : ";
					std::cin >> value;
					WriteProcessMemory(phandle, (LPVOID)addr, &value, sizeof(value), nullptr);
					cout << "If everything went well, thank you for using me :)";
				}
			}
			else if (readorwrite == 'r') {
				auto value = 0;
				ReadProcessMemory(phandle, (LPVOID)addr, &value, sizeof(addr), NULL);
				cout << "If everything is correct, nice!! this is the address!: " << value << std::endl;
				cout << "If everything went well, thank you for using me :)\n";
			}
		}
		else {
			cout << "Error Pid\n";
			return false;
		}
	}

	return true;
}