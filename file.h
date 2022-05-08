#ifndef MCX_FILE_H
#define MCX_FILE_H
#include <stdio.h>
#include "string.h"
#include <dirent.h>

void init(FILE);

static inline string readToEnd(FILE* f) {
    long pos = ftell(f);
    fseek(f, 0l, SEEK_END);
    long size = ftell(f) - pos;
    fseek(f, pos, SEEK_SET);
    char* res = malloc(size);
    fread(res, 1, size, f);
    return str(res);
}
static inline string readAllText(string path) {
    FILE* f = fopen(cptr(path), "r");
    string res = readToEnd(f);
    fclose(f);
    return res;
}
static inline string runProcess(string command) {
    FILE* f = popen(cptr(command), "r");
    string res = readToEnd(f);
    if (WEXITSTATUS(pclose(f)) == 0) return res;
    string tmp = {0};
    return tmp;
}
static inline void writeAllText(string path, string text) {
    FILE* f = fopen(cptr(path), "w");
    fputs(cptr(text), f);
    fclose(f);
}

list(string) listFiles(string directory, unsigned char kind);

static inline string realPath(string path) {
    return str(realpath(cptr(path), NULL));
}
bool fileExists(string path);
extern set(char)* illegalPath;
bool isPathLegal(string path);

#endif // MCX_FILE_H
