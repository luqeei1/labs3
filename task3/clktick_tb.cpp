#include "Vclktick.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include "vbuddy.cpp"     // include vbuddy code
#define MAX_SIM_CYC 1000000

int main(int argc, char **argv, char **env) {
  int simcyc;     // simulation clock count
  int tick;       // each clk cycle has two ticks for two edges
  int lights = 0;

  Verilated::commandArgs(argc, argv);
  // init top verilog instance
  Vclktick* top = new Vclktick;
  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace (tfp, 99);
  tfp->open ("clktick.vcd");

  if (vbdOpen() !=1) return(-1);
  vbdHeader("L3T3: FSM");

  vbdSetMode(1);


  top->clk = 1;
  top->rst = 0;
  top->en = 0;
  top->N = vbdValue();

  for (simcyc=0; simcyc<MAX_SIM_CYC; simcyc++) {
    // dump variables into VCD file and toggle clock
    for (tick=0; tick<2; tick++) {
      tfp->dump (2*simcyc+tick);
      top->clk = !top->clk;
      top->eval();
    }

    if(top->tick)
    {

        vbdBar(lights);
        lights = lights ^ 0xFF;
    }

    top->rst = (simcyc < 2);
    top->en = (simcyc > 2);
    top->N = vbdValue();
    vbdCycle(simcyc);


    if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
        exit(0);
  }

  vbdClose();     // ++++
  tfp->close(); 
  exit(0);
}
