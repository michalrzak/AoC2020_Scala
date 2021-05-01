#include <iostream>


int main(){
    
    size_t card_pkey {13233401};
    size_t door_pkey {6552760};
//    size_t card_pkey {5764801};
//    size_t door_pkey {17807724};
    
    size_t subject_number_c {7};
    size_t subject_number_d {7};

    size_t loop_size_c {0};
    size_t loop_size_d {0};
    size_t division_value {20201227};
    
    size_t card {1};
    size_t door {1};
    
    while(card != card_pkey){
        card *= subject_number_c;
        card %= division_value;
        ++loop_size_c;
    }
    
    while(door != door_pkey){
        door *= subject_number_d;
        door %= division_value;
        ++loop_size_d;
    }
    
    std::cout << loop_size_c << ' ' << loop_size_d << '\n';    
    std::cout << door << ' ' <<  card << '\n';
    
    subject_number_c = card;
    card = 1;
    for (size_t i {0}; i < loop_size_d; ++i){
        card *= subject_number_c;
        card %= division_value;
    }
    
    subject_number_d = door;
    door = 1;
    for (size_t i {0}; i < loop_size_c; ++i){
        door *= subject_number_d;
        door %= division_value;
    }
    
    std::cout << card << ' ' << door << '\n';
    return 0;
}
