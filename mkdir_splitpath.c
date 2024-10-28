

#include "types.h"
#include "string.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    int exists=0;
    char baseName;
    char dirName;
    if(pathName == "/"){
        printf(" % s\n","MKDIR ERROR: no path provided");
        return;
    }
    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW
    struct NODE* parent;
    struct NODE* currNode;
    struct NODE* prevNode;
    struct NODE* newNode;
    struct NODE n;
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
        n.parentPtr=parent;
        *n.name=baseName;
        n.fileType="D";
        if(prevNode==parent){
            parent->childPtr=&n;
        }
        else{
            prevNode->siblingPtr=&n;
        }
        printf(" % s\n",strcat(strcat("MKDIR SUCCESS: node ",pathName)," created"));
    }
    else{
        printf(" % s\n",strcat(strcat("MKDIR ERROR: directory ",baseName)," already exists"));
    }

    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // YOUR CODE HERE
    int pathSize = sizeof(pathName)/sizeof(pathName[0]);
    char *pathName2;
    strcpy(pathName2, pathName);
    char *token = strtok(pathName2, '/');
    while(strstr(pathName2, '/')){
        token = strtok(NULL,'/');
    }
    baseName=token;
    int baseSize = sizeof(baseName)/sizeof(baseName[0]);
    strncpy(dirName,pathName,pathSize-baseSize);

    char *dirName2;
    char* directory = strtok(dirName2,'/');
    struct NODE* currNode;
    if(pathName[0]=='/'){
        currNode = root;
    }
    else{
        currNode = cwd;
        directory=strtok(NULL,'/');
    }
    while(directory != NULL){
        currNode = currNode->childPtr;
        while(currNode!=NULL){
            if(currNode->name==directory){
                break;
            }
            currNode=currNode->siblingPtr;
        } 
        if(currNode==NULL){
            printf(" % s\n",strcat(strcat("ERROR: directory ",directory)," does not exist"));
            return NULL;
        }

        directory=strtok(NULL,'/');
    }
    return currNode;

}
