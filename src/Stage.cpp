#include "Stage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "WindowsWrapper.h"

#include "Back.h"
#include "Boss.h"
#include "Bullet.h"
#include "Caret.h"
#include "Draw.h"
#include "File.h"
#include "Flash.h"
#include "Frame.h"
#include "Main.h"
#include "Map.h"
#include "MapName.h"
#include "MyChar.h"
#include "NpChar.h"
#include "Organya.h"
#ifdef EXTRA_SOUND_FORMATS
#include "ExtraSoundFormats.h"
#endif
#include "TextScr.h"
#include "ValueView.h"

#ifdef JAPANESE
#define STAGE_ENTRY(parts, map, bkType, back, npc, boss, boss_no, name_en, name_jp) {parts, map, bkType, back, npc, boss, boss_no, name_jp}
#else
#define STAGE_ENTRY(parts, map, bkType, back, npc, boss, boss_no, name_en, name_jp) {parts, map, bkType, back, npc, boss, boss_no, name_en}
#endif

int gStageNo;
MusicID gMusicNo;
unsigned int gOldPos;
MusicID gOldNo;

const STAGE_TABLE gTMTDefault[95] = {
	STAGE_ENTRY( "0","0", 4, "bk0", "Guest", "0", 0, "Null", "troll" ),
STAGE_ENTRY( "Cent","Intro", 7, "bk0", "0", "0", 0, "   ", "troll" ),
STAGE_ENTRY( "Cave","Start", 0, "bkBlack", "Cemet", "0", 0, "Start Point", "troll" ),
STAGE_ENTRY( "Cave","MCamp", 0, "bkBlack", "Guest", "Guest", 0, "Mimiga Camp", "troll" ),
STAGE_ENTRY( "Cave","Path", 1, "bkBlack", "Cemet", "Fire", 0, "Dim Path", "troll" ),
STAGE_ENTRY( "Cave","Puu", 1, "bkBlack", "Cemet", "Bllg", 0, "Pooh's Restaurant", "troll" ),
STAGE_ENTRY( "Cave","Gun", 0, "bkGreen", "Guest", "0", 0, "?", "troll" ),
STAGE_ENTRY( "Weed","Thick", 1, "bkBlue", "Weed", "Maze", 0, "Thicket", "troll" ),
STAGE_ENTRY( "Pens","Frog", 1, "bkMaze", "Guest", "0", 0, "Frog Kingdom", "troll" ),
STAGE_ENTRY( "Cave","Shovel Camp", 1, "bkGreen", "Cemet", "Guest", 0, "Excavation Site", "troll" ),
STAGE_ENTRY( "Pens","Hospital", 0, "bkMaze", "Guest", "0", 0, "Clinic", "troll" ),
STAGE_ENTRY( "Cave","WCamp", 1, "bkGreen", "Guest", "0", 0, "Water Camp", "troll" ),
STAGE_ENTRY( "Cave","PuuW", 1, "bkGreen", "Bllgwater", "Bllgwater", 0, "Water Tower", "troll" ),
STAGE_ENTRY( "Cave","Tutorial", 1, "bkBlack", "Weed", "0", 0, "Fire Cavern", "troll" ),
STAGE_ENTRY( "Cave","Pool", 1, "bkGreen", "Eggs1", "0", 0, "Soap Pools", "troll" ),
STAGE_ENTRY( "Sand","Sand", 1, "bkBlue", "Eggssand", "MazeWeedOlay", 0, "Sand Zone", "troll" ),
STAGE_ENTRY( "Cent","Face", 0, "bk0", "Guest", "0", 0, "Su-'s Home", "troll" ),
STAGE_ENTRY( "Cave","MazeC", 1, "bkGreen", "0", "0", 0, "Distant Room ", "troll" ),
STAGE_ENTRY( "Cave","DimMaze", 1, "bkBlack", "Cemet", "0", 0, "Distant Maze", "troll" ),
STAGE_ENTRY( "Cave","DimStairs", 1, "bkGreen", "Regu", "Bllg", 0, "Pooh's Home", "troll" ),
STAGE_ENTRY( "Cave","CaveA", 1, "bkGreen", "Weed", "0", 0, "Dim Tower", "troll" ),
STAGE_ENTRY( "White","PuuBlack", 1, "bk0", "Dark", "Dark", 0, "?", "troll" ),
STAGE_ENTRY( "Cave","DimRoom", 0, "bkBlack", "0", "0", 0, "Dim Room", "troll" ),
STAGE_ENTRY( "Cave","SpongeM", 1, "bkBlack", "0", "0", 0, "Sponge Maze", "troll" ),
STAGE_ENTRY( "Weed","ThickR", 0, "bkBlue", "0", "0", 0, "Thicket Room", "troll" ),
STAGE_ENTRY( "Weed","ThickC", 1, "bkBlue", "0", "0", 0, "Thicket Circles", "troll" ),
STAGE_ENTRY( "Barr","Room", 1, "bkRoom", "0", "0", 0, "Green House", "troll" ),
STAGE_ENTRY( "Cave","Puz", 1, "bkGreen", "0", "0", 0, "Puzzle Digging Stage", "troll" ),
STAGE_ENTRY( "Oside","Oside", 7, "bkMoon", "Moon", "0", 0, "Outside Wall", "troll" ),
STAGE_ENTRY( "Mimi","MiBox", 0, "bkBlack", "0", "0", 0, "Save Point", "troll" ),
STAGE_ENTRY( "River","RiverFunnel", 1, "bkGreen", "0", "0", 0, "Someone's Camp", "troll" ),
STAGE_ENTRY( "Store","Cthu", 0, "bkBlack", "0", "0", 0, "Cthulhu's Abode", "troll" ),
STAGE_ENTRY( "EggIn","Egg1", 0, "bkBlack", "Eggs1", "0", 0, "Egg No. 01", "troll" ),
STAGE_ENTRY( "Pens","Pens2", 1, "bkBlue", "Guest", "0", 0, "Arthur's House", "troll" ),
STAGE_ENTRY( "Barr","Malco", 1, "bkBlack", "Weed", "Bllg", 0, "Power Room", "troll" ),
STAGE_ENTRY( "Barr","WeedS", 1, "bkBlack", "0", "0", 0, "Save Point", "troll" ),
STAGE_ENTRY( "Store","WeedD", 1, "bkBlack", "0", "0", 0, "Execution Chamber", "troll" ),
STAGE_ENTRY( "Weed","Frog", 2, "bkBlack", "Weed", "Frog", 0, "Gum", "troll" ),
STAGE_ENTRY( "Sand","Curly", 0, "bkBlack", "Sand", "Curly", 0, "Sand Zone Residence", "troll" ),
STAGE_ENTRY( "Pens","WeedB", 1, "bkBlack", "Ravil", "0", 0, "Grasstown Hut", "troll" ),
STAGE_ENTRY( "River","Stream", 5, "bkMaze", "Stream", "IronH", 0, "Main Artery", "troll" ),
STAGE_ENTRY( "Pens","CurlyS", 0, "bkBlack", "Sand", "Curly", 0, "Small Room", "troll" ),
STAGE_ENTRY( "Barr","Village", 0, "bkBlack", "Sand", "Bllg", 0, "Jenka's House", "troll" ),
STAGE_ENTRY( "Sand","Dark", 1, "bk0", "Sand", "0", 0, "Deserted House", "troll" ),
STAGE_ENTRY( "Gard","Gard", 1, "BkGard", "Toro", "Bllg", 0, "Sand Zone Storehouse", "troll" ),
STAGE_ENTRY( "Cent","Village", 1, "bkRed", "Guest", "Cent", 0, "Village", "troll" ),
STAGE_ENTRY( "Sand","SandE", 1, "bkBlack", "Sand", "Bllg", 0, "Sand Zone", "troll" ),
STAGE_ENTRY( "River","Tubes", 0, "bkMaze", "Stream", "0", 0, "Strong Current", "troll" ),
STAGE_ENTRY( "Maze","MazeW", 1, "bkBlack", "Maze", "X", 0, "Labyrinth W", "troll" ),
STAGE_ENTRY( "Maze","MazeO", 0, "bkBlack", "Guest", "0", 0, "Camp", "troll" ),
STAGE_ENTRY( "Maze","MazeD", 0, "bkBlack", "Guest", "Dark", 0, "Clinic Ruins", "troll" ),
STAGE_ENTRY( "Almond","Almond", 3, "BkWater", "Cemet", "Almo1", 0, "Core", "troll" ),
STAGE_ENTRY( "River","River", 1, "bkMaze", "Weed", "0", 0, "Waterway", "troll" ),
STAGE_ENTRY( "Eggs","Eggs2", 1, "bkBlue", "Eggs2", "0", 0, "Egg Corridor?", "troll" ),
STAGE_ENTRY( "River","Cthu2", 0, "bkMaze", "Cemet", "0", 0, "Stream", "troll" ),
STAGE_ENTRY( "Store","EggR2", 0, "bkBlack", "Eggs1", "TwinD", 0, "Egg Observation Room?", "troll" ),
STAGE_ENTRY( "EggX","EggX2", 0, "bkBlack", "Eggs1", "0", 0, "Egg No. 00", "troll" ),
STAGE_ENTRY( "Store","EgEnd2", 0, "bkBlack", "Eggs1", "0", 0, "Side Room", "troll" ),
STAGE_ENTRY( "Cave","Itoh", 1, "bkBlack", "Cemet", "0", 0, "Dank Cellar", "troll" ),
STAGE_ENTRY( "Cent","Cent", 1, "bkRed", "Guest", "Hell", 0, "Central", "troll" ),
STAGE_ENTRY( "River","Jail1", 1, "bkMaze", "Guest", "Cent", 0, "Sciddy bop bo daa", "troll" ),
STAGE_ENTRY( "Jail","Momo", 0, "bkBlack", "Guest", "0", 0, "Hideout", "troll" ),
STAGE_ENTRY( "Jail","lounge", 0, "bkBlack", "Guest", "0", 0, "Rest Area", "troll" ),
STAGE_ENTRY( "Store","CentW", 0, "bkBlack", "Guest", "CentW", 0, "Teleporter", "troll" ),
STAGE_ENTRY( "Store","Jail2", 0, "bkBlack", "Guest", "Cent", 0, "Jail No. 2", "troll" ),
STAGE_ENTRY( "White","Blcny1", 7, "BkFog", "Ravil", "Heri", 0, "Balcony", "troll" ),
STAGE_ENTRY( "Jail","Priso1", 1, "bkGreen", "Red", "0", 0, "Final Cave", "troll" ),
STAGE_ENTRY( "Cave","Vuln", 1, "bkGreen", "Guest", "Miza", 0, "Abode", "troll" ),
STAGE_ENTRY( "White","White", 1, "bkRed", "Weed2", "Weed", 0, "White Stone Wall", "troll" ),
STAGE_ENTRY( "Pens","Prefa1", 0, "bkBlack", "0", "0", 0, "Prefab Building", "troll" ),
STAGE_ENTRY( "Jail","Priso2", 1, "bkGreen", "Red", "0", 0, "Final Cave", "troll" ),
STAGE_ENTRY( "White","Ring3", 0, "bkBlack", "Miza", "Almo2", 0, "Black Space", "troll" ),
STAGE_ENTRY( "Pens","Little", 2, "BkBlue", "Guest", "0", 0, "Little House", "troll" ),
STAGE_ENTRY( "River","Blcny2", 7, "BkFog", "Weed", "Hell", 0, "Main ", "troll" ),
STAGE_ENTRY( "Fall","Fall", 1, "bkFall", "Guest", "Regu3", 0, "Fall", "troll" ),
STAGE_ENTRY( "River","Pixel", 1, "bkMaze", "Almo1", "0", 0, "Back Waterway", "troll" ),
STAGE_ENTRY( "Maze","e_Maze", 1, "bkBlack", "Guest", "Maze", 0, "", "troll" ),
STAGE_ENTRY( "Barr","e_Jenk", 0, "bkBlack", "Sand", "Bllg", 0, "", "troll" ),
STAGE_ENTRY( "Barr","e_Malc", 1, "bkBlack", "Weed", "Bllg", 0, "", "troll" ),
STAGE_ENTRY( "Mimi","e_Ceme", 0, "bkBlack", "Plant", "0", 0, "", "troll" ),
STAGE_ENTRY( "Fall","e_Sky", 1, "bkFall", "Guest", "Regu3", 0, "", "troll" ),
STAGE_ENTRY( "Pens","Prefa2", 0, "bkBlack", "0", "0", 0, "Prefab House", "troll" ),
STAGE_ENTRY( "Hell","Hell1", 2, "bkRed", "Hell", "0", 0, "Sacred Ground - B1", "troll" ),
STAGE_ENTRY( "Hell","Hell2", 2, "bkRed", "Hell", "0", 0, "Sacred Ground - B2", "troll" ),
STAGE_ENTRY( "Hell","Hell3", 1, "bkRed", "Hell", "Press", 0, "Sacred Ground - B3", "troll" ),
STAGE_ENTRY( "Hell","Hell4", 0, "bkBlack", "Hell", "0", 0, "Passage?", "troll" ),
STAGE_ENTRY( "Hell","Hell42", 0, "bkBlack", "Hell", "Press", 0, "Passage?", "troll" ),
STAGE_ENTRY( "Hell","Statue", 1, "bkRed", "0", "Cent", 0, "Statue Chamber", "troll" ),
STAGE_ENTRY( "White","Ballo1", 2, "bkBlack", "Bllg", "Frog", 0, "Seal Chamber", "troll" ),
STAGE_ENTRY( "White","Ostep", 7, "BkFog", "0", "0", 0, "Corridor", "troll" ),
STAGE_ENTRY( "Labo","e_Labo", 4, "bk0", "Guest", "0", 0, "", "troll" ),
STAGE_ENTRY( "0","Island", 0, "bkBlack", "Island", "0", 0, "", "troll" ),
STAGE_ENTRY( "Hell","Ballo2", 2, "bkRed", "Priest", "Bllg", 0, "Seal Chamber", "troll" ),
STAGE_ENTRY( "White","e_Blcn", 7, "BkFog", "Miza", "0", 0, "", "troll" ),
STAGE_ENTRY( "Oside","Clock", 6, "BkMoon", "Moon", "0", 0, "Clock Room", "troll" ),
//STAGE_ENTRY( "Barr","Cook", 0, "bkBlack", "Guest", "Regu2", 0, "Beta Characters Room (Cook)", "troll" ),
};

const STAGE_TABLE *gTMT = gTMTDefault;

BOOL LoadStageTable(void)
{
	std::string path;

	unsigned char *file_buffer;
	size_t file_size;

	// Try to load stage.tbl
	path = gDataPath + "/stage.tbl";
	file_buffer = LoadFileToMemory(path.c_str(), &file_size);

	if (file_buffer != NULL)
	{
		const unsigned long entry_count = file_size / 0xE5;

		STAGE_TABLE *pTMT = (STAGE_TABLE*)malloc(entry_count * sizeof(STAGE_TABLE));

		if (pTMT != NULL)
		{
			for (unsigned long i = 0; i < entry_count; ++i)
			{
				unsigned char *entry = file_buffer + i * 0xE5;

				memcpy(pTMT[i].parts, entry, 0x20);
				memcpy(pTMT[i].map, entry + 0x20, 0x20);
				pTMT[i].bkType = (entry[0x40 + 3] << 24) | (entry[0x40 + 2] << 16) | (entry[0x40 + 1] << 8) | entry[0x40];
				memcpy(pTMT[i].back, entry + 0x44, 0x20);
				memcpy(pTMT[i].npc, entry + 0x64, 0x20);
				memcpy(pTMT[i].boss, entry + 0x84, 0x20);
				pTMT[i].boss_no = entry[0xA4];
#ifdef JAPANESE
				memcpy(pTMT[i].name, entry + 0xA5, 0x20);
#else
				memcpy(pTMT[i].name, entry + 0xC5, 0x20);
#endif
			}

			gTMT = pTMT;
			free(file_buffer);
			return TRUE;
		}

		free(file_buffer);
	}

	// Try to load mrmap.bin
	path = gDataPath + "/mrmap.bin";
	file_buffer = LoadFileToMemory(path.c_str(), &file_size);

	if (file_buffer != NULL)
	{
		const unsigned long entry_count = file_buffer[0] | (file_buffer[1] << 8) | (file_buffer[2] << 16) | (file_buffer[3] << 24);

		STAGE_TABLE *pTMT = (STAGE_TABLE*)malloc(entry_count * sizeof(STAGE_TABLE));

		if (pTMT != NULL)
		{
			for (unsigned long i = 0; i < entry_count; ++i)
			{
				// For compatibility with Booster's Lab, we store our stage table in "MOD_MR" format.
				// This way, BL will load the sprites as PNG files instead of BMP.
				unsigned char *entry = file_buffer + 4 + i * 0x74;

				memcpy(pTMT[i].parts, entry, 0x10);
				memcpy(pTMT[i].map, entry + 0x10, 0x10);
				pTMT[i].bkType = entry[0x20];
				memcpy(pTMT[i].back, entry + 0x21, 0x10);
				memcpy(pTMT[i].npc, entry + 0x31, 0x10);
				memcpy(pTMT[i].boss, entry + 0x41, 0x10);
				pTMT[i].boss_no = entry[0x51];
				memcpy(pTMT[i].name, entry + 0x52, 0x22);
			}

			gTMT = pTMT;
			free(file_buffer);
			return TRUE;
		}

		free(file_buffer);
	}

	printf("Failed to load stage.tbl/mrmap.bin\n");
	return FALSE;
}

BOOL TransferStage(int no, int w, int x, int y)
{
	std::string path;
	std::string path_dir;
	BOOL bError;

	// Move character
	SetMyCharPosition(x * 0x10 * 0x200, y * 0x10 * 0x200);

	bError = FALSE;

	// Get path
	path_dir = "Stage";

	// Load tileset
	path = path_dir + "/Prt" + gTMT[no].parts;
	if (!ReloadBitmap_File(path.c_str(), SURFACE_ID_LEVEL_TILESET))
		bError = TRUE;

	path = path_dir + '/' + gTMT[no].parts + ".pxa";
	if (!LoadAttributeData(path.c_str()))
		bError = TRUE;

	// Load tilemap
	path = path_dir + '/' + gTMT[no].map + ".pxm";
	if (!LoadMapData2(path.c_str()))
		bError = TRUE;

	// Load NPCs
	path = path_dir + '/' + gTMT[no].map + ".pxe";
	if (!LoadEvent(path.c_str()))
		bError = TRUE;

	// Load script
	path = path_dir + '/' + gTMT[no].map + ".tsc";
	if (!LoadTextScript_Stage(path.c_str()))
		bError = TRUE;

	// Load background
	path = gTMT[no].back;
	if (!InitBack(path.c_str(), gTMT[no].bkType))
		bError = TRUE;

	// Get path
	path_dir = "Npc";

	// Load NPC sprite sheets
	path = path_dir + "/Npc" + gTMT[no].npc;
	if (!ReloadBitmap_File(path.c_str(), SURFACE_ID_LEVEL_SPRITESET_1))
		bError = TRUE;

	path = path_dir + "/Npc" + gTMT[no].boss;
	if (!ReloadBitmap_File(path.c_str(), SURFACE_ID_LEVEL_SPRITESET_2))
		bError = TRUE;

	if (bError)
		return FALSE;

	// Load map name
	ReadyMapName(gTMT[no].name);

	StartTextScript(w);
	SetFrameMyChar();
	ClearBullet();
	InitCaret();
	ClearValueView();
	ResetQuake();
	InitBossChar(gTMT[no].boss_no);
	ResetFlash();
	gStageNo = no;

	return TRUE;
}

enum
{
	MUSIC_TYPE_ORGANYA,
	MUSIC_TYPE_OTHER
};

//Music
static const struct
{
	const char *intro_file_path;
	const char *loop_file_path;
	int type;
	bool loop;	// Only applicable to non-Organya songs
} music_table[42] = {
	{"Resource/ORG/XXXX.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Wanpaku.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Anzen.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Gameover.org", NULL, MUSIC_TYPE_ORGANYA, false},
	{"Resource/ORG/Gravity.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Weed.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/MDown2.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/FireEye.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Vivi.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Mura.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Fanfale1.org", NULL, MUSIC_TYPE_ORGANYA, false},
	{"Resource/ORG/Ginsuke.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Cemetery.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Plant.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Kodou.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Fanfale3.org", NULL, MUSIC_TYPE_ORGANYA, false},
	{"Resource/ORG/Fanfale2.org", NULL, MUSIC_TYPE_ORGANYA, false},
	{"Resource/ORG/Dr.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Escape.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Jenka.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Maze.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Access.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/ironH.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Grand.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Curly.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Oside.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Requiem.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Wanpak2.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/quiet.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/LastCave.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Balcony.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/LastBtl.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/LastBtl3.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Ending.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Zonbie.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/BreakDown.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Hell.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Jenka2.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Marine.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Ballos.org", NULL, MUSIC_TYPE_ORGANYA, true},
	{"Resource/ORG/Toroko.org", NULL, MUSIC_TYPE_ORGANYA, false},
	{"Resource/ORG/White.org", NULL, MUSIC_TYPE_ORGANYA, true}
};

void ChangeMusic(MusicID no)
{
	if (no != MUS_SILENCE && no == gMusicNo)
		return;

	// Stop and keep track of old song
	gOldPos = GetOrganyaPosition();
	gOldNo = gMusicNo;
	StopOrganyaMusic();
#ifdef EXTRA_SOUND_FORMATS
	ExtraSound_PauseMusic();
#endif

	std::string intro_file_path;
	if (music_table[no].intro_file_path != NULL)
		intro_file_path = gDataPath + '/' + music_table[no].intro_file_path;

	std::string loop_file_path;
	if (music_table[no].loop_file_path != NULL)
		loop_file_path = gDataPath + '/' + music_table[no].loop_file_path;

	switch (music_table[no].type)
	{
		case MUSIC_TYPE_ORGANYA:
			// Load .org
			LoadOrganya(intro_file_path.c_str());

			// Reset position, volume, and then play the song
			ChangeOrganyaVolume(100);
			SetOrganyaPosition(0);
			PlayOrganyaMusic();

#ifdef EXTRA_SOUND_FORMATS
			ExtraSound_LoadMusic(NULL, NULL, false);	// Play a null song so any current song gets pushed back to the backup slot
#endif
			break;

#ifdef EXTRA_SOUND_FORMATS
		case MUSIC_TYPE_OTHER:
			ExtraSound_LoadMusic(music_table[no].intro_file_path != NULL ? intro_file_path.c_str() : NULL, music_table[no].loop_file_path != NULL ? loop_file_path.c_str() : NULL, music_table[no].loop);
			ExtraSound_UnpauseMusic();

			// Play a null Organya song so focussing and refocussing the window doesn't cause the old Organya song to start playing again
			intro_file_path = gDataPath + '/' + music_table[0].intro_file_path;
			LoadOrganya(intro_file_path.c_str());

			ChangeOrganyaVolume(100);
			SetOrganyaPosition(0);
			PlayOrganyaMusic();
			break;
#endif
	}

	gMusicNo = no;
}

void ReCallMusic(void)
{
	std::string path;

	// Stop old song
	StopOrganyaMusic();
#ifdef EXTRA_SOUND_FORMATS
	ExtraSound_PauseMusic();
#endif

	switch (music_table[gOldNo].type)
	{
		case MUSIC_TYPE_ORGANYA:
			// Load .org that was playing before
			path = gDataPath + '/' + music_table[gOldNo].intro_file_path;
			LoadOrganya(path.c_str());

			// Reset position, volume, and then play the song
			SetOrganyaPosition(gOldPos);
			ChangeOrganyaVolume(100);
			PlayOrganyaMusic();
			break;

#ifdef EXTRA_SOUND_FORMATS
		case MUSIC_TYPE_OTHER:
			ExtraSound_LoadPreviousMusic();
			ExtraSound_UnpauseMusic();
			break;
#endif
	}

	gMusicNo = gOldNo;
}
