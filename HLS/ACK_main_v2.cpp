#include <iostream> 
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <math.h>
#include <ap_int.h>
#include <iostream>
#include <ap_axi_sdata.h>

using namespace std;

typedef ap_axis <32,2,5,6> int_side_ch;


unsigned int ack_parameters[2];
unsigned int d1[4];

  
void ack1(hls:: stream<int_side_ch> &inStream , hls:: stream<int_side_ch> &outStream,int gain)
{ 
#pragma HLS INTERFACE axis port=inStream
#pragma HLS INTERFACE axis port=outStream
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=gain bundle=CRTL_BUS

	int_side_ch val_in1;
	int_side_ch val_in2;
	int_side_ch val_out;
	val_in1= inStream.read();
	int x=(int)val_in1.data;
	val_in2= inStream.read();
	int y=(int)val_in2.data;

    //ack_parameters.push(m);
		int d1[4] = { 0,0,0,0 };
		int ack_parameters[2] = { 0,0 };
		int m_parameter = 0;
		int n_parameter = 0;
		int m = 0;
		int n = 0;
		//ack_parameters.push(m);


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
    val_out.data=ack_parameters[1]+1;
    outStream.write(val_out);
}
