#include <iostream>
using namespace std;
#include "file_parsing.h"
#include "heap.h"
#include "user_io.h"
#include <set>
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


int main() {

    MinHeap heap;

    cout << "Hello Imagineers!" << endl;
    cout << "Testing Functionality" << endl;


    vector<string> filesToParse = printWelcomeMessage(rideMap);

    string date = getDate();

    cout << "Working to make your perfect day..." << endl;

    int numRides = 0;

    for (const auto & i : filesToParse) {
        parseFileInHeap(i, date, heap);
        numRides ++;
    }

    printSequence(heap, numRides);




    return 0;
}