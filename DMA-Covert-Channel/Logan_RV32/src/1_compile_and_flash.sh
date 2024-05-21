#!/bin/bash
export NUCLEI_SDK_ROOT=/home/cris/Documents/nuclei-sdk
export PATH=$PATH:/home/cris/Nuclei/gcc/bin 
export PATH=$PATH:/home/cris/Nuclei/openocd/bin

# For more SDK cmds -> https://doc.nucleisys.com/nuclei_sdk/develop/buildsystem.html#makefile-targets-of-make-command
make -C ./src SOC=gd32vf103 BOARD=gd32vf103c_longan_nano VARIANT=lite upload

