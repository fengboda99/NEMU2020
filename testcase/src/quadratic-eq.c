#include "trap.h"
#include "FLOAT.h"

/* solve 0.5x^2 + 0.5x - 0.5 = 0 */
FLOAT F_mul_F(FLOAT a, FLOAT b) {
	//nemu_assert(0);
	long long ans = 1ll*a*b;
	return ans>>16;
}
int main() {
	//FLOAT a = f2F(0.5);
	//FLOAT b = f2F(3);
	
	//FLOAT c = f2F(-0.5);
	FLOAT d = F_mul_F(3<<16, 3<<16);
	//FLOAT e = f2F(9.0);
	//set_bp();
	nemu_assert(d==(9<<16));
	//FLOAT dt = F_mul_F(b, b) - F_mul_F(F_mul_int(a, 4), c);
	//FLOAT sqrt_dt = sqrt(dt);

	//FLOAT x1 = F_div_F(-b + sqrt_dt, F_mul_int(a, 2));
	//FLOAT x2 = F_div_F(-b - sqrt_dt, F_mul_int(a, 2));

	//FLOAT x1_ans = f2F(0.618);
	//FLOAT x2_ans = f2F(-1.618);

	//nemu_assert(Fabs(x1_ans - x1) < f2F(1e-4));
	//nemu_assert(Fabs(x2_ans - x2) < f2F(1e-4));

	return 0;
}
