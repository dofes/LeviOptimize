#pragma once

#include "features/features.h"
#include "ll/api/reflection/Dispatcher.h"

namespace lo {
using ll::reflection::Dispatcher;
struct Config {

    int version = 9;

    struct {
        Dispatcher<bool, moving_block_opt::MovingBlockOpt>                  optMovingBlock  = true;
        Dispatcher<bool, hopper_item_opt::HopperItemOpt>                    optHopperItem   = true;
        Dispatcher<bool, chunk_leak_fix::ChunkLeakFix>                      fixChunkLeak    = true;
        Dispatcher<bool, seen_percent_opt::SeenPercentOpt>                  optSeenPercent  = true;
        Dispatcher<bool, packet_sender_opt::PacketSenderOpt>                packetSenderOpt = true;
        Dispatcher<push_entity_opt::Config, push_entity_opt::PushEntityOpt> optPushEntity{};
    } features{};
    struct {
        bool timingCommand = true;
    } commands{};
};

} // namespace lo
