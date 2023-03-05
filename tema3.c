/* ANGHELOIU George-Bogdan 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

typedef struct dir dir;
typedef struct fis fis;
typedef struct dir {
    char* nume;
    dir* parinte;
    fis* fisier;
    dir* directories;
    dir* st;
    dir* dr;
} TDir;
typedef struct fis {
    char* nume;
    dir* parinte;
    fis* st;
    fis* dr;
} TFis;

int dirExists(TDir* dir, char* name) {
    if(dir == NULL)
        return 0;
    if(strcmp(dir->nume, name) == 0)
        return 1;
    else if(dir->st == NULL && dir->dr == NULL)
        return 0;
    else    
        return dirExists(dir->dr, name) || dirExists(dir->st, name); 
}

int fileExists(TFis* file, char* name) {
    if(file == NULL)
        return 0;
    if(strcmp(file->nume, name) == 0)
        return 1;
    else if(file->st == NULL && file->dr == NULL)
        return 0;
    else    
        return fileExists(file->dr, name) || fileExists(file->st, name); 
}

int touch(TDir* crt, char* name) {
    TFis* fis = crt->fisier;
    // only if there are no files in the directory
    if(fis == NULL) {
        crt->fisier = malloc(sizeof(TFis));
        if(!crt->fisier)
            return 0;
        crt->fisier->dr = crt->fisier->st = NULL;
        crt->fisier->nume = malloc(strlen(name) + 1);
        if(!crt->fisier->nume) {
            free(crt->fisier);
            return 0;
        }
        strncpy(crt->fisier->nume, name, strlen(name) + 1);
        crt->fisier->parinte = NULL;
        return 1;
    }
    while(fis != NULL) {
        if(strcmp(fis->nume, name) > 0){
            if(fis->dr == NULL) {
                fis->dr = malloc(sizeof(TFis));
                if(!fis->dr)
                    return 0;
                fis->dr->dr = fis->dr->st = NULL;
                fis->dr->nume = malloc(strlen(name) + 1);
                if(!fis->dr->nume) {
                    free(fis->dr);
                    return 0;
                }
                strncpy(fis->dr->nume, name, strlen(name) + 1);
                fis->dr->parinte = fis->parinte;
                break;
            }
            fis = fis->dr;
        }else {
            if(fis->st == NULL) {
                fis->st = malloc(sizeof(TFis));
                if(!fis->st)
                    return 0;
                fis->st->dr = fis->st->st = NULL;
                fis->st->nume = malloc(strlen(name) + 1);
                if(!fis->st->nume) {
                    free(fis->st);
                    return 0;
                }
                strncpy(fis->st->nume, name, strlen(name) + 1);
                fis->st->parinte = fis->parinte;
                break;
            }
            fis = fis->st;
        }
    }
    return 1;
}

int mkdir(TDir* crt, char* name) {
    TDir* dir = crt->directories;
    // only if there are no files in the directory
    if(dir == NULL) {
        crt->directories = malloc(sizeof(TDir));
        if(!crt->directories)
            return 0;
        crt->directories->dr = crt->directories->st = NULL;
        crt->directories->nume = malloc(strlen(name) + 1);
        if(!crt->directories->nume) {
            free(crt->directories);
            return 0;
        }
        strncpy(crt->directories->nume, name, strlen(name) + 1);
        crt->directories->parinte = crt;
        return 1;
    }
    while(dir != NULL) {
        if(strcmp(dir->nume, name) < 0){
            if(dir->dr == NULL) {
                dir->dr = malloc(sizeof(TDir));
                if(!dir->dr)
                    return 0;
                dir->dr->dr = dir->dr->st = NULL;
                dir->dr->nume = malloc(strlen(name) + 1);
                if(!dir->dr->nume) {
                    free(dir->dr);
                    return 0;
                }
                strncpy(dir->dr->nume, name, strlen(name) + 1);
                dir->dr->parinte = dir->parinte;
                break;
            }
            dir = dir->dr;
        }else {
            if(dir->st == NULL) {
                dir->st = malloc(sizeof(TDir));
                if(!dir->st)
                    return 0;
                dir->st->dr = dir->st->st = NULL;
                dir->st->nume = malloc(strlen(name) + 1);
                if(!dir->st->nume) {
                    free(dir->st);
                    return 0;
                }
                strncpy(dir->st->nume, name, strlen(name) + 1);
                dir->st->parinte = dir->parinte;
                break;
            }
            dir = dir->st;
        }
    }
    return 1;
}

/*void reorderFiles(TFis** fis) {
    if(*fis == NULL)
        return;
    reorderFiles((*fis)->dr);
    reorderFiles((*fis)->st);
    TFis* temp1, *temp2;
    if((*fis)->dr != NULL)
        if(strcmp((*fis)->dr->nume, (*fis)->nume) > 0) {
            temp1 = (*fis)->dr;
            (*fis)->dr = temp1->dr;
            temp1->dr = (*fis);
            temp2 = (*fis)->st;
            (*fis)->st = temp1->st;
            temp1->st = temp2;
            (*fis) = temp1;
        }
    if((*fis)->st != NULL)
        if(strcmp((*fis)->st->nume, (*fis)->nume) < 0) {
            temp1 = (*fis)->st;
            (*fis)->st = temp1->st;
            temp1->st = (*fis);
            temp2 = (*fis)->dr;
            (*fis)->dr = temp1->dr;
            temp1->dr = temp2;
            (*fis) = temp1;
            if((*fis)->dr != NULL)
                if(strcmp((*fis)->dr->nume, (*fis)->nume) > 0) {
                    temp1 = (*fis)->dr;
                    (*fis)->dr = temp1->dr;
                    temp1->dr = (*fis);
                    temp2 = (*fis)->st;
                    (*fis)->st = temp1->st;
                    temp1->st = temp2;
                    (*fis) = temp1;
                }
        }
}*/

void* leftest(void** arb, void** prec, int fileMode) {
    if(fileMode) {
        TFis* fis = *((TFis**)arb);
        if(fis->st != NULL){
            *prec = *arb;
            return leftest((void**)&fis->st, prec, fileMode);
            return leftest((void**)&fis->st, prec, fileMode);
        } else
            return fis;
    }
    return NULL;
}

void* rightest(void** arb, void** prec, int fileMode) {
    if(fileMode) {
        TFis* fis = *((TFis**)arb);
        if(fis->dr != NULL){
            *prec = *arb;
            return rightest((void**)&fis->dr, prec, fileMode);
            return rightest((void**)&fis->dr, prec, fileMode);
        } else
            return fis;
    }
    return NULL;
}

void printDir(TDir* dir) {
    if(dir == NULL)
        return;
    printDir(dir->st);
    printf("%s ", dir->nume);
    printDir(dir->dr);
}

void printFiles(TFis* fis) {
    if(fis == NULL)
        return;
    printFiles(fis->dr);
    printf("%s ", fis->nume);
    printFiles(fis->st);
}

void ls(TDir* dir) {
    if(dir == NULL)
        return;
    printDir(dir->directories);
    printFiles(dir->fisier);
    printf("\n");
}

int rm(TFis** fis, char* name) {
    if(*fis == NULL)
        return 0;
    TFis *parent, *newRoot;
    int found = 0;
    parent = NULL;
    newRoot = *fis;
    TFis *left, *right, *leftPrev = NULL, *rightPrev = NULL;
    char *leftName, *rightName, *tempName;
    while(newRoot != NULL) {
        if(strcmp(newRoot->nume, name) == 0) {
            //printf("%s\n", parent->nume);
            if(parent == NULL) {
                if(newRoot->dr == NULL) {
                    (*fis) = newRoot->st;
                    free(newRoot->nume);
                    free(newRoot);
                    found = 1;
                } else if (newRoot->st == NULL){
                    (*fis) = newRoot->dr;
                    free(newRoot->nume);
                    free(newRoot);
                    found = 1;
                } else {
                    right = leftest((void**)&(newRoot->dr), (void**)&rightPrev, 1);
                    left = rightest((void**)&(newRoot->st), (void**)&leftPrev, 1);
                    leftName = left->nume;
                    rightName = right->nume;
                    tempName = name;
                    while(*rightName != '\0' && *leftName != '\0' && (tempName - name < strlen(name))) {
                        if(abs(*rightName - *tempName) < abs(*leftName - *tempName)) {
                            free(newRoot->nume);
                            newRoot->nume = malloc(sizeof(char) * (strlen(right->nume) + 1));
                            strncpy(newRoot->nume, right->nume, strlen(right->nume) + 1);
                            found = rm(&newRoot->dr, newRoot->nume);
                            break;
                        } else if(abs(*rightName - *tempName) > abs(*leftName - *tempName)) {
                            free(newRoot->nume);
                            newRoot->nume = malloc(sizeof(char) * (strlen(left->nume) + 1));
                            strncpy(newRoot->nume, left->nume, strlen(left->nume) + 1);
                            found = rm(&newRoot->st, newRoot->nume);
                            break;
                        } else {
                            rightName++;
                            leftName++;
                            tempName++;
                        }
                    }
                    if(!found) {
                        free(newRoot->nume);
                        newRoot->nume = malloc(sizeof(char) * (strlen(right->nume) + 1));
                        strncpy(newRoot->nume, right->nume, strlen(right->nume) + 1);
                        found = rm(&newRoot->dr, newRoot->nume);
                    }
                }
                break;
            }
            if (newRoot->dr == NULL) {
                //printf("%p\n", parent);
                if(parent->dr != NULL && parent->dr == newRoot) {
                    parent->dr = newRoot->st;
                    free(newRoot->nume);
                    free(newRoot);
                    found = 1;
                }
                else{
                    parent->st = newRoot->st;
                    free(newRoot->nume);
                    free(newRoot);
                    found = 1;
                }
            } else if (newRoot->st == NULL){
                if(parent->dr != NULL && parent->dr == newRoot) {
                    parent->dr = newRoot->dr;
                    free(newRoot->nume);
                    free(newRoot);
                    found = 1;
                }
                else {
                    parent->st = newRoot->dr;
                    free(newRoot->nume);
                    free(newRoot);
                    found = 1;
                }
            } else {
                right = leftest((void**)&(newRoot->dr), (void**)&rightPrev, 1);
                left = rightest((void**)&(newRoot->st), (void**)&leftPrev, 1);
                leftName = left->nume;
                rightName = right->nume;
                tempName = name;
                while(*rightName != '\0' && *leftName != '\0' && (tempName - name < strlen(name))) {
                    if(abs(*rightName - *tempName) < abs(*leftName - *tempName)) {
                        free(newRoot->nume);
                        newRoot->nume = malloc(sizeof(char) * (strlen(right->nume) + 1));
                        strncpy(newRoot->nume, right->nume, strlen(right->nume) + 1);
                        found = rm(&newRoot->dr, newRoot->nume);
                        found = 1;
                        break;
                    } else if(abs(*rightName - *tempName) > abs(*leftName - *tempName)) {
                        free(newRoot->nume);
                        newRoot->nume = malloc(sizeof(char) * (strlen(left->nume) + 1));
                        strncpy(newRoot->nume, left->nume, strlen(left->nume) + 1);
                        found = rm(&newRoot->st, newRoot->nume);
                        break;
                    } else {
                        rightName++;
                        leftName++;
                        tempName++;
                    }
                }
                if(!found) {
                    free(newRoot->nume);
                    newRoot->nume = malloc(sizeof(char) * (strlen(right->nume) + 1));
                    strncpy(newRoot->nume, right->nume, strlen(right->nume) + 1);
                    found = rm(&newRoot->dr, newRoot->nume);
                }
            }
            break;
            free(newRoot->nume);
            free(newRoot);
        } else if(strcmp(newRoot->nume, name) > 0) { //dreapta
            parent = newRoot;
            newRoot = newRoot->dr;
        } else { //stanga
            parent = newRoot;
            newRoot = newRoot->st;
        }
    }
    return found;
}

void deleteAll(void** arb, int fileMode) {
    if(!(*arb))
        return;
    if(fileMode) {
        TFis** fis = (TFis**)arb;
        if((*fis)->dr)
            deleteAll((void**)&(*fis)->dr, fileMode);
        if((*fis)->st)
            deleteAll((void**)&(*fis)->st, fileMode);
        free((*fis)->nume);
        free((*fis));
        *fis = NULL;
    } else {
        TDir** dir = (TDir**)arb;
        if((*dir)->dr)
            deleteAll((void**)&(*dir)->dr, fileMode);
        if((*dir)->st)
            deleteAll((void*)&(*dir)->st, fileMode);
        if((*dir)->directories)
            deleteAll((void*)&(*dir)->directories, fileMode);
        if((*dir)->fisier)
            deleteAll((void*)&(*dir)->fisier, 1);
        free((*dir)->nume);
        free((*dir));
        *dir = NULL;
    }  
}

int rmdir(TDir** dir, char* name) {
    if(*dir == NULL)
        return 0;
    TDir *parent, *newRoot;
    int found = 0;
    parent = NULL;
    newRoot = *dir;
    TDir *left, *right, *leftPrev = NULL, *rightPrev = NULL;
    char *leftName, *rightName, *tempName;
    while(newRoot != NULL) {
        if(strcmp(newRoot->nume, name) == 0) {
            if((*dir)->directories != NULL)
                deleteAll((void**)&(*dir)->directories, 0);
            if((*dir)->fisier != NULL) 
                deleteAll((void**)&(*dir)->fisier, 1);
            if(parent == NULL) {
                if(newRoot->dr == NULL) {
                    (*dir) = newRoot->st;
                    free(newRoot->nume);
                    free(newRoot);
                    found = 1;
                } else if (newRoot->st == NULL){
                    (*dir) = newRoot->dr;
                    free(newRoot->nume);
                    free(newRoot);
                    found = 1;
                } else {
                    right = leftest((void**)&(newRoot->dr), (void**)&rightPrev, 1);
                    left = rightest((void**)&(newRoot->st), (void**)&leftPrev, 1);
                    leftName = left->nume;
                    rightName = right->nume;
                    tempName = name;
                    while(*rightName != '\0' && *leftName != '\0' && (tempName - name < strlen(name))) {
                        if(abs(*rightName - *tempName) < abs(*leftName - *tempName)) {
                            free(newRoot->nume);
                            newRoot->nume = malloc(sizeof(char) * (strlen(right->nume) + 1));
                            strncpy(newRoot->nume, right->nume, strlen(right->nume) + 1);
                            found = rmdir(&newRoot->dr, newRoot->nume);
                            break;
                        } else if(abs(*rightName - *tempName) > abs(*leftName - *tempName)) {
                            free(newRoot->nume);
                            newRoot->nume = malloc(sizeof(char) * (strlen(left->nume) + 1));
                            strncpy(newRoot->nume, left->nume, strlen(left->nume) + 1);
                            found = rmdir(&newRoot->st, newRoot->nume);
                            break;
                        } else {
                            rightName++;
                            leftName++;
                            tempName++;
                        }
                    }
                    if(!found) {
                        free(newRoot->nume);
                        newRoot->nume = malloc(sizeof(char) * (strlen(right->nume) + 1));
                        strncpy(newRoot->nume, right->nume, strlen(right->nume) + 1);
                        found = rmdir(&newRoot->dr, newRoot->nume);
                    }
                }
                break;
            }
            if (newRoot->dr == NULL) {
                //printf("%p\n", parent);
                if(parent->dr != NULL && parent->dr == newRoot) {
                    parent->dr = newRoot->st;
                    free(newRoot->nume);
                    free(newRoot);
                    found = 1;
                }
                else{
                    parent->st = newRoot->st;
                    free(newRoot->nume);
                    free(newRoot);
                    found = 1;
                }
            } else if (newRoot->st == NULL){
                if(parent->dr != NULL && parent->dr == newRoot) {
                    parent->dr = newRoot->dr;
                    free(newRoot->nume);
                    free(newRoot);
                    found = 1;
                }
                else {
                    parent->st = newRoot->dr;
                    free(newRoot->nume);
                    free(newRoot);
                    found = 1;
                }
            } else {
                right = leftest((void**)&(newRoot->dr), (void**)&rightPrev, 1);
                left = rightest((void**)&(newRoot->st), (void**)&leftPrev, 1);
                leftName = left->nume;
                rightName = right->nume;
                tempName = name;
                while(*rightName != '\0' && *leftName != '\0' && (tempName - name < strlen(name))) {
                    if(abs(*rightName - *tempName) < abs(*leftName - *tempName)) {
                        free(newRoot->nume);
                        newRoot->nume = malloc(sizeof(char) * (strlen(right->nume) + 1));
                        strncpy(newRoot->nume, right->nume, strlen(right->nume) + 1);
                        found = rmdir(&newRoot->dr, newRoot->nume);
                        found = 1;
                        break;
                    } else if(abs(*rightName - *tempName) > abs(*leftName - *tempName)) {
                        free(newRoot->nume);
                        newRoot->nume = malloc(sizeof(char) * (strlen(left->nume) + 1));
                        strncpy(newRoot->nume, left->nume, strlen(left->nume) + 1);
                        found = rmdir(&newRoot->st, newRoot->nume);
                        break;
                    } else {
                        rightName++;
                        leftName++;
                        tempName++;
                    }
                }
                if(!found) {
                    free(newRoot->nume);
                    newRoot->nume = malloc(sizeof(char) * (strlen(right->nume) + 1));
                    strncpy(newRoot->nume, right->nume, strlen(right->nume) + 1);
                    found = rmdir(&newRoot->dr, newRoot->nume);
                }
            }
            break;
            free(newRoot->nume);
            free(newRoot);
        } else if(strcmp(newRoot->nume, name) < 0) { //dreapta
            parent = newRoot;
            newRoot = newRoot->dr;
        } else { //stanga
            parent = newRoot;
            newRoot = newRoot->st;
        }
    }
    return found;
}

int cd(TDir** result, TDir* dir, char* name) {
    if(!dir)
        return 0;
    if(strcmp(dir->nume, name) == 0) {
        *result = dir;
        return 1;
    } else if (strcmp(dir->nume, name) < 0) {
        return cd(result, dir->dr, name);
    } else if(strcmp(dir->nume, name) > 0) {
        return cd(result, dir->st, name);
    } else
        return 0;
}

void pwd(TDir* crt) {
    if(crt->parinte != NULL)
        pwd(crt->parinte);
    printf("/%s", crt->nume);
}

int findFile(TDir* dir, char* name) {
    int rez = 0;
    if(dir == NULL)
        return rez;
    if(!fileExists(dir->fisier, name)){
        if(dir->st)
            rez = rez || findFile(dir->st, name);
        if(dir->dr)
            rez = rez || findFile(dir->dr, name);
        if(dir->directories)
            rez = rez || findFile(dir->directories, name);
        return rez;
    } else {
        printf("File %s found!\n", name);
        pwd(dir);
        printf("\n");
        rez = 1;
        return rez;
    }
}

int findDir(TDir* dir, char* name) {
    int rez = 0;
    if(dir == NULL)
        return rez;
    if(strcmp(dir->nume, name) != 0) {
        if(dir->st)
            rez = rez || findDir(dir->st, name);
        if(dir->dr)
            rez = rez || findDir(dir->dr, name);
        if(dir->directories)
            rez = rez || findDir(dir->directories, name);
        return rez;
    } else {
        printf("Directory %s found!\n", name);
        pwd(dir);
        printf("\n");
        rez = 1;
        return rez;
    }
}

int main() {
    // initializam root
    TDir* root = malloc(sizeof(TDir));
    if(!root)
        return 0;
    root->nume = malloc(5 * sizeof(char));
    if(!(root->nume)) {
        free(root);
        return 0;
    }
    strncpy(root->nume, "root", 5);
    root->parinte = NULL;
    root->fisier = NULL;
    root->directories = NULL;
    root->st = NULL;
    root->dr = NULL;

    // directorul curent este root
    TDir* crt = root;
    
    // citirea comenzilor pana la "quit"
    char* line = malloc(N * sizeof(char)), *p;
    if(!line){
        free(root->nume);
        free(root);
        return 0;
    }
    size_t lineSize = N;
    while (getline(&line, &lineSize, stdin) > 0) {
        p = strtok(line, " \n");
        if (strcmp(p, "quit") == 0) {
            deleteAll((void*)&root, 0);
            break;
        } else if (strcmp(p, "touch") == 0) {
            p = strtok(NULL, " \n");
            if(dirExists(crt->directories, p))
                printf("Directory %s already exists!\n", p);
            else if(fileExists(crt->fisier, p)) {
                printf("File %s already exists!\n", p);
            } else {
                if(!touch(crt, p))
                    printf("Eroare touch!\n");
            }
        } else if(strcmp(p, "mkdir") == 0) {
            p = strtok(NULL, " \n");
            if(fileExists(crt->fisier, p)) {
                printf("File %s already exists!\n", p);
            }else if(dirExists(crt->directories, p))
                printf("Directory %s already exists!\n", p);
            else {
                if(!mkdir(crt, p))
                    printf("Eroare mkdir!\n");
            }
        } else if(strcmp(p, "ls") == 0) {
            ls(crt);
        } else if(strcmp(p, "rm") == 0) {
            p = strtok(NULL, " \n");
            if(!rm(&crt->fisier, p)) {
                printf("File %s doesn't exist!\n", p);
            }
        } else if(strcmp(p, "rmdir") == 0) {
            p = strtok(NULL, " \n");
            if(!rmdir(&crt->directories, p)) {
                printf("Directory %s doesn't exist!\n", p);
            }
        } else if(strcmp(p, "cd") == 0) {
            p = strtok(NULL, " \n");
            if(strcmp(p, "..") == 0) {
                if(strcmp(crt->nume, "root") == 0){}
                    //printf("Directory not found!\n");
                else 
                    crt = crt->parinte;
            } else if(!cd(&crt, crt->directories, p)) {
                printf("Directory not found!\n");
            }
        } else if(strcmp(p, "pwd") == 0) {
            pwd(crt);
            printf("\n");
        } else if(strcmp(p, "find") == 0) {
            p = strtok(NULL, " \n");
            if(strcmp(p, "-d") == 0){
                p = strtok(NULL, " \n");
                if(!findDir(root, p))
                    printf("Directory %s not found!\n", p);
            }
            else {
                p = strtok(NULL, " \n");
                if(!findFile(root, p))
                    printf("File %s not found!\n", p);
            }
        }
    }
}