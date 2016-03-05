#pragma once

#include "font.h"

#define SAVE_SIZE (0x8000) // 0x7A4C
#define BOX_SIZE (0x462)
#define POKEMON_LIST_MAX_COUNT (30) // Party: 6 | Box: 20 | BoxJP: 30
#define GAME_BOX_MAX_COUNT (12) // 12 | JP: 8
#define BANK_BOX_MAX_COUNT (20) // 20

/// 
typedef enum
{
	POKEMON_RED,	///< Pokémon Red
	POKEMON_BLUE,	///< Pokémon Blue
	POKEMON_GREEN,	///< Pokémon Green
	POKEMON_YELLOW,	///< Pokémon Yellow
} SAV_GameVersion;

/// 
typedef enum
{
	OPT_SOUND_MONO = 0x0,
	OPT_SOUND_STEREO = BIT(4),
	OPT_SOUND_EARPHONE1 = BIT(4),
	OPT_SOUND_EARPHONE2 = BIT(5),
	OPT_SOUND_EARPHONE3 = BIT(4) | BIT(5),
	OPT_BATTLE_STYLE_SWITCH = 0x0,
	OPT_BATTLE_STYLE_SET = BIT(6),
	OPT_BATTLE_EFFECT_YES = 0x0,
	OPT_BATTLE_EFFECT_NO = BIT(7),
} SAV_Option;

/// 
typedef enum
{
	STATUS_ASLEEP = BIT(3),		///< Asleep status
	STATUS_POISONED = BIT(4),	///< Poisoned status
	STATUS_BURNED = BIT(5),		///< Burned status
	STATUS_FROZEN = BIT(6),		///< Frozen status
	STATUS_PARALYZED = BIT(7),	///< Paralyzed status
} SAV_Status;

/// 
typedef enum
{
	TYPE_NORMAL = 0x0,		///< Normal type
	TYPE_FIGHTING = 0x1,	///< Fighting type
	TYPE_FLYING = 0x2,		///< Flying type
	TYPE_POISON = 0x3,		///< Poison type
	TYPE_GROUND = 0x4,		///< Ground type
	TYPE_ROCK = 0x5,		///< Rock type
	TYPE_BUG = 0x7,			///< Bug type
	TYPE_GHOST = 0x8,		///< Ghost type
	TYPE_FIRE = 0x14,		///< Fire type
	TYPE_WATER = 0x15,		///< Water type
	TYPE_GRASS = 0x16,		///< Grass type
	TYPE_ELECTRIC = 0x17,	///< Electric type
	TYPE_PSYCHIC = 0x18,	///< Psychic type
	TYPE_ICE = 0x19,		///< Ice type
	TYPE_DRAGON = 0x1A,		///< Dragon type
} SAV_Type;

/// 
typedef enum
{
	STAT_HP = 0,		///< The hit points stat
	STAT_ATTACK	= 1,	///< The attack stat
	STAT_DEFENSE = 2,	///< The defense stat
	STAT_SPEED = 3,		///< The speed stat
	STAT_SPECIAL = 4,	///< The special stat
} SAV_Stat;

/// 
typedef struct
{
	// Shared attributes
	uint8_t speciesIndex;
	uint16_t currentHP;
	uint8_t currentLevel;
	uint8_t status;
	uint8_t types[2];
	uint8_t catchRate;
	uint8_t moves[4];
	uint16_t originalTID;
	uint32_t experience;
	uint16_t EVs[5];
	uint8_t IVs[5];
	uint8_t PPUps[4];
	uint8_t PPs[4];

	// Party attributes
	uint8_t level;
	uint16_t maximumHP;
	uint16_t attack;
	uint16_t defense;
	uint16_t speed;
	uint16_t special;

	// Extra attributes
	uint8_t species;		///< Species
	uint8_t nameOT[11];		///< OT name
	uint8_t nameNK[11];		///< Nickname
	uint8_t nationalDex;	///< National Pokédex Id
} SAV_Pokemon;

/// 
typedef struct
{
	uint8_t count;

	uint8_t size;
	uint8_t capacity;
	uint8_t species[POKEMON_LIST_MAX_COUNT];
	SAV_Pokemon slots[POKEMON_LIST_MAX_COUNT];
} SAV_PokemonList;

/// 
typedef struct
{
	uint8_t boxCount;
	SAV_PokemonList boxes[GAME_BOX_MAX_COUNT];
} SAV_Game;

/// 
typedef struct
{
	uint8_t boxCount;
	SAV_PokemonList boxes[BANK_BOX_MAX_COUNT];
} SAV_Bank;

extern uint8_t save[];
extern SAV_Game sgame;
extern SAV_Bank sbank;

/**
 * @brief Initializes the save module.
 */
void saveInitialize(void);

/**
 * @brief Gets a box from a list.
 * @param[in] save The savedata buffer.
 * @param box The id of the box.
 * @param inBank Whether the box is in bank.
 * @return The pokemon list.
 */
SAV_PokemonList* saveGetBox(uint8_t box, bool inBank);

/**
 * @brief Gets a pokemon from a list.
 * @param[in] save The savedata buffer.
 * @param box The id of the box.
 * @param slot The id of the slot.
 * @param inBank Whether the box is in bank.
 * @return The pokemon.
 */
SAV_Pokemon* saveGetPkm(uint8_t box, uint8_t slot, bool inBank);

/**
 * @todo
 */
uint8_t getBoxCount(bool inBank);

/**
 * @todo
 */
const char8_t* saveGetTrainer(void);

/**
 * @brief Reads a save file to a save buffer.
 * @param[out] save The savedata buffer.
 * @param[in] path The path of the save file.
 */
void saveReadFile(uint8_t* save, const char* path);

/**
 * @brief Writes a save buffer to a save file.
 * @param[in] save The savedata buffer.
 * @param[in] path The path of the save file.
 */
void saveWriteFile(const uint8_t* save, const char* path);

/**
 * @brief Reads a save buffer to a save struct.
 * @param[in] save The savedata buffer.
 * @param[in] path The path of the save file.
 */
void saveReadData(const uint8_t* save, SAV_Game* sgame);

/**
 * @brief Writes a save struct to a save buffer.
 * @param[in/out] save The savedata buffer.
 * @param[in] path The path of the save file.
 */
void saveWriteData(uint8_t* save, const SAV_Game* sgame);

/**
 * @brief Fixs the checksum of a save.
 * @param[in/out] save The savedata buffer.
 */
void saveFixChecksum(uint8_t* save);