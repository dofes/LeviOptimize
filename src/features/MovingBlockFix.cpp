

#include "ll/api/memory/Hook.h"
#include "mc/network/packet/BlockActorDataPacket.h"
#include "mc/world/level/BlockSource.h"
#include "mc/world/level/block/Block.h"
#include "mc/world/level/block/actor/BlockActor.h"
#include "mc/world/level/block/actor/MovingBlockActor.h"


namespace levi_optimize_features::moving_block_fix {
thread_local bool saveDataFlag = true;

LL_AUTO_TYPED_INSTANCE_HOOK(
    BlockActorGetServerUpdatePacketHook,
    ll::memory::HookPriority::Normal,
    BlockActor,
    "?getServerUpdatePacket@BlockActor@@QEAA?AV?$unique_ptr@VBlockActorDataPacket@@U?$default_delete@"
    "VBlockActorDataPacket@@@std@@@std@@AEAVBlockSource@@@Z",
    std::unique_ptr<BlockActorDataPacket>,
    BlockSource* bs
) {
    saveDataFlag = false;
    return origin(bs);
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    MovingBlockActorSaveHook,
    ll::memory::HookPriority::Normal,
    MovingBlockActor,
    "?save@MovingBlockActor@@UEBA_NAEAVCompoundTag@@@Z",
    bool,
    CompoundTag& tag
) {
    if (saveDataFlag) {
        return origin(tag);
    }

    if (!LL_SYMBOL_CALL("?save@BlockActor@@UEBA_NAEAVCompoundTag@@@Z", bool, BlockActor*, CompoundTag&)(this, tag))
        return false;

    Block* block      = ll::memory::dAccess<Block*>(this, 0xC8);
    Block* extraBlock = ll::memory::dAccess<Block*>(this, 0xD0);

    tag.putCompound("movingBlock", block->getSerializationId().clone());
    tag.putCompound("movingBlockExtra", extraBlock->getSerializationId().clone());
    tag.putInt("pistonPosX", ll::memory::dAccess<int>(this, 58 * sizeof(int)));
    tag.putInt("pistonPosY", ll::memory::dAccess<int>(this, 59 * sizeof(int)));
    tag.putInt("pistonPosZ", ll::memory::dAccess<int>(this, 60 * sizeof(int)));
    tag.putBoolean("expanding", ll::memory::dAccess<bool>(this, 244));

    return true;
}
} // namespace levi_optimize_features::moving_block_fix
