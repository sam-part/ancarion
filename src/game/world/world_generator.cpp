#include "world_generator.h"

#include <windows.h>
#include <iostream>

World WorldGenerator::Generate()
{
    // Temporary code to test
    ChangeStage("Stage 1", 10);
    Sleep(500);
    ChangeStage("Stage 2", 20);
    Sleep(500);
    ChangeStage("Stage 3", 30);
    Sleep(500);
    ChangeStage("Stage 4", 40);
    Sleep(500);
    ChangeStage("Stage 5", 50);
    Sleep(500);
    ChangeStage("Stage 6", 60);
    Sleep(500);
    ChangeStage("Stage 7", 70);
    Sleep(500);
    ChangeStage("Stage 8", 80);
    Sleep(500);
    ChangeStage("Stage 9", 90);
    Sleep(500);
    ChangeStage("Stage 10", 100);
    return World();
}

void WorldGenerator::ChangeStage(std::string message, int percent_finished)
{
    current_stage = { message, percent_finished };

    stage_mutex.lock();
    stage_changed = true;
    stage_mutex.unlock();
}

bool WorldGenerator::StageChanged()
{
    bool was_stage_changed = stage_changed;

    stage_mutex.lock();
    stage_changed = false;
    stage_mutex.unlock();

    return was_stage_changed;
}

WorldGenerationStage WorldGenerator::GetCurrentStage()
{
    return current_stage;
}
