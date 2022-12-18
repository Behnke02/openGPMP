#! /bin/sh
#                        ___  ______________ _   __
#                        |  \/  |_   _| ___ \ | / /
#   ___  _ __   ___ _ __ | .  . | | | | |_/ / |/ / 
#  / _ \| '_ \ / _ \ '_ \| |\/| | | | |  __/|    \ 
# | (_) | |_) |  __/ | | | |  | | | | | |   | |\  \
#  \___/| .__/ \___|_| |_\_|  |_/ \_/ \_|   \_| \_/
#       | |                                        
#       |_|                                        
#
#
# this script acts as the main "runner" for openMTPK demonstrating its
# functionality by running each modules driver file 

# build + run test drivers in Makefile 
make arith -j4
make calculus -j4
make linalg -j4
make ml_dl -j4
make num-theory -j4

# delete generated binaries
make clean-mods

