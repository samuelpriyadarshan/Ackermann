Ackermann Function:
___________________

~ HLS Implementation:
	
	-> Create a project specifying xc7z010clg400-1 board part
	-> Include the source code and TB files named as ACK_DRS2.cpp and ACK_DRS2_TB.cpp
	-> Run C simulation to output the results for the values given in the testbench
	-> Design a custom IP for Ackermann and synthesize, Co-simulate the source code to get the RTL Design (verilog) 
	-> Export RTL which gives the designed IP as a Verilog file

~ Vivado IDE:

	-> Create a new project and specify the board files of Zybo
	-> Import the custom IP into the IP respository of Vivado IDE
	-> Open a new block design and include the custom IP along with the Zynq PS IP
	-> Upon running block and connection automation the IPs are interfaced together
	-> Validate and create a wrapper of the block designed
	-> Generate Bitstream & launch SDK 

~ SDK:

	-> Create a new application project with helloworld template
	-> Run the Ackermann application code (Ackermann_DRS2_SDK.c) on the ARM processor (software implementation) & custom IP peripheral interface code(hardware implementation)
	-> Program the FPGA and then connect to the Serial Monitor with a baud rate of 115200 (TeraTerm, PuTtY, SDK Terimnal)
	-> Run on hardware as a system debugger
	-> Compare and Analyze the performance on hardware and software implementations
