/****************************************************************************
 *
 *   Copyright (C) 2020 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

static constexpr float SAMPLING_RES = 10.0f;
static constexpr float SAMPLING_MIN_LAT	= -60.0f;
static constexpr float SAMPLING_MAX_LAT	= 60.0f;
static constexpr float SAMPLING_MIN_LON	= -180.0f;
static constexpr float SAMPLING_MAX_LON	= 180.0f;

static constexpr int LAT_DIM = 13;
static constexpr int LON_DIM = 37;

static constexpr const int8_t declination_table[LAT_DIM][LON_DIM] {
	{ 47, 46, 45, 43, 42, 41, 39, 37, 33, 29, 23, 16, 10, 4, -1, -6, -10, -15, -20, -27, -34, -42, -49, -56, -62, -67, -72, -74, -75, -73, -61, -22, 26, 42, 47, 48, 47 },
	{ 31, 31, 31, 30, 30, 30, 30, 29, 27, 24, 18, 11, 3, -4, -9, -13, -15, -18, -21, -27, -33, -40, -47, -52, -56, -57, -56, -52, -44, -30, -14, 2, 14, 22, 27, 30, 31 },
	{ 22, 23, 23, 23, 22, 22, 22, 23, 22, 19, 13, 5, -4, -12, -17, -20, -22, -22, -23, -25, -30, -36, -41, -45, -46, -44, -39, -31, -21, -11, -3, 4, 10, 15, 19, 21, 22 },
	{ 17, 17, 17, 18, 17, 17, 17, 17, 16, 13, 8, -1, -10, -18, -22, -25, -26, -25, -22, -20, -21, -25, -29, -32, -31, -28, -23, -16, -9, -3, 0, 4, 7, 11, 14, 16, 17 },
	{ 13, 13, 14, 14, 14, 13, 13, 12, 11, 9, 3, -5, -14, -20, -24, -25, -24, -21, -17, -12, -9, -11, -14, -17, -18, -16, -12, -8, -3, -0, 1, 3, 6, 8, 11, 12, 13 },
	{ 11, 11, 11, 11, 11, 10, 10, 10, 9, 6, -0, -8, -15, -21, -23, -22, -19, -15, -10, -5, -2, -2, -4, -7, -9, -8, -7, -4, -1, 1, 1, 2, 4, 7, 9, 10, 11 },
	{ 10, 9, 9, 9, 9, 9, 9, 8, 7, 3, -3, -10, -16, -20, -20, -18, -14, -9, -5, -2, 1, 2, 0, -2, -4, -4, -3, -2, -0, 0, 0, 1, 3, 5, 7, 9, 10 },
	{ 9, 9, 9, 9, 9, 9, 9, 8, 6, 1, -4, -11, -16, -18, -17, -14, -10, -5, -2, -0, 2, 3, 2, 0, -1, -2, -2, -1, -0, -1, -1, -1, 1, 3, 6, 8, 9 },
	{ 8, 9, 9, 10, 10, 10, 10, 8, 5, 0, -6, -12, -15, -16, -15, -11, -7, -4, -1, 1, 3, 4, 3, 2, 1, 0, -0, -0, -1, -2, -3, -4, -2, 0, 3, 6, 8 },
	{ 7, 9, 10, 11, 12, 12, 12, 9, 5, -1, -7, -13, -15, -15, -13, -10, -6, -3, 0, 2, 3, 4, 4, 4, 3, 2, 1, 0, -1, -3, -5, -6, -6, -3, 0, 4, 7 },
	{ 5, 8, 11, 13, 14, 15, 14, 11, 5, -2, -9, -15, -17, -16, -13, -10, -6, -3, 0, 3, 4, 5, 6, 6, 6, 5, 4, 2, -1, -5, -8, -9, -9, -6, -3, 1, 5 },
	{ 3, 8, 11, 15, 17, 17, 16, 12, 5, -4, -12, -18, -19, -18, -16, -12, -8, -4, -0, 3, 5, 7, 9, 10, 10, 9, 7, 4, -1, -6, -10, -12, -12, -9, -5, -1, 3 },
	{ 3, 8, 12, 16, 19, 20, 18, 13, 4, -8, -18, -24, -25, -23, -20, -16, -11, -6, -1, 3, 7, 11, 14, 16, 17, 17, 14, 8, -0, -8, -13, -15, -14, -11, -7, -2, 3 },
};

// Magnetic inclination data in degrees
static constexpr const int8_t inclination_table[LAT_DIM][LON_DIM] {
	{ -78, -76, -74, -72, -70, -68, -65, -63, -60, -57, -55, -54, -54, -55, -56, -57, -58, -59, -59, -59, -59, -60, -61, -63, -66, -69, -73, -76, -79, -83, -86, -87, -86, -84, -82, -80, -78 },
	{ -72, -70, -68, -66, -64, -62, -60, -57, -54, -51, -49, -48, -49, -51, -55, -58, -60, -61, -61, -61, -60, -60, -61, -63, -66, -69, -72, -76, -78, -80, -81, -80, -79, -77, -76, -74, -72 },
	{ -64, -62, -60, -59, -57, -55, -53, -50, -47, -44, -41, -41, -43, -47, -53, -58, -62, -65, -66, -65, -63, -62, -61, -63, -65, -68, -71, -73, -74, -74, -73, -72, -71, -70, -68, -66, -64 },
	{ -55, -53, -51, -49, -46, -44, -42, -40, -37, -33, -30, -30, -34, -41, -48, -55, -60, -65, -67, -68, -66, -63, -61, -61, -62, -64, -65, -66, -66, -65, -64, -63, -62, -61, -59, -57, -55 },
	{ -42, -40, -37, -35, -33, -30, -28, -25, -22, -18, -15, -16, -22, -31, -40, -48, -55, -59, -62, -63, -61, -58, -55, -53, -53, -54, -55, -55, -54, -53, -51, -51, -50, -49, -47, -45, -42 },
	{ -25, -22, -20, -17, -15, -12, -10, -7, -3, 1, 3, 2, -5, -16, -27, -37, -44, -48, -50, -50, -48, -44, -41, -38, -38, -38, -39, -39, -38, -37, -36, -35, -35, -34, -31, -28, -25 },
	{ -5, -2, 1, 3, 5, 8, 10, 13, 16, 20, 21, 19, 12, 2, -10, -20, -27, -30, -30, -29, -27, -23, -19, -17, -17, -17, -18, -18, -17, -16, -16, -16, -16, -15, -12, -9, -5 },
	{ 15, 18, 21, 22, 24, 26, 29, 31, 34, 36, 37, 34, 28, 20, 10, 2, -3, -5, -5, -4, -2, 2, 5, 7, 8, 7, 7, 6, 7, 7, 7, 6, 5, 6, 8, 11, 15 },
	{ 31, 34, 36, 38, 39, 41, 43, 46, 48, 49, 49, 46, 42, 36, 29, 24, 20, 19, 20, 21, 23, 25, 28, 30, 30, 30, 29, 29, 29, 29, 28, 27, 25, 25, 26, 28, 31 },
	{ 43, 45, 47, 49, 51, 53, 55, 57, 58, 59, 59, 56, 53, 49, 45, 42, 40, 40, 40, 41, 43, 44, 46, 47, 47, 47, 47, 47, 47, 47, 46, 44, 42, 41, 40, 42, 43 },
	{ 53, 54, 56, 57, 59, 61, 64, 66, 67, 68, 67, 65, 62, 60, 57, 55, 55, 54, 55, 56, 57, 58, 59, 59, 60, 60, 60, 60, 60, 60, 59, 57, 55, 53, 52, 52, 53 },
	{ 62, 63, 64, 65, 67, 69, 71, 73, 75, 75, 74, 73, 70, 68, 67, 66, 65, 65, 65, 66, 66, 67, 68, 68, 69, 70, 70, 71, 71, 70, 69, 67, 65, 63, 62, 62, 62 },
	{ 71, 71, 72, 73, 75, 77, 78, 80, 81, 81, 80, 79, 77, 76, 74, 73, 73, 73, 73, 73, 73, 74, 74, 75, 76, 77, 78, 78, 78, 78, 77, 75, 73, 72, 71, 71, 71 },
};

// Magnetic strength data in micro-Tesla or centi-Gauss
static constexpr const int8_t strength_table[LAT_DIM][LON_DIM] {
	{ 62, 60, 58, 56, 54, 52, 49, 46, 43, 41, 38, 36, 34, 32, 31, 31, 30, 30, 30, 31, 33, 35, 38, 42, 46, 51, 55, 59, 62, 64, 66, 67, 67, 66, 65, 64, 62 },
	{ 59, 56, 54, 52, 50, 47, 44, 41, 38, 35, 32, 29, 28, 27, 26, 26, 26, 25, 25, 26, 28, 30, 34, 39, 44, 49, 54, 58, 61, 64, 65, 66, 65, 64, 63, 61, 59 },
	{ 54, 52, 49, 47, 45, 42, 40, 37, 34, 30, 27, 25, 24, 24, 24, 24, 24, 24, 24, 24, 25, 28, 32, 37, 42, 48, 52, 56, 59, 61, 62, 62, 62, 60, 59, 56, 54 },
	{ 49, 47, 44, 42, 40, 37, 35, 33, 30, 28, 25, 23, 22, 23, 23, 24, 25, 25, 26, 26, 26, 28, 31, 36, 41, 46, 51, 54, 56, 57, 57, 57, 56, 55, 53, 51, 49 },
	{ 43, 41, 39, 37, 35, 33, 32, 30, 28, 26, 25, 23, 23, 23, 24, 25, 26, 28, 29, 29, 29, 30, 32, 36, 40, 44, 48, 51, 52, 52, 51, 51, 50, 49, 47, 45, 43 },
	{ 38, 36, 35, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 24, 25, 26, 28, 30, 31, 32, 32, 32, 33, 35, 38, 42, 44, 46, 47, 46, 45, 45, 44, 43, 41, 40, 38 },
	{ 34, 33, 32, 32, 31, 31, 31, 30, 30, 30, 29, 28, 27, 27, 27, 28, 29, 31, 32, 33, 33, 33, 34, 35, 37, 39, 41, 42, 43, 42, 41, 40, 39, 38, 36, 35, 34 },
	{ 33, 33, 32, 32, 33, 33, 34, 34, 35, 35, 34, 33, 32, 31, 30, 30, 31, 32, 33, 34, 35, 35, 36, 37, 38, 40, 41, 42, 42, 41, 40, 39, 37, 36, 34, 33, 33 },
	{ 34, 34, 34, 35, 36, 37, 39, 40, 41, 41, 40, 39, 37, 35, 35, 34, 35, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 45, 45, 43, 41, 39, 37, 35, 34, 34 },
	{ 37, 37, 38, 39, 41, 42, 44, 46, 47, 47, 46, 45, 43, 41, 40, 39, 39, 40, 41, 41, 42, 43, 45, 46, 47, 48, 49, 50, 50, 50, 48, 46, 43, 41, 39, 38, 37 },
	{ 42, 42, 43, 44, 46, 48, 50, 52, 53, 53, 52, 51, 49, 47, 45, 45, 44, 44, 45, 46, 46, 47, 48, 50, 51, 53, 54, 55, 56, 55, 54, 52, 49, 46, 44, 43, 42 },
	{ 48, 48, 49, 50, 52, 53, 55, 56, 57, 57, 56, 55, 53, 51, 50, 49, 48, 48, 48, 49, 49, 50, 51, 53, 55, 56, 58, 59, 60, 60, 58, 56, 54, 52, 50, 49, 48 },
	{ 54, 54, 54, 55, 56, 57, 58, 58, 59, 58, 58, 57, 56, 54, 53, 52, 51, 51, 51, 51, 52, 53, 54, 55, 57, 58, 60, 61, 62, 61, 61, 59, 58, 56, 55, 54, 54 },
};
