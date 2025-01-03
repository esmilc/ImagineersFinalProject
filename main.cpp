#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <chrono>
using namespace std;

#include "file_parsing.h"
#include "BPlusTree.h"
#include "heap.h"
#include "user_io.h"
#include "build_sequence_heap.h"

map<string, string> rideMap = { //key is user friendly value is file name
        {"Aladdin", "aladdin.csv"},
        {"Astro Orbiter", "astro_orbiter.csv"},
        {"Barnstormer", "barnstormer.csv"},
        {"Big Thunder Mountain", "big_thunder_mountain.csv"},
        {"Buzz Lightyear", "buzz_lightyear.csv"},
        {"Carousel Of Progress", "carousel_of_progress.csv"},
        {"Dumbo", "dumbo.csv"},
        {"Enchanted Tales With Belle", "enchanted_tales_with_belle.csv"},
        {"Haunted Mansion", "haunted_mansion.csv"},
        {"Jungle Cruise", "jungle_cruise.csv"},
        {"Laugh Floor", "laugh_floor.csv"},
        {"Little Mermaid", "little_mermaid.csv"},
        {"Mad Tea Party", "mad_tea_party.csv"},
        {"Meet Ariel", "meet_ariel.csv"},
        {"Meet Cinderella", "meet_cinderella.csv"},
        {"Meet Daring Disney Pals", "meet_daring_disney_pals.csv"},
        {"Meet Dashing Disney Pals", "meet_dashing_disney_pals.csv"},
        {"Meet Mickey", "meet_mickey.csv"},
        {"Meet Princess Tiana", "meet_princess_tiana.csv"},
        {"Mickeys Philharmagic", "mickeys_philharmagic.csv"},
        {"Peoplemover", "peoplemover.csv"},
        {"Peter Pan", "peter_pan.csv"},
        {"Pirates Of The Caribbean", "pirates_of_the_caribbean.csv"},
        {"Prince Charming Carousel", "prince_charming_carousel.csv"},
        {"Railroad Fantasy Land", "railroad_fantasy_land.csv"},
        {"Railroad Frontier Land", "railroad_frontier_land.csv"},
        {"Railroad Main Street Usa", "railroad_main_street_usa.csv"},
        {"Small World", "small_world.csv"},
        {"Space Mountain", "space_mountain.csv"},
        {"Swiss Family Treehouse", "swiss_family_treehouse.csv"},
        {"Tiki Room", "tiki_room.csv"},
        {"Tomorrowland Speedway", "tomorrowland_speedway.csv"},
        {"Tron Light Cycle", "tron_light cycle.csv"},
        {"Winnie The Pooh", "winnie_the_pooh.csv"}
};

string rideKeys[] = {
        "Aladdin",
        "Astro Orbiter",
        "Barnstormer",
        "Big Thunder Mountain",
        "Buzz Lightyear",
        "Carousel Of Progress",
        "Dumbo",
        "Enchanted Tales With Belle",
        "Haunted Mansion",
        "Jungle Cruise",
        "Laugh Floor",
        "Little Mermaid",
        "Mad Tea Party",
        "Meet Ariel",
        "Meet Cinderella",
        "Meet Daring Disney Pals",
        "Meet Dashing Disney Pals",
        "Meet Mickey",
        "Meet Princess Tiana",
        "Mickeys Philharmagic",
        "Peoplemover",
        "Peter Pan",
        "Pirates Of The Caribbean",
        "Prince Charming Carousel",
        "Railroad Fantasy Land",
        "Railroad Frontier Land",
        "Railroad Main Street Usa",
        "Small World",
        "Space Mountain",
        "Swiss Family Treehouse",
        "Tiki Room",
        "Tomorrowland Speedway",
        "Tron Light Cycle",
        "Winnie The Pooh"
};

// string daysInMonth[32] = { //Converts numeric date to date of month for 03/23
//     "NOT A DAY(0)","Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
//     "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
//     "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday",
//     "Thursday", "Friday", "Saturday", "Sunday", "Monday",
//     "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",
//     "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"
// };

//Remmember to delete before turning in (lines under) #FIXME
//IMPORTANT: Currently, I am implementing it so the user inputs a day and I'll get the data from that day. I'm doing this for
//simplification, if need be to make it different shouldn't be that much of a change.

void scheduleUsingTree(int numRides, int arrivalTime, unordered_map<string, BPlusTree*>& trees) {

    vector<pair<RideNode, int>> times;
    unordered_set<string> rode;

    int time = arrivalTime;
    int count = 0;
    while(true) {
        int min = 10000;
        RideNode minNode;
        for(auto tree : trees) {
            if(rode.find(tree.second->src->data[0].name) == rode.end()) {
                RideNode searchVal = tree.second->search(tree.second->src, time);
                if(searchVal.waitTime < min) {
                    min = searchVal.waitTime;
                    minNode = searchVal;
                }
            }
        }

        times.emplace_back(minNode, time);
        rode.insert(minNode.name);
        time += min + 6;
        count++;
        if(time > 1260 || count == numRides) {
            break;
        }
    }

    int x = 1;
    for(const auto& r : times) {
        cout << x << ". " << r.first.name << " at " << minutesToStandard(r.second) << " (wait time of " << r.first.waitTime << " mins)" << endl;
        x++;
    }
}

int main() {

    pair<int, vector<string>> filesToParsePair = printWelcomeMessage(rideMap, rideKeys); //This will take in the user inputs for the arrival time and vector of rides they will ride

    string date = getDate(); //This is responsible for grabbing date that user will ride

    cout << "Working to make your perfect day..." << endl << endl;

    unordered_map<string, BPlusTree*> rideTrees;

    int numRides = 0; //Backend: This is for me to be able to continue grabbing from min heap until all rides
    for (const auto & i : filesToParsePair.second) { //This is the logic for grabbing correct files and parsing through them.
        rideTrees[i] = new BPlusTree(i);
        parseFileInTree(i, "2024-03-" + date, *rideTrees[i]);
        numRides++;
    }

    cout << "Schedule Using B+ Tree" << endl;
    chrono::time_point<std::chrono::high_resolution_clock> start1 = chrono::high_resolution_clock::now();
    scheduleUsingTree(numRides, filesToParsePair.first, rideTrees);
    chrono::time_point<std::chrono::high_resolution_clock> end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed1 = end1 - start1;
    cout << "Great news! It only took our B+ Tree method " << elapsed1.count() << " seconds to make your itinerary!" << endl;

    for(auto x : rideTrees) {
        delete x.second;
    }
    cout << endl << endl;


    MinHeap heap; //Creation of heap

    numRides = 0; //Backend: This is for me to be able to continue grabbing from min heap until all rides
    for (const auto & i : filesToParsePair.second) { //This is the logic for grabbing correct files and parsing through them.
        parseFileInHeap(i, "2024-03-" + date, heap);
        numRides ++;
    }

    cout << "Schedule Using Heap" << endl;
    chrono::time_point<std::chrono::high_resolution_clock> start2 = chrono::high_resolution_clock::now();
    printSequenceUsingMinHeap(heap, numRides, filesToParsePair.first); //This is the logic for grabbing the sequence
    chrono::time_point<std::chrono::high_resolution_clock> end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed2 = end2 - start2;
    cout << "Great news! It only took our MinHeap method " << elapsed2.count() << " seconds to make your itinerary!" << endl;

    return 0;
}