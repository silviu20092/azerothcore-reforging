/*
 * Credits: silviu20092
 */

#include "ScriptMgr.h"
#include "item_reforge.h"

class mod_reforging_itemscript : public AllItemScript
{
public:
    mod_reforging_itemscript() : AllItemScript("mod_reforging_itemscript") {}

    bool CanItemRemove(Player* player, Item* item) override
    {
        sItemReforge->RemoveReforge(player, item, true);
        return true;
    }
};

void AddSC_mod_reforging_itemscript()
{
    new mod_reforging_itemscript();
}
