#include "types.h"
#include "string.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    int exists=0;
    char baseName[100];
    char dirName[100];
    if(pathName == "/"){
        printf(" % s\n","MKDIR ERROR: no path provided");
        return;
    }

    struct NODE* parent;
    struct NODE* currNode;
    struct NODE* prevNode;
    struct NODE* newNode;
    struct NODE* n = malloc(sizeof(struct NODE));
    parent = splitPath(pathName, baseName, dirName);
    if(parent==NULL){
        return;
    }
    currNode = parent->childPtr;
    prevNode = parent;
    while(currNode!=NULL){
        if(currNode->name==baseName){
            exists=1;
            break;
        }
        prevNode=currNode;
        currNode=currNode->siblingPtr;
    }


    if(exists == 0){
        n->parentPtr=parent;
        n->siblingPt=NULL;
        strcpy(n->name, baseName);
        n->fileType='D';
        if(prevNode==parent){
            parent->childPtr=n;
        }
        else{
            prevNode->siblingPtr=n;
        }
        printf(" % s%s%s\n","MKDIR SUCCESS: node ",pathName," created");
    }
    else{
        printf(" % s%s%s\n","MKDIR ERROR: directory ",baseName," already exists");
    }

    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){


    char* splitter = strrchr(pathName, '/');
    if (splitter != NULL){
        strncpy(dirName, pathName, splitter-pathName+1);
        dirName[splitter-pathName+1]='\0';
        strcpy(baseName, splitter+1);
    }
    else{
        strcpy(baseName,pathName);
        dirName[0]='/';
        dirName[1]='\0';
    }
    char dirName2[100];
    strcpy(dirName2,dirName);
    char* directory = strtok(dirName2,"/");
    struct NODE* currNode;
    if(pathName[0]=='/'){
        currNode = root;
    }
    else{
        currNode = cwd;
    }
    while(directory != NULL){
        currNode = currNode->childPtr;
        while(currNode!=NULL){
            if(strcmp(currNode->name,directory)==0){
                break;
            }
            currNode=currNode->siblingPtr;
        }
        if(currNode==NULL){
            printf(" % s%s%s\n","ERROR: directory ",directory," does not exist");
            return NULL;
        }

        directory=strtok(NULL,"/");
    }
    return currNode;

}
