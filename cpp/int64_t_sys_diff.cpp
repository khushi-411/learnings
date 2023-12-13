// https://github.com/lcompilers/lpython/blob/main/src/libasr/runtime/lfortran_intrinsics.c
// here, I used PRTd64, they are using Macros named as: "HAVE_LFORTRAN_MACHO"
// https://godbolt.org/z/ba3vdTxeh


#include <iostream>
#include <inttypes.h>  // to remove msvc compiler warnings

#define MAXUNITS 1000


struct UNIT_FILE {
    int32_t unit;
    FILE* filep;
    bool unit_file_bin;
};


int32_t last_index_used = -1;

struct UNIT_FILE unit_to_file[MAXUNITS];


FILE* get_file_pointer_from_unit(int32_t unit_num, bool *unit_file_bin) {
    for( int i = 0; i <= last_index_used; i++ ) {
        if( unit_to_file[i].unit == unit_num ) {
            *unit_file_bin = unit_to_file[i].unit_file_bin;
            return unit_to_file[i].filep;
        }
    }
    return NULL;
}


void read(int64_t *p, int32_t unit_num) {
    if (unit_num == -1) {
        scanf("%" PRId64, p);  // use "PRId64 to remove compiler warnings
        return;
    }
    bool unit_file_bin;
    FILE* filep = get_file_pointer_from_unit(unit_num, &unit_file_bin);
    if (!filep) {
        printf("No file found with given unit\n");
        exit(1);
    }

    if (unit_file_bin) {
        fread(p, sizeof(*p), 1, filep);
    } else {
        fscanf(filep, "%" PRId64, p);  // use "PRId64 to remove compiler warnings
    }
}


int main() {
    return 0;
}
