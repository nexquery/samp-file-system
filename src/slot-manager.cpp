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

#include "slot-manager.hpp"

bool SM::Logger = true;

int SM::Slot_Counter = 0;
std::priority_queue<int, std::vector<int>, std::greater<int>> *SM::Slot = new std::priority_queue<int, std::vector<int>, std::greater<int>>();

std::vector<fstream*>* SM::Dosya = new std::vector<fstream*>();

std::map<int, std::string>* SM::Dizin = new std::map<int, std::string>();
std::unordered_map<int, std::vector<SM::Klasor_Verileri>*>* SM::Dizin_List = new std::unordered_map<int, std::vector<Klasor_Verileri>*>();

bool Type_Sort(const SM::Klasor_Verileri& a, const SM::Klasor_Verileri& b)
{
	if (a.tur == 1 && b.tur != 1)
	{
		return a.tur > b.tur;
	}
	return a.tur < a.tur;
}

int SM::GetID()
{
	int gecerli_id = 0;
	if (Slot->empty())
	{
		Slot_Counter++;
		gecerli_id = Slot_Counter;
	}
	else
	{
		gecerli_id = Slot->top();
		Slot->pop();
	}
	return gecerli_id;
}

void SM::RemoveID(int id)
{
	Slot->push(id);
}

bool SM::IsValidID(int id)
{
	std::map<int, std::string>::iterator p = Dizin->find(id);
	if (p != Dizin->end())
	{
		return true;
	}
	return false;
}

void SM::UpdateList(int id, int mode)
{
	if (IsValidID(id))
	{
		std::map<int, std::string>::iterator g = Dizin->find(id);
		if (g != Dizin->end())
		{
			std::unordered_map<int, std::vector<Klasor_Verileri>*>::iterator p = Dizin_List->find(id);
			if (p != Dizin_List->end())
			{
				p->second->clear();
				Klasor_Verileri data;
				for (const auto& dir : std::filesystem::directory_iterator(g->second))
				{
					try
					{
						data.isim = dir.path().filename().string();
						data.dizin = dir.path().string();
						if (dir.is_regular_file()) { data.boyut = dir.file_size(), data.tur = 0; }
						if (dir.is_directory()) { data.boyut = 0, data.tur = 1; }
						if (dir.is_symlink()) { data.boyut = dir.file_size(), data.tur = 2; }
						if (dir.is_block_file()) { data.boyut = dir.file_size(), data.tur = 3; }
						if (dir.is_character_file()) { data.boyut = dir.file_size(), data.tur = 4; }
						if (dir.is_fifo()) { data.boyut = dir.file_size(), data.tur = 5; }
						if (dir.is_socket()) { data.boyut = dir.file_size(), data.tur = 6; }
						p->second->push_back(data);
					}
					catch (const std::system_error& e)
					{
						if (LogMode())
						{
							if (mode == 0)
							{
								sampgdk::logprintf("[file-system] Directory_Open: %s", e.what());
							}
							else
							{
								sampgdk::logprintf("[file-system] Directory_SetPath: %s", e.what());
							}
						}
					}
				}
				std::sort(p->second->begin(), p->second->end(), Type_Sort);
			}
		}
	}
	else
	{
		if (LogMode())
		{
			sampgdk::logprintf("[file-system] Directory_SetPath: You did not specify a valid handle. (new Dir:?)");
		}
	}
}

bool SM::LogMode()
{
	return Logger;
}

void SM::Destroy()
{
	delete Slot;
	delete Dizin;

	for (std::unordered_map<int, std::vector<SM::Klasor_Verileri>*>::iterator it = Dizin_List->begin(); it != Dizin_List->end(); it++)
	{
		delete it->second;
	}
	delete Dizin_List;

	for (std::vector<fstream*>::iterator it = Dosya->begin(); it != Dosya->end(); it++)
	{
		delete *it;
	}
	delete Dosya;
}