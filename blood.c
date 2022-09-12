#include "blood.h"
#include "stdio.h"


const blood_result_t bl_res_a_a = {
    .possible_blood_type_count = 2,
    .possible_blood_type = {BLOODTYPE_A, BLOODTYPE_O},
    .possible_gene_type_count = 2,
    .possible_gene_types = {BLOODGENE_AA, BLOODGENE_AO , BLOODGENE_OO}
};

const blood_result_t bl_res_b_b = {
    .possible_blood_type_count = 1,
    .possible_blood_type = {BLOODTYPE_B, BLOODTYPE_O},
    .possible_gene_type_count = 2,
    .possible_gene_types = {BLOODGENE_BB, BLOODGENE_BO, BLOODGENE_OO}
};

const blood_result_t bl_res_a_b = {
    .possible_blood_type_count = 4,
    .possible_blood_type = {BLOODTYPE_A, BLOODTYPE_B , BLOODTYPE_AB , BLOODTYPE_O},
    .possible_gene_type_count = 4,
    .possible_gene_types = {BLOODGENE_AB, BLOODGENE_AO, BLOODGENE_BO , BLOODGENE_OO}
};

const blood_result_t bl_res_a_o = {
    .possible_blood_type_count = 2,
    .possible_blood_type = {BLOODTYPE_A, BLOODTYPE_O},
    .possible_gene_type_count = 2,
    .possible_gene_types = {BLOODGENE_AO, BLOODGENE_OO}
};

const blood_result_t bl_res_b_o = {
    .possible_blood_type_count = 2,
    .possible_blood_type = {BLOODTYPE_B, BLOODTYPE_O},
    .possible_gene_type_count = 2,
    .possible_gene_types = {BLOODGENE_BO, BLOODGENE_OO}
};

const blood_result_t bl_res_ab_o = {
    .possible_blood_type_count = 2,
    .possible_blood_type = {BLOODTYPE_A, BLOODTYPE_B},
    .possible_gene_type_count = 2,
    .possible_gene_types = {BLOODGENE_AO, BLOODGENE_BO}
};

const blood_result_t bl_res_ab_ab = {
    .possible_blood_type_count = 3,
    .possible_blood_type = {BLOODTYPE_A, BLOODTYPE_AB, BLOODTYPE_B},
    .possible_gene_type_count = 1,
    .possible_gene_types = {BLOODGENE_AA, BLOODGENE_BB, BLOODGENE_AB}
};

const blood_result_t bl_res_o_o = {
    .possible_blood_type_count = 1,
    .possible_blood_type = {BLOODTYPE_O},
    .possible_gene_type_count = 1,
    .possible_gene_types = {BLOODGENE_OO}
};

const blood_result_t bl_res_a_ab = {
    .possible_blood_type_count = 2,
    .possible_blood_type = {BLOODTYPE_A, BLOODTYPE_AB},
    .possible_gene_type_count = 2,
    .possible_gene_types = {BLOODGENE_AA, BLOODGENE_AB}
};

const blood_result_t bl_res_b_ab = {
    .possible_blood_type_count = 2,
    .possible_blood_type = {BLOODTYPE_B, BLOODTYPE_AB},
    .possible_gene_type_count = 2,
    .possible_gene_types = {BLOODGENE_BB, BLOODGENE_AB}
};

blood_result_t* calculate_blood(blood_type_t father, blood_type_t mother){
    switch(father){
        case BLOODTYPE_A:
            switch(mother){
                case BLOODTYPE_A:
                    return (blood_result_t*)&bl_res_a_a;
                case BLOODTYPE_B:
                    return (blood_result_t*)&bl_res_a_b;
                case BLOODTYPE_AB:
                    return (blood_result_t*)&bl_res_a_ab;
                case BLOODTYPE_O:
                    return (blood_result_t*)&bl_res_a_o;
            }
        case BLOODTYPE_B:
            switch(mother){
                case BLOODTYPE_A:
                    return (blood_result_t*)&bl_res_a_b;
                case BLOODTYPE_B:
                    return (blood_result_t*)&bl_res_b_b;
                case BLOODTYPE_AB:
                    return (blood_result_t*)&bl_res_b_ab;
                case BLOODTYPE_O:
                    return (blood_result_t*)&bl_res_b_o;
            }
        case BLOODTYPE_AB:
            switch(mother){
                case BLOODTYPE_A:
                    return (blood_result_t*)&bl_res_a_ab;
                case BLOODTYPE_B:
                    return (blood_result_t*)&bl_res_b_ab;
                case BLOODTYPE_AB:
                    return (blood_result_t*)&bl_res_ab_ab;
                case BLOODTYPE_O:
                    return (blood_result_t*)&bl_res_ab_o;
            }
        case BLOODTYPE_O:
            switch(mother){
                case BLOODTYPE_A:
                    return (blood_result_t*)&bl_res_a_o;
                case BLOODTYPE_B:
                    return (blood_result_t*)&bl_res_b_o;
                case BLOODTYPE_AB:
                    return (blood_result_t*)&bl_res_ab_o;
                case BLOODTYPE_O:
                    return (blood_result_t*)&bl_res_o_o;
            }
    }
    return NULL;
}

uint8_t blood_gene2type(uint8_t gene){
    switch (gene)
    {
    case BLOODGENE_AA:
    case BLOODGENE_AO:
        return BLOODTYPE_A;
        break;
    case BLOODGENE_BB:
    case BLOODGENE_BO:
        return BLOODTYPE_B;
        break;
    case BLOODGENE_AB:
        return BLOODTYPE_AB;
        break;
    case BLOODGENE_OO:
        return BLOODTYPE_O;
        break;
    default:
        return 0;
        break;
    }
}

char* blood_type2str(uint8_t type){
    switch (type)
    {
    case BLOODTYPE_A:
        return "A";
        break;
    case BLOODTYPE_B:
        return "B";
        break;
    case BLOODTYPE_AB:
        return "AB";
        break;
    case BLOODTYPE_O:
        return "O";
        break;
    default:
        return "Unknown";
        break;
    }
}

char* blood_gene2str(uint8_t gene){
    switch (gene)
    {
    case BLOODGENE_AA:
        return "AA";
        break;
    case BLOODGENE_AO:
        return "AO";
        break;
    case BLOODGENE_BB:
        return "BB";
        break;
    case BLOODGENE_BO:
        return "BO";
        break;
    case BLOODGENE_AB:
        return "AB";
        break;
    case BLOODGENE_OO:
        return "OO";
        break;
    default:
        return "Unknown";
        break;
    }
}



void blood_result_format(blood_result_t* result, char* buffer){
    uint8_t len = 0;
    len += sprintf(buffer + len, "blood");
    for (uint8_t i = 0; i < result->possible_blood_type_count; i++)
    {
        len += sprintf(buffer + len, " %s", blood_type2str(result->possible_blood_type[i]));
    }

    len += sprintf(buffer + len, ". gene");
    for (uint8_t i = 0; i < result->possible_gene_type_count; i++)
    {
        len += sprintf(buffer + len, " %s", blood_gene2str(result->possible_gene_types[i]));
    }
}