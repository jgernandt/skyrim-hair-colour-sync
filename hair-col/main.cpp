#include "pch.h"

#include "detours.h"

#include "skse64_common/skse_version.h"
#include "skse64/PluginAPI.h"

#include "implementation.h"
#include "relocation.h"

#define PLUGIN_NAME "HairColourSync"

constexpr unsigned long VERSION_MAJOR{ 1 };
constexpr unsigned long VERSION_MINOR{ 0 };
constexpr unsigned long VERSION_PATCH{ 0 };
constexpr unsigned long VERSION = (VERSION_MAJOR & 0xFF) << 24 | (VERSION_MINOR & 0xFF) << 16 | (VERSION_PATCH & 0xFF) << 8;

extern "C" {
	
	__declspec(dllexport) SKSEPluginVersionData SKSEPlugin_Version = {
		SKSEPluginVersionData::kVersion,
		VERSION,
		PLUGIN_NAME,
		"jgernandt",
		"",
		0,
		SKSEPluginVersionData::kVersionIndependent_AddressLibraryPostAE | SKSEPluginVersionData::kVersionIndependent_StructsPost629,
		{ 0 },
		0,
	};

	__declspec(dllexport) bool SKSEPlugin_Load(const SKSEInterface* skse)
	{
		auto version = skse->runtimeVersion;
		int major = GET_EXE_VERSION_MAJOR(version);
		int minor = GET_EXE_VERSION_MINOR(version);
		int patch = GET_EXE_VERSION_BUILD(version);
		int platform = GET_EXE_VERSION_SUB(version);

		if (platform == RUNTIME_TYPE_BETHESDA) {
			gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\" PLUGIN_NAME ".log");
		}
		else if (platform == RUNTIME_TYPE_GOG) {
			gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition GOG\\SKSE\\" PLUGIN_NAME ".log");
		}
		else if (platform == RUNTIME_TYPE_EPIC) {
			gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition EPIC\\SKSE\\" PLUGIN_NAME ".log");
		}
		
#ifdef _DEBUG
		gLog.SetPrintLevel(IDebugLog::kLevel_DebugMessage);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);
#else
		gLog.SetPrintLevel(IDebugLog::kLevel_Message);
		gLog.SetLogLevel(IDebugLog::kLevel_Message);
#endif

		_MESSAGE("Skyrim version:\t%d.%d.%d", major, minor, patch);
		_MESSAGE("SKSE version:\t%d.%d.%d",
			GET_EXE_VERSION_MAJOR(skse->skseVersion),
			GET_EXE_VERSION_MINOR(skse->skseVersion),
			GET_EXE_VERSION_BUILD(skse->skseVersion));
		_MESSAGE("Plugin version:\t%d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

		if (!relocate(version)) {
			_FATALERROR("FATAL ERROR: Failed to setup address table");
			return false;
		}

		if (auto res = DetourTransactionBegin() != NO_ERROR) {
			_FATALERROR("FATAL ERROR: Failed to begin transaction (error code %d)", res);
			return false;
		}

		Biped__AttachArmor_trampoline = Biped__AttachArmor::get();
		if (auto res = DetourAttach(&Biped__AttachArmor_trampoline, &Biped__AttachArmor_detour) != NO_ERROR) {
			_FATALERROR("FATAL ERROR: Failed to attach detour to Biped::AttachArmor (error code %d)", res);
			return false;
		}

		if (auto res = DetourTransactionCommit() != NO_ERROR) {
			_FATALERROR("FATAL ERROR: Failed to commit transaction (error code %d)", res);
			return false;
		}

		_MESSAGE("Initialisation successful.");

		return true;
	}

	//Report incompatibility with legacy versions
	__declspec(dllexport) bool SKSEPlugin_Query(const SKSEInterface*, PluginInfo* info)
	{
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = SKSEPlugin_Version.name;
		info->version = SKSEPlugin_Version.pluginVersion;

		return false;
	}
};
