// ----------------------------------------------------------------------------
// COMP345 Assignment 4
// Due date: December 2, 2018
// Written by: Pierre-Andre Gagnon - 40067198
// ----------------------------------------------------------------------------

#include "common.h"

namespace KingOfNewYork
{
    const std::string GetDiceFaceString(const EDiceFace DiceFace)
    {
        std::string FaceName;
        switch (DiceFace)
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
        assert(!FaceName.empty());
        return FaceName;
    }

    const std::string GetMonsterNameString(const EMonsterName MonsterName)
    {
        std::string MonsterNameString;
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
        assert(!MonsterNameString.empty());
        return MonsterNameString;
    }

    const std::string GetTokenTypeString(const ETokenType TokenType)
    {
        std::string TokenTypeString;
        switch (TokenType)
        {
        case ETokenType::Carapace:
            TokenTypeString = "Carapace";
            break;
        case ETokenType::Jinx:
            TokenTypeString = "Jinx";
            break;
        case ETokenType::Souvenir:
            TokenTypeString = "Souvenir";
            break;
        case ETokenType::Web:
            TokenTypeString = "Web";
            break;
        }
        assert(!TokenTypeString.empty());
        return TokenTypeString;
    }

    const std::string GetHowToPlayString(const EHowToPlay HowToPlay)
    {
        std::string HowToPlayString;
        switch (HowToPlay)
        {
        case EHowToPlay::Discard:
            HowToPlayString = "Discard";
            break;
        case EHowToPlay::Keep:
            HowToPlayString = "Keep";
            break;
        }
        assert(!HowToPlayString.empty());
        return HowToPlayString;
    }

    const std::string GetTileTypeString(const ETileType TileType)
    {
        std::string FileTypeString;
        switch (TileType)
        {
        case ETileType::HighRise:
            FileTypeString = "High-Rise";
            break;
        case ETileType::Tank:
            FileTypeString = "Tank";
            break;
        case ETileType::PowerPlant:
            FileTypeString = "Power Plant";
            break;
        case ETileType::Jet:
            FileTypeString = "Jet";
            break;
        case ETileType::Hospital:
            FileTypeString = "Hospital";
            break;
        case ETileType::Infantry:
            FileTypeString = "Infantry";
            break;
        }
        assert(!FileTypeString.empty());
        return FileTypeString;
    }

    const std::string GetMonsterResourceString(EMonsterResource MonsterResource)
    {
        std::string MonsterResourceString;
        switch (MonsterResource)
        {
        case EMonsterResource::EnergyCube:
            MonsterResourceString = "Energy Cubes";
            break;
        case EMonsterResource::LifePoint:
            MonsterResourceString = "Life Points";
            break;
        case EMonsterResource::VictoryPoint:
            MonsterResourceString = "Victory Points";
            break;
        }
        assert(!MonsterResourceString.empty());
        return MonsterResourceString;
    };

    const std::string GetTurnPhaseString(ETurnPhase TurnPhase)
    {
        std::string TurnPhaseString;
        switch (TurnPhase)
        {
            case ETurnPhase::StartTurn:
                TurnPhaseString = "Start Turn";
                break;
            case ETurnPhase::RollDice:
                TurnPhaseString = "Roll Dice";
                break;
            case ETurnPhase::ResolveDice:
                TurnPhaseString = "Resolve Dice";
                break;
            case ETurnPhase::Move:
                TurnPhaseString = "Move";
                break;
            case ETurnPhase::BuyCards:
                TurnPhaseString = "Buy Cards";
                break;
            case ETurnPhase::EndTurn:
                TurnPhaseString = "End Turn";
                break;
        }
        assert(!TurnPhaseString.empty());
        return TurnPhaseString;
    };
}
