#pragma once
#include <vector>
#include <string>


#include "GameObjects.h"

// Represents a single item instance in the inventory
struct InventoryItem {
    std::string itemId;
    int quantity;
    std::shared_ptr<GameObjects> itemObject;

    InventoryItem(const std::string& id, int qty, std::shared_ptr<GameObjects> obj)
        : itemId(id), quantity(qty), itemObject(obj) {
    }
};


class InventorySystem {
public:
    // Core inventory operations functionalities for players
    bool AddItem(const std::string& itemId, int quantity = 1);
    bool RemoveItem(const std::string& itemId, int quantity = 1);
    bool HasItem(const std::string& itemId, int quantity = 1) const;

    // Item lookup and retrieval 
    std::shared_ptr<GameObjects> GetItemObject(const std::string& itemId) const;
    int GetItemQuantity(const std::string& itemId) const;
    const std::vector<InventoryItem>& GetAllItems() const { return inventoryItems; }

    // Item registration
    void RegisterItem(const std::string& itemId, std::shared_ptr<GameObjects> itemObject);

    // Inventory management
    int GetCurrentCapacity() const { return currentCapacity; }
    int GetMaxCapacity() const { return maxCapacity; }
    bool IsInventoryFull() const { return currentCapacity >= maxCapacity; }

    // Constructor
    InventorySystem(int maxCap = 20) : maxCapacity(maxCap), currentCapacity(0) {}

private:
    // Core inventory storage
    std::vector<InventoryItem> inventoryItems;
    std::unordered_map<std::string, std::shared_ptr<GameObjects>> itemRegistry;

    // Inventory constraints
    int maxCapacity;
    int currentCapacity;

    // Helper methods for finding our inventory item from our inventory items efficiently
    InventoryItem* FindInventoryItem(const std::string& itemId);
    const InventoryItem* FindInventoryItem(const std::string& itemId) const;
};
