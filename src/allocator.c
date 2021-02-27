#include "allocator.h"

cslist_t* allocate_n_buildings(size_t n, int building_type, bool fw_random) {
    cslist_t* ret = cslist_alloc(n);
    cslist_t* cursor = ret;
    for(size_t i=0;i<n;i++) {
        void* item;
        switch (building_type)
        {
        case BLDG_TYPE_COMMERCIAL:
            item = create_commercial_building(i, fw_random);
            cursor->item = item;
            break;
        case BLDG_TYPE_RESIDENTIAL:
            item = create_residential_building(i, fw_random);
            cursor->item = item;
            break;
        case BLDG_TYPE_INDUSTRIAL:
            item = create_industrial_building(i, fw_random);
            cursor->item = item;
            break;
        default:
            exit(3);
            break;
        }
        
        cursor->next = NULL;
        if(i<n-1) {
            cslist_t* tmp = cursor;
            cursor++;
            tmp->next = cursor;
        }
    }
    return ret;
}