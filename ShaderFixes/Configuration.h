#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED
// This is the configuration file for SMSM. 

// ----- Tonemapping

	#define TONEMAP_VANILLA 0
	// Does nothing in this section and only uses the original code. 

	// Only activate one of these at a time!

	#define TONEMAP_Hejl 0
	// "Hejl2015" filmic tonemapping. In this case, filmic tonemapping means more realistic colours, 
	// removing the awkward orange tint from skin and blown out sky.
	// Looks really nice, but a bit white compared to the original system. 

	#define TONEMAP_ACES 0
	// Academy-standard filmic tonemapping. 
	// Looks almost identical to the above. You may notice more contrast and less whiteness.

	#define TONEMAP_ACESSP 0
	// Sucker Punch's version of the ACES curve. 

	#define TONEMAP_U2 0
	// Uncharted 2 filmic tonemapping. A staple of many modern games. 
	// Tweaked to fit FF14 better. 

	#define TONEMAP_Luminance 0
	// Filmic tonemapping, but applied only to luminance. This is an interesting compromise
	// between it and the original tonemapping, as it looks the same as the vanilla game, but with
	// less blown out colours. But I don't recommend it - some stuff gets weird. 
	// Plus, it's bad practise! For more information, see
	// https://imdoingitwrong.wordpress.com/2010/08/19/why-reinhard-desaturates-my-blacks-3/#comment-3

	#define TONEMAP_Luminance2 0
	// Academy-standard filmic tonemapping, applied only to luminance, with special
	// compensation for colour crosstalk. Based on an interesting presentation I kind-of
	// understood. Looks really good - however, reacts differently to colour filters. 

	#define TONEMAP_Xponential 0
	// Nothing filmic here. Like vanilla but darker.

	#define TONEMAP_EVILS 1

	#define USE_Power 0
	// As the original tonemapper does, increases color to color^2 before adaptation and then sqrts it.
	// Should not be used. 

// ----- Color filters

  	#define COLORTONE 0
	static float3 colorToneAmount = float3(0.07, 0.03, 0.10)/2;
	// Adds a bit of colour tinting. Done in HDR.
	// Default is (0.07, 0.03, 0.10), a value carefully chosen to remove the game's green tint. 

	//#define SATURATION 3
	#define PSATURATION 0
    //static float saturationAmount = 1.18;
    //static float3 saturationAmount = 0.0 + float3(1.5, 1.5, 1.0); // For mode 2
    static float3 saturationAmount = 0.0 + float3(1.0, 1.0, 1.25); // For mode 3
	// Complete global (over)saturation. 
	// These values are also set for de-greenification. 
	// Different values set which luminance base to perform the saturation from.
	// 1: Normal 2: Brightest colour 3: Darkest colour

	#define CUBICCONTRAST 0
  	static float contrastCAmount = 0.18;
	// Hyper contrast. A powerful effect based on techniques used in film.
	// Default is 0.18, which is a nice boost.
	// But too powerful with the new tonemapping.

// ----- Bloom

	#define UseOriginalWhitening 0
	// FF14 adds a pale white outer rim to bloom by default.
	// I've disabled it, as it looks weird with the new tonemapping.
	// But you can turn it back on here. 

// ----- Dithering

	#define DitherMode 4
	// Dithering almost completely removes banding artifacts from the game. It doesn't affect colour tones.
	// 1 - Valve's dithering. Tiny effect. 
	// 2 - CeeJay.dk's dithering. Grid pattern with decent effect. 
	// 3 - Valve's dithering with a triangular distribution. 
	// 4 - Interleaved gradient noise, mixed with CeeJay.dk's dithering technique. Wider range. 

#endif // CONFIG_INCLUDED