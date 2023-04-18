#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 1024 // Define block size in bytes

typedef struct block {
    char data[BLOCK_SIZE]; // Data block
    struct block *next; // Pointer to next block
} Block;

int main(int argc, char *argv[]) {
    FILE *input_file = fopen(argv[1], "rb");
    if (input_file == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    Block *first_block = NULL;
    Block *prev_block = NULL;

    while (!feof(input_file)) {
        Block *new_block = malloc(sizeof(Block)); // Allocate memory for new block
        if (new_block == NULL) {
            printf("Error allocating memory for block.\n");
            return 1;
        }
        fread(new_block->data, 1, BLOCK_SIZE, input_file); // Read file into block

        new_block->next = NULL; // Set next pointer to NULL for now

        if (prev_block != NULL) {
            prev_block->next = new_block; // Link previous block to new block
        }
        else {
            first_block = new_block; // Set first block to new block
        }

        prev_block = new_block; // Set previous block to new block
    }

    // Traverse linked list and print block data
    Block *current_block = first_block;
    int block_num = 0;
    while (current_block != NULL) {
        printf("Block %d: %s\n", block_num, current_block->data);
        current_block = current_block->next;
        block_num++;
    }

    // Free memory used by linked list
    current_block = first_block;
    while (current_block != NULL) {
        Block *next_block = current_block->next;
        free(current_block);
        current_block = next_block;
    }

    fclose(input_file); // Close input file
    return 0;
}
