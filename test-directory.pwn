/*
 * 	File-System
 *
 *	Directory Test
 *
 *	05.08.2022
 */

#include <a_samp>
#include <file-system5>

main()
{
	/*----------------------------------------------------*/

	// Default Directory
	new ret = Directory_Exists("gamemodes");
	printf("Default Directory Ret: %d\n", ret);

	// Windows Directory
	new ret2 = Directory_Exists("C:\\Program Files");
	printf("Windows Directory Ret2: %d\n", ret2);

	// Linux Directory
	new ret3 = Directory_Exists("/home/nexor/Desktop/samp/samp03");
	printf("Linux Directory Ret3: %d\n", ret3);

	// Windows + Linux
	new ret4 = Directory_Exists("./scriptfiles");
	printf("Windows + Linux Directory Ret4: %d\n", ret4);

	// Invalid
	new ret5 = Directory_Exists("./scriptfiles-123456789");
	printf("Directory_Exists Invalid Ret5: %d\n", ret5);

	/*----------------------------------------------------*/

	new ret6 = Directory_Create("./gamemodes/test-folder");
	printf("Directory_Create Ret6: %d\n", ret6);

	new ret7 = Directory_Create(".\\gamemodes\\test-folder2");
	printf("Directory_Create Ret7: %d\n", ret7);

	/*----------------------------------------------------*/

	new ret8 = Directory_Delete(".\\gamemodes//test-folder2");
	printf("Directory_Delete Ret8: %d\n", ret8);

	new ret9 = Directory_Delete("asdqwe"); // buglu
	printf("Directory_Delete Ret9: %d\n", ret9);

	/*----------------------------------------------------*/

	new ret10 = Directory_Empty("./gamemodes/test-folder");
	printf("Directory_Empty Ret10: %d\n", ret10);

	new ret11 = Directory_Empty("gamemodes");
	printf("Directory_Empty Ret11: %d\n", ret11);

	/*----------------------------------------------------*/

	new ret12 = Directory_Rename("./gamemodes/test-folder", "./gamemodes/test-folder5"); // Kontrol edilecek
	printf("Directory_Rename Ret12: %d\n", ret12);

	new ret13 = Directory_Rename("./gamemodes/test-folder", "./gamemodes/test-folder5");
	printf("Directory_Rename Ret13: %d\n", ret13);

	/*----------------------------------------------------*/

	new current_path[260];
	Directory_CurrentPath(current_path);
	printf("Directory_CurrentPath: %s\n", current_path);

	/*----------------------------------------------------*/

	new ret14 = Directory_Copy("./gamemodes/test-folder5", "./scriptfiles/test-folder5"); // Kontrol edilecek
	printf("Directory_Copy Ret14: %d\n", ret14);

	new ret15 = Directory_Copy("./gamemodes/test-folder5", "./scriptfiles/test-folder5");
	printf("Directory_Copy Ret15: %d\n", ret15);

	new ret16 = Directory_Copy("qwerty", "/scriptfiles/qwerty");
	printf("Directory_Copy Ret16: %d\n", ret16);

	/*----------------------------------------------------*/

	new Dir:ret17 = Directory_Open("zxcvy");
	printf("Directory_Open Ret17: %d\n", _:ret17);

	new Dir:ret18 = Directory_Open(); // current path
	printf("Directory_Open Ret18: %d\n", _:ret18);

	/*----------------------------------------------------*/

	if(ret18)
	{
		new file_name[50], full_path[260], file_size, file_type;
		for(new i = 0; i < Directory_Size(ret18); i++)
		{
			Directory_List(ret18, i, file_name, full_path, file_size, file_type);
			printf("File: %s", file_name);
			printf("Path: %s", full_path);
			printf("Size: %d", file_size);
			if(file_type == ft_directory)
			{
				printf("Type: %d :: Directory", file_type);
			}
			else if(file_type == ft_regular)
			{
				printf("Type: %d :: File", file_type);
			}
			printf(" ");
		}

		format(current_path, sizeof(current_path), "%s/scriptfiles", current_path);
		Directory_SetPath(ret18, current_path);

		new get_path[256];
		Directory_GetPath(ret18, get_path);
		printf("\nGetPath: %s\n", get_path);

		for(new i = 0; i < Directory_Size(ret18); i++)
		{
			Directory_List(ret18, i, file_name, full_path, file_size, file_type);
			printf("File: %s", file_name);
			printf("Path: %s", full_path);
			printf("Size: %d", file_size);
			if(file_type == ft_directory)
			{
				printf("Type: %d :: Directory", file_type);
			}
			else if(file_type == ft_regular)
			{
				printf("Type: %d :: File", file_type);
			}
			printf(" ");
		}

		new ret19 = Directory_Close(ret18);
		printf("Directory_Close Ret19: %d\n", ret19);

		new ret20 = Directory_Close(ret18);
		printf("Directory_Close Ret20: %d\n", ret20);
	}

	Directory_Open();
}
