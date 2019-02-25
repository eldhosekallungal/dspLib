#ifndef _DSP_LIB_MATH_H_
#define _DSP_LIB_MATH_H_
#include <stdint.h>
/* The mathematical library contains the necessary implementation of different functions
* used for DSP application.*/
/* Polar angles
* ------------
* Polar angles are defined from -pi to pi
* In sampling domain -fs/2 to fs/2
* represented in Q29 signed integer format
*/
#define PI		1686629713
#define PI_BY_2	843314856

/* Cordic algorithm */
/* Cordic angles in radian in Q29 format */
#define CORDIC_ANGLE_ITR1	421657428
#define CORDIC_ANGLE_ITR2	248918914
#define CORDIC_ANGLE_ITR3	131521918
#define CORDIC_ANGLE_ITR4	66762579
#define CORDIC_ANGLE_ITR5	33510843
#define CORDIC_ANGLE_ITR6	16771758
#define CORDIC_ANGLE_ITR7	8387925
#define CORDIC_ANGLE_ITR8	4194219
#define CORDIC_ANGLE_ITR9	2097141
#define CORDIC_ANGLE_ITR10	1048575

#define CORDIC_ANGLE_ITR11	524288
#define CORDIC_ANGLE_ITR12	262144
#define CORDIC_ANGLE_ITR13	131072
#define CORDIC_ANGLE_ITR14	65536
#define CORDIC_ANGLE_ITR15	32768
#define CORDIC_ANGLE_ITR16	16384
#define CORDIC_ANGLE_ITR17	8192
#define CORDIC_ANGLE_ITR18	4096
#define CORDIC_ANGLE_ITR19	2048
#define CORDIC_ANGLE_ITR20	1024
#define CORDIC_ANGLE_ITR21	512
#define CORDIC_ANGLE_ITR22	256
#define CORDIC_ANGLE_ITR23	128
#define CORDIC_ANGLE_ITR24	64
#define CORDIC_ANGLE_ITR25	32
#define CORDIC_ANGLE_ITR26	16
#define CORDIC_ANGLE_ITR27	8
#define CORDIC_ANGLE_ITR28	4
#define CORDIC_ANGLE_ITR29	2
#define CORDIC_ANGLE_ITR30	1
 /* Cordic process gain Q30 signed format */	
#define CORDIC_GAIN_ITR1	759250124
#define CORDIC_GAIN_ITR2	679093956
#define CORDIC_GAIN_ITR3	658817908
#define CORDIC_GAIN_ITR4	653730435
#define CORDIC_GAIN_ITR5	652457347
#define CORDIC_GAIN_ITR6	652138997
#define CORDIC_GAIN_ITR7	652059405
#define CORDIC_GAIN_ITR8	652039506
#define CORDIC_GAIN_ITR9	652034532
#define CORDIC_GAIN_ITR10	652033288
#define CORDIC_GAIN_ITR11	652032977
#define CORDIC_GAIN_ITR12	652032899
#define CORDIC_GAIN_ITR13	652032880
#define CORDIC_GAIN_ITR14	652032875
#define CORDIC_GAIN_ITR15	652032874
#define CORDIC_GAIN_ITR16	652032874
#define CORDIC_GAIN_ITR17	652032874
#define CORDIC_GAIN_ITR18	652032874
#define CORDIC_GAIN_ITR19	652032874
#define CORDIC_GAIN_ITR20	652032874
#define CORDIC_GAIN_ITR21	652032874
#define CORDIC_GAIN_ITR22	652032874
#define CORDIC_GAIN_ITR23	652032874
#define CORDIC_GAIN_ITR24	652032874
#define CORDIC_GAIN_ITR25	652032874
/**
 * function : dspLib_Math_Cordic
 * \brief function will give the new rotated co-ordinates.
 * \param x_0 [in] int32_t : x co-ordinate.
 *		  y_0 [in] int32_t : y co-ordinate.
 *		  pX  [out] int32_t pointer : pointer to rotated x co-ordinate.
 *		  pY  [out] int32_t pointer : pointer to rotated y co-ordinate.
 *		  angle [in] int32_t Q29 format : angle can be either from -PI to PI, represented in signed Q29 format.
 * \return void
*/
void dspLib_Math_Cordic(int32_t x_0, int32_t y_0, int32_t *pX, int32_t *pY, int32_t angle);
/**
 * function : dspLib_Math_Sin
 * \brief function will find the value of sine for the given angle.
 * \param angle [in] int32_t Q29 format: input angle form -PI to PI.
 * \return value of sin(angle) in Q30 format.
*/
int32_t dspLib_Math_Sin(int32_t angle);
/**
 * function : dspLib_Math_Cos
 * \brief function will find the value of cosine for the given angle.
 * \param angle [in] int32_t Q29 format: input angle form -PI to PI.
 * \return value of cos(angle) in Q30 format.
*/
int32_t dspLib_Math_Cos(int32_t angle);

#endif