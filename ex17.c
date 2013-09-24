#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_DATA 512

struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};

struct Database {
	struct Address rows[MAX_ROWS];
};

struct Connection {
	struct Database *db;
	FILE *file;
};

void die(const char *msg) {
	if(errno) {
		perror(msg);
	}
	else {
		printf("ERROR: %s\n", msg);
	}
	exit(1);
}

void Address_print(struct Address *addr) {
	printf("Printing Address\n -> id: %d, set: %d, name: %s, email: %s,", addr->id, addr->set, addr->name, addr->email);
}

void Database_load(struct Connection *con) {
	int rc = fread(con->db, sizeof(struct Database), 1, con->file);
	if(rc != 1) die("Failed to load database.");
}

struct Connection *Database_open(const char *filename, char mode) {
	struct Connection *connection = malloc(sizeof(struct Connection));
	if(!connection) die("memory error");

	connection->db = malloc(sizeof(struct Database));
    if(!connection->db) die("Memory error");

    if(mode == 'c') {
    	connection->file = fopen(filename, "w");
    }
    else {
    	connection->file = fopen(filename, "r+");
    	if(connection->file) {
    		Database_load(connection);
    	}
    }

    if(!connection->file) die("Failed to open file.");

    return connection;
}

void Database_close(struct Connection *connection) {
	if(connection) {
		if(connection->file) fclose(connection->file);
		if(connection->db) free(connection->db);
		free(connection);
	}
}

void Database_write(struct Connection *connection) {
	rewind(connection->file);
	int rc = fwrite(connection->db, sizeof(struct Database), 1, connection->file);
	if(rc !=1) die("failed to write database");

	rc = fflush(connection->file);
	if(rc == -1) die("Cannot flush database.");
}

void Database_create(struct Connection *connection) {
	int i = 0;
	for(i=0; i < MAX_ROWS; i++) {
		struct Address addr = {.id =i, .set = 0}; 
		connection->db->rows[i] = addr;
	}
}

void Database_set(struct Connection *connection, int id, const char *name, const char* email) {
	struct Address *addr = &connection->db->rows[id];
	if(addr->set) die("Already set, delete it first");

	addr->set = 1;
    char *res = strncpy(addr->name, name, MAX_DATA);
    if(!res) die("Name copy failed");

    res = strncpy(addr->email, email, MAX_DATA);
    if(!res) die("Email copy failed");	
}

void Database_get(struct Connection *connection, int id) {
    struct Address *addr = &connection->db->rows[id];
    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}
void Database_delete(struct Connection *connection, int id) {
    struct Address addr = {.id = id, .set = 0};
    connection->db->rows[id] = addr;
}


void Database_list(struct Connection *connection) {
    int i = 0;
    struct Database *db = connection->db;
    for(i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];
        if(cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[]) {

	if(argc < 3) die("USAGE: ex17 <file> <action> [action params]");

	char *filename = argv[1];
	char action = argv[2][0];

	struct Connection *connection = Database_open(filename, action);
	int id = 0;

	if(argc > 3) id = atoi(argv[3]);
	if(id >= MAX_ROWS) die("There's not that many records.");

    switch(action) {
        case 'c':
            Database_create(connection);
            Database_write(connection);
            break;

        case 'g':
            if(argc != 4) die("Need an id to get");

            Database_get(connection, id);
            break;

        case 's':
            if(argc != 6) die("Need id, name, email to set");

            Database_set(connection, id, argv[4], argv[5]);
            Database_write(connection);
            break;

        case 'd':
            if(argc != 4) die("Need id to delete");

            Database_delete(connection, id);
            Database_write(connection);
            break;

        case 'l':
            Database_list(connection);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(connection);	


	return 0;
}



