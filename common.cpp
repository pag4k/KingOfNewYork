#include <assert.h>
#include "common.h"

std::string GetFaceName(EDiceFace Face)
{
    std::string FaceName = "";
    switch (Face)
    {
    case EDiceFace::Attack:
        FaceName = "Attack";
        break;
    case EDiceFace::Celebrity:
        FaceName = "Celebrity";
        break;
    case EDiceFace::Destruction:
        FaceName = "Destruction";
        break;
    case EDiceFace::Energy:
        FaceName = "Energy";
        break;
    case EDiceFace::Heal:
        FaceName = "Heal";
        break;
    case EDiceFace::Ouch:
        FaceName = "Ouch";
        break;
    }
    assert(FaceName != "");
    return FaceName;
}

std::string GetMonsterName(EMonsterName MonsterName)
{
    std::string MonsterNameString = "";
    switch (MonsterName)
    {
    case EMonsterName::CaptainFish:
        MonsterNameString = "Captain Fish";
        break;
    case EMonsterName::Draconis:
        MonsterNameString = "Draconis";
        break;
    case EMonsterName::Kong:
        MonsterNameString = "Kong";
        break;
    case EMonsterName::Mantis:
        MonsterNameString = "Mantis";
        break;
    case EMonsterName::Rob:
        MonsterNameString = "Rob";
        break;
    case EMonsterName::Sherrif:
        MonsterNameString = "Sherrif";
        break;
    }
    assert(MonsterNameString != "");
    return MonsterNameString;
}