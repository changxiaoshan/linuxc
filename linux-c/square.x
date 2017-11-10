struct square_in{
 long args;
};

struct square_out{
 long result;
};

program SQUARE_PROG {
	version SQUARE_VERS {
		square_out SQUAREPROC(square_in) =1;
	} =1;
} = 0x3123000;
