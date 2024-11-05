module topmod #(
    parameter DATA_WIDTH = 8
)(

    input   logic       rst,
    input   logic       en,
    input   logic       clk,
    input   logic [15:0]   n,
    output  logic [7:0] data_out,
    output  logic tick

);

f1_fsm fsm(
    .rst(rst),
    .en(tick),
    .clk(clk),
    .data_out(data_out)
);



clktick clock(
    .clk(clk),
    .rst(rst),
    .en(en),
    .N(n),
    .tick(tick)

);


endmodule
