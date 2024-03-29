#pragma once

#include "features/features.h"
#include "ll/api/reflection/Dispatcher.h"

namespace lo {
using ll::reflection::Dispatcher;
struct Config {

    int version = 7;

    struct {
        Dispatcher<bool, moving_block_fix::MovingBlockFix> fixMovingBlock = true;
        Dispatcher<bool, hopper_item_fix::HopperItemFix>   fixHopperItem  = true;
        Dispatcher<bool, chunk_leak_fix::ChunkLeakFix>     fixChunkLeak   = true;
        Dispatcher<bool, seen_percent_opt::SeenPercentOpt> optSeenPercent = true;
        struct {
            Dispatcher<bool, push_entity_opt::PushEntityOpt> enable              = true;
            bool                                             disableVec0Push     = true;
            int                                              maxPushTimes        = -1;
            bool                                             unlimitedPlayerPush = false;
        } optPushEntity{};
    } features{};
    struct {
        bool timingCommand = true;
    } commands{};
};

} // namespace lo
