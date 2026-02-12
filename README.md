![Noahh Logo](https://github.com/noahh-sdk.png?size=80) 

# Noahh SDK

**Noahh** is a [Geometry Dash](https://store.steampowered.com/app/322170/Geometry_Dash/) **mod loader** and **modding SDK** with a modern approach towards mod development. Unlike previous mod loaders, which merely inject the DLLs and let devs handle the rest, Noahh aims to be a more comprehensive project, which manages loaded mods & hooks itself. Noahh has been built to ensure performance, compatibility, portability and ease of use. For devs, Noahh means **easy development and portability**; for end users, Noahh means **an uniform and easy experience** using mods.

## Why Noahh?

There's nothing worse than having to read thousands of words just to see what some library's code actually looks like, so instead, here's a **Hello World** in Noahh right off the bat:

```cpp
#include <Noahh.hpp>

USE_NOAHH_NAMESPACE();

class $modify(MenuLayer) {
	void onMoreGames(CCObject*) {
		FLAlertLayer::create(
			"Noahh",
			"Hello World from my Custom Mod!",
			"OK"
		)->show();
	}
};
```

This code hooks the "More Games" button in Geometry Dash, and makes it show a different popup when clicked. Compared to traditional modding methods such as MinHook, we would argue that this is **much easier to write, understand & maintain**.

Noahh is in many ways a **declarative framework**; you tell it what you want, not how to accomplish it. Noahh has been built to let modders focus on what mod they want to make, not how exactly to build it. Its goal is to **abstract away** unnecessary details, while still enabling developers have **precise control** over their mod.

One of our main design goals with Noahh has been to make a framework so good that **after using it once, you never want to go back**.

## Documentation

Detailed documentation, tutorials, and references on using the Noahh SDK can be found [here](https://noahh-sdk.github.io/docs/).

## Contribution

You can contribute to Noahh by opening a [Pull Request](https://github.com/noahh-sdk/noahh/pulls)!

## Questions, help, etc.

If you have any further questions, need help, or just want to share your love for catgirls, be sure to join [our Discord server](https://discord.gg/9e43WMKzhp)!