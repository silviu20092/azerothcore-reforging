/*
 * Credits: silviu20092
 */

#ifndef _ITEM_REFORGE_H_
#define _ITEM_REFORGE_H_

#include "Define.h"

class ItemReforge
{
public:
    struct ReforgingData
    {
        uint32 guid;
        uint32 item_guid;
        uint32 stat_decrease;
        uint32 stat_increase;
        uint32 stat_value;
    };
private:
    static constexpr float PERCENTAGE_MIN = 10.0f;
    static constexpr float PERCENTAGE_MAX = 90.0f;
    static constexpr const char* RED_COLOR = "b50505";
    static constexpr const char* GREEN_COLOR = "056e3a";
    static constexpr uint32 MAX_REFORGEABLE_STATS = 15;
    
    bool enabled;
    std::vector<uint32> reforgeableStats;
    float percentage;

	ItemReforge();
	~ItemReforge();

	typedef std::unordered_map<uint32, ReforgingData> ReforgingDataContainer;

    ReforgingDataContainer reforgingDataMap;

    void CleanupDB() const;

    static std::string TextWithColor(const std::string& text, const std::string& color);
public:
    static constexpr const char* DefaultReforgeableStats = "6,13,14,31,32,36,37";
    static constexpr float PERCENTAGE_DEFAULT = 40.0f;
    static constexpr int VISUAL_FEEDBACK_SPELL_ID = 46331;

	static ItemReforge* instance();

    void SetEnabled(bool value);
    bool GetEnabled() const;
    void SetReforgeableStats(const std::string& stats);
    bool IsReforgeableStat(uint32 stat) const;
    const std::vector<uint32>& GetReforgeableStats() const;
    void SetPercentage(float value);
    float GetPercentage() const;

    void LoadFromDB();

    std::string GetSlotIcon(uint8 slot, uint32 width = 30, uint32 height = 30, int x = 0, int y = 0) const;
    std::string GetSlotName(uint8 slot) const;
    std::string StatTypeToString(uint32 statType) const;

    bool IsReforgeable(const Player* player, const Item* item) const;
    bool IsAlreadyReforged(const Item* item) const;
    Item* GetItemInSlot(const Player* player, uint8 slot) const;
    uint32 CalculateReforgePct(int32 value) const;
    std::vector<_ItemStat> LoadItemStatInfo(const Item* item, bool onlyReforgeable = false) const;
    const _ItemStat* FindItemStat(const std::vector<_ItemStat>& stats, uint32 statType) const;

    bool Reforge(Player* player, ObjectGuid itemGuid, uint32 statDecrease, uint32 statIncrease);
    void SendItemPacket(Player* player, const Item* item) const;
    void SendItemPackets(Player* player) const;
    void HandleReload(Player* player, bool apply) const;
    void HandleReload(bool apply) const;
    const ReforgingData* GetReforgingData(const Item* item) const;
    std::vector<Item*> GetPlayerItems(const Player* player, bool inBankAlso) const;
    bool CanRemoveReforge(const Item* item) const;
    bool RemoveReforge(Player* player, ObjectGuid itemGuid);
    bool RemoveReforge(Player* player, Item* item, bool force = false);
    void VisualFeedback(Player* player);
    void HandleCharacterRemove(uint32 guid);

    void HandleStatModifier(Player* player, uint32 statType, int32 val, bool apply);

    static void SendMessage(Player* player, const std::string& message);
    static std::string TextRed(const std::string& text);
    static std::string TextGreen(const std::string& text);
    static std::string ItemIcon(const ItemTemplate* proto, uint32 width = 30, uint32 height = 30, int x = 0, int y = 0);
    static std::string ItemNameWithLocale(const Player* player, const ItemTemplate* itemTemplate, int32 randomPropertyId);
    static std::string ItemLink(const Player* player, const ItemTemplate* itemTemplate, int32 randomPropertyId);
    static std::string ItemLinkForUI(const Item* item, const Player* player);
};

#define sItemReforge ItemReforge::instance()

#endif
