#pragma once

struct MemoryBlock {
	int start;	// start address of the block
	int size;	// size of the block
	int pid;		// -1 if free
	
	MemoryBlock() {};
	MemoryBlock(int sstart, int ssize, int spid) : start(sstart), size(ssize), pid(spid) {};
};
