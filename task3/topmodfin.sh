#!/bin/sh

# cleanup
rm -rf obj_dir
rm -f *.vcd

# run Verilator to translate Verilog into C++, including C++ testbench
verilator -Wall --cc --trace topmod.sv --exe topmod.cpp

# build C++ project via make automatically generated by Verilator
make -j -C obj_dir/ -f Vtopmod.mk Vtopmod

# run executable simulation file
echo "\nRunning simulation"
obj_dir/Vtopmod
echo "\nSimulation completed"

