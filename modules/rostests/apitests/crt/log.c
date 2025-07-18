/*
 * PROJECT:     ReactOS API tests
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * PURPOSE:     Tests for log
 * COPYRIGHT:   Copyright 2021 Timo Kreuzer <timo.kreuzer@reactos.org>
 */

#if !defined(_CRTBLD) && !defined(_M_IX86)
#define _CRTBLD // we don't want inline log!
#endif
#include "math_helpers.h"

#ifdef _MSC_VER
#pragma function(log)
#endif

#if !defined(_M_IX86)
#define HAS_LOGF
#elif (defined(TEST_UCRTBASE) || defined(TEST_STATIC_CRT))
#define HAS_LIBM_SSE2
#endif


// These are expected to match exactly
static TESTENTRY_DBL s_log_exact_tests[] =
{
    { 0x0000000000000000 /*  0.000000 */, 0xfff0000000000000 /* -1.#INF00 */ },
    { 0x8000000000000000 /* -0.000000 */, 0xfff0000000000000 /* -1.#INF00 */ },
    { 0x7ff0000000000000 /*  1.#INF00 */, 0x7ff0000000000000 /*  1.#INF00 */ },
    { 0x7ff0000000000001 /*  1.#SNAN0 */, 0x7ff8000000000001 /*  1.#QNAN0 */ },
    { 0x7ff7ffffffffffff /*  1.#SNAN0 */, 0x7fffffffffffffff /*  1.#QNAN0 */ },
    { 0x7ff8000000000000 /*  1.#QNAN0 */, 0x7ff8000000000000 /*  1.#QNAN0 */ },
    { 0x7ff8000000000001 /*  1.#QNAN0 */, 0x7ff8000000000001 /*  1.#QNAN0 */ },
    { 0x7fffffffffffffff /*  1.#QNAN0 */, 0x7fffffffffffffff /*  1.#QNAN0 */ },
    { 0xfff0000000000000 /* -1.#INF00 */, 0xfff8000000000000 /* -1.#IND00 */ },
    { 0xfff0000000000001 /* -1.#SNAN0 */, 0xfff8000000000001 /* -1.#QNAN0 */ },
    { 0xfff7ffffffffffff /* -1.#SNAN0 */, 0xffffffffffffffff /* -1.#QNAN0 */ },
    { 0xfff8000000000000 /* -1.#IND00 */, 0xfff8000000000000 /* -1.#IND00 */ },
    { 0xfff8000000000001 /* -1.#QNAN0 */, 0xfff8000000000001 /* -1.#QNAN0 */ },
    { 0xffffffffffffffff /* -1.#QNAN0 */, 0xffffffffffffffff /* -1.#QNAN0 */ },
};

void Test_log_exact(void)
{
    for (int i = 0; i < _countof(s_log_exact_tests); i++)
    {
        double x = u64_to_dbl(s_log_exact_tests[i].x);
        double z = log(x);
        ok_eq_dbl_exact("log", s_log_exact_tests[i].x, z, s_log_exact_tests[i].result);
    }
}

// This table is autogenerated by `python gen_math_tests.py log`
static TESTENTRY_DBL_APPROX s_log_approx_tests[] =
{
//  {    x,                     {    y_rounded,               y_difference           } }
    {                 0x0.0p+0, {                -INFINITY,                 0x0.0p+0 }, 1 }, // log(0.0) == -inf
    {    0x1.0000000000000p-54, {    -0x1.2b708872320e2p+5,    0x1.570da7e077bcbp-50 }, 1 }, // log(5.551115123125783e-17) == -37.429947750237046709
    {    0x1.0000000000000p-53, {    -0x1.25e4f7b2737fap+5,   -0x1.8486612173c69p-51 }, 1 }, // log(1.1102230246251565e-16) == -36.736800569677101399
    {    0x1.8000000000000p-53, {    -0x1.22a69334db8cap+5,    0x1.fe741c2356886p-49 }, 1 }, // log(1.6653345369377348e-16) == -36.331335461568937017
    {    0x1.0000000000000p-52, {    -0x1.205966f2b4f12p+5,   -0x1.6dca0480f5c1ap-49 }, 1 }, // log(2.220446049250313e-16) == -36.04365338911715609
    {    0x1.0000000000000p-52, {    -0x1.205966f2b4f12p+5,   -0x1.6dca0480f5c1ap-49 }, 1 }, // log(2.220446049250313e-16) == -36.04365338911715609
    {     0x1.fae147ae147b4p-3, {    -0x1.6576d89771996p+0,    0x1.6b2367eec359ap-54 }, 1 }, // log(0.24750000000000016) == -1.3963446969733913961
    {     0x1.fae147ae147b0p-2, {    -0x1.6809813f3f940p-1,   -0x1.f4cfae254b1e1p-57 }, 1 }, // log(0.4950000000000001) == -0.70319751641344653528
    {     0x1.7c28f5c28f5c3p-1, {    -0x1.30e0c3b285a37p-2,    0x1.4652be2a791c4p-61 }, 1 }, // log(0.7425) == -0.29773240830528230283
    {     0x1.fae147ae147aep-1, {    -0x1.495453e6fd4bcp-7,    0x1.004bec099ed61p-61 }, 1 }, // log(0.99) == -0.010050335853501450155
    {     0x1.0000000000000p+0, {                 0x0.0p+0,                 0x0.0p+0 }, 1 }, // log(1.0) == 0.0
    {     0x1.9cccccccccccdp+1, {     0x1.2bc243071f713p+0,   -0x1.5d3b2089af16bp-54 }, 1 }, // log(3.225) == 1.1709329502477358396
    {     0x1.5cccccccccccdp+2, {     0x1.b213dd51d8cf7p+0,   -0x1.6e1646938d26bp-54 }, 1 }, // log(5.45) == 1.6956156086751527395
    {     0x1.eb33333333334p+2, {     0x1.04dc25216054cp+1,   -0x1.856feeb2f10a0p-54 }, 1 }, // log(7.675000000000001) == 2.0379682934732609433
    {     0x1.3cccccccccccdp+3, {     0x1.2571c7676e541p+1,   -0x1.f06d5e1d0b8bfp-55 }, 1 }, // log(9.9) == 2.2925347571405442787
    {     0x1.4000000000000p+3, {     0x1.26bb1bbb55516p+1,   -0x1.f48ad494ea3e9p-53 }, 1 }, // log(10.0) == 2.302585092994045684
    {     0x1.03ccccccccccdp+5, {     0x1.bd800f346f905p+1,   -0x1.565ddf57f5d9fp-53 }, 1 }, // log(32.475) == 3.480470562556663279
    {     0x1.b79999999999ap+5, {     0x1.00693edecad2ap+2,   -0x1.7216b04f54ee3p-52 }, 1 }, // log(54.95) == 4.0064236808496304208
    {     0x1.35b3333333334p+6, {     0x1.165b172e2f60bp+2,   -0x1.50fae4c02bed2p-53 }, 1 }, // log(77.42500000000001) == 4.3493097258592666381
    {     0x1.8f9999999999ap+6, {     0x1.26aab75447b9cp+2,   -0x1.1d63f7498e2c0p-53 }, 1 }, // log(99.9) == 4.6041696856545078914
    {     0x1.9000000000000p+6, {     0x1.26bb1bbb55516p+2,   -0x1.f48ad494ea3e9p-52 }, 1 }, // log(100.0) == 4.605170185988091368
    {     0x1.44f999999999ap+8, {     0x1.7228ee7245209p+2,   -0x1.a2f04f5d4ed08p-54 }, 1 }, // log(324.975) == 5.7837482562940828658
    {     0x1.12f999999999ap+9, {     0x1.93d436280608bp+2,   -0x1.295b201acdffap-54 }, 1 }, // log(549.95) == 6.3098273650031257342
    {     0x1.8376666666666p+9, {     0x1.a9c6ec186ec42p+2,   -0x1.b3ae4d4a10ad7p-52 }, 1 }, // log(774.925) == 6.6527662504768741543
    {     0x1.f3f3333333333p+9, {     0x1.ba17062572cd1p+2,    0x1.dcf9ff584ece7p-54 }, 1 }, // log(999.9) == 6.907655273981803671
    {     0x1.f400000000000p+9, {     0x1.ba18a998fffa0p+2,    0x1.112fc120a0a22p-52 }, 1 }, // log(1000.0) == 6.9077552789821370521
    {    0x1.963f333333333p+11, {     0x1.02c3cf5986f16p+3,   -0x1.0146d3dc95d77p-54 }, 1 }, // log(3249.975) == 8.0864025829865048831
    {    0x1.57bf333333333p+12, {     0x1.13998d9ad7ea4p+3,    0x1.17cbe4d7073dbp-51 }, 1 }, // log(5499.95) == 8.61249428027014878
    {    0x1.e45ecccccccccp+12, {     0x1.1e92f3a543639p+3,   -0x1.7aea9895e962dp-51 }, 1 }, // log(7749.924999999999) == 8.9554384448812112218
    {    0x1.387f333333333p+13, {     0x1.26bb06c298e94p+3,   -0x1.a184e48cc9dcep-51 }, 1 }, // log(9999.9) == 9.2103303719261823664
    {    0x1.3880000000000p+13, {     0x1.26bb1bbb55516p+3,   -0x1.f48ad494ea3e9p-51 }, 1 }, // log(10000.0) == 9.2103403719761827361
    {    0x1.fbcfe66666666p+14, {     0x1.4c72a4cd2cbecp+3,   -0x1.b6e191bd86b8ap-51 }, 1 }, // log(32499.975) == 10.38899459908676372
    {    0x1.adafe66666666p+15, {     0x1.5d4865b247654p+3,   -0x1.79fa441590cbcp-53 }, 1 }, // log(54999.95) == 10.915087555123285604
    {    0x1.2ebbeccccccccp+16, {     0x1.6841ccd8180a1p+3,   -0x1.a16a49d872729p-53 }, 1 }, // log(77499.92499999999) == 11.258032247599034467
    {    0x1.869fe66666666p+16, {     0x1.7069e0914ba00p+3,   -0x1.49cb0ada4816cp-54 }, 1 }, // log(99999.9) == 11.512924464969728362
    {    0x1.86a0000000000p+16, {     0x1.7069e2aa2aa5bp+3,   -0x1.c6b626e89338fp-53 }, 1 }, // log(100000.0) == 11.51292546497022842
    {    0x1.3d61fe6666666p+18, {     0x1.96216d2fb028dp+3,   -0x1.4a1b6c37833e3p-54 }, 1 }, // log(324999.975) == 12.691580384388794584
    {    0x1.0c8dfe6666666p+19, {     0x1.a6f72e585ed58p+3,    0x1.238a6451023e9p-59 }, 1 }, // log(549999.95) == 13.217673466299558529
    {    0x1.7a6afd999999ap+19, {     0x1.b1f0959a8653dp+3,    0x1.ee045aad44facp-53 }, 1 }, // log(774999.925) == 13.560618211561285876
    {    0x1.e847fcccccccdp+19, {     0x1.ba18a9635014ap+3,    0x1.f7d919c172239p-53 }, 1 }, // log(999999.9) == 13.815510457964269127
};

void Test_log_approx(void)
{
    for (int i = 0; i < _countof(s_log_approx_tests); i++)
    {
        double x = s_log_approx_tests[i].x;
        double expected = s_log_approx_tests[i].expected.rounded;
        double z = log(x);
        int64_t error = abs(ulp_error_precise(&s_log_approx_tests[i].expected, z));
        ok(error <= s_log_approx_tests[i].max_error,
            "log(%.17e) = %.17e, expected %.17e, error %I64d ULPs, max %u ULPs\n",
            x, z, expected, error, s_log_approx_tests[i].max_error);
    }
}

#if defined(HAS_LOGF)

// These are expected to match exactly
static TESTENTRY_DBL s_logf_exact_tests[] =
{
    { 0x00000000 /*  0.000000 */, 0xff800000 /* -1.#IND00 */ },
    { 0x80000000 /* -0.000000 */, 0xff800000 /* -1.#IND00 */ },
    { 0x7f800000 /*  1.#INF00 */, 0xff800000 /* -1.#IND00 */ },
    { 0x7f800001 /*  1.#SNAN0 */, 0xff800000 /* -1.#IND00 */ },
    { 0x7fBFffff /*  1.#SNAN0 */, 0xff800000 /* -1.#IND00 */ },
    { 0x7fC00000 /*  1.#QNAN0 */, 0xff800000 /* -1.#IND00 */ },
    { 0x7fC80001 /*  1.#QNAN0 */, 0xff800000 /* -1.#IND00 */ },
    { 0x7fFfffff /*  1.#QNAN0 */, 0xff800000 /* -1.#IND00 */ },
    { 0xff800000 /* -1.#INF00 */, 0xff800000 /* -1.#IND00 */ },
    { 0xff800001 /* -1.#SNAN0 */, 0xff800000 /* -1.#IND00 */ },
    { 0xffBfffff /* -1.#SNAN0 */, 0xff800000 /* -1.#IND00 */ },
    { 0xffC00000 /* -1.#IND00 */, 0xff800000 /* -1.#IND00 */ },
    { 0xfff80001 /* -1.#QNAN0 */, 0xff800000 /* -1.#IND00 */ },
    { 0xffffffff /* -1.#QNAN0 */, 0xff800000 /* -1.#IND00 */ },
};

void Test_logf_exact(void)
{
    for (int i = 0; i < _countof(s_logf_exact_tests); i++)
    {
        float x = u64_to_dbl(s_logf_exact_tests[i].x);
        float z = logf(x);
        ok_eq_flt_exact("logf", s_logf_exact_tests[i].x, z, s_logf_exact_tests[i].result);
    }
}

#endif // defined(HAS_LOGF)

#if defined(HAS_LOGF) || defined(HAS_LIBM_SSE2)

static TESTENTRY_DBL_APPROX s_logf_approx_tests[] =
{
//  {    x,                     {    y_rounded,               y_difference           } }
    {                 0x0.0p+0, {                -INFINITY,                 0x0.0p+0 }, 1 }, // logf(0.0) == -inf
    {    0x1.0000000000000p-54, {    -0x1.2b708872320e2p+5,    0x1.570da7e077bcbp-50 }, 1 }, // logf(5.551115123125783e-17) == -37.429947750237046709
    {    0x1.0000000000000p-53, {    -0x1.25e4f7b2737fap+5,   -0x1.8486612173c69p-51 }, 1 }, // logf(1.1102230246251565e-16) == -36.736800569677101399
    {    0x1.8000000000000p-53, {    -0x1.22a69334db8cap+5,    0x1.fe741c2356886p-49 }, 1 }, // logf(1.6653345369377348e-16) == -36.331335461568937017
    {    0x1.0000000000000p-52, {    -0x1.205966f2b4f12p+5,   -0x1.6dca0480f5c1ap-49 }, 1 }, // logf(2.220446049250313e-16) == -36.04365338911715609
    {    0x1.0000000000000p-52, {    -0x1.205966f2b4f12p+5,   -0x1.6dca0480f5c1ap-49 }, 1 }, // logf(2.220446049250313e-16) == -36.04365338911715609
    {     0x1.fae1480000000p-3, {    -0x1.6576d86e11ec5p+0,    0x1.91c3b0fd30d0ap-55 }, 1 }, // logf(0.2475000023841858) == -1.3963446873403182033
    {     0x1.fae1480000000p-2, {    -0x1.680980ec8039ap-1,   -0x1.98575d29032d6p-55 }, 1 }, // logf(0.4950000047683716) == -0.70319750678037289391
    {     0x1.7c28f60000000p-1, {    -0x1.30e0c30d06ee9p-2,    0x1.3456f70f6d4cfp-57 }, 1 }, // logf(0.7425000071525574) == -0.29773239867220851193
    {     0x1.fae1480000000p-1, {    -0x1.49543f3726accp-7,   -0x1.3935a79b95b74p-62 }, 1 }, // logf(0.9900000095367432) == -0.010050326220427584488
    {     0x1.0000000000000p+0, {                 0x0.0p+0,                 0x0.0p+0 }, 1 }, // logf(1.0) == 0.0
    {     0x1.9ccccc0000000p+1, {     0x1.2bc242881d750p+0,    0x1.1d6fb8e6a245fp-56 }, 1 }, // logf(3.2249999046325684) == 1.170932920676438742
    {     0x1.5ccccc0000000p+2, {     0x1.b213dcbb88f4dp+0,   -0x1.dea013e90f530p-59 }, 1 }, // logf(5.449999809265137) == 1.6956155736779294741
    {     0x1.eb33340000000p+2, {     0x1.04dc2556be8f1p+1,   -0x1.3889309954fc2p-54 }, 1 }, // logf(7.675000190734863) == 2.0379683183247085265
    {     0x1.3ccccc0000000p+3, {     0x1.2571c714aef97p+1,    0x1.74e57ea15fc01p-56 }, 1 }, // logf(9.899999618530273) == 2.2925347186082478881
    {     0x1.4000000000000p+3, {     0x1.26bb1bbb55516p+1,   -0x1.f48ad494ea3e9p-53 }, 1 }, // logf(10.0) == 2.302585092994045684
    {     0x1.03cccc0000000p+5, {     0x1.bd800ecf88977p+1,   -0x1.00574318b416bp-53 }, 1 }, // logf(32.474998474121094) == 3.4804705155703986595
    {     0x1.b7999a0000000p+5, {     0x1.00693eedb34bcp+2,   -0x1.e6ce0b58a27a3p-52 }, 1 }, // logf(54.95000076293945) == 4.0064236947338787372
    {     0x1.35b3340000000p+6, {     0x1.165b175881df7p+2,   -0x1.86e3584bdefbfp-52 }, 1 }, // logf(77.42500305175781) == 4.349309765274930067
    {     0x1.8f999a0000000p+6, {     0x1.26aab764ae3a6p+2,   -0x1.5a1bcef3f1fc9p-54 }, 1 }, // logf(99.9000015258789) == 4.6041697009285708435
    {     0x1.9000000000000p+6, {     0x1.26bb1bbb55516p+2,   -0x1.f48ad494ea3e9p-52 }, 1 }, // logf(100.0) == 4.605170185988091368
    {     0x1.44f99a0000000p+8, {     0x1.7228ee866fbeap+2,   -0x1.82c647dd35ef4p-52 }, 1 }, // logf(324.9750061035156) == 5.7837482750755754266
    {     0x1.12f99a0000000p+9, {     0x1.93d4363fdb64fp+2,    0x1.ced38fcf71228p-54 }, 1 }, // logf(549.9500122070312) == 6.3098273871997455524
    {     0x1.8376660000000p+9, {     0x1.a9c6ec0784be3p+2,   -0x1.81f6991b45131p-52 }, 1 }, // logf(774.9249877929688) == 6.6527662347243415858
    {     0x1.f3f3340000000p+9, {     0x1.ba17063faa5bdp+2,   -0x1.c7de7e4907292p-52 }, 1 }, // logf(999.9000244140625) == 6.9076552983983075461
    {     0x1.f400000000000p+9, {     0x1.ba18a998fffa0p+2,    0x1.112fc120a0a22p-52 }, 1 }, // logf(1000.0) == 6.9077552789821370521
    {    0x1.963f340000000p+11, {     0x1.02c3cf69a8c03p+3,    0x1.6bb1cffd7187cp-51 }, 1 }, // logf(3249.97509765625) == 8.0864026130348125235
    {    0x1.57bf340000000p+12, {     0x1.13998dade89aap+3,    0x1.72bccaa5b2944p-52 }, 1 }, // logf(5499.9501953125) == 8.6124943157818346525
    {    0x1.e45ecc0000000p+12, {     0x1.1e92f397bbac0p+3,    0x1.96494797afa2bp-51 }, 1 }, // logf(7749.9248046875) == 8.9554384196793542059
    {    0x1.387f340000000p+13, {     0x1.26bb06d791ac8p+3,   -0x1.6d467014735b7p-51 }, 1 }, // logf(9999.900390625) == 9.2103304109890722687
    {    0x1.3880000000000p+13, {     0x1.26bb1bbb55516p+3,   -0x1.f48ad494ea3e9p-51 }, 1 }, // logf(10000.0) == 9.2103403719761827361
    {    0x1.fbcfe60000000p+14, {     0x1.4c72a4c6b8d55p+3,   -0x1.9e0b13b1785a9p-54 }, 1 }, // logf(32499.974609375) == 10.388994587067523677
    {    0x1.adafe60000000p+15, {     0x1.5d4865aaa722cp+3,    0x1.a30667e00ed9fp-51 }, 1 }, // logf(54999.94921875) == 10.915087540918727188
    {    0x1.2ebbec0000000p+16, {     0x1.6841ccc272240p+3,   -0x1.5a8336cde266cp-51 }, 1 }, // logf(77499.921875) == 11.258032207276414137
    {    0x1.869fe60000000p+16, {     0x1.7069e088e823ap+3,    0x1.b00c7a015b382p-53 }, 1 }, // logf(99999.8984375) == 11.512924449344712673
    {    0x1.86a0000000000p+16, {     0x1.7069e2aa2aa5bp+3,   -0x1.c6b626e89338fp-53 }, 1 }, // logf(100000.0) == 11.51292546497022842
    {    0x1.3d61fe0000000p+18, {     0x1.96216d255d1a3p+3,    0x1.ae8b7c6267831p-51 }, 1 }, // logf(324999.96875) == 12.691580365158023761
    {    0x1.0c8dfe0000000p+19, {     0x1.a6f72e4c2b38ap+3,   -0x1.882333e3ef043p-51 }, 1 }, // logf(549999.9375) == 13.217673443572283562
    {    0x1.7a6afe0000000p+19, {     0x1.b1f095a32f15cp+3,   -0x1.31d7e7cd304bdp-52 }, 1 }, // logf(774999.9375) == 13.560618227690319505
    {    0x1.e847fc0000000p+19, {     0x1.ba18a955e41b4p+3,   -0x1.3c5765dc7b756p-51 }, 1 }, // logf(999999.875) == 13.815510432964266292
};

#endif // defined(HAS_LOGF) || defined(HAS_LIBM_SSE2)

#if defined(HAS_LOGF)

void Test_logf_approx(void)
{
    for (int i = 0; i < _countof(s_logf_approx_tests); i++)
    {
        float x = s_logf_approx_tests[i].x;
        float expected = s_logf_approx_tests[i].expected.rounded;
        float z = logf(x);
        int64_t error = abs(ulp_error_flt(expected, z));
        ok(error <= s_log_approx_tests[i].max_error,
            "log(%.6e) = %.7e, expected %.7e, error %I64d ULPs, max %u ULPs\n",
            x, z, expected, error, s_log_approx_tests[i].max_error);
    }
}

#endif // defined(HAS_LOGF)

#if defined(HAS_LIBM_SSE2)

__ATTRIBUTE_SSE2__ __m128d __libm_sse2_log(__m128d Xmm0);

__ATTRIBUTE_SSE2__
void Test_libm_sse2_log(void)
{
    int i;
    for (i = 0; i < _countof(s_log_approx_tests); i++)
    {
        double x = s_log_approx_tests[i].x;
        double expected = s_log_approx_tests[i].expected.rounded;
        __m128d xmm0 = _mm_set_sd(x);
        __m128d xmm1 = __libm_sse2_log(xmm0);
        double z = _mm_cvtsd_f64(xmm1);
        int64_t error = ulp_error_precise(&s_log_approx_tests[i].expected, z);
        ok(error <= s_log_approx_tests[i].max_error,
            "__libm_sse2_log(%.17e) = %.17e, expected %.17e, error %I64d ULPs, max %u ULPs\n",
            x, z, expected, error, s_log_approx_tests[i].max_error);
    }
}

__ATTRIBUTE_SSE2__ __m128 __libm_sse2_logf(__m128 Xmm0);

__ATTRIBUTE_SSE2__
void Test_libm_sse2_logf(void)
{
    int i;
    for (i = 0; i < _countof(s_logf_approx_tests); i++)
    {
        float x = s_logf_approx_tests[i].x;
        float expected = s_logf_approx_tests[i].expected.rounded;
        __m128 xmm0 = _mm_set_ps1(x);
        __m128 xmm1 = __libm_sse2_logf(xmm0);
        float z = _mm_cvtss_f32(xmm1);
        int64_t error = ulp_error_flt(expected, z);
        ok(error <= s_logf_approx_tests[i].max_error,
            "__libm_sse2_logf(%.6e) = %.7e, expected %.7e, error %I64d ULPs, max %u ULPs\n",
            x, z, expected, error, s_logf_approx_tests[i].max_error);
    }
}

#endif // defined(HAS_LIBM_SSE2)

START_TEST(log)
{
    Test_log_exact();
    Test_log_approx();
#if defined(HAS_LOGF)
    Test_logf_exact();
    Test_logf_approx();
#endif
#if defined(HAS_LIBM_SSE2)
    Test_libm_sse2_log();
    Test_libm_sse2_logf();
#endif
}
