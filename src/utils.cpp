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

#include "utils.hpp"

void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace) 
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) 
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

void Utils::String_Replace(std::string& string)
{
	// Windowsta '/' karakterini -> '\' dönüþtür.
	#ifdef _WIN32
		ReplaceStringInPlace(string, "/", "\\");
	#else
	// Linuxta '\' karakterini -> '/' dönüþtür.
		ReplaceStringInPlace(string, "\\", "/");
	#endif
}