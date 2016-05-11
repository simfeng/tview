#include "common.h"
#include "debug.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char *
T_strdup(const char *str)
{
	size_t len;
	char *copy;

	len = strlen(str) + 1;
	if( !(copy = (char *)malloc(len)))  return 0;
	memcpy(copy, str,len);
	return copy;
}

char *
right_trim(char *str)
{
	int len = strlen(str);
	char *cur = str + len - 1; //move to last character
	BOOL is_space;

	while(cur != str && (isspace(*cur)||*cur == '\n')) --cur;
	is_space = (isspace(*cur) || *cur == '\n');
	cur[is_space ? 0 : 1 ] = '\0';

	return str;
}

void 
GatherFileType(const char *name, char *type)
{
	struct stat buf;
	
	if(stat(name,&buf) == -1){
		perror("stat");
		exit(1);
	}

	switch(buf.st_mode & S_IFMT){
		case S_IFBLK:
			strcpy(type,"Block Device");
			break;
		case S_IFCHR:
			strcpy(type,"Character device");
			break;
		case S_IFDIR:
			strcpy(type,"Directory");
			break;
		case S_IFIFO:
			strcpy(type,"FIFO/Pipe");
			break;
		case S_IFLNK:
			strcpy(type,"Symlink");
			break;
		case S_IFREG:
			strcpy(type,"Regular File");
			break;
		case S_IFSOCK:
			strcpy(type,"Socket");
			break;
		default:
			strcpy(type, "Unknown");
			break;
	}

}

