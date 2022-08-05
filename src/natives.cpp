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

#include "natives.hpp"
#include "utils.hpp"
#include "slot-manager.hpp"

cell AMX_NATIVE_CALL Native::FileSystem_EnableLog(AMX* amx, cell* params)
{
	SM::Logger = static_cast<cell>(params[1]);
	return 1;
}

cell AMX_NATIVE_CALL Native::Directory_Exists(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::error_code ex;
	std::string path = Service::Native_GetString(amx, params[1]);
	Utils::String_Replace(path);
	cell ret = fs::is_directory(path, ex);
	if (ex.value() != 0 && SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: %s", __func__, ex.message().c_str());
	}
	return ret;
}

cell AMX_NATIVE_CALL Native::Directory_Create(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::error_code ex;
	std::string path = Service::Native_GetString(amx, params[1]);
	Utils::String_Replace(path);
	cell ret = fs::create_directories(path, ex);
	if (ex.value() != 0 && SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: %s", __func__, ex.message().c_str());
	}
	return ret;
}

cell AMX_NATIVE_CALL Native::Directory_Delete(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::error_code ex;
	std::string path = Service::Native_GetString(amx, params[1]);
	Utils::String_Replace(path);
	if (!fs::is_directory(path))
	{
		return 0;
	}
	fs::remove_all(path, ex);
	if (ex.value() != 0 && SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: %s", __func__, ex.message().c_str());
	}
	return (ex.value() == 0) ? (1) : (0);
}

cell AMX_NATIVE_CALL Native::Directory_Empty(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::error_code ex;
	std::string path = Service::Native_GetString(amx, params[1]);
	Utils::String_Replace(path);
	cell ret = fs::is_empty(path, ex);
	if (ex.value() != 0 && SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: %s", __func__, ex.message().c_str());
	}
	return ret;
}

cell AMX_NATIVE_CALL Native::Directory_Rename(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::error_code ex;
	std::string old_name = Service::Native_GetString(amx, params[1]);
	std::string new_name = Service::Native_GetString(amx, params[2]);
	Utils::String_Replace(old_name);
	Utils::String_Replace(new_name);
	fs::rename(old_name, new_name, ex);
	if (ex.value() != 0 && SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: %s", __func__, ex.message().c_str());
	}
	return (ex.value() == 0) ? (1) : (0);
}

cell AMX_NATIVE_CALL Native::Directory_CurrentPath(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	Service::Native_SetString(amx, params[1], params[2], fs::current_path().string());
	return 1;
}

cell AMX_NATIVE_CALL Native::Directory_Copy(AMX* amx, cell* params)
{
	CHECK_PARAMS(params[0] / sizeof(cell));

	// From
	std::string from = Service::Native_GetString(amx, params[1]);
	Utils::String_Replace(from);

	// To
	std::string to = Service::Native_GetString(amx, params[2]);
	Utils::String_Replace(to);

	// Kopyalama modu
	std::error_code ex;
	fs::copy_options mod{};

	// Modları çek
	for (size_t i = 3; i <= params[0] / sizeof(cell); i++)
	{
		cell* address = nullptr;
		amx_GetAddr(amx, params[i], &address);

		if (address == nullptr) {
			break;
		}

		if (*address == 0) mod = mod | fs::copy_options::none;
		if (*address == 1) mod = mod | fs::copy_options::skip_existing;
		if (*address == 2) mod = mod | fs::copy_options::overwrite_existing;
		if (*address == 3) mod = mod | fs::copy_options::update_existing;
		if (*address == 4) mod = mod | fs::copy_options::recursive;
		if (*address == 5) mod = mod | fs::copy_options::copy_symlinks;
		if (*address == 6) mod = mod | fs::copy_options::skip_symlinks;
		if (*address == 7) mod = mod | fs::copy_options::directories_only;
		if (*address == 8) mod = mod | fs::copy_options::create_symlinks;
		if (*address == 9) mod = mod | fs::copy_options::create_hard_links;
	}	
	
	fs::copy(from, to, mod, ex);

	if (ex.value() != 0 && SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: %s\n", __func__, ex.message().c_str());
	}

	return (ex.value() == 0) ? (1) : (0);
}

cell AMX_NATIVE_CALL Native::Directory_Open(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::error_code ex;
	std::string path = Service::Native_GetString(amx, params[1]);
	Utils::String_Replace(path);

	// Eğer konum "." ise varsayılan konumu samp-serverin çalıştığı dizin olarak ayarla
	if (path == ".")
	{
		path = fs::current_path().string();
	}

	// Dizine erişilebiliyor mu?
	if (!fs::is_directory(path, ex))
	{
		if (ex.value() != 0 && SM::LogMode())
		{
			sampgdk::logprintf("[file-system] %s: %s\n", __func__, ex.message().c_str());
		}
		return 0;
	}

	// Yeni bir id al
	cell id = SM::GetID();

	// Yeni bir vektör pointerı oluştur
	std::vector<SM::Klasor_Verileri>* p = new std::vector<SM::Klasor_Verileri>();

	// Geçerli dizini kaydet
	SM::Dizin->insert({ id, path });

	// Geçerli vektör pointerını kaydet
	SM::Dizin_List->insert({ id, p });

	// Klasör verilerini güncelle
	SM::UpdateList(id, 0);
	return id;
}

cell AMX_NATIVE_CALL Native::Directory_Close(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	cell id = static_cast<cell>(params[1]);
	if (SM::IsValidID(id))
	{
		SM::RemoveID(id);

		std::map<int, std::string>::iterator g = SM::Dizin->find(id);
		if (g != SM::Dizin->end())
		{
			SM::Dizin->erase(g);
		}

		std::unordered_map<int, std::vector<SM::Klasor_Verileri>*>::iterator p = SM::Dizin_List->find(id);
		if (p != SM::Dizin_List->end())
		{
			delete p->second;
			SM::Dizin_List->erase(p);
		}
		return 1;
	}
	if (SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: You did not specify a valid handle. (new Dir:?)\n", __func__);
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::Directory_SetPath(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::error_code ex;
	std::string path = Service::Native_GetString(amx, params[2]);

	Utils::String_Replace(path);
	bool ret = fs::is_directory(path, ex);

	if (ex.value() != 0 && SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: %s", __func__, ex.message().c_str());
		return 0;
	}

	cell id = static_cast<cell>(params[1]);

	std::map<int, std::string>::iterator p = SM::Dizin->find(id);
	if (p != SM::Dizin->end())
	{
		p->second = path;
		SM::UpdateList(id, 1);
		return 1;
	}

	if (SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: You did not specify a valid handle. (new Dir:?)", __func__);
	}
	
	return 0;
}

cell AMX_NATIVE_CALL Native::Directory_GetPath(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	cell id = static_cast<cell>(params[1]);
	std::map<int, std::string>::iterator p = SM::Dizin->find(id);
	if (p != SM::Dizin->end())
	{
		Service::Native_SetString(amx, params[2], params[3], p->second.c_str());
		return 1;
	}
	if (SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: You did not specify a valid handle. (new Dir:?)", __func__);
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::Directory_Size(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	cell id = static_cast<cell>(params[1]);
	std::unordered_map<int, std::vector<SM::Klasor_Verileri>*>::iterator p = SM::Dizin_List->find(id);
	if (p != SM::Dizin_List->end())
	{
		if (!p->second->empty())
		{
			return p->second->size();
		}
		else
		{
			return 0;
		}
	}
	if (SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: You did not specify a valid handle. (new Dir:?)", __func__);
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::Directory_List(AMX* amx, cell* params)
{
	CHECK_PARAMS(8);
	cell id = static_cast<cell>(params[1]);
	cell index = static_cast<cell>(params[2]);
	std::unordered_map<int, std::vector<SM::Klasor_Verileri>*>::iterator p = SM::Dizin_List->find(id);
	if (p != SM::Dizin_List->end())
	{
		if (!p->second->empty())
		{
			if (index >= 0 && (unsigned long)index <= p->second->size() - 1)
			{
				Service::Native_SetString(amx, params[3], params[7], p->second->at(index).isim);
				Service::Native_SetString(amx, params[4], params[8], p->second->at(index).dizin);
				Service::Native_SetInt(amx, params[5], (int)p->second->at(index).boyut);
				Service::Native_SetInt(amx, params[6], p->second->at(index).tur);
				return 1;
			}
		}
	}
	if (SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: You did not specify a valid handle. (new Dir:?)", __func__);
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::File_Exists(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::error_code ex;
	std::string path = Service::Native_GetString(amx, params[1]);
	Utils::String_Replace(path);
	cell ret = fs::is_regular_file(path, ex);
	if (ex.value() != 0 && SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: %s", __func__, ex.message().c_str());
	}
	return ret;
}

cell AMX_NATIVE_CALL Native::File_Create(AMX* amx, cell* params)
{
	CHECK_PARAMS(params[0] / sizeof(cell));

	// Dosya konumu ve adı
	std::string path = Service::Native_GetString(amx, params[1]);
	Utils::String_Replace(path);

	// Dosya
	std::ofstream dosya;

	// Hangi modda açılacak ?
	std::ios_base::openmode mod{};

	// Modları çek
	for (size_t i = 2; i <= params[0] / sizeof(cell); i++)
	{
		cell* address = nullptr;
		amx_GetAddr(amx, params[i], &address);

		if (address == nullptr) {
			break;
		}

		if (*address == 0) mod = mod | std::ios_base::in;
		if (*address == 1) mod = mod | std::ios_base::out;
		if (*address == 2) mod = mod | std::ios_base::ate;
		if (*address == 3) mod = mod | std::ios_base::app;
		if (*address == 4) mod = mod | std::ios_base::trunc;
		if (*address == 5) mod = mod | std::ios_base::binary;
	}

	dosya.open(path, mod);

	if (dosya.is_open()) 
	{
		dosya.close();
		return 1;
	}

	return 0;
}

cell AMX_NATIVE_CALL Native::File_Delete(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	std::error_code ex;
	std::string path = Service::Native_GetString(amx, params[1]);
	Utils::String_Replace(path);
	cell ret = fs::remove(path, ex);
	if (ex.value() != 0 && SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: %s", __func__, ex.message().c_str());
	}
	return ret;
}

cell AMX_NATIVE_CALL Native::File_Copy(AMX* amx, cell* params)
{
	CHECK_PARAMS(params[0] / sizeof(cell));

	// From
	std::string from = Service::Native_GetString(amx, params[1]);
	Utils::String_Replace(from);

	// To
	std::string to = Service::Native_GetString(amx, params[2]);
	Utils::String_Replace(to);

	// Kopyalama modu
	std::error_code ex;
	fs::copy_options mod{};

	// Modları çek
	for (size_t i = 3; i <= params[0] / sizeof(cell); i++)
	{
		cell* address = nullptr;
		amx_GetAddr(amx, params[i], &address);

		if (address == nullptr) {
			break;
		}

		if (*address == 0) mod = mod | fs::copy_options::none;
		if (*address == 1) mod = mod | fs::copy_options::skip_existing;
		if (*address == 2) mod = mod | fs::copy_options::overwrite_existing;
		if (*address == 3) mod = mod | fs::copy_options::update_existing;
		if (*address == 4) mod = mod | fs::copy_options::recursive;
		if (*address == 5) mod = mod | fs::copy_options::copy_symlinks;
		if (*address == 6) mod = mod | fs::copy_options::skip_symlinks;
		if (*address == 7) mod = mod | fs::copy_options::directories_only;
		if (*address == 8) mod = mod | fs::copy_options::create_symlinks;
		if (*address == 9) mod = mod | fs::copy_options::create_hard_links;
	}

	fs::copy_file(from, to, mod, ex);

	if (ex.value() != 0 && SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: %s\n", __func__, ex.message().c_str());
	}

	return (ex.value() == 0) ? (1) : (0);
}

cell AMX_NATIVE_CALL Native::File_Rename(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	std::error_code ex;
	std::string old_name = Service::Native_GetString(amx, params[1]);
	std::string new_name = Service::Native_GetString(amx, params[2]);
	Utils::String_Replace(old_name);
	Utils::String_Replace(new_name);
	fs::rename(old_name, new_name, ex);
	if (ex.value() != 0 && SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: %s", __func__, ex.message().c_str());
	}
	return (ex.value() == 0) ? (1) : (0);
}

cell AMX_NATIVE_CALL Native::File_Open(AMX* amx, cell* params)
{
	CHECK_PARAMS(params[0] / sizeof(cell));

	// Dosya konumu ve adı
	std::string path = Service::Native_GetString(amx, params[1]);
	Utils::String_Replace(path);

	// Dosya
	fstream* f = new fstream();

	// Hangi modda açılacak ?
	std::ios_base::openmode mod{};

	// Modları çek
	for (size_t i = 2; i <= params[0] / sizeof(cell); i++)
	{
		cell* address = nullptr;
		amx_GetAddr(amx, params[i], &address);

		if (address == nullptr) {
			break;
		}

		if (*address == 0) mod = mod | std::ios_base::in;
		if (*address == 1) mod = mod | std::ios_base::out;
		if (*address == 2) mod = mod | std::ios_base::ate;
		if (*address == 3) mod = mod | std::ios_base::app;
		if (*address == 4) mod = mod | std::ios_base::trunc;
		if (*address == 5) mod = mod | std::ios_base::binary;
	}

	// Dosyayı aç
	f->open(path, mod);

	if (f->is_open())
	{
		SM::Dosya->push_back(f);
		return (cell)f;
	}

	delete f;

	if (SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: The file could not be opened.", __func__);
	}

	return 0;
}

cell AMX_NATIVE_CALL Native::File_Write(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	fstream* address = (fstream*)params[1];
	for (std::vector<fstream*>::iterator p = SM::Dosya->begin(); p != SM::Dosya->end(); p++)
	{
		if (*p == address)
		{
			std::string icerik = Service::Native_GetString(amx, params[2]);
			address->write(icerik.c_str(), strlen(icerik.c_str()));
			return 1;
		}
	}
	if (SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: You did not specify a valid handle. (new File:?)", __func__);
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::File_Read(AMX* amx, cell* params)
{
	CHECK_PARAMS(3);
	fstream* address = (fstream*)params[1];
	for (std::vector<fstream*>::iterator p = SM::Dosya->begin(); p != SM::Dosya->end(); p++)
	{
		if (*p == address)
		{
			cell len = static_cast<cell>(params[3]);
			char* buffer = new char[len];

			address->getline(buffer, len);
			Service::Native_SetString(amx, params[2], params[3], buffer);

			delete[] buffer;

			if (address->eof())
			{
				address->clear();
				address->seekg(0, ios::beg);
				return 0;
			}

			return 1;
		}
	}
	if (SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: You did not specify a valid handle. (new File:?)", __func__);
	}
	return 0;
}

cell AMX_NATIVE_CALL Native::File_Close(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);
	fstream* address = (fstream*)params[1];
	for (std::vector<fstream*>::iterator p = SM::Dosya->begin(); p != SM::Dosya->end(); p++)
	{
		if (*p == address)
		{
			delete address;
			SM::Dosya->erase(p);
			return 1;
		}
	}
	if (SM::LogMode())
	{
		sampgdk::logprintf("[file-system] %s: You did not specify a valid handle. (new File:?)", __func__);
	}
	return 0;
}