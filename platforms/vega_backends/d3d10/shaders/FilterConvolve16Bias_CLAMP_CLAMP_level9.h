#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /D SWRAP=2 /D TWRAP=2 /nologo /Zpc /Tps_4_0_level_9_1
//    /Dop_main=FilterConvolve16Bias /EFilterConvolve16Bias
//    /FhFilterConvolve16Bias_CLAMP_CLAMP_level9.h /Vn
//    g_ps20_FilterConvolve16Bias_CLAMP_CLAMP convolve_gen_16_bias.psh
//
//
// Buffer Definitions: 
//
// cbuffer constants
// {
//
//   float3 offsetWeight[16];           // Offset:    0 Size:   252
//   float divisor;                     // Offset:  256 Size:     4
//   float bias;                        // Offset:  272 Size:     4
//   bool preserve_alpha;               // Offset:  288 Size:     4
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// srcSampler                        sampler      NA          NA    0        1
// srcTex                            texture  float4          2d    0        1
// constants                         cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_POSITION              0   xyzw        0      POS  float       
// COLOR                    0   xyzw        1     NONE  float       
// TEXCOORD                 0   xy          2     NONE  float   xy  
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_Target                0   xyzw        0   TARGET  float   xyzw
//
//
// Constant buffer to DX9 shader constant mappings:
//
// Target Reg Buffer  Start Reg # of Regs        Data Conversion
// ---------- ------- --------- --------- ----------------------
// c0         cb0             0        18  ( FLT, FLT, FLT, FLT)
// c18        cb0            18         1  (BOOL, FLT, FLT, FLT)
//
//
// Sampler/Resource to DX9 shader sampler mappings:
//
// Target Sampler Source Sampler  Source Resource
// -------------- --------------- ----------------
// s0             s0              t0               
//
//
// Level9 shader bytecode:
//
    ps_2_0
    dcl t1.xy
    dcl_2d s0
    add r0.xy, t1, c1
    add r1.xy, t1, c0
    add r2.xy, t1, c2
    add r3.xy, t1, c3
    add r4.xy, t1, c4
    add r5.xy, t1, c5
    add r6.xy, t1, c6
    add r7.xy, t1, c7
    add r8.xy, t1, c8
    add r9.xy, t1, c9
    add r10.xy, t1, c10
    texld r0, r0, s0
    texld r1, r1, s0
    texld r2, r2, s0
    texld r3, r3, s0
    texld r4, r4, s0
    texld r5, r5, s0
    texld r6, r6, s0
    texld r7, r7, s0
    texld r8, r8, s0
    texld r9, r9, s0
    texld r10, r10, s0
    mul r0, r0, c1.z
    mad r0, r1, c0.z, r0
    mad r0, r2, c2.z, r0
    mad r0, r3, c3.z, r0
    mad r0, r4, c4.z, r0
    mad r0, r5, c5.z, r0
    mad r0, r6, c6.z, r0
    mad r0, r7, c7.z, r0
    mad r0, r8, c8.z, r0
    mad r0, r9, c9.z, r0
    mad r0, r10, c10.z, r0
    add r1.xy, t1, c11
    add r2.xy, t1, c12
    add r3.xy, t1, c13
    add r4.xy, t1, c14
    add r5.xy, t1, c15
    texld r1, r1, s0
    texld r2, r2, s0
    texld r3, r3, s0
    texld r4, r4, s0
    texld r5, r5, s0
    texld r6, t1, s0
    mad r0, r1, c11.z, r0
    mad r0, r2, c12.z, r0
    mad r0, r3, c13.z, r0
    mad r0, r4, c14.z, r0
    mad r0, r5, c15.z, r0
    rcp r1.x, c16.x
    mad r0, r0, r1.x, c17.x
    rcp r1.x, r0.w
    mul r1.xyz, r0, r1.x
    cmp r1.xyz, -r0.w, r0, r1
    mul r6.xyz, r6.w, r1
    cmp_sat r0, -c18.x, r0, r6
    mov oC0, r0

// approximately 57 instruction slots used (17 texture, 40 arithmetic)
ps_4_0
dcl_constantbuffer cb0[19], dynamicIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_input_ps linear v2.xy
dcl_output o0.xyzw
dcl_temps 3
mov r0.xyzw, l(0,0,0,0)
mov r1.x, l(0)
loop 
  ige r1.y, r1.x, l(16)
  breakc_nz r1.y
  add r1.yz, v2.xxyx, cb0[r1.x + 0].xxyx
  sample r2.xyzw, r1.yzyy, t0.xyzw, s0
  mad r0.xyzw, r2.xyzw, cb0[r1.x + 0].zzzz, r0.xyzw
  iadd r1.x, r1.x, l(1)
endloop 
div r0.xyzw, r0.xyzw, cb0[16].xxxx
add r0.xyzw, r0.xyzw, cb0[17].xxxx
if_nz cb0[18].x
  sample r1.xyzw, v2.xyxx, t0.xyzw, s0
  ge r1.x, l(0.000000), r0.w
  div r2.xyz, r0.xyzx, r0.wwww
  movc r1.xyz, r1.xxxx, r0.xyzx, r2.xyzx
  mul r0.xyz, r1.wwww, r1.xyzx
  mov r0.w, r1.w
endif 
mov_sat o0.xyzw, r0.xyzw
ret 
// Approximately 22 instruction slots used
#endif

const BYTE g_ps20_FilterConvolve16Bias_CLAMP_CLAMP[] =
{
     68,  88,  66,  67, 219, 112, 
    202, 107,  45,  56,  69, 199, 
     44,  81, 182, 247,  17,  29, 
     26, 108,   1,   0,   0,   0, 
    164,   9,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    108,   4,   0,   0, 216,   6, 
      0,   0,  84,   7,   0,   0, 
    252,   8,   0,   0, 112,   9, 
      0,   0,  65, 111, 110,  57, 
     44,   4,   0,   0,  44,   4, 
      0,   0,   0,   2, 255, 255, 
    236,   3,   0,   0,  64,   0, 
      0,   0,   2,   0,  40,   0, 
      0,   0,  64,   0,   0,   0, 
     64,   0,   1,   0,  36,   0, 
      0,   0,  64,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     18,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  18,   0, 
      1,   0,  18,   0,   1,   0, 
      0,   0,   0,   2, 255, 255, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   1,   0,   3, 176, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   0,   8,  15, 160, 
      2,   0,   0,   3,   0,   0, 
      3, 128,   1,   0, 228, 176, 
      1,   0, 228, 160,   2,   0, 
      0,   3,   1,   0,   3, 128, 
      1,   0, 228, 176,   0,   0, 
    228, 160,   2,   0,   0,   3, 
      2,   0,   3, 128,   1,   0, 
    228, 176,   2,   0, 228, 160, 
      2,   0,   0,   3,   3,   0, 
      3, 128,   1,   0, 228, 176, 
      3,   0, 228, 160,   2,   0, 
      0,   3,   4,   0,   3, 128, 
      1,   0, 228, 176,   4,   0, 
    228, 160,   2,   0,   0,   3, 
      5,   0,   3, 128,   1,   0, 
    228, 176,   5,   0, 228, 160, 
      2,   0,   0,   3,   6,   0, 
      3, 128,   1,   0, 228, 176, 
      6,   0, 228, 160,   2,   0, 
      0,   3,   7,   0,   3, 128, 
      1,   0, 228, 176,   7,   0, 
    228, 160,   2,   0,   0,   3, 
      8,   0,   3, 128,   1,   0, 
    228, 176,   8,   0, 228, 160, 
      2,   0,   0,   3,   9,   0, 
      3, 128,   1,   0, 228, 176, 
      9,   0, 228, 160,   2,   0, 
      0,   3,  10,   0,   3, 128, 
      1,   0, 228, 176,  10,   0, 
    228, 160,  66,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   0,   8, 228, 160, 
     66,   0,   0,   3,   1,   0, 
     15, 128,   1,   0, 228, 128, 
      0,   8, 228, 160,  66,   0, 
      0,   3,   2,   0,  15, 128, 
      2,   0, 228, 128,   0,   8, 
    228, 160,  66,   0,   0,   3, 
      3,   0,  15, 128,   3,   0, 
    228, 128,   0,   8, 228, 160, 
     66,   0,   0,   3,   4,   0, 
     15, 128,   4,   0, 228, 128, 
      0,   8, 228, 160,  66,   0, 
      0,   3,   5,   0,  15, 128, 
      5,   0, 228, 128,   0,   8, 
    228, 160,  66,   0,   0,   3, 
      6,   0,  15, 128,   6,   0, 
    228, 128,   0,   8, 228, 160, 
     66,   0,   0,   3,   7,   0, 
     15, 128,   7,   0, 228, 128, 
      0,   8, 228, 160,  66,   0, 
      0,   3,   8,   0,  15, 128, 
      8,   0, 228, 128,   0,   8, 
    228, 160,  66,   0,   0,   3, 
      9,   0,  15, 128,   9,   0, 
    228, 128,   0,   8, 228, 160, 
     66,   0,   0,   3,  10,   0, 
     15, 128,  10,   0, 228, 128, 
      0,   8, 228, 160,   5,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 228, 128,   1,   0, 
    170, 160,   4,   0,   0,   4, 
      0,   0,  15, 128,   1,   0, 
    228, 128,   0,   0, 170, 160, 
      0,   0, 228, 128,   4,   0, 
      0,   4,   0,   0,  15, 128, 
      2,   0, 228, 128,   2,   0, 
    170, 160,   0,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   3,   0, 228, 128, 
      3,   0, 170, 160,   0,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,  15, 128,   4,   0, 
    228, 128,   4,   0, 170, 160, 
      0,   0, 228, 128,   4,   0, 
      0,   4,   0,   0,  15, 128, 
      5,   0, 228, 128,   5,   0, 
    170, 160,   0,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   6,   0, 228, 128, 
      6,   0, 170, 160,   0,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,  15, 128,   7,   0, 
    228, 128,   7,   0, 170, 160, 
      0,   0, 228, 128,   4,   0, 
      0,   4,   0,   0,  15, 128, 
      8,   0, 228, 128,   8,   0, 
    170, 160,   0,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   9,   0, 228, 128, 
      9,   0, 170, 160,   0,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,  15, 128,  10,   0, 
    228, 128,  10,   0, 170, 160, 
      0,   0, 228, 128,   2,   0, 
      0,   3,   1,   0,   3, 128, 
      1,   0, 228, 176,  11,   0, 
    228, 160,   2,   0,   0,   3, 
      2,   0,   3, 128,   1,   0, 
    228, 176,  12,   0, 228, 160, 
      2,   0,   0,   3,   3,   0, 
      3, 128,   1,   0, 228, 176, 
     13,   0, 228, 160,   2,   0, 
      0,   3,   4,   0,   3, 128, 
      1,   0, 228, 176,  14,   0, 
    228, 160,   2,   0,   0,   3, 
      5,   0,   3, 128,   1,   0, 
    228, 176,  15,   0, 228, 160, 
     66,   0,   0,   3,   1,   0, 
     15, 128,   1,   0, 228, 128, 
      0,   8, 228, 160,  66,   0, 
      0,   3,   2,   0,  15, 128, 
      2,   0, 228, 128,   0,   8, 
    228, 160,  66,   0,   0,   3, 
      3,   0,  15, 128,   3,   0, 
    228, 128,   0,   8, 228, 160, 
     66,   0,   0,   3,   4,   0, 
     15, 128,   4,   0, 228, 128, 
      0,   8, 228, 160,  66,   0, 
      0,   3,   5,   0,  15, 128, 
      5,   0, 228, 128,   0,   8, 
    228, 160,  66,   0,   0,   3, 
      6,   0,  15, 128,   1,   0, 
    228, 176,   0,   8, 228, 160, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   1,   0, 228, 128, 
     11,   0, 170, 160,   0,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,  15, 128,   2,   0, 
    228, 128,  12,   0, 170, 160, 
      0,   0, 228, 128,   4,   0, 
      0,   4,   0,   0,  15, 128, 
      3,   0, 228, 128,  13,   0, 
    170, 160,   0,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   4,   0, 228, 128, 
     14,   0, 170, 160,   0,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,  15, 128,   5,   0, 
    228, 128,  15,   0, 170, 160, 
      0,   0, 228, 128,   6,   0, 
      0,   2,   1,   0,   1, 128, 
     16,   0,   0, 160,   4,   0, 
      0,   4,   0,   0,  15, 128, 
      0,   0, 228, 128,   1,   0, 
      0, 128,  17,   0,   0, 160, 
      6,   0,   0,   2,   1,   0, 
      1, 128,   0,   0, 255, 128, 
      5,   0,   0,   3,   1,   0, 
      7, 128,   0,   0, 228, 128, 
      1,   0,   0, 128,  88,   0, 
      0,   4,   1,   0,   7, 128, 
      0,   0, 255, 129,   0,   0, 
    228, 128,   1,   0, 228, 128, 
      5,   0,   0,   3,   6,   0, 
      7, 128,   6,   0, 255, 128, 
      1,   0, 228, 128,  88,   0, 
      0,   4,   0,   0,  31, 128, 
     18,   0,   0, 161,   0,   0, 
    228, 128,   6,   0, 228, 128, 
      1,   0,   0,   2,   0,   8, 
     15, 128,   0,   0, 228, 128, 
    255, 255,   0,   0,  83,  72, 
     68,  82, 100,   2,   0,   0, 
     64,   0,   0,   0, 153,   0, 
      0,   0,  89,   8,   0,   4, 
     70, 142,  32,   0,   0,   0, 
      0,   0,  19,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   0,   0,   0,   0, 
     85,  85,   0,   0,  98,  16, 
      0,   3,  50,  16,  16,   0, 
      2,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0, 104,   0, 
      0,   2,   3,   0,   0,   0, 
     54,   0,   0,   8, 242,   0, 
     16,   0,   0,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  54,   0,   0,   5, 
     18,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  48,   0, 
      0,   1,  33,   0,   0,   7, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,  16,   0,   0,   0, 
      3,   0,   4,   3,  26,   0, 
     16,   0,   1,   0,   0,   0, 
      0,   0,   0,   9,  98,   0, 
     16,   0,   1,   0,   0,   0, 
      6,  17,  16,   0,   2,   0, 
      0,   0,   6, 129,  32,   4, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     69,   0,   0,   9, 242,   0, 
     16,   0,   2,   0,   0,   0, 
    150,   5,  16,   0,   1,   0, 
      0,   0,  70, 126,  16,   0, 
      0,   0,   0,   0,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     50,   0,   0,  11, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0, 166, 138,  32,   4, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  30,   0,   0,   7, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,   1,   0,   0,   0, 
     22,   0,   0,   1,  14,   0, 
      0,   8, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
      6, 128,  32,   0,   0,   0, 
      0,   0,  16,   0,   0,   0, 
      0,   0,   0,   8, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,   6, 128,  32,   0, 
      0,   0,   0,   0,  17,   0, 
      0,   0,  31,   0,   4,   4, 
     10, 128,  32,   0,   0,   0, 
      0,   0,  18,   0,   0,   0, 
     69,   0,   0,   9, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  16,  16,   0,   2,   0, 
      0,   0,  70, 126,  16,   0, 
      0,   0,   0,   0,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     29,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  14,   0, 
      0,   7, 114,   0,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  55,   0,   0,   9, 
    114,   0,  16,   0,   1,   0, 
      0,   0,   6,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   0,   0, 
      0,   0, 246,  15,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   5, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  21,   0,   0,   1, 
     54,  32,   0,   5, 242,  32, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 116,   0, 
      0,   0,  22,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      6,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  82,  68, 
     69,  70, 160,   1,   0,   0, 
      1,   0,   0,   0, 152,   0, 
      0,   0,   3,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    255, 255,  16,   1,   0,   0, 
    108,   1,   0,   0, 124,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
    135,   0,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      1,   0,   0,   0,  12,   0, 
      0,   0, 142,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 115, 114, 
     99,  83,  97, 109, 112, 108, 
    101, 114,   0, 115, 114,  99, 
     84, 101, 120,   0,  99, 111, 
    110, 115, 116,  97, 110, 116, 
    115,   0, 142,   0,   0,   0, 
      4,   0,   0,   0, 176,   0, 
      0,   0,  48,   1,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  16,   1,   0,   0, 
      0,   0,   0,   0, 252,   0, 
      0,   0,   2,   0,   0,   0, 
     32,   1,   0,   0,   0,   0, 
      0,   0,  48,   1,   0,   0, 
      0,   1,   0,   0,   4,   0, 
      0,   0,   2,   0,   0,   0, 
     56,   1,   0,   0,   0,   0, 
      0,   0,  72,   1,   0,   0, 
     16,   1,   0,   0,   4,   0, 
      0,   0,   2,   0,   0,   0, 
     56,   1,   0,   0,   0,   0, 
      0,   0,  77,   1,   0,   0, 
     32,   1,   0,   0,   4,   0, 
      0,   0,   2,   0,   0,   0, 
     92,   1,   0,   0,   0,   0, 
      0,   0, 111, 102, 102, 115, 
    101, 116,  87, 101, 105, 103, 
    104, 116,   0, 171, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      3,   0,  16,   0,   0,   0, 
      0,   0,   0,   0, 100, 105, 
    118, 105, 115, 111, 114,   0, 
      0,   0,   3,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  98, 105, 
     97, 115,   0, 112, 114, 101, 
    115, 101, 114, 118, 101,  95, 
     97, 108, 112, 104,  97,   0, 
      0,   0,   1,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  57,  46,  50, 
     57,  46,  57,  53,  50,  46, 
     51,  49,  49,  49,   0, 171, 
    171, 171,  73,  83,  71,  78, 
    108,   0,   0,   0,   3,   0, 
      0,   0,   8,   0,   0,   0, 
     80,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,   0,   0,   0, 
     92,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,  15,   0,   0,   0, 
     98,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   3,   3,   0,   0, 
     83,  86,  95,  80,  79,  83, 
     73,  84,  73,  79,  78,   0, 
     67,  79,  76,  79,  82,   0, 
     84,  69,  88,  67,  79,  79, 
     82,  68,   0, 171,  79,  83, 
     71,  78,  44,   0,   0,   0, 
      1,   0,   0,   0,   8,   0, 
      0,   0,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  83,  86,  95,  84, 
     97, 114, 103, 101, 116,   0, 
    171, 171
};
