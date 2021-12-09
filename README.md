# Silent's Messy Shader Mod - for FF14

![Preview Image](https://user-images.githubusercontent.com/16026653/129494572-8f3d45e8-4edd-4421-b7eb-ffc21b47f349.jpg)

A messy shader modification for Final Fantasy 14.

Unlike the popular Reshade/GShade shader mods, this uses 3DMigoto to *replace* the game's own shaders with custom ones. This allows for much much higher fidelity when it comes to colour control and even the ability to improve on normally impossible to touch aspects of the game's graphics!

Because this works through shader replacement, it has a low performance impact and does not need to be updated through patches unless an affected shader is changed.

### [Download it here.](https://github.com/s-ilent/smsm-ff14/archive/refs/heads/main.zip)

## Features

* **Filmic tonemapping** replaces the game's internal colour processing algorithm with one which is standard in modern games. It brings out the fine details of the art in FF14 while removing the dreaded "grey haze" many Reshade presets seek to destroy, without crushing any details. Because it works in HDR space, it can even show details that weren't visible before.
* **Tweaked reflections** to be less jaggy and more blurry, by applying a simple scattering filter to hide the sampling steps. 
* **Softer bloom** that more closely matches the intended look of the game when running it at higher resolutions like 4k. 
* **Sharper sun shafts** using dithered sampling, which avoids the stepped look of the original.
* **Smoother radial blur** using dithered sampling, which avoids the stepped look of the original. 
* **Less banding** with a dithered output, reducing the banding visible when looking at the skybox. 
* **Bokeh depth of field** in cutscenes and /gpose mode. 
<<<<<<< HEAD
* **Screenspace shadows** based off surface normal maps, adding subtle shadows to objects based on the ridges on their surface.
=======
* **Not an overlay** - won't overlap the game's UI, won't render through it, won't have artifacts around UI elements. 

![See, UI works!](https://user-images.githubusercontent.com/16026653/129494753-8958c9af-2891-4785-aabd-eef6958c7c8d.jpg)

>>>>>>> origin/main

## Installation

Copy the contents of the repository to the /game directory where ffxiv_dx11.exe sits. i.e.

`C:\Program Files\FINAL FANTASY XIV - A Realm Reborn\game\`

The game MUST be set to DX11 in the launcher. 
<!--
This relies on 3DMigoto to do the hard work.

1. Download and install 3DMigoto from https://github.com/bo3b/3Dmigoto/releases.
2. 3DMigoto comes with 3 folders. Extract the contents of the x64 folder next to ffxiv_dx11.exe. i.e.

`C:\Program Files\FINAL FANTASY XIV - A Realm Reborn\game\`

The game MUST be set to DX11 in the launcher. 

3. Finally, place the ShaderFixes folder from this repo next to ffxiv_dx11.exe, overwriting the folder created by 3DMigoto.
-->

### Uninstallation

Delete d3d11.dll, nvapi64.dll, d3dcompiler_46.dll, and the ShaderFixes folder.

## Screenshots

![Dusk and dawn's warm tones are expanded.](https://user-images.githubusercontent.com/16026653/129495100-bf11aa72-7c96-4327-b637-4e6782bb8e91.jpg)

![2.0 areas look expecially nice with the new colour grading.](https://user-images.githubusercontent.com/16026653/129494848-084b538a-8ea7-4fff-aa39-5fe608a72b2f.jpg)

![Sun shafts and moon shafts look more stable now.](https://user-images.githubusercontent.com/16026653/129495045-53050e6f-524a-43d3-859c-0e9cbec3bb22.jpg)

![3.0 areas also get nice boosts.](https://user-images.githubusercontent.com/16026653/129495129-9d3b0a89-2a73-4a86-a6b9-9c6db85c084b.jpg)


## Notes

### General
Shaders are currently provided in binary and source format. As the title of this mod suggests, the source code is messy. I wrote a lot of this while still learning about shader programming, sorry!

### Compatibility
While this mod is compatible with Reshade/GShade, some tools may raise warnings due to having multiple DirectX injection tools active at once. You should generally be safe to ignore these and proceed. 

### Tonemapping and lighting
Some scenes may look odd due to the lighting parameters used by the game. 

I've done rigorous testing and these scenes are few and far between. 

It's not possible to fix them, but workarounds might be possible. Feel free to report them if you see them. 

### Depth of field
In FF14, depth of field is compured at quarter resolution and upscaled to the main screen resolution. The depth buffer provided to depth of field in this case is also quarter resolution. 

As such, when depth of field is shallow, it will appear similar to the original depth of field, as it would look noticeably lower-resolution otherwise. 

Under certain conditions - almost entirely when using /gpose - you might see big jagged edges around objects when the depth of field is set to custom parameters. This seems unavoidable due to the nature of how FF14 does depth of field - remember, quarter resolution - so please tweak the parameters if this happens.

## License
This mod is licensed under the MIT license where applicable.

This does not apply to the portions of the mod part of the 3DMigoto software. 3DMigoto is licensed under GPLv3, and you can find the source code here: https://github.com/bo3b/3Dmigoto
