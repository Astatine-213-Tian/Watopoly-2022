#include <iostream>
#include "tuition.h"
#include "player.h"

using namespace std;

Tuition::Tuition() : NonProperty{"TUITION"} {}

void Tuition::passBy(Player &p) {}

void Tuition::landOn(Player &p) {
    int ans;
    cout << "Please choose a way to pay your tuition." << endl;
    cout << "Enter 1 to pay $300. \nEnter 2 to pay 10\% of your total asset." << endl;
    cin >> ans;
    if (ans == 1) {
        if(!p.payMoney(300)) {
            // bankrupt
        }
    } else if (ans == 2) {
        // TODO calculate total asset
//        float total = p.calculateAssetsValue();
//        if(!p.payMoney(total * 0.1)) // bankrupt
    }
}