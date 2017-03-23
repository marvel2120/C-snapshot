#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#define MAX_KEY 16
#define MAX_LINE 1024
#define MAX_COMMAND 32

typedef struct entry entry;
typedef struct snapshot snapshot;
typedef struct value value;

struct value {
  value* next;
  int value;
};

struct entry {
  entry* prev;
  entry* next;
  value* values;
  char key[MAX_KEY];
};

struct snapshot {
  snapshot* prev;
  snapshot* next;
  entry* entries;
  int id;
};

const char* HELP =
	"BYE   clear database and exit\n"
	"HELP  display this help message\n"
	"\n"
	"LIST KEYS       displays all keys in current state\n"
	"LIST ENTRIES    displays all entries in current state\n"
	"LIST SNAPSHOTS  displays all snapshots in the database\n"
	"\n"
	"GET <key>    displays entry values\n"
	"DEL <key>    deletes entry from current state\n"
	"PURGE <key>  deletes entry from current state and snapshots\n"
	"\n"
	"SET <key> <value ...>     sets entry values\n"
	"PUSH <key> <value ...>    pushes values to the front\n"
	"APPEND <key> <value ...>  appends values to the back\n"
	"\n"
	"PICK <key> <index>   displays value at index\n"
	"PLUCK <key> <index>  displays and removes value at index\n"
	"POP <key>            displays and removes the front value\n"
	"\n"
	"DROP <id>      deletes snapshot\n"
	"ROLLBACK <id>  restores to snapshot and deletes newer snapshots\n"
	"CHECKOUT <id>  replaces current state with a copy of snapshot\n"
	"SNAPSHOT       saves the current state as a snapshot\n"
	"\n"
	"MIN <key>  displays minimum value\n"
	"MAX <key>  displays maximum value\n"
	"SUM <key>  displays sum of values\n"
	"LEN <key>  displays number of values\n"
	"\n"
	"REV <key>   reverses order of values\n"
	"UNIQ <key>  removes repeated adjacent values\n"
	"SORT <key>  sorts values in ascending order\n"
	"\n"
	"DIFF <key> <key ...>   displays set difference of values in keys\n"
	"INTER <key> <key ...>  displays set intersection of values in keys\n"
	"UNION <key> <key ...>  displays set union of values in keys\n";

#endif


