#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;
char slot[20];

char get_block(void)
{
    char block;
    cout << "Enter one block: ";
    cin >> block;
    return toupper(block);
}
//
// Function print_slots
// Prints the contents of the slots array in a well formatted form.
// Input: Array of slots
// Returns: Nothing (void)
//
// Example function call: print_slots(slot_array);

void print_slots(char slots[])
{
    unsigned int j = 1;
    for (j = 1; j <= 20; j++)
    {
        cout << setw(3) << j;
    }
    cout << endl;
    for (j = 0; j < 20; j++)
    {
        cout << setw(3) << slots[j];
    }
    cout << endl;
}

// Function put_block
// This function stores a character into the character array representing the slots
//
// Inputs:
// block - type char - The character to be inserted into a slot
// position - type unsigned int - index of the slot where the block will go
// array - type char - array of slots containing the blocks
//
// Returns:
// position - type unsigned int - the index of the slot where the block was placed
//
// Example function call: 	put_block(block, position, slots);

unsigned int put_block(char block, unsigned int position, char array[])
{
    bool debug = true;
    array[position] = block;
    if (debug)
        cout << "Block " << block << " inserted into slot " << position + 1 << endl;
    return position;
}

// Function remove_block
// This function removes a block from the slot array
// The slot where the block is removed is then set to a space
//
// Inputs:
// position - type unsigned int - index of the slot where block is located
// array - type char - array of slots containing the blocks
//
// Returns:
// block - type char - the block removed from the slot
//
// Example function call: 	remove_block(position, slots);

unsigned int remove_block(unsigned int position, char array[])
{
    bool debug = true;
    char block = ' ';
    block = array[position];
    array[position] = ' ';  // Reset slot to blank after block removed
    if (debug)
        cout << "Block " << block << " removed from slot " << position + 1 << endl;
    return block;
}


// Function shift_right
// This function increments the index simulating a movement of the robot
// to the next higher slot (index) of the array
//
// Inputs:
// position - type unsigned int - current slot position
//
// Returns:
// position - type unsigned int - The updated position which is input position + 1
//
// Example function call:  position = shift_right(position)
//

unsigned int shift_right(unsigned int position)
{
    bool debug = true;
    position++;
    if (debug)
        cout << "Position right shifted to " << position << endl;
    return position;
}

// Function shift_left
// This function decrements the index simulating a movement of the robot
// to the next lower slot (index) of the array
//
// Inputs:
// position - type unsigned int - current slot position
//
// Returns:
// position - type unsigned int - The updated position which is input position - 1
//
// Example function call: position = shift_left(position)
//

unsigned int shift_left(unsigned int position)
{
    bool debug = true;
    position--;
    if (debug)
        cout << "Position left shifted to " << position << endl;
    return position;
}

// Function robot_ltoreq_slot
// This function compares the value of the block held by the robot
// with the value of the block in a slot
//
// Inputs:
// robot - type char - value of block held by robot
// in_slot - type char - value of block in the slot
//
// Returns:
// true or false
// TRUE if block held by robot is LESS than or equal to the block in slot
// FALSE if block held by robot is GREATER than block in slot
//
// Example function call: if ( compare_blocks(robot_block, slot_block) )
//

bool robot_ltoreq_slot(char robot, char in_slot)
{
    bool debug = true;
    if (debug)
        cout << endl <<  "Comparing robot block " << robot << " with block in slot " << in_slot << endl;
    if (robot <= in_slot)
    {
        if (debug)
            cout << "Returning true. Robot block LESS than or EQUAL to block in slot. " << endl;
        return true;
    }
    else
    {
        if (debug)
            cout << "Returning false. Robot block GREATER than block in slot. " << endl;
        return false;
    }
}
// This function checks if the blocks are less than or == to the block in the robots hand
// If the block is equal to it return TRUE if the block is < it return FALSE

bool robot_equal_slot(char robot, char in_slot)
{
    bool debug = true;
    if (debug)
        cout << endl <<  "Comparing robot block " << robot << " with block in slot " << in_slot << endl;
    if (robot == in_slot)
    {
        if (debug)
            cout << "Returning true. Robot block EQUAL to block in slot. " << endl;
        return true;
    }
    else
    {
        if (debug)
            cout << "Returning false. Robot block LESS THAN than block in slot. " << endl;
        return false;
    }
}

// Function switch_blocks
// This function switches the block held by the robot with a block in a slot.
// After the switch the robot is holding the block removed from the slot.
//
// Inputs:
// robot - type char - The block to be inserted into a slot
// position - type unsigned int - index of the slot where the block will go
// array - type char - array of slots containing the blocks
//
// Returns:
// robot - type char. The value of the block removed from the slot.
//
// Example function call: block = switch_blocks(block,  position, array);
//

char switch_blocks(char robot, unsigned int position, char array[])
{
    char temp_hold;
    bool debug = true;
    if (debug)
        cout << "Switching blocks " << robot << " with " << array[position] << endl;
    temp_hold = robot;
    robot = array[position];
    array[position] = temp_hold;
    return robot;
}
// Function test_empty
// This function tests the array to determine if a slot is empty (NULL)
// or if the slot contains a blank. The slot array must be intialized to
// all NULL or all blanks (spaces) before any blocks are added.
//
// Inputs:
// position - type unsigned int - index of slot to be tested
//
// Returns:
// true or false as value o function
// TRUE if slot is empty
// FALSE if the slot contains a block
//
// Example function call: if ( test_empty(index, array) )
//


bool test_empty(unsigned int position, char array[])
{
    char blank = ' '; // Blank space
    bool debug = true;
    if  (array[position] == NULL || array[position] == blank)
    {
        if (debug)
            cout << "Slot " << position << " empty. " << endl;
        return true;
    }
    else
    {
        if (debug)
            cout << "Slot " << position << " contains a block " << endl;
        return false;
    }

}

char shift_all_left(char array[],int position, char block){
    int i = position;
    char temp_block = block;
    block = NULL;
    while(i >= 0){
        block = switch_blocks(block,i,array);
        shift_left(i);
        i--;
    }
    return temp_block;
}

char shift_all_right(char array[],int position, char block){
    int i = position;
    char temp_block = block;
    block = NULL;
    while(i <= 19){
        block = switch_blocks(block,i,array);
        shift_right(i);
        i++;
    }
    return temp_block;
}

char get_block_testone(void)
{
    static unsigned int index = 0;
    char test_case_one[21] = "AXFIUTRPQVWSEYJINYTB";
    return test_case_one[index++];
}


int main() {
    //char block = get_block();
    char block;
    int counter = 0;
    bool shift_status = false;
    //Initialize every slot to NULL in the array
    for (int i = 0; i < 20; i++) {
        slot[i] = NULL;
    }

    //Put the first block from the chute INTO SLOT 10(hardware restriction)

    do {
        block = get_block_testone();
        shift_status = false;
        if (counter == 0) {
            put_block(block, 10, slot);
        }
        if (block < slot[10] || block == slot[10] && counter !=
                                                     0) { // This section of the code handles if the block is less than the block in the middle
            for (int i = 10; i >= 0; i--) {
                if ((block > slot[i])) {
                    shift_all_left(slot, i, block);
                    put_block(block, i, slot);
                    break;
                } else if (slot[i] == NULL) {
                    put_block(block, i, slot);
                } else if (!(test_empty(0, slot))) {
                    for (int j = 0; j <= 10; j++) {
                        if (block <= slot[j]) {
                            shift_all_right(slot, j, block);
                            put_block(block, j, slot);
                            shift_status = true;
                            break;
                        }
                    }
                }
                if (shift_status) {
                    break;
                }
            }
        }

        if (block > slot[10] &&
            counter != 0) { //This section of the code handles if the block is greater than the block in the middle
            for (int i = 10; i <= 19; i++) {
                if ((block <= slot[i]) && (block > slot[i - 1])) {
                    shift_all_right(slot, i, block);
                    put_block(block, i, slot);
                    break;
                } else if (slot[i] == NULL) {
                    put_block(block, i, slot);
                    break;
                } else if (!(test_empty(19, slot))) {
                    for (int k = 19; k >= 10; k--) {
                        if (block >= slot[k]) {
                            shift_all_left(slot, k, block);
                            put_block(block, k, slot);
                            shift_status = true;
                            break;
                        }
                    }
                    if (shift_status) {
                        break;
                    }
                }
            }
        }

        counter++;
        print_slots(slot);
    } while (counter <= 19);
    return 0;
}
