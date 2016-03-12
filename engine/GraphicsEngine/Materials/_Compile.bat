fxc -nologo -T vs_2_0 -O0 -Fh -Vn MaterialUnlitVS -Vd MaterialUnlitVS.vhl 1> 1.txt 2> 2.txt
fxc -nologo -T vs_2_0 -O0 -Fh -Vn MaterialDiffuseVS -Vd MaterialDiffuseVS.vhl 1>> 1.txt 2>> 2.txt
fxc -nologo -T vs_2_0 -O0 -Fh -Vn MaterialDiffuseSpecularVS -Vd MaterialDiffuseSpecularVS.vhl 1>> 1.txt 2>> 2.txt

fxc -nologo -T vs_2_0 -O0 -Fh -Vn MaterialRoadVS -Vd MaterialRoadVS.vhl 1>> 1.txt 2>> 2.txt
fxc -nologo -T ps_2_0 -O0 -Fh -Vn MaterialRoadPS -Vd MaterialRoadPS.vhl 1>> 1.txt 2>> 2.txt