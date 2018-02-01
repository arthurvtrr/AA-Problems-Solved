/* atan2 example */
#include <stdio.h>      /* printf */
#include <math.h>       /* atan2 */

#define PI 3.14159265

int main ()
{
  double x, y, result;
  x = -100.0;
  y = -0.001;
  result = atan2 (y,x) * 180 / PI;
  if (result < 0.0) result += 360;
  printf ("The arc tangent for (x=%f, y=%f) is %f degrees\n", x, y, result );
  return 0;
}
