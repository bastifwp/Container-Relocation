#!/bin/bash

#Cantidad de ejecuciones en paralelo
ncores=20

seedList="121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140"

parallel -j ${ncores} bash tests.sh {} ::: ${seedList}