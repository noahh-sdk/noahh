# Noahh SDK
Noahh is a revolutionary Geometry Dash modding framework. Documentation on using the Noahh SDK can be found on the [Noahh Documentation](https://noahh-sdk.github.io/docs/).

## SDK

The SDK repo contains headers for Geometry Dash, Cocos2d-x, and the Noahh framework itself. The Geometry Dash headers are generated using codegen, although pre-genned headers can be found through the [bin](https://github.com/noahh-sdk/bin) submodule.

## Basic Usage

While traditional modding techniques involve convoluted setups using hooking libraries and calling conventions, Noahh simplifies the development of mods to a single macro: `$modify`. Using it, you can hook functions in any class as long as the addresses of those functions is defined in the codegenned bindings.

For example, to alter the behaviour of the "More Games" button in GD, all you have to do is this:

```cpp
class $modify(MenuLayer) {
    void onMoreGames(CCObject*) {
		FLAlertLayer::create(
            "Noahh",
            "Hello World from my Custom Mod!",´
            "OK"
        )->show(); 
    }
};
```

> :warning: Make sure that your overridden funcion's signature matches the original's. Emitting parameters / the `virtual` keyword may cause issues.

If you want to call the original function, all you need to do is the base class name and the function name, in the same way you would call the base of a virtual function.

```cpp
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        auto label = CCLabelBMFont::create("Hello world!", "bigFont.fnt");
        label->setPosition(100, 100);
        this->addChild(label);

        return true;
    }
};
```

If you to give a name to your modified class, specify it as the first parameter to `$modify`:

```cpp
class $modify(CustomMenuLayer, MenuLayer) {
    void onMoreGames(CCObject*) {
		FLAlertLayer::create(
            "Noahh",
            "Hello World from my Custom Mod!",´
            "OK"
        )->show(); 
    }
};
```

## Documentation

Documentation on using the Noahh SDK can be found on the [Noahh Documentation](https://noahh-sdk.github.io/docs/).