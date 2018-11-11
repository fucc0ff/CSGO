#include <windows.h>
#include <iostream>
#include <tlhelp32.h>
#include "Memory.h"
#include <math.h>

using namespace std;

namespace Boffsets {
	DWORD dwClient;
	DWORD dwEngine;
	DWORD dwForceJump = 0x50E33AC;
	DWORD dwLocalPlayer = 0xC638AC;
	DWORD dwHealth = 0xFC;
	DWORD dwfFlags = 0x100;
	DWORD dwcrosshairoff = 0xB2DC;
	DWORD dwELD = 0x10;
	DWORD dwTeamOff = 0xF0;
	DWORD dwEntity = 0x4C40664;
	DWORD dwAttack = 0x3081D40;
	DWORD dwGlowIndex = 0xA344;
	DWORD dwGlowObj = 0x517F940;
	DWORD dwVecOrigin = 0x134;
	DWORD dwVecView = 0x104;
	DWORD dwClientSTof = 0x588B34;
	DWORD dwVecViewAngles = 0x4D10;
}

#define FL_ONGROUND ( 1 << 0 )


struct cigdem
{

	DWORD lcl()
	{
		return RM<DWORD>(Boffsets::dwClient + Boffsets::dwLocalPlayer);
	}

	int cigdemhopp()
	{
		return RM<int>(Boffsets::dwClient + Boffsets::dwForceJump);
	}

	int fFlagz()
	{
		DWORD lcl = this->lcl();
		return RM<int>(lcl + Boffsets::dwfFlags);
	}

	int bizimtakim()
	{
		DWORD lcl = this->lcl();
		return RM<int>(lcl + Boffsets::dwTeamOff);
	}

	int crosshairid()
	{
		DWORD lcl = this->lcl();
		return RM<int>(lcl + Boffsets::dwcrosshairoff);
	}

	DWORD dusmanCH()
	{
		return RM<DWORD>(Boffsets::dwClient + Boffsets::dwEntity + ((crosshairid() - 1) * Boffsets::dwELD));
	}

	int dusmancan()
	{
		DWORD dusmanCH = this->dusmanCH();
		return RM<int>(dusmanCH + Boffsets::dwHealth);
	}

	int dusmantakim()
	{
		DWORD dusmanCH = this->dusmanCH();
		return RM<int>(dusmanCH + Boffsets::dwTeamOff);
	}

	DWORD GlowObj()
	{
		return RM<DWORD>(Boffsets::dwClient + Boffsets::dwGlowObj);
	}



	DWORD Entity(int i)
	{
		return RM<DWORD>(Boffsets::dwClient + Boffsets::dwEntity + i * Boffsets::dwELD);
	}

	int EntityCan(int i)
	{
		DWORD Entity = this->Entity(i);
		return RM<int>(Entity + Boffsets::dwHealth);
	}

	int EntityTeamFnc(int i)
	{
		DWORD Entity = this->Entity(i);
		return RM<int>(Entity + Boffsets::dwTeamOff);
	}
	int GlowInd(int i)
	{
		DWORD Entity = this->Entity(i);
		return RM<int>(Entity + Boffsets::dwGlowIndex);
	}

	void gl0w1(int i, float z)
	{
		DWORD GlowObj = this->GlowObj();
		int GlowInd = this->GlowInd(i);
		WM<float>(GlowObj + ((GlowInd * 0x38) + 0x4), z);
	}

	void gl0w2(int i, float b)
	{
		DWORD GlowObj = this->GlowObj();
		int GlowInd = this->GlowInd(i);
		WM<float>(GlowObj + ((GlowInd * 0x38) + 0x8), b);
	}

	void gl0w3(int i, float r)
	{
		DWORD GlowObj = this->GlowObj();
		int GlowInd = this->GlowInd(i);
		WM<float>(GlowObj + ((GlowInd * 0x38) + 0xC), r);
	}

	void gl0w4(int i, float u)
	{
		DWORD GlowObj = this->GlowObj();
		int GlowInd = this->GlowInd(i);
		WM<float>(GlowObj + ((GlowInd * 0x38) + 0x10), u);
	}

	void gl00w(int i, bool l)
	{
		DWORD GlowObj = this->GlowObj();
		int GlowInd = this->GlowInd(i);
		WM<bool>(GlowObj + ((GlowInd * 0x38) + 0x24), l);
	}

	void gl000w(int i, bool m)
	{
		DWORD GlowObj = this->GlowObj();
		int GlowInd = this->GlowInd(i);
		WM<bool>(GlowObj + ((GlowInd * 0x38) + 0x25), m);
	}

	void setattack(int k)
	{
		WM<int>(Boffsets::dwClient + Boffsets::dwAttack, k);
	}

	void Setcigdemhopp(int v)
	{
		WM<int>(Boffsets::dwClient + Boffsets::dwForceJump, v);
	}



};

struct cigdem *pcigdem;


void sik()
{

	struct cigdem;
	for (;; Sleep(1))
	{
		for (short int i = 0; i < 64; i++)
		{
			
			if (pcigdem->bizimtakim() == pcigdem->EntityTeamFnc(i))
			{
				pcigdem->gl0w1(i, 0);
				pcigdem->gl0w2(i, 0);
				pcigdem->gl0w3(i, 2);
				pcigdem->gl0w4(i, 1);
			}
			else
			{
				pcigdem->gl0w1(i, 2);
				pcigdem->gl0w2(i, 0);
				pcigdem->gl0w3(i, 0);
				pcigdem->gl0w4(i, 1);
			}
			pcigdem->gl00w(i, true);
			pcigdem->gl000w(i, false);
		}

		while (GetAsyncKeyState(VK_MENU))
		{
			if (pcigdem->crosshairid() != 0 && pcigdem->crosshairid() < 64)
			{
				if (pcigdem->bizimtakim() != pcigdem->dusmantakim() && pcigdem->dusmancan() > 0)
				{
					Sleep(3);
					pcigdem->setattack(5);
					Sleep(3);
					pcigdem->setattack(4);
					Sleep(10);
				}
			}
		}
		if (pcigdem->cigdemhopp() == 5)
		{
			while (GetAsyncKeyState(VK_SPACE))
			{
				if (pcigdem->fFlagz() & FL_ONGROUND)
					pcigdem->Setcigdemhopp(5);
				else
					pcigdem->Setcigdemhopp(4);
			}
		}

		if (!FindWindow(NULL, "Counter-Strike: Global Offensive"))
			exit(0);

		if (GetAsyncKeyState(VK_HOME))
			exit(0);
	}


}

int main()
{
	if (!FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		cout << "CS:GO'yu acmamissin amk mali..." << endl;
		system("pause");
		exit(0);
	}

	while (!Boffsets::dwClient) {
		pMemory->FindProcess("csgo.exe");
		Boffsets::dwClient = pMemory->ModulePointer("client_panorama.dll");
		Boffsets::dwEngine = pMemory->ModulePointer("engine_panorama.dll");
	}

	sik();


}
