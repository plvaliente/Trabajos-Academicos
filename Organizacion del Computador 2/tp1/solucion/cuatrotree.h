#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/** Estructuras **/

#define NODESIZE 3

typedef struct ctTree_t {
  struct ctNode_t* root; //8
  uint32_t size; // 4
} __attribute__((__packed__)) ctTree; //TOTAL 12

typedef struct ctNode_t {
  struct ctNode_t* father; //8
  uint32_t value[NODESIZE]; //12
  uint8_t len; //1
  struct ctNode_t* child[NODESIZE+1]; //32
} __attribute__((__packed__)) ctNode; //TOTAL 53

typedef struct ctIter_t {
  ctTree* tree; //8
  struct ctNode_t* node; //8
  uint8_t current; //1
  uint32_t count; //4
} __attribute__((__packed__)) ctIter; //TOTAL 21


/** Funciones de CuatroTree **/

extern void ct_new(ctTree** pct);

extern void ct_delete(ctTree** pct);

void ct_add(ctTree* ct, uint32_t value);

extern void ct_print(ctTree* ct, FILE *pFile);


/** Funciones de Iterador de CuatroTree **/

extern ctIter* ctIter_new(ctTree* ct);

extern void ctIter_delete(ctIter* ctIt);

extern void ctIter_first(ctIter* ctIt);

extern void ctIter_next(ctIter* ctIt);

extern uint32_t ctIter_get(ctIter* ctIt);

extern uint32_t ctIter_valid(ctIter* ctIt);

