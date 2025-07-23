/*
 * Copyright (C) 2008-2010 Trinity <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2023+ Nathan Handley <https://github.com/NathanHandley>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "ObjectMgr.h"
#include "AuctionHouseMgr.h"
#include "AuctionHouseBot.h"
#include "Config.h"
#include "Player.h"
#include "WorldSession.h"
#include "GameTime.h"
#include "DatabaseEnv.h"

#include <unordered_set>

#include "AuctionHouseBotFixedPrice.h"

using namespace std;

// TODO this should all be moved to config file
static const float DEFAULT_VARIANCE_TOP_PERCENT = 1.20;
static const float DEFAULT_VARIANCE_BOTTOM_PERCENT = 0.95;
static const unordered_set<uint32> BAGS_TWENTY = { 21876, 34067, 34845, 35516, 41599, 50317 };
static const unordered_set<uint32> BAGS_TWENTY_FOUR = { 38082, 41600, 43345, 49295, 50316 };
static const unordered_map<uint32, float> PRICE_BY_ITEMS = {
    { 51809, 20000000 },    // 26 (36) portable hole 2000g
    { 49290, 2100000000 },  // magic rooster egg 210000
    { 54068, 800000000 },   // Wooly White Rhino 80000
    { 54860, 798000000 },   // X-53 Touring Rocket 79800g
    { 54069, 760000000 },   // blazing hippogryph 76000
    { 54811, 735000000 },   // Celestial Steed  73500g
    { 43599, 630000000 },   // Big Blizzard Bear 63000g 
    { 49284, 525000000 },   // Reins of the Swift Spectral Tiger 52500g
    { 38576, 400000000 },   // big battle bear 40000
    { 198628, 340000000 },  // x-51 nether rocket xtreme 34000
    { 52200, 175680000 },   // crimson deathcharger 17568
    { 33224, 170000000 },   // Reins of the Spectral Tiger 17000g
    { 44413, 160000000 },   // mekgineer's chopper (alliance) 16000
    { 41508, 160000000 },   // Mechano-hog (horde) 16000  
    { 35225, 147000000 },   // X-51 Nether-Rocket 14700g
    { 34061, 52200000 },    // turbocharged flying machine 5220
    { 34060, 50000000 },    // Flying Machine Control 5000
    { 44554, 1000000 }      // flying carpet 100
};

static bool containsInSet(uint32 item, const unordered_set<uint32>& setObj)
{
    return setObj.find(item) != setObj.end();
}

static bool containsInMap(uint32 item, const unordered_map<uint32, float>& mapObj)
{
    return mapObj.find(item) != mapObj.end();
}

static FixedPriceResult buildResultWithStandardVariance(const float& outBuyoutPrice)
{
    return { outBuyoutPrice, DEFAULT_VARIANCE_TOP_PERCENT, DEFAULT_VARIANCE_BOTTOM_PERCENT };
}

FixedPriceResult getFixedPriceIfApplicable (
    ItemTemplate const* itemProto,
    float outBuyoutPrice,
    float sellVarianceBuyoutPriceTopPercent,
    float sellVarianceBuyoutPriceBottomPercent
)
{
    // 20 (32) slot bags 123g
    if (containsInSet(itemProto->ItemId, BAGS_TWENTY))
    {
        outBuyoutPrice = 1230000;
    }

    // 24 (34) slot bags 700g
    if (containsInSet(itemProto->ItemId, BAGS_TWENTY_FOUR))
    {
        outBuyoutPrice = 7000000;
    }
    
    auto it = PRICE_BY_ITEMS.find(itemProto->ItemId);
    if (it != PRICE_BY_ITEMS.end())
    {
        outBuyoutPrice = it->second;
    }
    return buildResultWithStandardVariance(outBuyoutPrice);
}
