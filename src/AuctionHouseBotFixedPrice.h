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

#include "Common.h"
#include "ObjectGuid.h"
#include "ItemTemplate.h"
#include <unordered_map>

struct FixedPriceResult 
{
    float outBuyoutPrice;
    float sellVarianceBuyoutPriceTopPercent;
    float sellVarianceBuyoutPriceBottomPercent;
};

FixedPriceResult getFixedPriceIfApplicable (
    ItemTemplate const* itemProto,
    float outBuyoutPrice,
    float sellVarianceBuyoutPriceTopPercent,
    float sellVarianceBuyoutPriceBottomPercent,
    const std::unordered_map<uint32, float>& prices
);
