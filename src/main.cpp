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

#include "precompiler.hpp"
#include "compilation-date.hpp"
#include "version.hpp"
#include "natives.hpp"
#include "slot-manager.hpp"

extern void* pAMXFunctions;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return sampgdk::Supports() | SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	bool load = sampgdk::Load(ppData);
	sampgdk::logprintf("");
	sampgdk::logprintf(" =================================");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |      File System v%d.%d.%d       |", MINOR, MAJOR, PATCH);
	sampgdk::logprintf(" |           Loaded              |");
	sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  Coding:                      |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  Burak (Nexor)                |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  Compiled:                    |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  %02d.%02d.%04d, %02d:%02d:%02d         |", BUILD_DAY, BUILD_MONTH, BUILD_YEAR, BUILD_HOUR, BUILD_MIN, BUILD_SEC);
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  Github:                      |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  github.com/nexquery          |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  Discord:                     |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  Nexor#4730                   |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" =================================");
	sampgdk::logprintf("");
	return load;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
    SM::Destroy();

	sampgdk::logprintf("");
	sampgdk::logprintf(" =================================");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |      File System v%d.%d.%d       |", MINOR, MAJOR, PATCH);
	sampgdk::logprintf(" |           Unloaded            |");
	sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  Coding:                      |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  Burak (Nexor)                |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  Compiled:                    |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  %02d.%02d.%04d, %02d:%02d:%02d         |", BUILD_DAY, BUILD_MONTH, BUILD_YEAR, BUILD_HOUR, BUILD_MIN, BUILD_SEC);
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  Github:                      |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  github.com/nexquery          |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  Discord:                     |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" |  Nexor#4730                   |");
    sampgdk::logprintf(" |                               |");
    sampgdk::logprintf(" =================================");
	sampgdk::logprintf("");
	sampgdk::Unload();
}

extern "C" const AMX_NATIVE_INFO Native_List[] =
{
	// Log
	AMX_DEFINE_NATIVE(FileSystem_EnableLog)

    // Directory
	AMX_DEFINE_NATIVE(Directory_Exists)
    AMX_DEFINE_NATIVE(Directory_Create)
    AMX_DEFINE_NATIVE(Directory_Delete)
    AMX_DEFINE_NATIVE(Directory_Empty)
    AMX_DEFINE_NATIVE(Directory_Rename)
    AMX_DEFINE_NATIVE(Directory_CurrentPath)
    AMX_DEFINE_NATIVE(Directory_Copy)
    AMX_DEFINE_NATIVE(Directory_Open)
    AMX_DEFINE_NATIVE(Directory_Close)
    AMX_DEFINE_NATIVE(Directory_SetPath)
    AMX_DEFINE_NATIVE(Directory_GetPath)
    AMX_DEFINE_NATIVE(Directory_Size)
    AMX_DEFINE_NATIVE(Directory_List)

    // File
    AMX_DEFINE_NATIVE(File_Exists)
    AMX_DEFINE_NATIVE(File_Create)
    AMX_DEFINE_NATIVE(File_Delete)
    AMX_DEFINE_NATIVE(File_Copy)
    AMX_DEFINE_NATIVE(File_Rename)
    AMX_DEFINE_NATIVE(File_Open)
    AMX_DEFINE_NATIVE(File_Write)
    AMX_DEFINE_NATIVE(File_Read)
    AMX_DEFINE_NATIVE(File_Close)

    // Null
	{NULL, NULL}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx)
{
	return amx_Register(amx, Native_List, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
	return AMX_ERR_NONE;
}