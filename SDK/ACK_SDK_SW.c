#include <math.h>
#include <stdio.h>
#include "platform.h"
#include <xil_printf.h>
#include <XTime_l.h>



int main(){
  init_platform();
  int x,y,d1[4] = { 0,0,0,0 },ack_parameters[2] = { 0,0 },m_parameter = 0,n_parameter = 0, m = 0, n = 0;
  XTime start,stop;
  printf("Hello World\n");
  x=3;
  y=13;
  printf("The Ackermann parameters are %d and %d \n", x,y);

  XTime_GetTime(&start);

  ack_parameters[0] = x; // ackermann parameter m
  ack_parameters[1] = y; // ackermann parameter n

  n = x - 1; // m-1 of goal

  //while (!ack_parameters.empty()).

	while (d1[0] != 0 || d1[1] != 0 || d1[2] != 0 || d1[3] != 0 || ack_parameters[0] != 0)

	{

		m_parameter = ack_parameters[0]; // gets the value of Ackermann parameter m, x in this scenario
		n_parameter = ack_parameters[1]; // gets the value of Ackermann parameter n, y in this scenario

		if (m_parameter == 0) {

		if (d1[m] == 0 && d1[m - 1] != 0)

		{

		m = m - 1;

		n = x - 1 - m;

		d1[m] = d1[m] - 1;

		ack_parameters[0] = n;

		ack_parameters[1] = n_parameter + 1;

		m = m + 1;

		n = n - 1;

		}

		else if (d1[m] == 0 && d1[m - 1] == 0 && d1[m - 2] == 0)

		{

		m = m - 3;

		n = x - 1 - m;

		d1[m] = d1[m] - 1;

		ack_parameters[0] = n;

		ack_parameters[1] = n_parameter + 1;

		m = m + 1;

		n = n - 1;

		}

		else if (d1[m] == 0 && d1[m - 1] == 0)

		{

		m = m - 2;

		n = x - 1 - m;

		d1[m] = d1[m] - 1;

		ack_parameters[0] = n;

		ack_parameters[1] = n_parameter + 1;

		m = m + 1;

		n = n - 1;

		}







		else

		{

		ack_parameters[1] = ack_parameters[1] + 1;

		ack_parameters[0] = 0;

		d1[m]--;

		}

		}

		//ack_parameters.pop();

		else if (n_parameter == 0 && m_parameter == 1)

		{

		ack_parameters[1] = 1;

		ack_parameters[0] = 0;

		}

		else if (n_parameter == 0) {

		ack_parameters[1] = 1;

		ack_parameters[0] = m_parameter - 1;

		n = n - 1;

		m = m + 1;

		}

		else {







		ack_parameters[0] = m_parameter;

		ack_parameters[1] = n_parameter - 1;

		d1[m]++;



		}



		}


XTime_GetTime(&stop);




printf("Ackermann value: %d\n",ack_parameters[1]+1);

printf("Clock cycles taken = %llu \n",2*(stop-start));
printf("Time taken for the GCD = %.9f s\n",1.0*(stop-start)/(COUNTS_PER_SECOND));
cleanup_platform();
}

