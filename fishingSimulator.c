#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

//constants
#define BUCKET_SIZE  10
#define POND_CAPACITY 15
//structs
typedef struct{
    unsigned char size; //size of the Fish
    char *species; //species of the Fish
} Fish;

typedef struct{
    char *name; //name if the Fisher
    unsigned char keepSize; //the size of fish that the Fisher is willing to keep
    Fish bucket[BUCKET_SIZE]; //a bucket that can hold at most BUCKET_SIZE number of fish 
    unsigned char numFish; //number of fish in the bucket
} Fisher;

typedef struct{
    Fish fish[POND_CAPACITY];  //an array that can hold at most BUCKET_SIZE number of fish 
    unsigned char numFish; //number of fish in the pond
} Pond;
//Method Declarations
int addFish(Pond *p, unsigned char size, char *species);
void listFish(Fish *arrayOfFish, int n);
char likes(Fisher *fisher, Fish *f);
int keep(Fisher *fisher, Fish *f);
int castLine(Fisher *fisher, Pond *p);
void giveAwayFish(Fisher *fisher1, Fisher *fisher2, Pond *p);

int main(){
    // Seed rand
    srand(time(NULL));
    //create pond
    Pond pond;
    pond.numFish = 0;
    Pond *p = &pond;
    //create fisher fred
    Fisher Fred;
    Fred.name = "Fred";
    Fred.keepSize = 15;
    Fred.numFish = 0;
    Fisher *f1 = &Fred;
    //create fisher suzy
    Fisher Suzy;
    Suzy.name = "Suzy";
    Suzy.numFish = 0;
    Suzy.keepSize = 10;
    Fisher *f2 = &Suzy;
    //add fish to the pond
    addFish(p, 4, "Sunfish");
    addFish(p, 25, "Pike");
    addFish(p, 20, "Bass");
    addFish(p, 30, "Perch");
    addFish(p, 14, "Sunfish");
    addFish(p, 15, "Pike");
    addFish(p, 9, "Pike");
    addFish(p, 12, "Bass");
    addFish(p, 5, "Sunfish");
    addFish(p, 12, "Sunfish");
    addFish(p, 10, "Bass");
    addFish(p, 2, "Bass");
    addFish(p, 16, "Perch");
    addFish(p, 30, "Sunfish");
    addFish(p, 7, "Perch");
    //list the current fish in the pond
    printf("Fish in the pond:\n");
    listFish(pond.fish, POND_CAPACITY);
    //let Fred cast ten times
    for (int i=0; i<10; i++){
        castLine(f1, p);
    }
    //list the fish in Fred's bucket
    printf("\nFirst Fred attempts to catch 10 fish in the big pond ...\nFred's Fish:\n");
    listFish(Fred.bucket, (int)Fred.numFish);
    //let Suzy cast ten times
    for (int i=0; i<10; i++){
        castLine(f2, p);
    }
    //list the fish in Suzy's bucket
    printf("\nSuzy now attempts to catch 10 fish in the big pond ...\nSuzy's Fish:\n");
    listFish(Suzy.bucket, (int)Suzy.numFish);
    //list the fish that remain in the pond
    printf("\nHere is what is left of the pond ...\n");
    listFish(pond.fish, (int)pond.numFish);
    //give all of Suzy's fish to Fred or return them to the pond
    giveAwayFish(f2, f1, p);
    //list Fred's fish, Suzy's fish and the pond's remaining fish respectively
    printf("\nFred's Fish:\n");
    listFish(Fred.bucket, (int)Fred.numFish);
    printf("\nSuzy's Fish:\n");
    listFish(Suzy.bucket, (int)Suzy.numFish);
    printf("\nFish in the pond:\n");
    listFish(pond.fish, (int)pond.numFish);
    
    return 0;
}
//add fish to the pond
int addFish(Pond *p, unsigned char size, char *species){
    int pSize = 0;
    if (p->numFish != 0){
        pSize = (int) p->numFish; //convert numFish to an int
    }
    if (pSize == POND_CAPACITY){ //if the pond is at capacity then return 0
        return 0;
    }
    //if the pond is not at capacity then add a fish to it by setting the fish's attributes
    p->fish[pSize].size = size;
    p->fish[pSize].species = species;
    pSize++;
    p->numFish = (char) pSize;
    return 1;
}
//list the fish
void listFish(Fish *arrayOfFish, int n){
    for (int i=0; i<n; i++){
        printf("%d cm %s\n", (int)arrayOfFish[i].size, arrayOfFish[i].species); //print out the contents of the array
    }
}
//check if a fisher likes a particular fish
char likes(Fisher *fisher, Fish *f){
    //if the size of the fish is >= the keepsize of the fish is not a Sunfish then return 1, otherwise return 0
    if (((int)f->size >= (int)fisher->keepSize) && f->species!="Sunfish"){
        return 1;
    }
    return 0;
}
//function that adds fish to the bucket
int keep(Fisher *fisher, Fish *f){
    int pSize = 0;
    if (fisher->numFish != 0){
        pSize = (int) fisher->numFish; //convert numFish to an int
    }
    if (pSize == BUCKET_SIZE){ //if the bucket is at capacity then return 0
        return 0;
    }
    //if the bucket is not at capacity then add a fish to it by setting the fish's attributes
    fisher->bucket[pSize].size = f->size;
    fisher->bucket[pSize].species = f->species;
    pSize++;
    fisher->numFish = (char) pSize;
    return 1;
}
//simulate casting a line
int castLine(Fisher *fisher, Pond *p){
    //if the pond is empty, return 0
    if (((int)p->numFish) == 0){
        return 0;
    }
    int nF = (int) p->numFish;
    //create a random index
    int rIndex = rand() % nF;
    
    char l = likes(fisher, &(p->fish[rIndex]));
    if (l){ //see if the fisher likes fish at the random index
        int k = keep(fisher, &(p->fish[rIndex])); 
        if (k){ //see if the fisher wants to keep it
            if (rIndex != nF-1){ //if the random index is not the last index, set the value at the random index to the value at the last index
                p->fish[rIndex] = p->fish[nF-1];
            }
            nF--;
            p->numFish = (char) nF;
        }   
    }
    return 1;
}
//function that gices away fisher 1's fish to fisher 2 or returns them to the pond
void giveAwayFish(Fisher *fisher1, Fisher *fisher2, Pond *p){
    int nF1 = (int) fisher1->numFish;
    for (int i=0; i<nF1; i++){
        if (likes(fisher2, &(fisher1->bucket[i]))){ //see if the fisher likes fish 
            if ((keep(fisher2, &(fisher1->bucket[i]))) == 0){ //see if the fisher wants to keep it
                addFish(p, fisher1->bucket[i].size, fisher1->bucket[i].species); //if not then add the fish to the pond
            }
        }
        else{
           addFish(p, fisher1->bucket[i].size, fisher1->bucket[i].species); //if not then add the fish to the pond
        }
    }
    fisher1->numFish = 0; //set the number of fish in fisher 1's bucket to 0
}
