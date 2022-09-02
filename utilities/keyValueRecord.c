#include <stdlib.h>
#include "keyValueRecord.h"

record* makeRecord(float key, float value){
	record* r = makeEmptyRecord();
	r->key = key;
	r->value = value;
    return r;
}

record* makeEmptyRecord(){
    record* r = (record*)malloc(sizeof(record));
    r->key = (r->value = -1);
	return r;
}

record* copyAllocateRecord(record *r){
	record* p = makeEmptyRecord();
    copyRecord(p, r);
    return p;
}

void copyRecord(record*p, record *r){
	p->key = r->key;
	p->value = r->value;
}

void destroyRecord(record *r){
	free(r); r=NULL;
}