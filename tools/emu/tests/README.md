# Emulator tests

Scripts for `tools/emu/play.py`, which plays the built ROM on a headless mGBA
core. Each script says at the top what it checks and what to expect; they
print values and take screenshots rather than pass or fail on their own.

    tools/emu/build.sh                      # once, after building mGBA in build/mgba
    cd tools/emu/tests
    python3 ../play.py builds.txt
    python3 ../play.py boss_moves.txt sheet.png

The scripts reach what they test through the hooks in `src/rogue/rogue_debug.c`:
`debug room 7` walks into an event room, `debug battle 0` starts a battle,
`debug attack 12` lands one of Sora's attacks on the locked-on enemy, and so
on. `@gRogue.field` is the address of a field of the mod's structs.

| Script | Checks |
|---|---|
| `start.txt` | included by the others: boots into the first room |
| `battle.txt` | included by the others: a normal battle, enemies in |
| `builds.txt` | build damage bonuses |
| `launch.txt` | the combo finisher launching an enemy |
| `boss_moves.txt` | Larxene's knives and Vexen's ice block |
| `relics.txt` | glass cannon, life steal, bigger combo bonus |
| `second_wind.txt` | the survival relic |
| `air_jump.txt` | the air jump |
| `sleight.txt` | stocking three cards and playing them |
| `tag.txt` | a tag character standing in for one move |
| `new_cards.txt` | the cards from the custom sheets |
| `effect_moves.txt` | the moves made from other characters' effects |
| `hub_progress.txt` | meeting a character, its boon in the hub, the records page |
| `mickey_boss.txt` | Mickey fighting with Leon's moves |
| `mickey_hero.txt` | Mickey played in place of Sora, hub and battle |
| `enemy_tags.txt` | enemy cards calling their enemy or boss in for its attack |
| `profile_battle.txt` | frame load and missed frames in a crowded battle |
| `skill_tree.txt` | the ability tree and the starting cards bought from Axel in the hub |
| `more_moves.txt` | the later moves, the three new spells and the move modifiers |
| `effect_cards.txt` | the cards with an effect of their own |
| `relics_more.txt` | burn, freeze, shock, the shadow step and the air dash |
| `card_mods.txt` | a card played alone finding its enchantment |
| `sleight_card.txt` | a sleight played from a single card |
| `riku_hero.txt` | Riku played with the game's own Riku mode |
| `friend_bosses.txt` | the six friends who fight with Leon's moves |
| `boss_ai.txt` | Leon, and whoever stands in for him, walking up and swinging |
| `endless.txt` | the starting card in the deck, the seal of a boss, and a full run going on past its last floor |
| `styles.txt` | the elemental styles going off every few hits of a combo |
| `gadgets.txt` | gadget relics: things circling Sora, the timed ones, the dodge's trail, jumping and landing |
| `gadgets_more.txt` | a fusion of two gadgets, and the ones set off by turning the hand and by standing still |
| `options.txt` | the options page: swapping the way L and R turn the hand |
| `roxas_hero.txt` | Roxas played from the sheet in the game's own style: hub, room and battle |
| `sephiroth_boss.txt` | Sephiroth, a boss drawn from his own sheet with moves of his own |
| `sheet_bosses.txt` | the other bosses made the same way: Sora of his second journey and Roxas three times over |
| `hero_movesets.txt` | what each hero does that Sora does not: pearls, the thrown Keyblade, pillars and the double hit |
| `hub_drawn.txt` | the characters drawn from standing sprites, on the far side of the hub, and the boon of one |
| `flat_battle.txt` | the flat battle: one line, Up to jump, and its moves asked for one by one |
| `options_flat.txt` | the options page turning the flat battle on and setting a technique on a place |
