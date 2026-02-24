<p align="center">
	<img src="/title.png" />
	<h3 align="center">
		<a href="https://noahh-sdk.org">Home page</a>
	</h3>
</p>

<p align="center"><b>Noahh</b> is a <a href="https://store.steampowered.com/app/322170/Geometry_Dash/">Geometry Dash</a> <b>mod loader</b> and <b>modding SDK</b> with a modern approach towards mod development.</p>

## Why Noahh?

Unlike previous mod loaders, which merely inject the DLLs and let devs handle the rest, Noahh aims to be a more comprehensive project that provides all the tools needed for creating mods in one package.

Noahh's goal is to solve **mod incompatibility** - to ensure that mods work together without buttons getting misplaced or hooks mysteriously disappearing.

## "Hello World!" Example

Here's a **Hello World** mod in Noahh:

```cpp
#include <Noahh/Bindings.hpp>
#include <Noahh/modify/MenuLayer.hpp>

using namespace noahh::prelude;

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

This code modifies what happens when the "More Games" button is clicked on the home scene in Geometry Dash, showing a custom popup.

## Documentation

Detailed documentation, tutorials, and installation instructions on using Noahh can be found [here](https://docs.noahh-sdk.org).

New to modding GD? Noahh's documentation also comes with a handy [tutorial book](https://docs.noahh-sdk.org/#/handbook/chap0) that explains all the basics of GD modding!

## Contribution

You can contribute to Noahh by opening a [Pull Request](https://github.com/noahh-sdk/noahh/pulls)! Please follow the contribution guidelines.

## Questions, help, etc.

If you have any further questions, need help, or just want to share your love for catgirls, be sure to join [our Discord server](https://discord.gg/9e43WMKzhp)!

