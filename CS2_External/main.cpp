#include "Offsets.h"
#include "Cheats.h"
#include "Utils/Format.hpp"
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <cstdlib>
#include <KnownFolders.h>
#include <ShlObj.h>
//����client.h   https://github.com/a2x/cs2-dumper/blob/main/output/client.dll.hpp
//����offsets.h   https://github.com/a2x/cs2-dumper/blob/main/output/offsets.hpp
namespace fs = std::filesystem;

int main()
{
	auto ProcessStatus = ProcessMgr.Attach("cs2.exe");
	char documentsPath[MAX_PATH];
	if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, documentsPath) != S_OK) {
		std::cerr << "Failed to get document folder path." << std::endl;
		goto END;
	}
	MenuConfig::path = documentsPath;
	MenuConfig::path += "/CS2�ڲ�";
	
	std::cerr << "Notice:" << std::endl;

	std::cerr << "Due to the recent VAC update, please use the trumpet game, any cheat software has risks, it will cause you VAC" << std::endl;
	std::cerr << ", we are not responsible, Please find Taobao customer service to receive a Steam account" << std::endl;
	
	if (ProcessStatus != StatusCode::SUCCEED)
	{
		std::cout << "[Error] Attach process failed with code:" << ProcessStatus << std::endl;
		goto END;
	}

	if (!Offset::UpdateOffsets())
	{
		std::cout << "[Error] failed to update the offset." << std::endl;
		goto END;
	}

	if (!gGame.InitAddress())
	{
		std::cout << "[Error] Initialization failed." << std::endl;
		goto END;
	}

	/*std::cout << Format("[�Ѿ���ȡ����Ϸ����] ����ID:%d\n", ProcessMgr.ProcessID);*/
	//std::cout << Format("[Game] Client:%llX\n", gGame.GetClientDLLAddress());

	/*std::cout << "Offset:" << std::endl;
	std::cout << Format("--EntityList:%llX\n", Offset::EntityList);
	std::cout << Format("--Matrix:%llX\n", Offset::Matrix);
	std::cout << Format("--LocalPlayerController:%llX\n", Offset::LocalPlayerController);
	std::cout << Format("--ViewAngles:%llX\n", Offset::ViewAngle);
	std::cout << Format("--LocalPlayerPawn:%llX\n", Offset::LocalPlayerPawn);*/


	/*if (fs::exists(MenuConfig::path))
		std::cout << "�����ļ���������: "<< MenuConfig::path << std::endl;
	else
	{
		if (fs::create_directory(MenuConfig::path))
			std::cout << "�Ѵ��������ļ���: " << MenuConfig::path << std::endl;
		else
		{
			std::cerr << "�޷���������Ŀ¼." << std::endl;
			goto END;
		}
	}*/

	std::cout << "running..." << std::endl;


	try
	{
		Gui.AttachAnotherWindow("Counter-Strike 2,���־�Ӣ��ȫ����", "SDL_app", Cheats::Run);
	}
	catch (OSImGui::OSException& e)
	{
		std::cout << e.what() << std::endl;
	}

END:

	system("pause");
	return 0;
}
