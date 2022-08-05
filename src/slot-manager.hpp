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

#include "precompiler.hpp"

class SM
{
	public:

		struct Klasor_Verileri
		{
			std::string isim;
			std::string dizin;
			uintmax_t boyut;
			int tur;
		};

		static std::map<int, std::string>* Dizin;
		static std::unordered_map<int, std::vector<Klasor_Verileri>*>* Dizin_List;

		static std::vector<fstream*> *Dosya;

		static bool Logger;

		static int GetID();
		static void RemoveID(int id);
		static bool IsValidID(int id);
		static void UpdateList(int id, int mode);
		static bool LogMode();
		static void Destroy();

	private:

		static int Slot_Counter;
		static std::priority_queue<int, std::vector<int>, std::greater<int>> *Slot;
};