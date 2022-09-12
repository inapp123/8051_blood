#include <stdint.h>

typedef enum {
    BLOODTYPE_A = 0,
    BLOODTYPE_B,
    BLOODTYPE_AB,
    BLOODTYPE_O,

    BLOODTYPE_MAX
} blood_type_t;

typedef enum {
    BLOODGENE_AA = 0,
    BLOODGENE_AB,
    BLOODGENE_BB,
    BLOODGENE_OO,
    BLOODGENE_AO,
    BLOODGENE_BO,

    BLOODGENE_MAX
} blood_gene_type_t;

typedef struct
{
    uint8_t possible_blood_type_count;
    blood_type_t possible_blood_type[BLOODTYPE_MAX];
    uint8_t possible_gene_type_count;
    uint8_t possible_gene_types[BLOODGENE_MAX];
} blood_result_t;

blood_result_t* calculate_blood(blood_type_t father, blood_type_t mother);
void blood_result_format(blood_result_t* result, char* buffer);


// extern const blood_result_t bl_res_a_a;
// extern const blood_result_t bl_res_b_b;
// extern const blood_result_t bl_res_a_b;
// extern const blood_result_t bl_res_a_o;
// extern const blood_result_t bl_res_b_o;
// extern const blood_result_t bl_res_ab_o;
// extern const blood_result_t bl_res_ab_ab;
// extern const blood_result_t bl_res_o_o;
// extern const blood_result_t bl_res_a_ab;
// extern const blood_result_t bl_res_b_ab;

