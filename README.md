# About this fork
This is a fork of NathanHandley/mod-ah-bot (which in turn is a fork of the original AHBot) that adds two main features:

## Client addons can query the minimum price the buyer bot is willing to pay for an item

The command `.ahbot buyeritemvalue <itemid>` can be used to anticipate how much the buyer is guaranteed to bid. The buyer may bid _more_ than that amount because the algorithm adds variances and multipliers.

This feature can be paired with the [AHBot Tooltip](https://github.com/abracadaniel22/AHBotTooltip) addon. The addon updates the item tooltips by adding the minimum amount the buyer is guaranteed to bid, allowing the player to setup their auctions much easier.

## Ability to set a minimum fixed bid price for items in the database

A new `acore_world.mod_ahbot` table is added that allows setting minimum price for items, before any variance is calculated. This allows admins to load up the database with real world or custom values when they are not satisfied with the standard multipliers and algorithms for certain items.

This feature can be paired with the [AHBot Price Updater](https://github.com/abracadaniel22/ahbot-price-updater) app, which can run periodically to download and parse auctioneer data files and populate the table with real world data.

This feature can be tweaked with two new settings:

- `AuctionHouseBot.DatabasePrices.Enabled`: can be used to toggle checking prices from the DB table for both buyer and seller.
- `AuctionHouseBot.DatabasePrices.BuyerUseDbPricesExclusively`: can set the buyer to only check prices in DB table, and use sell price otherwise. This can help if the buyer is defaulting to too high or too low prices when an item price is not saved in the db table.

# Original readme:

## Description

A fork of the auction house bot for AzerothCore.  This fork gives a much more blizzlike experience in the offerings on the auction house.  Most notable differences:
 - Things like Glyphs show up
 - Auction item stack sizes are customizable and more 'realistic'
 - The buyer bot's buying amounts and behavior was changed substantially
 - A separate set of exclusion item IDs was added to have crafted items listed, to encourage gathing professions.
	- Empty the list to have crafted goods appear in the AH, or use other IDs you want to keep separate
 - Moved database configuration completely to config

## Requirements
Requires an AzerothCore version that is caught up to at least change set 3f46e05 (https://github.com/azerothcore/azerothcore-wotlk/commit/3f46e05d3691895b6b8a5b3832d17ecb1e210791)

## Installation

```
1. Simply place the module under the `modules` directory of your AzerothCore source. 
2. Re-run cmake and launch a clean build of AzerothCore.
```

## Usage

Edit the module configuration and add a character GUID ID to the "AuctionHouseBot.GUIDs" variable, which is sourced from your character table in the character database.  These names will be visable in the auction house, so pick good names.  Find the configuration as named mod_ahbot.conf.dist / mod_ahbot.conf.  IMPORTANT: If you are using a bot mod (like playerbots), then ensure you use regular non-bot characters for your auctionhouse character(s)

Notes:
- These accounts do not need any security level and can be a player accounts.
- The characters used by the ahbot are not meant to be used ingame. If you use it to browse the auction house, you might have issues like "Searching for items..." displaying forever.
- Important!  By default, most player crafted items (except glyphs, bolts, maybe a few other things) are disabled from showing up in the auction house in order to encourage player crafting on lower pop servers.  If you want different behavior, alter the config variable "AuctionHouseBot.DisabledCraftedItemIDs" by deleting IDs you wish to show up.  Note that fish are also disabled to encourage fishing, and that's also managed by disabled lists.
- It takes a few hours for the auction house to fully populate, as only 75 items gets added by default every 'tick'.  You can change this in the config with the AuctionHouseBot.ItemsPerCycle variable.

## Credits

- NathanHandley: Created this rewrite of the one that was ported to AzerothCore
- Ayase: ported the bot to AzerothCore
- Other contributors (check the contributors list)
