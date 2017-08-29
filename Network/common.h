#pragma once

#include <glm\glm.hpp>

#define PACKET_BACKUP 8 //Number of previous states to keep

//server commands
typedef enum {
	scmd_GameState,
	scmd_Snapshot,
	scmd_EOF
} serv_cmd;

//client commands
typedef enum {
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
