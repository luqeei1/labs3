#include <iostream>
#include <chrono>
#include <thread>
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vf1_fsm.h"

#include "vbuddy.cpp"     // include vbuddy code
#define MAX_SIM_CYC 1000000

int main(int argc, char **argv, char **env) {
  int simcyc;     // simulation clock count
  int tick;       // each clk cycle has two ticks for two edges

  Verilated::commandArgs(argc, argv);
  // init top verilog instance
  Vf1_fsm* top = new Vf1_fsm;
    Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace (tfp, 99);
  tfp->open ("f1_fsm.vcd");

  if (vbdOpen() !=1) return(-1);
  vbdHeader("L3T2: FSM");


  top->clk = 1;
  top->rst = 0;
  top->en = vbdFlag();

  for (simcyc=0; simcyc<MAX_SIM_CYC; simcyc++) {
    // dump variables into VCD file and toggle clock
    for (tick=0; tick<2; tick++) {
      tfp->dump (2*simcyc+tick);
      top->clk = !top->clk;
      top->eval ();
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    vbdBar(top->data_out & 0xFF);

    vbdCycle(simcyc);

    if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
        exit(0);
  }

   vbdClose();     // ++++
  tfp->close(); 
  printf("Exiting\n");
  exit(0);
}
