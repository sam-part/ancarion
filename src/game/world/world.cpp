#include "world.h"

ChunkInfo& World::chunk(int x, int y)
{
    return chunks[size.GetIndex_2D(x, y)];
}

const ChunkInfo& World::GetChunk(int x, int y)
{
    return chunks[size.GetIndex_2D(x, y)];
}

const ChunkInfo& World::GetChunk(int index)
{
    return chunks[index];
}

Size World::GetSize()
{
    return size;
}
