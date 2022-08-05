/*
 * 	File-System
 *
 *	File Test
 *
 *	05.08.2022
 */

#include <a_samp>
#include <file-system5>

main()
{
	new ret = File_Exists("samp-server.exe");
	printf("[Ret 1]: %d\n", ret);

	ret = File_Exists("samp03svr");
	printf("[Ret 2]: %d\n", ret);

	ret = File_Exists("pawno/pawncc.exe");
	printf("[Ret 3]: %d\n", ret);

	ret = File_Create("Nexor.ini", ios_app); //---------------------------------->
	printf("[Ret 4]: %d\n", ret);

	ret = File_Create("Nexor.ini", 0);
	printf("[Ret 5]: %d\n", ret);

	ret = File_Delete("Nexor.ini");
	printf("[Ret 6]: %d\n", ret);

	ret = File_Delete("Nexor.ini");
	printf("[Ret 7]: %d\n", ret);

	ret = File_Copy("samp-server.exe", "scriptfiles/samp-server.exe");
	printf("[Ret 8]: %d\n", ret);

	ret = File_Copy("samp-server.exe", "scriptfiles/samp-server.exe");
	printf("[Ret 9]: %d\n", ret);

	ret = File_Copy("samp03svr", "scriptfiles/samp03svr");
	printf("[Ret 10]: %d\n", ret);

	ret = File_Copy("samp03svr", "scriptfiles/samp03svr");
	printf("[Ret 11]: %d\n", ret);

	ret = File_Rename("scriptfiles/samp-server.exe", "scriptfiles/server.exe");
	printf("[Ret 12]: %d\n", ret);

	ret = File_Rename("scriptfiles/samp-server.exe", "scriptfiles/server.exe");
	printf("[Ret 13]: %d\n", ret);

	ret = File_Rename("scriptfiles/samp03svr", "scriptfiles/server");
	printf("[Ret 14]: %d\n", ret);

	ret = File_Rename("scriptfiles/samp03svr", "scriptfiles/server");
	printf("[Ret 15]: %d\n", ret);

	ret = File_Permissions("scriptfiles/server.exe", perms_all, perm_options_replace);
	printf("[Ret 16]: %d\n", ret);

	ret = File_Permissions("scriptfiles/server", perms_all, perm_options_replace);
	printf("[Ret 17]: %d\n", ret);

	new File:file = File_Open("Nexor.txt", .openmode = ios_out), buffer[156];
	if(file)
	{
		File_Write(file, "QWE\n");
		File_Write(file, "ASD\n");
		File_Write(file, "ZXC\n");
		File_Close(file);

		file = File_Open("Nexor.txt", .openmode = ios_in);
		while(File_Read(file, buffer))
		{
			printf(buffer);
		}
		printf(" ");
		File_Close(file);
	}

	ret = File_Close(file);
	printf("[Ret 18]: %d\n", ret);
}