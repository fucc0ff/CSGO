class cMemory
{
public:
	HANDLE HandleProcess;
	DWORD  ProcessID;

	bool  FindProcess(const char* name)
	{
		PROCESSENTRY32 ProcessEntry;
		ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (hSnap == INVALID_HANDLE_VALUE) return 0;

		do
		{
			if (!strcmp(ProcessEntry.szExeFile, name))
			{
				ProcessID = ProcessEntry.th32ProcessID;
				CloseHandle(hSnap);

				HandleProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_VM_OPERATION, false, ProcessID);
				return true;
			}
		} while (Process32Next(hSnap, &ProcessEntry));

		CloseHandle(hSnap);
		//	std::cout << "Error 1\n\n";
	}
	DWORD ModulePointer(const char* name)
	{
		MODULEENTRY32 ModuleEntry = { 0 };
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);

		if (!hSnap) return NULL;

		ModuleEntry.dwSize = sizeof(ModuleEntry);
		BOOL Run = Module32First(hSnap, &ModuleEntry);

		while (Run) {
			if (!strcmp(ModuleEntry.szModule, name))
			{
				CloseHandle(hSnap);
				return (DWORD)ModuleEntry.modBaseAddr;
			}
			Run = Module32Next(hSnap, &ModuleEntry);
		}
		CloseHandle(hSnap);
		//	std::cout << "Error 2\n\n";
		return NULL;
	}

};

cMemory *pMemory = new cMemory;

template <class T>
T RM(DWORD adress)
{
	T out;
	ReadProcessMemory(pMemory->HandleProcess, (LPVOID)adress, &out, sizeof(T), NULL);
	return out;
}

template <class T>
void WM(DWORD adress, T value)
{
	WriteProcessMemory(pMemory->HandleProcess, (LPVOID)adress, &value, sizeof(T), 0);
}
