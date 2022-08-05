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

#pragma once

#pragma once

#include "precompiler.hpp"
#include "service.hpp"

#define AMX_DEFINE_NATIVE(native) {#native, Native::native},

#define CHECK_PARAMS(n) \
	if (params[0] != (n * 4)) \
	{ \
		sampgdk::logprintf("%s: Expecting %d parameter(s), but found %d.", __func__, n, params[0] / sizeof(cell)); \
		return 0; \
	}

namespace Native
{
	// Log
	cell AMX_NATIVE_CALL FileSystem_EnableLog(AMX* amx, cell* params);

	// Directory
	cell AMX_NATIVE_CALL Directory_Exists(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL Directory_Create(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL Directory_Delete(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL Directory_Empty(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL Directory_Rename(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL Directory_CurrentPath(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL Directory_Copy(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL Directory_Open(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL Directory_Close(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL Directory_SetPath(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL Directory_GetPath(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL Directory_Size(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL Directory_List(AMX* amx, cell* params);

	// File
	cell AMX_NATIVE_CALL File_Exists(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL File_Create(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL File_Delete(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL File_Copy(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL File_Rename(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL File_Open(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL File_Write(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL File_Read(AMX* amx, cell* params);
	cell AMX_NATIVE_CALL File_Close(AMX* amx, cell* params);
};