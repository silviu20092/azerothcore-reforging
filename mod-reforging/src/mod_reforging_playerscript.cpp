/*
 * Credits: silviu20092
 */

#include "ScriptMgr.h"
#include "DatabaseEnv.h"
#include "Player.h"
#include "item_reforge.h"

class mod_reforging_playerscript : public PlayerScript
{
private:
    class SendReforgePackets : public BasicEvent
    {
    public:
        SendReforgePackets(Player* player) : player(player)
        {
            player->m_Events.AddEvent(this, player->m_Events.CalculateTime(DELAY_MS));
        }

        bool Execute(uint64 /*e_time*/, uint32 /*p_time*/)
        {
            sItemReforge->SendItemPackets(player);
            return true;
        }
    private:
        static constexpr uint64 DELAY_MS = 3000;

        Player* player;
    };
public:
    mod_reforging_playerscript() : PlayerScript("mod_reforging_playerscript",
        {
            PLAYERHOOK_ON_AFTER_MOVE_ITEM_FROM_INVENTORY,
            PLAYERHOOK_ON_DELETE_FROM_DB,
            PLAYERHOOK_ON_LOGIN,
            PLAYERHOOK_ON_APPLY_ITEM_MODS_BEFORE
        }) {}

    void OnAfterMoveItemFromInventory(Player* player, Item* it, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/) override
    {
        sItemReforge->RemoveReforge(player, it, true);
    }

    void OnDeleteFromDB(CharacterDatabaseTransaction trans, uint32 guid) override
    {
        trans->Append("DELETE FROM character_reforging WHERE guid = {}", guid);
        sItemReforge->HandleCharacterRemove(guid);
    }

    void OnLogin(Player* player) override
    {
        new SendReforgePackets(player);
    }

    void OnApplyItemModsBefore(Player* player, uint8 slot, bool apply, uint8 itemProtoStatNumber, uint32 statType, int32& val) override
    {
        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (!item)
            return;

        ItemTemplate const* proto = item->GetTemplate();
        if (!proto || proto->StatsCount == 0)
            return;

        const ItemReforge::ReforgingData* reforging = sItemReforge->GetReforgingData(item);
        if (reforging != nullptr)
        {
            if (itemProtoStatNumber == proto->StatsCount - 1)
                sItemReforge->HandleStatModifier(player, reforging->stat_increase, reforging->stat_value, apply);

            if (statType == reforging->stat_decrease)
                val -= reforging->stat_value;
        }
    }
};

void AddSC_mod_reforging_playerscript()
{
    new mod_reforging_playerscript();
}
