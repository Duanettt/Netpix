#include "InventorySystem.h"


bool InventorySystem::AddItem(const std::string& itemId, int quantity)
{
    // Pre checks to ensure no bugs.
    if (quantity <= 0) return false;
    if (currentCapacity + quantity >= maxCapacity) return false;

    // we first check if the item is an actual valid item within our registry..
    auto registryItem = itemRegistry.find(itemId);
    if (itemRegistry.find(itemId) == itemRegistry.end()) return false;

    // we now need to add the item to our inventory vector.
    // We find our inventory item using the helper methods which iterate through the vector and return our pointer
    InventoryItem* existingItem = FindInventoryItem(itemId);
    if (existingItem)
    {
        existingItem->quantity + quantity;
    }
    else
    {
        // place a new instance of our inventory item into our vector
        inventoryItems.emplace_back(itemId, quantity, registryItem->second);
    }

    currentCapacity += quantity;

    return true;
}

bool InventorySystem::RemoveItem(const std::string& itemId, int quantity)
{
    if (currentCapacity <= 0) return false;
    if (quantity <= 0) return false;

    // Check again if our item is within our registry.
    auto registryItem = itemRegistry.find(itemId);
    if (itemRegistry.find(itemId) == itemRegistry.end()) return false;


    InventoryItem* existingItem = FindInventoryItem(itemId);
    
    if (!existingItem || existingItem->quantity < quantity) return false;

    existingItem->quantity -= quantity;
    currentCapacity -= quantity;

    if (existingItem->quantity == 0)
    {
        auto it = std::find_if(inventoryItems.begin(), inventoryItems.end(),
            [&itemId](const InventoryItem& item) { return item.itemId == itemId; });
        if (it != inventoryItems.end()) {
            inventoryItems.erase(it);
        }
    }


    return true;
}

bool InventorySystem::HasItem(const std::string& itemId, int quantity) const
{
    const InventoryItem* item = FindInventoryItem(itemId);
    return item && item->quantity > quantity;
}

std::shared_ptr<GameObjects> InventorySystem::GetItemObject(const std::string& itemId) const
{
    auto it = itemRegistry.find(itemId);
    return (it != itemRegistry.end() ? it->second : nullptr);
}

int InventorySystem::GetItemQuantity(const std::string& itemId) const
{
    const InventoryItem* item = FindInventoryItem(itemId);

    return item ? item->quantity : 0;
}

void InventorySystem::RegisterItem(const std::string& itemId, std::shared_ptr<GameObjects> itemObject)
{
    if (itemObject)
    {
       itemRegistry[itemId] = itemObject;
    }
}

InventoryItem* InventorySystem::FindInventoryItem(const std::string& itemId) {
    auto it = std::find_if(inventoryItems.begin(), inventoryItems.end(),
        [&itemId](const InventoryItem& item) { return item.itemId == itemId; });
    return it != inventoryItems.end() ? &(*it) : nullptr;
}

const InventoryItem* InventorySystem::FindInventoryItem(const std::string& itemId) const {
    auto it = std::find_if(inventoryItems.begin(), inventoryItems.end(),
        [&itemId](const InventoryItem& item) { return item.itemId == itemId; });
    return it != inventoryItems.end() ? &(*it) : nullptr;
}
