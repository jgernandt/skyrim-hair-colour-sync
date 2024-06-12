#include "pch.h"
#include "relocation.h"

#include "skse64_common/skse_version.h"

#include "versionlibdb.h"

#include "implementation.h"

std::uintptr_t Biped__AttachArmor::address = 0;
std::uintptr_t BSShaderProperty__SetMaterial::address = 0;

bool relocate(int version)
{
	bool result = true;

	auto base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL));

	if (version == RUNTIME_VERSION_1_6_1170) {
		Biped__AttachArmor::address = base + Biped__AttachArmor::kDefaultOffset;
		BSShaderProperty__SetMaterial::address = base + BSShaderProperty__SetMaterial::kDefaultOffset;
	}
	else {
		VersionDb db;

		int major = GET_EXE_VERSION_MAJOR(version);
		int minor = GET_EXE_VERSION_MINOR(version);
		int patch = GET_EXE_VERSION_BUILD(version);

		if (db.Load(major, minor, patch, 0)) {

			unsigned long long offset = 0;
			if (db.FindOffsetById(Biped__AttachArmor::kID, offset)) {
				Biped__AttachArmor::address = base + offset;
			}
			else {
				_ERROR("ERROR: Failed to get the address of ID:%d", Biped__AttachArmor::kID);
				result = false;
			}
			if (db.FindOffsetById(BSShaderProperty__SetMaterial::kID, offset)) {
				BSShaderProperty__SetMaterial::address = base + offset;
			}
			else {
				_ERROR("ERROR: Failed to get the address of ID:%d", BSShaderProperty__SetMaterial::kID);
				result = false;
			}
		}
		else {
			_ERROR("ERROR: Failed to load Address Library v%d.%d.%d.0", major, minor, patch);
			result = false;
		}
	}

	return result;
}
