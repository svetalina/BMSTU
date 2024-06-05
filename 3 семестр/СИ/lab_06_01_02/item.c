#include "item.h"

int item_read(FILE *f, item_t *record)
{
    if (fscanf(f, "%s", record->name) != 1 || \
        fscanf(f, "%f", &(record->mass)) != 1 || \
        fscanf(f, "%f", &(record->volume)) != 1)
        return ERROR_SYMBOL;
        
    if (strlen(record->name) > NAME_SIZE - 2)
        return ERROR_NAME;
    if (record->mass <= 0)
        return ERROR_MASS;
    if (record->volume <= 0)
    {
        return ERROR_VOLUME;
    }
	
    return EXIT_SUCCESS;
}

void item_print(item_t *record)
{
    printf("%s\n", record->name);
    printf("%f\n", record->mass);
    printf("%f\n", record->volume);
}

void item_compare(item_t *record_1, item_t *record_2)
{
    int ro_1 = record_1->mass / record_1->volume;
    int ro_2 = record_2->mass / record_2->volume;
    if (ro_1 > ro_2)
    {
        item_t temp = *record_1;
        *record_1 = *record_2;
        *record_2 = temp;
    }
}
