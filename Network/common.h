#pragma once

#include <glm/glm.hpp>
#include <cstdint>

#define PROT_ID 69420
#define PACKET_BACKUP 8 //Number of previous states to keep

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
