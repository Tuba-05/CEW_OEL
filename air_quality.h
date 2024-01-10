#ifndef AIR_QUALITY_H
#define AIR_QUALITY_H

// Functions to calculate SO2:
int compare_so2(float value){
    printf("%f",value);
    if (value <= 350) {
        return value; // Value is between 0.1 and 350 (inclusive)
    } else {
        return -1; // Value is outside the specified range
    }
}

// Function to compare NO:
int compare_no(float value) {
    if (value >= 0.1 && value <= 100) {
        return value; // Value is between 0.1 and 100 (inclusive)
    } else {
        return -1; // Value is outside the specified range
    }
}

// Functions to calculate O3:
int compare_o3(float value) {
    if (value <= 180) {
        return value; // Value is between 0.1 and 180 (inclusive)
    } else {
        return -1; // Value is outside the specified range
    }
}


#endif 
