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

#include "service.hpp"

void Service::Native_SetInt(AMX* amx, cell output, int value)
{
	cell* address;
	amx_GetAddr(amx, output, &address);
	*address = value;
}

void Service::Native_SetFloat(AMX* amx, cell output, float value)
{
	cell* address;
	amx_GetAddr(amx, output, &address);
	*address = amx_ftoc(value);
}

void Service::Native_SetString(AMX* amx, cell output, cell size, std::string string)
{
	cell* address = NULL;
	amx_GetAddr(amx, output, &address);
	amx_SetString(address, string.c_str(), 0, 0, static_cast<size_t>(size));
}

std::string Service::Native_GetString(AMX* amx, cell input)
{
	char* string = NULL;
	amx_StrParam(amx, input, string);
	return string ? string : "";
}