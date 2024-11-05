module f1_fsm (
    input   logic       rst,
    input   logic       en,
    input   logic       clk,
    output  logic [7:0] data_out,
);

    typedef enum [7:0] {S0,S1,S2,S3,S4,S5,S6,S7,S8} my_state;
    my_state current_state, next_state;   

    always @(posedge clk, posedge rst) 
        if(rst) current_state <= S0;
        else    current_state <= next_state;

    always_comb 
        case(current_state)
            S0: if(en) next_state = S1;
                else next_state = current_state;
            S1:  if(en)    next_state = S2;
                else      next_state = current_state;
            S2:  if(en)  next_state = S3;
                else      next_state = current_state;
            S3:  if(en)    next_state = S4;
                else      next_state = current_state;
            S4:  if(en)   next_state = S5;
                else      next_state = current_state;
            S5:  if(en)   next_state = S6;
                else      next_state = current_state;
            S6:  if(en)   next_state = S7;
                else      next_state = current_state;
            S7:  if(en)  next_state = S8;
                else      next_state = current_state;
            S8:  if(en)   next_state = S0;
                else      next_state = current_state;
            
            default: next_state = S0;
        endcase
            
    always_comb
        case (current_state)
            S0:    data_out = 8'b0000_0000;
            S1:    data_out = 8'b0000_0001;
            S2:    data_out = 8'b0000_0011;
            S3:    data_out = 8'b0000_0111;
            S4:    data_out = 8'b0000_1111;
            S5:    data_out = 8'b0001_1111;
            S6:    data_out = 8'b0011_1111;
            S7:    data_out = 8'b0111_1111;
            S8:    data_out = 8'b1111_1111;
        endcase

    assign data_out = current_state;

endmodule