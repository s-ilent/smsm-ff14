#ifndef TONEMAPPING_INCLUDED
#define TONEMAPPING_INCLUDED

float3 Tonemap_Hejl2015(float3 color, float whitePt) {

	float4 vh = float4(color, whitePt); // pack: [r, g, b, w]
	float4 va = (1.425 * vh) + 0.05f; // eval filmic curve
	float4 vf = ((vh * va + 0.004f) / ((vh * (va + 0.55f) + 0.0491f))) - 0.0821f;
	return vf.rgb / vf.www; // white point correction
}

float3 Tonemap_Hejl2015L(float3 color, float whitePt) {
  //float luma = dot(color.xyz, lumaCoef);   
  float luma = dot(color.xyz, 1.0/3.0);
  float2 vh = float2(luma, whitePt); // pack: [x, w]
  float2 va = (1.425 * vh) + 0.05f; // eval filmic curve
  float2 vf = ((vh * va + 0.004f) / ((vh * (va + 0.55f) + 0.0491f))) - 0.0821f;
  vf.x = vh/vf;
  return color / vf.x / vf.y; // white point correction
}

float3 Tonemap_Filmic(float3 color, float W, float A, float B, float C, float D, float E, float F)
{
    float4 res = float4(color.rgb, W);
    res        = (res * ( A * res + C * B) + D * E) / (res * ( A * res + B) + D * F);
    res       -= E / F;
    return res.rgb / res.a;
}

float3 ACESFilm(float3 color, float whitePt) {
  float a = 2.51f;
  float b = 0.03f;
  float c = 2.43f;
  float d = 0.59f;
  float e = 0.14f;
  float4 x = float4(color, whitePt);
  x = ((x*(a*x+b))/(x*(c*x+d)+e));
  return x.rgb/x.www;
}

float ACESFilmL(float luma) {
  float a = 2.51f;
  float b = 0.03f;
  float c = 2.43f;
  float d = 0.59f;
  float e = 0.14f;
  float x = luma;
  x = ((x*(a*x+b))/(x*(c*x+d)+e));
  return x;
}

float3 ACESFilmC(float3 color) {
  float a = 2.51f;
  float b = 0.03f;
  float c = 2.43f;
  float d = 0.59f;
  float e = 0.14f;
  float3 x = color;
  x = ((x*(a*x+b))/(x*(c*x+d)+e));
  return x;
}

// Source: http://www.glowybits.com/blog/2016/12/21/ifl_iss_hdr_1/
float3 RgbAcesSdrSrgb(float3 x)
{
    return (
    //return saturate(
            (x * (x * (x * (x * 8.4680 + 1.0) - 0.002957) + 0.0001004) - 0.0000001274) /
            (x * (x * (x * (x * 8.3604 + 1.8227) + 0.2189) - 0.002117) + 0.00003673));
}

float3 colourCrosstalkEffect (float3 color, float whitePt) {
  // Experimental based on GPUOpen presentation
  /*
  float peak = max3(color.rgb);
  float3 ratio = color.rgb/peak;
  peak = Tonemap_Hejl2015L(peak, whitePt);
  color.rgb = peak*ratio;
  */
  //color.rgb *= 1+whitePt;
  float peak = max3(color.rgb);
  float3 ratio = color.rgb/peak;
  //peak = ACESFilmL(peak);
  //peak = ACESFilmL(peak)/ACESFilmL(whitePt+1); // This seems incorrect...
  peak = Tonemap_Hejl2015L(peak, 5.6);
  {
    // Defines the output white point. Unless you have a HDR monitor -
    // and hacked the game to output HDR - this is normally 1.0.
    static const float white = 1.0f;
    // However, things come out a bit dull that way without the whitePt correction.
    //float white = 1.15;

    // Crosstalk amount. Determines the "indirect path to white", and thus,
    // how saturated bright objects (like aetherytes) are.
    static const float crosstalk = 2; // Too high messes up skin tones
    // Overall colour saturation. Adjust carefully. 
    static const float saturation = 1.250;
    // Crosstalk saturation. How saturated bright colours are. 
    static const float crossSaturation = 8;

    // Wrap crosstalk in transform
    ratio = pow(ratio, saturation / crossSaturation);
    ratio = lerp(ratio, white, pow(peak, crosstalk));
    ratio = pow(ratio, crossSaturation);
  }
  // Final colour
  color.rgb = peak*ratio;
  return color;
}
 
float3 jodieRoboTonemap(float3 c){
    float l = dot(c, float3(0.2126, 0.7152, 0.0722));
    float3 tc=c/sqrt(c*c+1.);
    return lerp(c/sqrt(l*l+1.),tc,tc);
}

float3 jodieReinhardTonemap(float3 c){
    float l = dot(c, float3(0.2126, 0.7152, 0.0722));
    float3 tc=c/(c+1.);
    return lerp(c/(l+1.),tc,tc);
}

float3 roboTonemap(float3 c){
    return c/sqrt(1.+c*c);
}

float3 ACESLumTest (float3 c, float whitePt) {
  float w = dot(c, 1.0/3.0);
  //float w = dot(c, float3(0.2126, 0.7152, 0.0722));
  float3 tc = ACESFilmC(c);
  c = lerp(c/ACESFilmL(w+1.), tc, tc);
  return c / ACESFilmL(whitePt);
}

float ExpContrast (float x) {
  return (1.0524 * exp(6.0 * x) - 1.05248) / (exp(6.0 * x) + 20.0855);
}

float3 LinToLog( float3 LinearColor )
{
    float3 LogColor = ( 300 * log10( LinearColor * (1 - .0108) + .0108 ) + 685 ) / 1023;    // Cineon
    //LogColor = saturate( LogColor );

    return LogColor;
}

#define LUMA_REC709 float3(0.2126, 0.7152, 0.0722)

float genericTonemap(float x, float contrast, float shoulder,
        float midGreyIn, float midGreyOut, float hdrMax) {
    // Lottes, 2016,"Advanced Techniques and Optimization of VDR Color Pipelines"
    // https://gpuopen.com/wp-content/uploads/2016/03/GdcVdrLottes.pdf
    float mc = pow(midGreyIn, contrast);
    float mcs = pow(mc, shoulder);

    float hc = pow(hdrMax, contrast);
    float hcs = pow(hc, shoulder);

    float b1 = -mc + hc * midGreyOut;
    float b2 = (hcs - mcs) * midGreyOut;
    float b = b1 / b2;

    float c1 = hcs * mc - hc * mcs * midGreyOut;
    float c2 = (hcs - mcs) * midGreyOut;
    float c = c1 / c2;

    float xc = pow(x, contrast);
    return saturate(xc / (pow(xc, shoulder) * b + c));
}

float3 EVILS(float3 x) {
    // Troy Sobotka, 2021, "EVILS - Exposure Value Invariant Luminance Scaling"
    // https://colab.research.google.com/drive/1iPJzNNKR7PynFmsqSnQm3bCZmQ3CvAJ-#scrollTo=psU43hb-BLzB

    // TODO: These constants were chosen to match our ACES tone mappers as closely as possible
    //       in terms of compression. We should expose these parameters to users via an API.
    //       We must however carefully validate exposed parameters as it is easy to get the
    //       generic tonemapper to produce invalid curves.
    float contrast = 1.6f;
    float shoulder = 1.0f;
    float midGreyIn = 0.18f;
    float midGreyOut = 0.227f;
    float hdrMax = 64.0f;

    // We assume an input compatible with Rec.709 luminance weights
    float luminanceIn = dot(x, LUMA_REC709);
    float luminanceOut = genericTonemap(luminanceIn, contrast, shoulder, midGreyIn, midGreyOut, hdrMax);
    float peak = max(x, 0);
    float3 chromaRatio = max(x / peak, 0.0f);

    float chromaRatioLuminance = dot(chromaRatio, LUMA_REC709);

    float3 maxReserves = 1.0f - chromaRatio;
    float maxReservesLuminance = dot(maxReserves, LUMA_REC709);

    float luminanceDifference = max(luminanceOut - chromaRatioLuminance, 0.0f);
    float scaledLuminanceDifference =
            luminanceDifference / max(maxReservesLuminance, 1.17549e-38f);

    float chromaScale = (luminanceOut - luminanceDifference) /
            max(chromaRatioLuminance, 1.17549e-38f);

    return saturate(chromaScale * chromaRatio + scaledLuminanceDifference * maxReserves);
}

#endif // TONEMAPPING_INCLUDED