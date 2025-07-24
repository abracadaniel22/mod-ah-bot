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
#include <unordered_map>

#include "AuctionHouseBotFixedPrice.h"

using namespace std;

// ensure final price stay close enough to the "fixed" price
static const float DEFAULT_VARIANCE_TOP_PERCENT = 1.15;
static const float DEFAULT_VARIANCE_BOTTOM_PERCENT = 0.95;

FixedPriceResult getFixedPriceIfApplicable (
    ItemTemplate const* itemProto,
    float outBuyoutPrice,
    float sellVarianceBuyoutPriceTopPercent,
    float sellVarianceBuyoutPriceBottomPercent,
    const std::unordered_map<uint32, float>& prices
)
{
    float newBuyoutPrice = 0;
    auto it = prices.find(itemProto->ItemId);
    if (it != prices.end())
    {
        newBuyoutPrice = it->second;
    }

    if (newBuyoutPrice != 0)
    {
        outBuyoutPrice = newBuyoutPrice;
        sellVarianceBuyoutPriceTopPercent = DEFAULT_VARIANCE_TOP_PERCENT;
        sellVarianceBuyoutPriceBottomPercent = DEFAULT_VARIANCE_BOTTOM_PERCENT;
    }
    return {outBuyoutPrice, sellVarianceBuyoutPriceTopPercent, sellVarianceBuyoutPriceBottomPercent};
}
