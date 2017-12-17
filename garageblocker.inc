/*

	About: Garage Blocker
	Author: ziggi
	Thanks: BeckzyBoi for data (http://forum.sa-mp.com/showthread.php?t=645807)

*/

#if !defined _samp_included
	#error "Please include a_samp or a_npc before garageblocker"
#endif

#if !defined AddSimpleModel
	#error "This library works only with SA-MP 0.3.8 and above!"
#endif

#if defined _garageblocker_included
	#endinput
#endif

#define _garageblocker_included

/*
	Defines
*/

#if !defined GARAGEBLOCKER_MODELS_DIR
	#define GARAGEBLOCKER_MODELS_DIR "garageblocker/"
#endif

#if !defined GARAGEBLOCKER_BASE_NEWID
	#define GARAGEBLOCKER_BASE_NEWID (-1000)
#endif

#define GARAGEBLOCKER_MAX_DFF_NAME (17)

#if defined CreateDynamicObject && !defined GARAGEBLOCKER_NO_STREAMER
	#define GarageBlocker_CreateObject CreateDynamicObject
#else
	#define GarageBlocker_CreateObject CreateObject
#endif

/*
	Enums
*/

enum E_GARAGE_DOOR {
	E_GD_MODEL,
	Float:E_GD_POS_X,
	Float:E_GD_POS_Y,
	Float:E_GD_POS_Z,
	Float:E_GD_POS_RZ,
	E_GARAGE_OBJECT:E_GD_OBJECT,
};

enum E_GARAGE_OBJECT {
	E_GO_MODLAS2,
	E_GO_GARAGDOOR1_LAWN,
	E_GO_MODSHOPDOOR1_SFS,
	E_GO_MODSHOPDOOR_SFSE,
	E_GO_CMDGRGDOOR_LVS,
	E_GO_LAESPRAYDOOR1,
	E_GO_LAWNSPRAYDOOR1,
	E_GO_SPRAYDOOR_LAW2,
	E_GO_SPRAYSHPDR2_SFSE,
	E_GO_SPDR_SFW,
	E_GO_VGWSPRY1,
	E_GO_CE_SPRAYDOOR1,
	E_GO_CXF_SPRAYDOOR1,
	E_GO_BOMBDOOR_LAS,
};

enum E_GARAGE_OBJECT_INFO {
	E_GOI_BASEID,
	E_GOI_DFF[GARAGEBLOCKER_MAX_DFF_NAME],
	E_GOI_NEWID,
};

/*
	Vars
*/

static
	gGarageDoors[][E_GARAGE_DOOR] = {
		// mod shops
		{5340, 2644.8594, -2039.2344, 14.0391, 270.0, E_GO_MODLAS2},
		{5779, 1041.3516, -1025.9297, 32.6719, 90.0, E_GO_GARAGDOOR1_LAWN},
		{10575, -2716.3516, 217.4766, 5.3828, 0.0, E_GO_MODSHOPDOOR1_SFS},
		{11313, -1935.8594, 239.5313, 35.3516, 0.0, E_GO_MODSHOPDOOR_SFSE},
		{9093, 2386.6563, 1043.6016, 11.5938, 90.0, E_GO_CMDGRGDOOR_LVS},
		// pay n sprays
		{5422, 2071.4766, -1831.4219, 14.5625, 0.0, E_GO_LAESPRAYDOOR1},
		{5856, 1024.9844, -1029.3516, 33.1953, 90.0, E_GO_LAWNSPRAYDOOR1},
		{6400, 488.2813, -1734.6953, 12.3906, 90.0, E_GO_SPRAYDOOR_LAW2},
		{11319, -1904.5313, 277.8984, 42.9531, 0.0, E_GO_SPRAYSHPDR2_SFSE},
		{9625, -2425.7266, 1027.9922, 52.2813, 90.0, E_GO_SPDR_SFW},
		{7891, 1968.7422, 2162.4922, 12.0938, 0.0, E_GO_VGWSPRY1},
		{13028, 720.0156, -462.5234, 16.8594, 90.0, E_GO_CE_SPRAYDOOR1},
		{3294, -1420.5469, 2591.1563, 57.7422, 90.0, E_GO_CXF_SPRAYDOOR1},
		{3294, -100.0000, 1111.4141, 21.6406, 270.0, E_GO_CXF_SPRAYDOOR1},
		// bomb shops
		{5043, 1843.3672, -1856.3203, 13.8750, 0.0, E_GO_BOMBDOOR_LAS},
		{7707, 2006.0000, 2317.6016, 11.3125, 270.0, E_GO_BOMBDOOR_LAS},
		{7709, 2006.0000, 2303.7266, 11.3125, 90.0, E_GO_BOMBDOOR_LAS}
	},
	gGarageObjects[E_GARAGE_OBJECT][E_GARAGE_OBJECT_INFO] = {
		{5340, "modlas2"},
		{5779, "garagdoor1_lawn"},
		{10575, "modshopdoor1_sfs"},
		{11313, "modshopdoor_sfse"},
		{9093, "cmdgrgdoor_lvs"},
		{5422, "laespraydoor1"},
		{5856, "lawnspraydoor1"},
		{6400, "spraydoor_law2"},
		{11319, "sprayshpdr2_sfse"},
		{9625, "spdr_sfw"},
		{7891, "vgwspry1"},
		{13028, "ce_spraydoor1"},
		{3294, "cxf_spraydoor1"},
		{5043, "bombdoor_las"}
	};

static stock const
	MODELS_DIR[] = GARAGEBLOCKER_MODELS_DIR;

/*
	OnGameModeInit
*/

public OnGameModeInit()
{
	static
		string[sizeof(MODELS_DIR) + GARAGEBLOCKER_MAX_DFF_NAME + 4],
		E_GARAGE_OBJECT:obj,
		newid;

	newid = GARAGEBLOCKER_BASE_NEWID;

	for (obj = E_GARAGE_OBJECT:0; _:obj < sizeof(gGarageObjects); _:obj++) {
		format(string, sizeof(string), GARAGEBLOCKER_MODELS_DIR "%s.dff", gGarageObjects[obj][E_GOI_DFF]);

		AddSimpleModel(-1, gGarageObjects[obj][E_GOI_BASEID], newid, string, GARAGEBLOCKER_MODELS_DIR "doors.txd");
		gGarageObjects[obj][E_GOI_NEWID] = newid;
		newid--;
	}

	for (new i = 0; i < sizeof(gGarageDoors); i++) {
		obj = gGarageDoors[i][E_GD_OBJECT];

		GarageBlocker_CreateObject(gGarageObjects[obj][E_GOI_NEWID], gGarageDoors[i][E_GD_POS_X], gGarageDoors[i][E_GD_POS_Y], gGarageDoors[i][E_GD_POS_Z], 0.0, 0.0, gGarageDoors[i][E_GD_POS_RZ]);
	}

	#if defined GarageBlocker_OnGameModeInit
		return GarageBlocker_OnGameModeInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit GarageBlocker_OnGameModeInit
#if defined GarageBlocker_OnGameModeInit
	forward GarageBlocker_OnGameModeInit();
#endif

/*
	OnPlayerConnect
*/

public OnPlayerConnect(playerid)
{
	for (new i = 0; i < sizeof(gGarageDoors); i++) {
		RemoveBuildingForPlayer(playerid, gGarageDoors[i][E_GD_MODEL], gGarageDoors[i][E_GD_POS_X], gGarageDoors[i][E_GD_POS_Y], gGarageDoors[i][E_GD_POS_Z], 1.0);
	}
	
	#if defined GarageBlocker_OnPlayerConnect
		return GarageBlocker_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect GarageBlocker_OnPlayerConnect
#if defined GarageBlocker_OnPlayerConnect
	forward GarageBlocker_OnPlayerConnect(playerid);
#endif
