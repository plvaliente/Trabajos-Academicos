#include "cuatrotree.h"
typedef int bool;
#define true 1
#define false 0

bool validValue(ctNode* currNode, uint32_t newVal){
	ctNode* node = currNode;
	int validxC;
	bool noEsta = true;
	bool esNULL = false;
	while( noEsta && !(esNULL) ){
		if(node->len ==1 && node->value[0] == newVal ){
			noEsta = false;
		}
		else if( node->len == 2 && (node->value[0] == newVal || node->value[1] == newVal) ){
			noEsta = false;
		}
		else if( node->len == 3 && (node->value[0] == newVal || node->value[1] == newVal || node->value[2] == newVal) ){
			noEsta = false;
		}
		else{
			if(newVal < node->value[0]){
				validxC = 0;
			}
			else{
				if(newVal < node->value[1]){
					validxC = 1;
				}
				else{
					if(newVal < node->value[2]){
						validxC = 2;
				}
					else{
						validxC = 3;
					}
				}
			}
			node = node->child[validxC];
			if(node == NULL){
				esNULL = true;
			}	
		}	
	}
	return (noEsta || esNULL);
}
ctNode* ct_aux_search(ctNode* currNode, ctNode* fatherNode, uint32_t newVal){
	ctNode* result = currNode;
	int validxC;
	while( result->len == 3 ){
		//Entonces no tengo lugar en el nodo parametro
		if(newVal < result->value[0]){
			validxC = 0;
		}
		else{
			if(newVal < result->value[1]){
				validxC = 1;
			}
			else{
				if(newVal < result->value[2]){
					validxC = 2;
			}
				else{
					validxC = 3;
				}
			}
		}
		fatherNode = result;
		result = result->child[validxC];
		if(result == NULL){
			//compruebo que sea distinto a null, si es null creo nuevo nodo y lo conecto
			ctNode* nuevo = (ctNode*)malloc ( sizeof(ctNode) );
			nuevo->father = fatherNode;
			nuevo->len = 0;
			for (int i = 0; i < NODESIZE ; i++){
				nuevo->value[i] = 0;
			}
			for (int i = 0; i < NODESIZE+1 ; i++){
				nuevo->child[i] = NULL ;
			}
			fatherNode->child[validxC] = nuevo;
			result = nuevo;
		}	
	}//si no entro al while tengo lugar en el nodo apuntado apuntado
	return result;
}

void ct_aux_fill(ctNode* currNode, uint32_t newVal){
	uint32_t acc;
	if(currNode->len == 0){
		currNode->value[0] = newVal;
	}
	else{
			if(newVal < currNode->value[0]){
				acc = currNode->value[1];
				currNode->value[1] = currNode->value[0];
				currNode->value[0] = newVal;
				currNode->value[2] = acc;
			}
			else{
					
				if(newVal < currNode->value[1] || currNode->len == 1){

					acc = currNode->value[1];
					currNode->value[1] = newVal;
					currNode->value[2] = acc;
				}
				else{
					currNode->value[2] = newVal;
				}
			}	
		}	
	currNode->len++;
}

void ct_add(ctTree* ct, uint32_t newVal) {
	if(ct->root == NULL){
		ctNode* nuevo = (ctNode*)malloc ( sizeof(ctNode) );
		nuevo->father = NULL;
		for (int i = 0; i < NODESIZE ; i++){
			nuevo->value[i] = 0;
		}
		nuevo->len = 0;
		for (int i = 0; i < NODESIZE+1 ; i++){
			nuevo->child[i] = NULL ;
		}
		ct->root = nuevo;
	}
	bool add = validValue(ct->root, newVal);
	if(add){
		ctNode* node = ct_aux_search(ct->root, ct->root->father, newVal);
		ct_aux_fill(node, newVal);
		ct->size++;
	}
}