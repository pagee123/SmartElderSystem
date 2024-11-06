module uart_demo(
    inout [30:25]exp_io
    
    );
	rx rx(
		.rx_pin(exp_io[26]),

		.tx_pin(exp_io[27])

		);
	
endmodule
