/*
 * Copyright (C) 2022 Burak (Nexor)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined _PLUGIN_FILE_SYSTEM_
	#endinput
#endif
#define _PLUGIN_FILE_SYSTEM_

enum OpenMode
{
	ios_base_in,				// Open for input operations.
	ios_base_out,				// Open for output operations.
	ios_base_ate,				// Set the initial position at the end of the file. If this flag is not set, the initial position is the beginning of the file.
	ios_base_app,				// All output operations are performed at the end of the file, appending the content to the current content of the file.
	ios_base_trunc,				// If the file is opened for output operations and it already existed, its previous content is deleted and replaced by the new one.
	ios_base_binary				// Open in binary mode.
};

enum FileType
{
	ft_regular,					//  Represents a conventional disk file.
	ft_directory,				//  Represents a directory.
	ft_symlink,					//  Represents a symbolic link. (Not supported.)
	ft_block,					//  Represents a block-special file on UNIX-based systems. (Not supported.)
	ft_character,				//  Represents a character-special file on UNIX-based systems. (Not supported.)
	ft_fifo,					//  Represents a FIFO file on UNIX-based systems. (Not supported.)
	ft_socket					//  Represents a socket on UNIX based systems. (Not supported.)
};

enum CopyOptions
{
	co_none,					//	Perform the default behavior for the operation.
	co_skip_existing,			//	Do not copy if the file already exists, do not report an error.
	co_overwrite_existing,		//	Overwrite the file if it already exists.
	co_update_existing,			//	Overwrite the file if it already exists and is older than the replacement.
	co_recursive,				//	Recursively copy subdirectories and their contents.
	co_copy_symlinks,			//	Copy symbolic links as symbolic links, instead of copying the files they point to.
	co_skip_symlinks,			//	Ignore symbolic links.
	co_directories_only,		//	Only iterate over directories, ignore files.
	co_create_symlinks,			//	Make symbolic links instead of copying files. An absolute path must be used as the source path unless the destination is the current directory.
	co_create_hard_links		//	Make hard links instead of copying files.
};

// Log
native FileSystem_EnableLog(bool:enable);

// Directory
native Directory_Exists(const path[]);
native Directory_Create(const path[]);
native Directory_Delete(const path[]);
native Directory_Empty(const path[]);
native Directory_Rename(const old_name[], const new_name[]);
native Directory_CurrentPath(path[], len = sizeof(path));
native Directory_Copy(const from[], const to[], {CopyOptions, _}:...);
native Dir:Directory_Open(const path[] = ".");
native Directory_SetPath(Dir:dir, const path[]);
native Directory_GetPath(Dir:dir, path[], len = sizeof(path));
native Directory_Size(Dir:dir);
native Directory_List(Dir:dir, index, file_name[], full_path[], &file_size, &file_type, len = sizeof(file_name), len2 = sizeof(full_path));
native Directory_Close(Dir:dir);

// File
native File_Exists(const path[]);
native File_Create(const path[], {OpenMode, _}:...);
native File_Delete(const path[]);
native File_Copy(const from[], const to[], {CopyOptions, _}:...);
native File_Rename(const old_name[], const new_name[]);
native File:File_Open(const path[], {OpenMode, _}:...);
native File_Write(File:file, const string[]);
native File_Read(File:file, string[], len = sizeof(string));
native File_Close(File:file);