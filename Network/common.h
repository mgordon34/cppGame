#pragma once

#include <glm/glm.hpp>
#include <cstdint>

#define PROT_ID 69420
#define PACKET_BACKUP 8 //Number of previous states to keep

//Client Gamestate
enum cl_state {
	MENU,
	CONNECTING,
	PRE_GAME,
	PLAY,
	EXIT
};

//Sever Gamestate
enum sv_state { SV_MENU,
	SV_CONNECTING,
	SV_PRE_GAME,
	SV_PLAY,
	SV_END
};

//server commands
enum serv_cmd {
	scmd_GameState,
	scmd_Snapshot,
	scmd_EOF
};

//client commands
enum cl_cmd {
	ccmd_Update,
	ccmd_EOF
};

//
// EntityState for sending data over network
//
typedef struct {
	int id;
	short type;

	int xPos;
	int yPos;

} EntityState;

//
// ClSnapshot for handling snapshot data
//
typedef struct {
	int numEntities;
	int start;

} ClSnapshot;
