#include <stdbool.h>

bool not(bool a){
    return !a;
}

bool and(bool a,bool b) {
    return a && b;
}

bool or (bool a, bool b){
    return a || b;
}

bool xor (bool a, bool b){
    return ((a && !b) || (!a && b)); // equivalence taken from logic lecture 4
}

bool impl (bool a, bool b){
    return (!a || b); // equivalence taken from logic lecture 4
}
bool eq (bool a, bool b){
    return a==b;
}