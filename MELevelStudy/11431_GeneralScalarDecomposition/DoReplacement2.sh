cat AfterMathematicaStep1 | sed "s/C[0-9][0-9]/X/g" | sed "s/X X/X/g" | sed "s/X X/X/g" | sed "s/g[LR]/X/g" | sed "s/X X/X/g" | sed "s/X X/X/g" | sed "s/E[1-6][1-6][1-6][1-6]/X/g" | sed "s/X X/X/g" | sed "s/X X/X/g" | sed "s/MZ/X/g" | sed "s/X X/X/g" | sed "s/X X/X/g" | sed "s/X^[0-9]/X/g" > AfterCleaning
