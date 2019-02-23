#include "dspLib_Math.h"
/* Cordeic angles 
 * --------------
 * Representation in Q29 signed format
 */
static int32_t dspLib_MathCordic_Angles[] = 
{
	CORDIC_ANGLE_ITR1,
	CORDIC_ANGLE_ITR2,
	CORDIC_ANGLE_ITR3,
	CORDIC_ANGLE_ITR4,
	CORDIC_ANGLE_ITR5,
	CORDIC_ANGLE_ITR6,
	CORDIC_ANGLE_ITR7,
	CORDIC_ANGLE_ITR8,
	CORDIC_ANGLE_ITR9,
	CORDIC_ANGLE_ITR10,
	CORDIC_ANGLE_ITR11,
	CORDIC_ANGLE_ITR12,
	CORDIC_ANGLE_ITR13,
	CORDIC_ANGLE_ITR14,
	CORDIC_ANGLE_ITR15,
	CORDIC_ANGLE_ITR16,
	CORDIC_ANGLE_ITR17,
	CORDIC_ANGLE_ITR18,
	CORDIC_ANGLE_ITR19,
	CORDIC_ANGLE_ITR20,
	CORDIC_ANGLE_ITR21,
	CORDIC_ANGLE_ITR22,
	CORDIC_ANGLE_ITR23,
	CORDIC_ANGLE_ITR24,
	CORDIC_ANGLE_ITR25,
};
/* CORDIC algorithm */
void dspLib_Math_Cordic(int32_t x_0, int32_t y_0, int32_t *pX, int32_t *pY, int32_t angle) {
	
	/* x' = x - (y * d * (2^-n))   >> x' = x -/+ (y >> n)
	 * y' = y + (x * d * (2^-n))   >> y' = y +/- (x >> n)
	 * z' = z - (d * atan((2^-n))) >> z' = z -/+ angle[n]
	*/
	int32_t x, y, z;
	uint8_t cnt = 0;
	
	while((angle >= PI_BY_2) || (angle <= -PI_BY_2)) {
		if(angle >= PI_BY_2) {
			x = -y_0;
			y = x_0;
			angle = angle - PI_BY_2;
		}
		else if(angle <= -PI_BY_2) {
			x = y_0;
			y = -x_0;
			angle = angle + PI_BY_2;
		}
		else {
			x = x_0;
			y = y_0;
			break;
		}
		x_0 = x;
		y_0 = y;
	}
	
	x = x_0;
	y = y_0;
	z = angle;
	
	while(cnt < 19) {
		if(z > 0) {
			x = x_0 - (y_0 >> cnt);
			y = y_0 + (x_0 >> cnt);
			z = z - dspLib_MathCordic_Angles[cnt];
		}
		else {
			x = x_0 + (y_0 >> cnt);
			y = y_0 - (x_0 >> cnt);	
			z = z + dspLib_MathCordic_Angles[cnt];
		}
		x_0 = x;
		y_0 = y;
		cnt++;
	}
	
	*pX = x;
	*pY = y;
}
	
int32_t dspLib_Math_Sin(int32_t angle) {
	
	int32_t x,y;
	
	x = CORDIC_GAIN_ITR19;
	y = 0;
	
	dspLib_Math_Cordic(x, y, &x, &y, angle);
	
	return y;
}

int32_t dspLib_Math_Cos(int32_t angle) {
	
	int32_t x,y;
	
	x = CORDIC_GAIN_ITR19;
	y = 0;
	
	dspLib_Math_Cordic(x, y, &x, &y, angle);
	
	return x;
}

void dspLib_Math_ComplexExpPair(int32_t angle, int32_t *pX, int32_t *pY) {
	
	int32_t x,y;
	
	x = CORDIC_GAIN_ITR19;
	y = 0;
	
	dspLib_Math_Cordic(x, y, pX, pY, angle);
}