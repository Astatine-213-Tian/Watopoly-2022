#include <iostream>
#include <unordered_map>
#include "timsLine.h"
#include "player.h"

using namespace std;

void TimsLine::passBy(Player &p) {}

void TimsLine::landOn(Player &p) {
    if (queue.find(&p) == queue.end()) {
        queue[&p] = 1;
    }
    
    if (queue[&p] < 3) {
        char ans;
        cout << "You are stuck in the line..." << endl;
        cout << "What do you choose to get out of this line?" << endl;
        cout << "Enter R for a new roll. \nEnter P for paying $50. \nEnter C for using one Roll Up the Rim Cup." << endl;
        cin >> ans;
        switch (ans) {
        case 'R':
            //roll
            break;
        case 'P':
            if (p.payMoney(50)) {
                queue.erase(&p);
            } else {
                //bankrupt
            } 
            break;
        case 'C':
            if (p.getNumCup() > 0) {
                p.useCup();
                queue.erase(&p);
            } else {
                cout << "You don't have enough cups to use." << endl;
            }
            break;
        default:
            break;
        }
    } else {
        cout << "This is your third round in the line." << endl;
        if (p.getNumCup() == 0) {
            cout << "Please pay $50 to get out of the line." << endl;
            if (p.payMoney(50)) {
                queue.erase(&p);
            } else {
                //bankrupt
            }
        } else {
            char ans;
            cout << "What do you choose to get out of this line?" << endl;
            cout << "Enter P for paying $50. \nEnter C for using one Roll Up the Rim Cup." << endl;
            cin >> ans;
            if (ans == 'P') {
                if (p.payMoney(50)) {
                    queue.erase(&p);
                } else {
                    // bankrupt
                } 
            } else if (ans == 'C') {
                p.useCup();
                queue.erase(&p);
            }
            // bad input
        }
    }
}