@echo off
:loop
"c:\Program Files (x86)\Graphviz2.38\bin\dot.exe" -T svg -o "PinoutGraphviz.svg" "PinoutGraphviz.gv"
timeout /t 2
goto loop