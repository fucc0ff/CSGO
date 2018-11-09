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

#define Pi 3.141592

#define FL_ONGROUND ( 1 << 0 )

struct vec4
{
	float x, y, z;	
};

vec4 OurLoc, EntityLoc, Angels, eymAngles;

float Bestie = 0;
float EnemyLocEyes;
float OurLocEyes;
float DistEnemy = 999;
float CurrentDist;
float CurrDist;
float Distence(vec4 us,vec4 enemy );

int i;

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
		DWORD Entity = this-> Entity(i);
		return RM<int>(Entity + Boffsets::dwTeamOff);
	}

	int EntityLoc(int i)
	{
		DWORD Entity = this->Entity(i);
		return RM<int>(Entity + Boffsets::dwVecOrigin);
	}

	int OurLoc()
	{
		DWORD lcl = this->lcl();
		return RM<int>(lcl + Boffsets::dwVecOrigin);
	}

	int EntityView(int i)
	{
		DWORD Entity = this->Entity(i);
		return RM<int>(Entity + Boffsets::dwVecView);
	}

	int GlowInd(int i)
	{
		DWORD Entity = this->Entity(i);
		return RM<int>(Entity + Boffsets::dwGlowIndex);
	}

	DWORD ClientSt()
	{
		return RM<DWORD>(Boffsets::dwEngine + Boffsets::dwClientSTof);
	}


	float Angels()
	{
		DWORD ClientSt = this->ClientSt();
		return RM<float>(ClientSt + Boffsets::dwVecViewAngles);
	}
	void gl0w1(int i ,float z)
	{
		DWORD GlowObj = this->GlowObj();
		int GlowInd = this->GlowInd(i);
		WM<float>(GlowObj + ((GlowInd * 0x38) + 0x4), z);
	}

	void gl0w2(int i ,float b)
	{
		DWORD GlowObj = this->GlowObj();
		int GlowInd = this->GlowInd(i);
		WM<float>(GlowObj + ((GlowInd * 0x38) + 0x8), b);
	}

	void gl0w3(int i,float r)
	{
		DWORD GlowObj = this->GlowObj();
		int GlowInd = this->GlowInd(i);
		WM<float>(GlowObj + ((GlowInd * 0x38) + 0xC), r);
	}

	void gl0w4(int i ,float u)
	{
		DWORD GlowObj = this->GlowObj();
		int GlowInd = this->GlowInd(i);
		WM<float>(GlowObj + ((GlowInd * 0x38) + 0x10), u);
	}

	void gl00w(int i ,bool l)
	{
		DWORD GlowObj = this->GlowObj();
		int GlowInd = this->GlowInd(i);
		WM<bool>(GlowObj + ((GlowInd * 0x38) + 0x24), l);
	}

	void gl000w(int i ,bool m)
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

#define PROCESS "csgo.exe"


void sik()
{
	
	struct cigdem;
	for (;; Sleep(1))
	{
		for (short int i = 0; i < 64; i++)
		{
			pcigdem->Entity(i);
			if (pcigdem->bizimtakim() != pcigdem->dusmantakim() && pcigdem->dusmancan() > 0)
			{
				pcigdem->EntityLoc(i);
					pcigdem->OurLoc();
				CurrDist = Distence(pcigdem->OurLoc, pcigdem->EntityLoc);
				if (CurrDist < DistEnemy)
				{
					DistEnemy = CurrDist;
					Bestie = i;
					
				}

			}

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
			pcigdem->gl00w(i,true);
			pcigdem->gl000w(i,false);
		}
		while (GetAsyncKeyState(VK_CONTROL))
		{
			CurrDist = 99999;
			DistEnemy = 99999;
			Bestie;
			pcigdem->Entity(Bestie);
			pcigdem->EntityCan(Bestie);
			if (Bestie > 0 && pcigdem->EntityCan(i) > 0)
			{
				pcigdem->OurLoc();
				pcigdem->Entity(Bestie);
				pcigdem->EntityLoc(Bestie);
				pcigdem->EntityView(Bestie);
				pcigdem->Angels;
				eymAngles = CalcAci(pcigdem->OurLoc, pcigdem->EntityLoc);

				WriteProcessMemory(pMemory->HandleProcess, (BYTE*)(pcigdem->ClientSt + Boffsets::dwVecViewAngles), &eymAngles.y, sizeof(float), NULL);    //Aim angels
				WriteProcessMemory(pMemory->HandleProcess, (BYTE*)(pcigdem->ClientSt + Boffsets::dwVecViewAngles + 0x4), &eymAngles.x, sizeof(float), NULL);


			}
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


vec4 CalcAci(vec4 sors, vec4 dist)
{
	vec4 fark;
	vec4 acilar;

	fark.x = dist.x - sors.x;
	fark.y = dist.y - sors.y;
	fark.z = dist.z - sors.z;

	float kare = sqrtf(fark.x*fark.x + fark.y*fark.y +fark.z*fark.z);

	acilar.x = (float)atan2(fark.y, fark.x) * 180.0 / Pi;
	acilar.y = -(float)atan2(fark.z, kare) * 180.0 / Pi;
	acilar.z = 0;
	return acilar;
}

float Distence(vec4 us, vec4 enemy)
{
	float distance = sqrt(pow(enemy.x - us.x, 2) + pow(enemy.y - us.y, 2) + pow(enemy.z - us.z, 2));

	return distance;
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

float Distence(vec4 us, vec4 enemy)
{
	float distence = sqrt(pow(enemy.x - us.x, 2) + pow(enemy.y - us.y, 2) + pow(enemy.z - us.z, 2));

	return distence;
}
