#ifndef KEY_VALUE_RECORD_H
#define KEY_VALUE_RECORD_H

struct s_record
{
	float key;
	float value;
};typedef struct s_record record;

/**
 * @pre 'r' is a valid pointer to a record.
 * @param r the record to be destroyed
 * @post 'r' is no more in the heap.
 */
void destroyRecord(record *r);

/**
 * This functions copies all the fields of 'r' in 'p'
 * @pre 'p' and 'r' are valid and allocated records.
 * @param r the record to be copied
 */
void copyRecord(record *p,record *r);

/**
 * This functions allocate a new record 'p' and copies all the attributes of 'r' in 'p'
 * @pre 'r' is a valid allocated record
 * @param r the record to be copied
 * @return the copied record
 */
record *copyAllocateRecord(record *r);

/**
 * @return a new record with no specific value stored.
 */
record *makeEmptyRecord();

/**
 * @return a new record with (key,value) set
 */
record *makeRecord(float key,float value);

#endif